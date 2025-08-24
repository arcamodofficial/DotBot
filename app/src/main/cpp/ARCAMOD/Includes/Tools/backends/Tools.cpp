#include "Tools.h"
#include <android/log.h>
#include <libgen.h>
#include <fcntl.h>
#include <cinttypes>
#include <unistd.h>
#include <sys/mman.h>
#include "../../Obfusheader/Obfusheader.hpp"
#include "../../KittyMemory/KittyInclude.hpp"
#include "../../Logger/Includes.h"
#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <dobby.h>
#include <dlfcn.h>
#include <csetjmp>
#include <cstring>
#include <csignal>
#include <utility>
#include <unistd.h>
#include <cctype>

pid_t target_pid = -1;

#define INRANGE(x, a, b)        (x >= a && x <= b)
#define getBits(x)              (INRANGE(x,OBF('0'),'9') ? (x - OBF('0')) : ((x&(~0x20)) - OBF('A') + 0xa))
#define getByte(x)              (getBits(x[0]) << 4 | getBits(x[1]))

#if defined(__arm__)
#define process_vm_readv_syscall 376
#define process_vm_writev_syscall 377
#elif defined(__aarch64__)
#define process_vm_readv_syscall 270
#define process_vm_writev_syscall 271
#elif defined(__i386__)
#define process_vm_readv_syscall 347
#define process_vm_writev_syscall 348
#else
#define process_vm_readv_syscall 310
#define process_vm_writev_syscall 311
#endif

ssize_t process_v(pid_t __pid, const struct iovec *__local_iov, unsigned long __local_iov_count, const struct iovec *__remote_iov, unsigned long __remote_iov_count, unsigned long __flags, bool iswrite) {
    return syscall((iswrite ? process_vm_writev_syscall : process_vm_readv_syscall), __pid, __local_iov, __local_iov_count, __remote_iov, __remote_iov_count, __flags);
}

bool pvm(void *address, void *buffer, size_t size, bool iswrite) {
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = buffer;
    local[0].iov_len = size;
    remote[0].iov_base = address;
    remote[0].iov_len = size;

    if (target_pid == -1) {
        target_pid = getpid();
    }

    ssize_t bytes = process_v(target_pid, local, 1, remote, 1, 0, iswrite);
    return bytes == size;
}

bool Tools::Hook(void *target, void *replace, void **backup) {
    if (!target || target == nullptr) {
        return false;
    }

    return (DobbyHook(target, replace, backup) == 0);
}

bool Tools::HookSym(const char *sym, void *replace, void **backup) {
    void *target = DobbySymbolResolver(NULL, sym);

    if (!target || target == nullptr) {
        return false;
    }

    return (DobbyHook(target, replace, backup) == 0);
}

bool Tools::HookSymLib(const char *lib, const char *sym, void *replace, void **backup) {
    void *target = DobbySymbolResolver(lib, sym);

    if (!target || target == nullptr) {
        return false;
    }

    return (DobbyHook(target, replace, backup) == 0);
}

bool Tools::Patch(const char *lib, const char *offset, const char *replace) {
    uintptr_t patchTarget = CALL(&Tools::GetRealOffsets, lib, offset);

    if (patchTarget == 0) {
        return false;
    }

    MemoryPatch tempPatch = MemoryPatch::createWithHex(patchTarget, replace);

    if (!tempPatch.isValid()) {
        return false;
    }

    __MemoryPatchCache[patchTarget] = tempPatch;

    if (tempPatch.Modify()) {
        return true;
    }

    return false;
}

bool Tools::Restore(const char *lib, const char *offset, const char *replace) {
    uintptr_t patchTarget = Tools::GetRealOffsets(lib, offset);

    if (patchTarget == 0) {
        return false;
    }

    MemoryPatch tmpPatch = __MemoryPatchCache[patchTarget];

    if (!tmpPatch.isValid()) {
        return false;
    }

    if (tmpPatch.Restore()) {
        return true;
    }

    return false;
}

