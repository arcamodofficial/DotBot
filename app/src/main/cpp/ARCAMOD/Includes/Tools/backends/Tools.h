#pragma once

#include <map>
#include <jni.h>
#include <type_traits>
#include <cstdio>
#include <openssl/md5.h>
#include <string>
#include <unistd.h>
#include <fstream>
#include <sys/mman.h>
#include <vector>
#include <codecvt>
#include <cstdlib>
#include "../../KittyMemory/KittyInclude.hpp"
#include "../../Obfusheader/Obfusheader.hpp"

struct mapsCache {
    std::string identifier;
    ProcMap map;
};

static std::vector<mapsCache> __mapsCache;

static std::map<uintptr_t, MemoryPatch> __MemoryPatchCache;
typedef unsigned short UTF16;
typedef wchar_t UTF32;
typedef char UTF8;


namespace Tools {
	bool Hook(void *target, void *replace, void **backup);
    bool HookSym(const char *sym, void *replace, void **backup);
    bool HookSymLib(const char *lib, const char *sym, void *replace, void **backup);
	bool Patch(const char *lib, const char *offset, const char *replace);
    bool Restore(const char *lib, const char *offset, const char *replace);
    void RestoreAll();
	bool Read(void *addr, void *buffer, size_t length);
	bool Write(void *addr, void *buffer, size_t length);
	bool ReadAddr(void *addr, void *buffer, size_t length);
	bool WriteAddr(void *addr, void *buffer, size_t length);
	bool SetWriteable(void *addr);
	bool PVM_ReadAddr(void *addr, void *buffer, size_t length);
	bool PVM_WriteAddr(void *addr, void *buffer, size_t length);
    bool IsAllocated(void *addr);
    bool IsReadable(void *addr);
	bool IsPtrValid(void *addr);
	
	uintptr_t GetBaseAddress(const char *name);
	uintptr_t GetEndAddress(const char *name);
	uintptr_t FindPattern(const char *lib, const char* pattern);
    uintptr_t GetRealOffsets(const char *libraryName, const char *relativeAddr);
    
    uintptr_t string2Offset(const char *c);
    
    ProcMap findMapInCache(std::string id);
    
    ProcMap getLibraryMap(const char *libraryName);
    
    bool IsLibraryLoaded(const char *name);
    
    const char *TempFile(const char *name);
	
	const char *GetAndroidID(JNIEnv *env, jobject context);
	const char *GetDeviceModel(JNIEnv *env);
    const char *GetDeviceManufacturer(JNIEnv *env);
	const char *GetDeviceBrand(JNIEnv *env);
	const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid);
	std::string RandomString(const int len);
    std::string GetPackageName(JNIEnv *env, jobject context);

    std::string CalcMD5(std::string s);
    std::string CalcSHA256(std::string s);
    jobject GetContext(JNIEnv *env);
    const char *GetDynamicSO(JNIEnv *env, const char *name);
    const char *GetLibPath(JNIEnv *env, const char *name);
    bool CopySdcardFile(JNIEnv *env, const char *src, const char *dest);
    void *LoadLibraryInSystem(JNIEnv *env, const char *path);
    void *DeleteAndBlurOurLib(JNIEnv *env);
    void LoadSO(JavaVM *ejvm, const char* arg1);
    bool MakeThread(void *(*fun)(void *));
    bool IsRecording(JavaVM *ejvm);

	std::string Il2CppToString(const UTF16* source, size_t len);
    std::vector<wchar_t> Il2CppToWchar(const UTF16* source, size_t len);

    bool PatchAddress(uintptr_t addr, std::string edit);
}

bool HookInDobby(void *target, void *replace, void **backup);
void * ResolverInDobby(const char *lib, const char *sym);

