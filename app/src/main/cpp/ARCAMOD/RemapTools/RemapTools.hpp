#include <cstdint>
#include <link.h>
#include <sys/mman.h>
#include <vector>
#include <string>

namespace RemapTools {
    struct ProcMapInfo {
        uintptr_t start;
        uintptr_t end;
        uintptr_t offset;
        uint8_t perms;
        ino_t inode;
        char* dev;
        char* path;
    };

    static std::vector<ProcMapInfo> ListModulesWithName(std::string name) PASS_OBF_STRING PASS_OBF {
        std::vector<ProcMapInfo> returnVal;
        char buffer[512];
        FILE *fp = fopen(OBF("/proc/self/maps"), OBF("r"));

        if (fp != nullptr) {
            while (fgets(buffer, sizeof(buffer), fp)) {
                if (strstr(buffer, name.c_str())) {
                    ProcMapInfo info{};
                    char perms[10];
                    char path[255];
                    char dev[25];

                    sscanf(buffer, OBF("%lx-%lx %s %ld %s %ld %s"), &info.start, &info.end, perms, &info.offset, dev, &info.inode, path);

                    if (strchr(perms, OBF('r'))) info.perms |= PROT_READ;
                    if (strchr(perms, OBF('w'))) info.perms |= PROT_WRITE;
                    if (strchr(perms, OBF('x'))) info.perms |= PROT_EXEC;

                    info.dev = dev;
                    info.path = path;

                    returnVal.push_back(info);
                }
            }
            fclose(fp);
        }
        return returnVal;
    }

    static bool RemapLibrary(std::string name) PASS_OBF_STRING PASS_OBF {
        std::vector<ProcMapInfo> maps = ListModulesWithName(name);

        for (ProcMapInfo info : maps) {
            void *address = (void *)info.start;
            size_t size = info.end - info.start;

            void *map = mmap(0, size, PROT_WRITE | PROT_EXEC, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);

            if ((info.perms & PROT_READ) == 0) {
                mprotect(address, size, PROT_READ);
            }

            if (map == nullptr) {
                LOGEO("Failed to Allocate Memory: %s", strerror(errno));
                return false;
            }

            std::memmove(map, address, size);
//                munmap(address, size);
//                memcpy(map, address, size);
            mremap(map, size, size, MREMAP_MAYMOVE | MREMAP_FIXED, info.start);

            mprotect((void *)info.start, size, info.perms);
        }

        return true;
    }
}