void Tools::RestoreAll() {
    for (auto& [key, value] : __MemoryPatchCache) {
        value.Restore();
    }
}

bool Tools::Read(void *addr, void *buffer, size_t length) {
    return memcpy(buffer, addr, length) != 0;
}

bool Tools::Write(void *addr, void *buffer, size_t length) {
    return memcpy(addr, buffer, length) != 0;
}

bool Tools::ReadAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(buffer, addr, length) != 0;
}

bool Tools::WriteAddr(void *addr, void *buffer, size_t length) {
    unsigned long page_size = sysconf(_SC_PAGESIZE);
    unsigned long size = page_size * sizeof(uintptr_t);
    return mprotect((void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size), (size_t) size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0 && memcpy(addr, buffer, length) != 0;
}

bool Tools::SetWriteable(void *addr) {
    long page_size = sysconf(_SC_PAGESIZE);
    long protect_size = page_size * sizeof(uintptr_t);
    void *p = (void *) ((uintptr_t) addr - ((uintptr_t) addr % page_size) - page_size);
    return mprotect(p, (size_t) protect_size, PROT_EXEC | PROT_READ | PROT_WRITE) == 0;
}

bool Tools::PVM_ReadAddr(void *addr, void *buffer, size_t length) {
    return pvm(addr, buffer, length, false);
}

bool Tools::PVM_WriteAddr(void *addr, void *buffer, size_t length) {
    Tools::SetWriteable(addr);
    return pvm(addr, buffer, length, true);
}

bool Tools::IsAllocated(void *x) {
    static jmp_buf jump;
    static sighandler_t handler = [](int) { longjmp(jump, 1); };
    [[maybe_unused]] char c;
    [[maybe_unused]] int d;
    bool ok = true;
    sighandler_t old_handler = signal(SIGSEGV, handler);
    //if (!setjmp (jump)) c = *(char *) (x); if (x == NULL || c == NULL) else ok = false;
    if (!setjmp(jump)) {
        c = *(char *) (x);
        d = *(int *) (x);

        void *jz = (void *) (x);

        if (jz == NULL) {
            ok = false;
        }
    } else {
        ok = false;
    }
    signal(SIGSEGV, old_handler);
    return ok;
};

template<typename T, typename = std::enable_if<std::is_pointer<T>::value>>
T GCheckObj(T obj) {
    if (obj && Tools::IsAllocated(obj)) return obj;
    return nullptr;
}

bool Tools::IsReadable(void *addr) {
    int nullfd = open(OBF("/dev/random"), (int)(OBF("\1")[0]));

    bool ok = write(nullfd, addr, sizeof(addr)) >= 0;

    close(nullfd);

    uintptr_t p = -1;
    if (addr && pvm(addr, &p, 4, false) && p != -1 && ok) {
        return true;
    }

    return false;
}

bool Tools::IsPtrValid(void *addr) {
    if (!addr || (addr == NULL) || !Tools::IsAllocated(addr) || !Tools::IsReadable(addr) || !GCheckObj(addr)) {
        return false;
    }

    return true;
}

uintptr_t Tools::GetBaseAddress(const char *name) {
    ProcMap libMap = CALL(&Tools::getLibraryMap, name);

    if (!libMap.isValid()) {
        return 0;
    }

    return libMap.startAddress;
}

uintptr_t Tools::GetEndAddress(const char *name) {
    uintptr_t end = 0;
    char line[512];

    FILE *f = fopen(OBF("/proc/self/maps"), OBF("r"));

    if (!f) {
        return 0;
    }

    bool found = false;
    while (fgets(line, sizeof line, f)) {
        uintptr_t tmpEnd;
        char tmpName[256];
        if (sscanf(line, OBF("%*" PRIXPTR "-%" PRIXPTR "%*s %*s %*s %*s %s"), &tmpEnd, tmpName) > 0) {
            if (!strcmp(basename(tmpName), name)) {
                if (!found) {
                    found = true;
                }
            } else {
                if (found) {
                    end = tmpEnd;
                    break;
                }
            }
        }
    }

    fclose(f);
    return end;
}

uintptr_t Tools::FindPattern(const char *lib, const char *pattern) {
    auto start = GetBaseAddress(lib);
    if (!start)
        return 0;
    auto end = GetEndAddress(lib);
    if (!end)
        return 0;
    auto curPat = reinterpret_cast<const unsigned char *>(pattern);
    uintptr_t firstMatch = 0;
    for (uintptr_t pCur = start; pCur < end; ++pCur) {
        if (*(uint8_t *) curPat == (uint8_t) OBF('\?') || *(uint8_t *) pCur == getByte(curPat)) {
            if (!firstMatch) {
                firstMatch = pCur;
            }
            curPat += (*(uint16_t *) curPat == (uint16_t) OBF('\?\?') || *(uint8_t *) curPat != (uint8_t) OBF('\?')) ? 2 : 1;
            if (!*curPat) {
                return firstMatch;
            }
            curPat++;
            if (!*curPat) {
                return firstMatch;
            }
        } else if (firstMatch) {
            pCur = firstMatch;
            curPat = reinterpret_cast<const unsigned char *>(pattern);
            firstMatch = 0;
        }
    }
    return 0;
}

uintptr_t Tools::GetRealOffsets(const char *libraryName, const char *relativeAddr) {
    ProcMap libMap = Tools::getLibraryMap(libraryName);

    if (!libMap.isValid()) {
        return 0;
    }

    uintptr_t libStartAddress = libMap.startAddress;
    int base = 16;

    uintptr_t offsetAddress;
    const char *s = relativeAddr;
    unsigned long long acc;
    int c;
    unsigned long long cutoff;
    int neg = 0, any, cutlim;

    do {
        c = *s++;
    } while (c == OBF(' ') || (c >= OBF('\t') && c <= OBF('\r')));
    if (c == OBF('-')) {
        neg = 1;
        c = *s++;
    } else if (c == OBF('+'))
        c = *s++;
    if ((base == 0 || base == 16) &&
        c == OBF('0') && (*s == OBF('x') || *s == OBF('X'))) {
        c = s[1];
        s += 2;
        base = 16;
    }
    if (base == 0)
        base = c == OBF('0') ? 8 : 10;
    cutoff = (unsigned long long)ULLONG_MAX / (unsigned long long)base;
    cutlim = (unsigned long long)ULLONG_MAX % (unsigned long long)base;
    for (acc = 0, any = 0;; c = *s++) {
        if ((c >= OBF('0') && c <= OBF('9')))
            c -= OBF('0');
        else if ((c >= OBF('A') && c <= OBF('Z')) || (c >= OBF('a') && c <= OBF('z')))
            c -= (c >= OBF('A') && c <= OBF('Z')) ? OBF('A') - 10 : OBF('a') - 10;
        else
            break;
        if (c >= base)
            break;
        if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
            any = -1;
        else {
            any = 1;
            acc *= base;
            acc += c;
        }
    }
    if (any < 0) {
        acc = ULLONG_MAX;
        errno = ERANGE;
    } else if (neg) {
        acc = -acc;
    }

    return (static_cast<uintptr_t>(libStartAddress + acc));
}

uintptr_t Tools::string2Offset(const char *c) {
    int base = 16;

    if (sizeof(uintptr_t) == sizeof(unsigned long)) {
        return strtoul(c, nullptr, base);
    }

    return strtoull(c, nullptr, base);
}

ProcMap Tools::findMapInCache(std::string id) {
    ProcMap ret;
    for(int i = 0; i < __mapsCache.size(); i++){
        if(__mapsCache[i].identifier == id){
            ret = __mapsCache[i].map;
            break;
        }
    }
    return ret;
}

ProcMap Tools::getLibraryMap(const char *libraryName) {
    ProcMap libMap;

    libMap = Tools::findMapInCache(libraryName);

    if (!libMap.isValid()) {
        libMap = KittyMemory::getElfBaseMap(libraryName);

        if (libMap.isValid()) {
            mapsCache cachedMap;
            cachedMap.identifier = libraryName;
            cachedMap.map        = libMap;
            __mapsCache.push_back(cachedMap);
        }
    }

    return libMap;
}

bool Tools::IsLibraryLoaded(const char *name) {
    ProcMap libMap = Tools::getLibraryMap(name);
    return (libMap.isValid());
}

const char *Tools::TempFile(const char *name) {
    std::string file_name(name);
    std::string path_main(OBF("/storage/emulated/0/Android/data/com.activision.callofduty.shooter/cache/Cache/"));

    path_main += file_name;

    return path_main.data();
}


const char *Tools::GetAndroidID(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass(OBF("android/content/Context"));
    jmethodID getContentResolverMethod = env->GetMethodID(contextClass, OBF("getContentResolver"), OBF("()Landroid/content/ContentResolver;"));
    jclass settingSecureClass = env->FindClass(OBF("android/provider/Settings$Secure"));
    jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, OBF("getString"), OBF("(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;"));

    auto obj = env->CallObjectMethod(context, getContentResolverMethod);
    auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(OBF("android_id")));
    return env->GetStringUTFChars(str, 0);
}

