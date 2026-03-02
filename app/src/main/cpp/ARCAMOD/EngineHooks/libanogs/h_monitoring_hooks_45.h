#ifndef ARCAMOD_H_MONITORING_HOOKS_45_H
#define ARCAMOD_H_MONITORING_HOOKS_45_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (Series 45)
__int64 (*o_sub_104A18)(int a1, int a2, int a3, int a4, __int64 a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17);
__int64 (*o_sub_106DA8)(__int64 a1, __int64 a2);
unsigned (*o_sub_107E0C)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17);
void (*o_sub_108A38)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17, __int64 a18, __int64 a19, __int64 a20, __int64 a21, __int64 a22, char a23, __int64 a24);
bool (*o_sub_200B8C)(__int64 a1, __int64 a2);
void (*o_sub_200CE4)(__int64 a1, __int64 a2, __int64 a3);
_QWORD *(*o_sub_2006F0)(__int64 a1);
_QWORD *(*o_sub_200728)(__int64 a1);
unsigned (*o_sub_300494)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
bool (*o_sub_300A88)(__int64 a1);

// Hook 1: sub_104A18 - Multi-Parameter Integer Handler (Offset: 0x104A18)
static __int64 __fastcall h_sub_104A18(int a1, int a2, int a3, int a4, __int64 a5, int a6, int a7, int a8, int a9, int a10, int a11, int a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;

    std::stringstream ss;
    ss << OBF("Multi-Parameter Integer Handler\n");
    ss << OBF("a1: ") << a1 << OBF(" a2: ") << a2 << OBF("\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_104A18] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", info.offset);
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_104A18(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17);
    LOGIO("Result: 0x%llx", result);
    return result;
}

// Hook 2: sub_106DA8 - Dual Parameter Handler (Offset: 0x106DA8)
static __int64 __fastcall h_sub_106DA8(__int64 a1, __int64 a2) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_106DA8] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    __int64 result = o_sub_106DA8(a1, a2);
    LOGIO("Result: 0x%llx", result);
    return result;
}

// Hook 3: sub_107E0C - Extended Parameter Processor (Offset: 0x107E0C)
static unsigned __fastcall h_sub_107E0C(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_107E0C] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    unsigned result = o_sub_107E0C(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17);
    LOGIO("Result: %u", result);
    return result;
}

// Hook 4: sub_108A38 - Complex Multi-Parameter Processor (Offset: 0x108A38)
static void __fastcall h_sub_108A38(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17, __int64 a18, __int64 a19, __int64 a20, __int64 a21, __int64 a22, char a23, __int64 a24) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_108A38] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    o_sub_108A38(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17, a18, a19, a20, a21, a22, a23, a24);
}

// Hook 5: sub_200B8C - Bool Validator (Offset: 0x200B8C)
static bool __fastcall h_sub_200B8C(__int64 a1, __int64 a2) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return false;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_200B8C] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    bool result = o_sub_200B8C(a1, a2);
    LOGIO("Result: %s", result ? "true" : "false");
    return result;
}

// Hook 6: sub_200CE4 - Memory Manager (Offset: 0x200CE4)
static void __fastcall h_sub_200CE4(__int64 a1, __int64 a2, __int64 a3) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_200CE4] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    o_sub_200CE4(a1, a2, a3);
}

// Hook 7: sub_2006F0 - QWORD Pointer Manager (Offset: 0x2006F0)
static _QWORD *__fastcall h_sub_2006F0(__int64 a1) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return nullptr;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_2006F0] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    _QWORD *result = o_sub_2006F0(a1);
    LOGIO("Result: 0x%llx", (uintptr_t)result);
    return result;
}

// Hook 8: sub_200728 - QWORD System Handler (Offset: 0x200728)
static _QWORD *__fastcall h_sub_200728(__int64 a1) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return nullptr;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_200728] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    _QWORD *result = o_sub_200728(a1);
    LOGIO("Result: 0x%llx", (uintptr_t)result);
    return result;
}

// Hook 9: sub_300494 - Quad Parameter Unsigned Handler (Offset: 0x300494)
static unsigned __fastcall h_sub_300494(__int64 a1, __int64 a2, __int64 a3, __int64 a4) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_300494] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    unsigned result = o_sub_300494(a1, a2, a3, a4);
    LOGIO("Result: %u", result);
    return result;
}

// Hook 10: sub_300A88 - Advanced Bool Validator (Offset: 0x300A88)
static bool __fastcall h_sub_300A88(__int64 a1) {
    uintptr_t blocked_offsets[] = {};

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset == blocked_offsets[i]) {
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            return false;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL [sub_300A88] ===" LOG_COLOR_RESET);
    LOGIO("Offset: 0x%lx", offset);

    bool result = o_sub_300A88(a1);
    LOGIO("Result: %s", result ? "true" : "false");
    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_45_H