inline uintptr_t RealGetOffsets(const char *libraryName, const char *relativeAddr) __attribute((__annotate__("indibr"))) {
    ProcMap libMap = CALL(&Tools::getLibraryMap, libraryName);

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

inline bool HidePatch(uintptr_t patchTarget, const char *replace) __attribute((__annotate__("indibr"))) {
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

inline std::string getFileMD5(const std::string &filename) __attribute((__annotate__("indibr"))) __attribute((__annotate__("strenc"))) {
    // Open the file as a binary stream
    std::ifstream file(filename);
    if (!file.is_open()) {

//        std::cerr << "Failed to open file: " << filename << std::endl;
        return OBF("null");
    }

    // Create MD5 context
    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    // Read the file in chunks and update the MD5 context
    const std::size_t bufferSize = 1024 * 16; // 16KB buffer
    std::vector<char> buffer(bufferSize);
    while (file.good()) {
        file.read(buffer.data(), buffer.size());
        MD5_Update(&md5Context, buffer.data(), file.gcount());
    }

    // Finalize the MD5 hash
    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    MD5_Final(md5Digest, &md5Context);

    // Convert the hash to a hexadecimal string
    std::ostringstream md5String;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        md5String << std::hex << std::setw(2) << std::setfill('0') << (int)md5Digest[i];
    }

    return md5String.str();
}

#define HOOK(ptr, rep, bak) (CALL(&DobbyHook, (void *) (ptr), (void *) rep, (void **) &bak) == 0)
#define HOOK2(name, offset, rep, bak) (CALL(&DobbyHook, (void *) (RealGetOffsets(OBF(name), OBF(offset))), (void *) rep, (void **) &bak) == 0) //Tools::Hook((void *) (Tools::GetRealOffsets(OBF(name), OBF(offset))), (void *) rep, (void **) &bak)
#define HOOK_NO_ORIG(name, offset, rep) (CALL(&DobbyHook, (void *) (RealGetOffsets(OBF(name), OBF(offset))), (void *) rep, (void **) (NULL)) == 0) //Tools::Hook((void *) (Tools::GetRealOffsets(OBF(name), OBF(offset))), (void *) rep, (void **) (NULL)
#define HOOK_BATCH(name, offset1, rep1, bak1, offset2, rep2, bak2) \
    (HOOK2(name, offset1, rep1, bak1) && HOOK2(name, offset2, rep2, bak2))
#define HOOK_NO_ORIG2(ptr, rep) HookInDobby((void *) (ptr), (void *) rep, (void **) (NULL)) //Tools::Hook((void *) (Tools::GetRealOffsets(OBF(name), OBF(offset))), (void *) rep, (void **) (NULL)
#define HOOKSYM(sym, rep, bak) Tools::HookSym(OBF(sym), (void *) rep, (void **) &bak)
#define HOOKSYM_LIB(lib, sym, rep, bak) (CALL(&DobbyHook, (void *) (CALL(&DobbySymbolResolver, OBF(lib), OBF(sym))), (void *) rep, (void **) &bak) == 0) //HookInDobby(ResolverInDobby(OBF(lib), OBF(sym)), (void *) rep, (void **) &bak)
#define IsLoaded(lib) CALL(&Tools::IsLibraryLoaded, OBF(lib))
#define IsValid(ptr) ((void *) (ptr)) //CALL(&Tools::IsPtrValid, (void *) (ptr))
#define PATCH(lib, addr, edit) (CALL(&HidePatch, CALL(&RealGetOffsets, OBF(lib), OBF(addr)), OBF(edit)) == true)
#define PATCH_ADDR(addr, edit) Tools::PatchAddress((uintptr_t) (addr), OBF(edit))

// While-based macros (descriptive and clear)
#define WhileHook(call) do {} while (!(call))
#define WhilePatch(call) do {} while (!(call))
#define ENSURE_SUCCESS(call) do {} while (!(call))
// Modifikasi macro HOOK2 di Tools.h
#define HOOK2(name, offset, rep, bak) (CALL(&DobbyHook, (void *) (RealGetOffsets(name, offset)), (void *) rep, (void **) &bak) == 0)
#define RGBA(r, g, b, a) new float[]{ \
    static_cast<float>(r) / 255.0f, \
    static_cast<float>(g) / 255.0f, \
    static_cast<float>(b) / 255.0f, \
    static_cast<float>(a) / 255.0f \
}

template <typename T>
T CastPointer(uintptr_t address) {
    return *reinterpret_cast<T *>(address);
}

template <typename T>
T CastFunction(uintptr_t address) {
    return reinterpret_cast<T>(address);
}
/*
const wchar_t* utf16_to_utf32(const UTF16* source, size_t len) {
	auto output = new UTF32[len + 1];

	for (int i = 0; i < len; i++) {
		const UTF16 uc = source[i];
		if (!is_surrogate(uc)) {
			output[i] = uc;
		}
		else {
			if (is_high_surrogate(uc) && is_low_surrogate(source[i]))
				output[i] = surrogate_to_utf32(uc, source[i]);
			else
				output[i] = L'?';
		}
	}

	output[len] = L'\0';
	return output;
}*/