const char *Tools::GetDeviceModel(JNIEnv *env) {
    jclass buildClass = env->FindClass(OBF("android/os/Build"));
    jfieldID modelId = env->GetStaticFieldID(buildClass, OBF("MODEL"), OBF("Ljava/lang/String;"));

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *Tools::GetDeviceManufacturer(JNIEnv *env) {
    jclass buildClass = env->FindClass(OBF("android/os/Build"));
    jfieldID modelId = env->GetStaticFieldID(buildClass, OBF("MANUFACTURER"), OBF("Ljava/lang/String;"));

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *Tools::GetDeviceBrand(JNIEnv *env) {
    jclass buildClass = env->FindClass(OBF("android/os/Build"));
    jfieldID modelId = env->GetStaticFieldID(buildClass, OBF("BRAND"), OBF("Ljava/lang/String;"));

    auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
    return env->GetStringUTFChars(str, 0);
}

const char *Tools::GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
    jclass uuidClass = env->FindClass(OBF("java/util/UUID"));

    auto len = strlen(uuid);

    jbyteArray myJByteArray = env->NewByteArray(len);
    env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

    jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, OBF("nameUUIDFromBytes"), OBF("([B)Ljava/util/UUID;"));
    jmethodID toStringMethod = env->GetMethodID(uuidClass, OBF("toString"), OBF("()Ljava/lang/String;"));

    auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
    auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
    return env->GetStringUTFChars(str, 0);
}

