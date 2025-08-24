#ifndef ARCAMOD_MEMORY_MAP_UTILS_H
#define ARCAMOD_MEMORY_MAP_UTILS_H

#include <cstdio>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

#define PROT_NONE   0
#define PROT_READ   1
#define PROT_WRITE  2
#define PROT_EXEC   4

#define MAP_SHARED    0x01
#define MAP_PRIVATE   0x02
#define MAP_FIXED     0x10
#define MAP_ANONYMOUS 0x20

#define ARCAMOD_EXPORT __attribute__((visibility("default")))
#define ARCAMOD_IMPORT __attribute__((visibility("default")))
#define ARCAMOD_HIDDEN __attribute__((visibility("hidden")))

#ifdef __cplusplus
extern "C" {
#endif

void flush_cache(void *start, void *end);
void clear_cache(void *start, void *end);

#ifdef __cplusplus
}
#endif

#pragma once
#define DoThread(thr) Tools::MakeThread(thr)

uint8_t originalCode[4];
uintptr_t base_address = 0;

static uintptr_t GetLibBase(const char *libName) {
    FILE *fp = fopen(OBF("/proc/self/maps"), "r");
    if (!fp) return 0;

    char line[512];
    uintptr_t base = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (strstr(line, libName)) {
            sscanf(line, OBF("%lx-%*s"), &base);
            break;
        }
    }
    fclose(fp);
    return base;
}

static uintptr_t GetBaseAddress(const char *library_name) {
    uintptr_t base_address = 0;
    char buffer[256];
    FILE *fp = fopen(OBF("/proc/self/maps"), "r");

    if (!fp) {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library_name)) {
            sscanf(buffer, OBF("%lx"), &base_address);
            break;
        }
    }

    fclose(fp);
    return base_address;
}

static void read_proc_maps(const char *library_name) {
    FILE *maps = fopen(OBF("/proc/self/maps"), "r");
    if (!maps) {
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), maps)) {
        if (strstr(line, library_name)) {
        }
    }

    fclose(maps);
}

static void read_proc_maps() {
    FILE *fp = fopen(OBF("/proc/self/maps"), "r");
    if (!fp) {
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
    }

    fclose(fp);
}

static uintptr_t GetBaseAddressFromLibrary(const std::string &library_name) {
    std::ifstream proc_maps(OBF("/proc/self/maps"));
    std::string line;
    uintptr_t base_address = 0;

    while (std::getline(proc_maps, line)) {
        if (line.find(library_name) != std::string::npos) {
            std::istringstream iss(line);
            std::string address_range;
            iss >> address_range;

            std::size_t dash_pos = address_range.find('-');
            if (dash_pos != std::string::npos) {
                std::string start_address_str = address_range.substr(0, dash_pos);
                base_address = std::stoull(start_address_str, nullptr, 16);
            }
            break;
        }
    }

    return base_address;
}

static void DumpMemory(void *addr, size_t size) {
    unsigned char *p = (unsigned char *) addr;
    char line[80];
    int len = 0;

    for (size_t i = 0; i < size; i++) {
        if (i % 16 == 0) {
            if (i > 0) {
//                LOGI("%s", line);
            }
            len = sprintf(line, OBF("%08lx: "), (unsigned long) addr + i);
        }
        len += sprintf(line + len, OBF("%02x "), p[i]);
    }
    if (len > 0) {
//        LOGI("%s", line);
    }
}

static void FindStrings(void *start, size_t size) {
    char *p = (char *) start;
    for (size_t i = 0; i < size; i++) {
        if (isprint(p[i])) {
            size_t len = 0;
            while (i + len < size && isprint(p[i + len])) {
                len++;
            }
            if (len > 4) {
//                LOGI("String at offset 0x%lx: %.*s", i, (int) len, &p[i]);
            }
            i += len;
        }
    }
}

static const char *GetSectionName(const char *library_name, uintptr_t offset) {
    static char section_buffer[64] = {0};

    FILE *fp = fopen(OBF("/proc/self/maps"), "r");
    if (!fp) {
        return nullptr;
    }

    char line[512];
    char name[256];
    uintptr_t start, end;
    uintptr_t absolute_offset = base_address + offset;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, OBF("%lx-%lx %*s %*s %*s %*s %255s"), &start, &end, name) == 3) {
            if (strstr(name, library_name) && absolute_offset >= start && absolute_offset < end) {
                snprintf(section_buffer, sizeof(section_buffer),
                         OBF("%s (0x%lx-0x%lx)"),
                         name, start, end);
                fclose(fp);
                return section_buffer;
            }
        }
    }

    fclose(fp);
    return nullptr;
}

static int backtrace(void **buffer, int size) {
    if (size <= 0 || !buffer)
        return 0;

    register void *frame_pointer asm("x29");
    void *current_fp = frame_pointer;
    int frame_count = 0;

    while (frame_count < size && current_fp) {
        void **fp_as_array = static_cast<void **>(current_fp);

        void *return_address = fp_as_array[1];
        buffer[frame_count++] = return_address;

        current_fp = fp_as_array[0];

        if (reinterpret_cast<uintptr_t>(current_fp) < 0x10000 ||
            reinterpret_cast<uintptr_t>(current_fp) > 0x7FFFFFFFFF) {
            break;
        }
    }

    return frame_count;
}

#define __int8 char
#define __int16 short
#define __int32 int
#define __int64 long long
#define _BYTE unsigned char
#define _WORD unsigned short
#define _DWORD unsigned int
#define _QWORD unsigned long long
#define _OWORD __int128

__int64 (*o_GameEngine_SystemSetting__set_EnableVulkan)(__int64 a1) = nullptr;

#endif //ARCAMOD_MEMORY_MAP_UTILS_H
