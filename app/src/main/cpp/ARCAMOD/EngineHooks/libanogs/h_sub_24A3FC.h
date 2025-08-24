#ifndef ARCAMOD_H_SUB_24A3FC_H
#define ARCAMOD_H_SUB_24A3FC_H

#include <stdio.h>
#include <string.h>

static const char* GetLibraryNameFromAddress(uintptr_t address) {
    static char line[512];
    static char path[256];
    FILE* fp = fopen("/proc/self/maps", "r");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            uintptr_t start, end;
            if (sscanf(line, "%lx-%lx %*s %*s %*s %*s %s", &start, &end, path) == 3) {
                if (address >= start && address < end) {
                    char* filename = strrchr(path, '/');
                    fclose(fp);
                    return filename ? filename + 1 : path;
                }
            }
        }
        fclose(fp);
    }
    return "unknown";
}

__int64 __fastcall (*o_sub_24A3FC)(__int64 a1);

static __int64 __fastcall h_sub_24A3FC(__int64 a1) {
    uintptr_t blocked_offsets[] = {
        // 0x219494,
    };

    const bool enable_blocking = false;

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    unsigned __int16 original_value = *(unsigned __int16 *)(a1 + 4);

    bool is_blocked = false;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
            is_blocked = true;
            break;
        }
    }

    if (is_blocked) {
        LOGIO("sub_24A3FC [BLOCKED] | Value: %u (0x%X) | Caller offset: 0x%lx | Param a1: 0x%llx",
              original_value, original_value, offset_call, a1);
    } else {
        LOGIO("sub_24A3FC [MONITOR] | Value: %u (0x%X) | Caller offset: 0x%lx | Param a1: 0x%llx",
              original_value, original_value, offset_call, a1);
    }

    if (enable_blocking && is_blocked) {
        return 0;
    }

    return o_sub_24A3FC ? o_sub_24A3FC(a1) : original_value;
}

void __fastcall (*o_sub_2193E4)(__int64 a1, int a2, __int16 a3);

static void __fastcall h_sub_2193E4(__int64 a1, int a2, __int16 a3) {
    uintptr_t blocked_offsets[] = {
    };

    const bool enable_blocking = false;

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    bool is_blocked = false;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
            is_blocked = true;
            break;
        }
    }

    LOGIO("sub_2193E4 [%s] | Param a1: 0x%llx | Param a2: %d | Param a3: %d | Caller offset: 0x%lx",
          is_blocked ? "BLOCKED" : "MONITOR", a1, a2, a3, offset_call);

    if (enable_blocking && is_blocked) {
        LOGIO("sub_2193E4 [BLOCKED] | Rantai panggilan ke sub_24A3FC diblokir");
        return;
    }

    if (o_sub_2193E4) {
        o_sub_2193E4(a1, a2, a3);
    }
}

void __fastcall (*o_sub_21A0F8)(__int64 a1);

static void __fastcall h_sub_21A0F8(__int64 a1) {
    uintptr_t blocked_offsets[] = {
    };

    const bool enable_blocking = false;

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    bool is_blocked = false;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
            is_blocked = true;
            break;
        }
    }

    int mode = 0;
    if (a1) {
        mode = *(int *)(a1 + 8);
    }

    LOGIO("sub_21A0F8 [%s] | Param a1: 0x%llx | Mode: %d | Caller offset: 0x%lx",
          is_blocked ? "BLOCKED" : "MONITOR", a1, mode, offset_call);

    if (enable_blocking && is_blocked) {
        LOGIO("sub_21A0F8 [BLOCKED] | Rantai panggilan ke sub_2193E4 -> sub_24A3FC diblokir");
        return;
    }

    if (o_sub_21A0F8) {
        o_sub_21A0F8(a1);
    }
}

bool __fastcall (*o_sub_21AB84)();

static bool __fastcall h_sub_21AB84() {
    uintptr_t blocked_offsets[] = {
    };

    const bool enable_blocking = false;

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    bool is_blocked = false;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
            is_blocked = true;
            break;
        }
    }

    LOGIO("sub_21AB84 [%s] | Entry point fungsi pemeriksaan | Caller offset: 0x%lx",
          is_blocked ? "BLOCKED" : "MONITOR", offset_call);

    if (enable_blocking && is_blocked) {
        LOGIO("sub_21AB84 [BLOCKED] | Seluruh rantai eksekusi pemeriksaan diblokir");
        return true;
    }

    uintptr_t dword_5FE888_addr = base_address + 0x5FE888;
    unsigned int num_checks = *(unsigned int*)(dword_5FE888_addr);
    LOGIO("sub_21AB84 [INFO] | Jumlah pemeriksaan thread: %u", num_checks);

    bool result = false;
    if (o_sub_21AB84) {
        result = o_sub_21AB84();
    }

    LOGIO("sub_21AB84 [RESULT] | Hasil eksekusi: %s", result ? "true" : "false");

    return result;
}

void __fastcall (*o_sub_21B078)();

static int log_throttle_counter = 0;

static void __fastcall h_sub_21B078() {
    uintptr_t blocked_offsets[] = {
    };

    const bool enable_blocking = false;

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    const char* library_name = GetLibraryNameFromAddress(pointer_call);

    if (log_throttle_counter % 100 == 0) {
        LOGIO("sub_21B078 [MONITOR] | Infinite loop monitoring thread | Caller address: 0x%lx | From library: %s | Count: %d",
              pointer_call, library_name, log_throttle_counter);

        if (pointer_call == 0x1109360) {
            LOGIO("sub_21B078 [FOUND TARGET] | Alamat target 0x1109360 ditemukan dalam library: %s", library_name);
        }
    }
    log_throttle_counter++;

    bool is_blocked = false;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
            is_blocked = true;
            break;
        }
    }

    if (enable_blocking && is_blocked) {
        LOGIO("sub_21B078 [BLOCKED] | Thread monitoring dimodifikasi");

        sleep(5);

        if (o_sub_21B078) {
            o_sub_21B078();
        }
        return;
    }

    if (o_sub_21B078) {
        o_sub_21B078();
    }
}

#endif //ARCAMOD_H_SUB_24A3FC_H 