std::string Tools::RandomString(const int len) {
    static const char alphanumerics[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    srand((unsigned) time(0) * getpid());

    std::string tmp;
    tmp.reserve(len);
    for (int i = 0; i < len; ++i) {
        tmp += alphanumerics[rand() % (sizeof(alphanumerics) - 1)];
    }
    return tmp;
}

std::string Tools::GetPackageName(JNIEnv *env, jobject context) {
    jclass contextClass = env->FindClass("android/content/Context");
    jmethodID getPackageNameId = env->GetMethodID(contextClass, "getPackageName", "()Ljava/lang/String;");

    auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
    return env->GetStringUTFChars(str, 0);
}

std::string Tools::CalcMD5(std::string s) {
    std::string result;

    unsigned char hash[MD5_DIGEST_LENGTH];
    char tmp[4];

    MD5_CTX md5;
    MD5_Init(&md5);
    MD5_Update(&md5, s.c_str(), s.length());
    MD5_Final(hash, &md5);
    for (unsigned char i : hash) {
        sprintf(tmp, "%02x", i);
        result += tmp;
    }
    return result;
}

std::string Tools::CalcSHA256(std::string s) {
    std::string result;

    unsigned char hash[SHA256_DIGEST_LENGTH];
    char tmp[4];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, s.c_str(), s.length());
    SHA256_Final(hash, &sha256);
    for (unsigned char i : hash) {
        sprintf(tmp, "%02x", i);
        result += tmp;
    }
    return result;
}

