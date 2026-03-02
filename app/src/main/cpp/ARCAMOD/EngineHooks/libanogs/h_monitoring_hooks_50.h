#ifndef ARCAMOD_H_MONITORING_HOOKS_50_H
#define ARCAMOD_H_MONITORING_HOOKS_50_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks series 50 (completely unused offsets)
__int64 (*o_sub_1A000C)(int, int, int, int, int, int, int, int, int, void *ptr);
void (*o_sub_1A003C)(_QWORD *a1);
_QWORD *(*o_sub_1A0094)(_QWORD *a1);
_QWORD *(*o_sub_1A0108)(_QWORD *a1);
__int64 (*o_sub_2A04D8)(__int64 a1, __int64 a2, __int64 a3, __int128 *a4);
__int64 (*o_sub_2A0560)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
unsigned (*o_sub_2A05B4)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
unsigned (*o_sub_2A05FC)(_QWORD *a2, int a3, __int64 a4, __int64 a5);
bool (*o_sub_3A00A4)();
bool (*o_sub_3A0214)();

// Hook 1: sub_1A000C - Multi-Parameter System Manager (Offset: 0x1A000C)
static __int64 __fastcall h_sub_1A000C(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, void *ptr) {
    const char *blocked_strings[] = {};
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
    ss << OBF("Parameters:\n");
    ss << OBF("a1-a9: ") << std::dec << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << "," << a9 << OBF("\n");
    ss << OBF("ptr: ") << std::hex << (uintptr_t)ptr << OBF("\n");
    ss << OBF("Multi-Parameter System Manager: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1A000C] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1A000C(a1, a2, a3, a4, a5, a6, a7, a8, a9, ptr);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1A000C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 2: sub_1A003C - QWORD Pointer Handler (Offset: 0x1A003C)
static void __fastcall h_sub_1A003C(_QWORD *a1) {
    const char *blocked_strings[] = {};
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
    ss << OBF("Parameters:\n");
    ss << OBF("a1: ") << std::hex << (uintptr_t)a1 << OBF("\n");
    if (a1) {
        ss << OBF("Value: ") << std::hex << *a1 << OBF("\n");
    }
    ss << OBF("QWORD Pointer Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1A003C] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_1A003C(a1);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1A003C] ===" LOG_COLOR_RESET "\n");
}

// Hook 3: sub_1A0094 - QWORD Result Manager (Offset: 0x1A0094)
static _QWORD *__fastcall h_sub_1A0094(_QWORD *a1) {
    const char *blocked_strings[] = {};
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
    ss << OBF("Parameters:\n");
    ss << OBF("a1: ") << std::hex << (uintptr_t)a1 << OBF("\n");
    if (a1) {
        ss << OBF("Value: ") << std::hex << *a1 << OBF("\n");
    }
    ss << OBF("QWORD Result Manager: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1A0094] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *result = o_sub_1A0094(a1);

    LOGIO("Result: 0x%llx", (uintptr_t)result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1A0094] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_1A0108 - Advanced QWORD Processor (Offset: 0x1A0108)
static _QWORD *__fastcall h_sub_1A0108(_QWORD *a1) {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("Parameters: a1=0x") << std::hex << (uintptr_t)a1 << OBF(", Advanced QWORD Processor\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return nullptr;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_1A0108(a1);
}

// Hook 5: sub_2A04D8 - Quad Parameter Processor (Offset: 0x2A04D8)
static __int64 __fastcall h_sub_2A04D8(__int64 a1, __int64 a2, __int64 a3, __int128 *a4) {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("Quad Parameter Processor: a1-a4\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return 0;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_2A04D8(a1, a2, a3, a4);
}

// Hook 6: sub_2A0560 - System Resource Handler (Offset: 0x2A0560)
static __int64 __fastcall h_sub_2A0560(__int64 a1, __int64 a2, __int64 a3, __int64 a4) {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("System Resource Handler: 4 params\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return 0;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_2A0560(a1, a2, a3, a4);
}

// Hook 7: sub_2A05B4 - Unsigned Parameter Validator (Offset: 0x2A05B4)
static unsigned __fastcall h_sub_2A05B4(__int64 a1, __int64 a2, __int64 a3, __int64 a4) {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("Unsigned Parameter Validator\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return 0;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_2A05B4(a1, a2, a3, a4);
}

// Hook 8: sub_2A05FC - Advanced Unsigned Handler (Offset: 0x2A05FC)
static unsigned __fastcall h_sub_2A05FC(_QWORD *a2, int a3, __int64 a4, __int64 a5) {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("Advanced Unsigned Handler\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return 0;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_2A05FC(a2, a3, a4, a5);
}

// Hook 9: sub_3A00A4 - Boolean System Validator (Offset: 0x3A00A4)
static bool __fastcall h_sub_3A00A4() {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("Boolean System Validator\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return false;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_3A00A4();
}

// Hook 10: sub_3A0214 - Advanced Boolean Controller (Offset: 0x3A0214)
static bool __fastcall h_sub_3A0214() {
    const char *blocked_strings[] = {};
    uintptr_t blocked_offsets[] = {};
    if (base_address == 0) base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;
    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;
    std::stringstream ss;
    ss << OBF("Advanced Boolean Controller\n");
    info.string_param = ss.str();
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
            return false;
        }
    }
    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) monitoring_history.erase(monitoring_history.begin());
    return o_sub_3A0214();
}

#endif //ARCAMOD_H_MONITORING_HOOKS_50_H