jobject Tools::GetContext(JNIEnv *env) {
    jclass activityThread = env->FindClass("android/app/ActivityThread");
    jmethodID currentActivityThread = env->GetStaticMethodID(activityThread, "currentActivityThread", "()Landroid/app/ActivityThread;");
    jobject at = env->CallStaticObjectMethod(activityThread, currentActivityThread);

    jmethodID getApplication = env->GetMethodID(activityThread, "getApplication", "()Landroid/app/Application;");
    jobject context = env->CallObjectMethod(at, getApplication);
    return context;
}

bool Tools::MakeThread(void *(*fun)(void *)) {
    pthread_t thread_id;
    int result = pthread_create(&thread_id, 0, fun, 0);

    return (result == 0);
}

const char *Tools::GetDynamicSO(JNIEnv *env, const char *name) {
    jclass bydzClass = env->FindClass(OBF("com/moba/unityplugin/DynamicSOLoader"));
    jmethodID methodId = env->GetStaticMethodID(bydzClass, OBF("GetDynamicDownloadFolderPath"), OBF("(Ljava/lang/String;)Ljava/lang/String;"));
    jstring arg = env->NewStringUTF(name);
    jstring result = (jstring)env->CallStaticObjectMethod(bydzClass, methodId, arg);

    return env->GetStringUTFChars(result, 0);
}

const char *Tools::GetLibPath(JNIEnv *env, const char *name) {
    jclass bydzClass = env->FindClass(OBF("com/moba/unityplugin/DynamicSOLoader"));
    jmethodID methodId = env->GetStaticMethodID(bydzClass, OBF("GetApplibPath"), OBF("(Ljava/lang/String;)Ljava/lang/String;"));
    jstring arg = env->NewStringUTF(name);
    jstring result = (jstring)env->CallStaticObjectMethod(bydzClass, methodId, arg);

    return env->GetStringUTFChars(result, 0);
}

bool Tools::CopySdcardFile(JNIEnv *env, const char *src, const char *dest) {
    jstring jArg1 = env->NewStringUTF(src);
    jstring jArg2 = env->NewStringUTF(dest);

    // Get the class and method IDs for the CopySdcardFile method
    jclass cls = env->FindClass(OBF("com/moba/unityplugin/DynamicSOLoader"));
    jmethodID methodId = env->GetStaticMethodID(cls, OBF("CopySdcardFile"), OBF("(Ljava/lang/String;Ljava/lang/String;)Z"));

    // Call the CopySdcardFile method and get the result
    jboolean result = env->CallStaticBooleanMethod(cls, methodId, jArg1, jArg2);

    // Clean up the jstring objects
    env->DeleteLocalRef(jArg1);
    env->DeleteLocalRef(jArg2);

    // Return the result as a bool
    return (result == JNI_TRUE);
}

void *Tools::LoadLibraryInSystem(JNIEnv *env, const char *path) {
    jclass systemClass = env->FindClass(OBF("com/moba/unityplugin/DynamicSOLoader"));
    jmethodID loadMethodId = env->GetStaticMethodID(systemClass, OBF("LoadSO"), OBF("(Ljava/lang/String;)V"));
    jstring libPath = env->NewStringUTF(path);
    env->CallStaticVoidMethod(systemClass, loadMethodId, libPath);
    return nullptr;
}

void *Tools::DeleteAndBlurOurLib(JNIEnv *env) {
    jclass bydzClass = env->FindClass(OBF("com/bydzns/MainActivity"));
    jmethodID deleteMethodId = env->GetStaticMethodID(bydzClass, OBF("DeleteAndBlurOurLib"), OBF("()V"));
    env->CallStaticVoidMethod(bydzClass, deleteMethodId);
    return nullptr;
}

void Tools::LoadSO(JavaVM *ejvm, const char* arg1) {
    JNIEnv *env;
    ejvm->AttachCurrentThread(&env, NULL);

    jclass dynamicSOLoaderClass = env->FindClass(OBF("com/moba/unityplugin/DynamicSOLoader"));
    jfieldID activityFieldID = env->GetStaticFieldID(dynamicSOLoaderClass, OBF("mCurrentActivity"), OBF("Landroid/app/Activity;"));
    jobject activityObj = env->GetStaticObjectField(dynamicSOLoaderClass, activityFieldID);

    jstring jArg1 = env->NewStringUTF(arg1);

    // Get the class and method IDs for the LoadSO method
    jclass jCls = env->FindClass(OBF("com/moba/unityplugin/DynamicSOLoader"));

    jmethodID methodId = env->GetStaticMethodID(jCls, OBF("LoadSO"), OBF("(Ljava/lang/String;Landroid/app/Activity;)V"));

    // Call the LoadSO method
    env->CallStaticVoidMethod(jCls, methodId, jArg1, activityObj);
}

bool Tools::IsRecording(JavaVM *ejvm) {
    JNIEnv *env;
    ejvm->AttachCurrentThread(&env, NULL);

    jclass mediaProjectionManagerClass = env->FindClass("android/media/projection/MediaProjectionManager");
    jmethodID getSystemServiceMethod = env->GetStaticMethodID(mediaProjectionManagerClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");
    jobject mediaProjectionManagerObject = env->CallStaticObjectMethod(mediaProjectionManagerClass, getSystemServiceMethod, env->NewStringUTF("media_projection"));

    jmethodID isProjectionActiveMethod = env->GetMethodID(mediaProjectionManagerClass, "isProjectionActive", "()Z");
    jboolean isProjectionActive = env->CallBooleanMethod(mediaProjectionManagerObject, isProjectionActiveMethod);

    ejvm->DetachCurrentThread();

    return isProjectionActive;
}

std::string Tools::Il2CppToString(const UTF16* source, size_t len) {
    std::string output;
/*
    for (int i = 0; i < len; i++) {
        wchar_t ss = static_cast<wchar_t>(source[i]);

        char cch;

        if (ss < 128) {
            cch = static_cast<char>(ss);
        } else {
            cch = static_cast<char>(ss & 0xFF);
        }

        output += cch;
    }
*/

    std::stringstream name_stringstream;

    for (std::size_t i = 0; i < len; ++i) {
        name_stringstream << static_cast<char>(source[i]);
    }

    output = name_stringstream.str();

    return output;
}

std::vector<wchar_t> Tools::Il2CppToWchar(const UTF16 *source, size_t len) {
    std::vector<wchar_t> wideText;
    wideText.reserve(len);

    for (std::size_t i = 0; i < len; i++) {
        wideText.push_back(static_cast<wchar_t>(source[i]));
    }

    return wideText;
}

bool Tools::PatchAddress(uintptr_t addr, std::string edit) {
    MemoryPatch patchAdd = MemoryPatch::createWithHex(addr, edit);

    if (patchAdd.Modify()) {
        return true;
    }

    return false;
}

bool HookInDobby(void *target, void *replace, void **backup) {
    return Tools::Hook(target, replace, backup);
}

void * ResolverInDobby(const char *lib, const char *sym) {
    void *target = DobbySymbolResolver(lib, sym);

    if (!target || target == nullptr) {
        return NULL;
    }

    return (target);
}