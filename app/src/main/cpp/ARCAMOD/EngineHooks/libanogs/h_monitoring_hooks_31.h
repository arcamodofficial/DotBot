#ifndef ARCAMOD_H_MONITORING_HOOKS_31_H
#define ARCAMOD_H_MONITORING_HOOKS_31_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (100 series)
__int64 (*o_sub_1007E4)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_1011AC)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_100480)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_1004F0)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_1013A8)();
__int64 (*o_sub_100844)();
__int64 (*o_sub_100A40)(_BYTE *a1);
__int64 (*o_sub_100B68)();
__int64 (*o_sub_100DE0)();
__int64 (*o_sub_1010AC)();

// Hook 1: sub_1007E4 - Complex Multi-Parameter String Handler (Offset: 0x1007E4)
static __int64 __fastcall h_sub_1007E4(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("a3: ") << std::hex << a3 << OBF("\n");
    ss << OBF("a4: ") << std::hex << a4 << OBF("\n");
    ss << OBF("a5: ") << std::hex << a5 << OBF("\n");
    ss << OBF("a6: ") << std::hex << a6 << OBF("\n");
    ss << OBF("a7: ") << std::hex << a7 << OBF("\n");
    ss << OBF("a8: ") << std::hex << a8 << OBF("\n");
    ss << OBF("a9: ") << std::hex << a9 << OBF("\n");
    ss << OBF("a10: ") << std::hex << (uintptr_t)a10 << OBF("\n");
    ss << OBF("a11: ") << std::hex << a11 << OBF("\n");
    ss << OBF("a12: ") << std::hex << a12 << OBF("\n");
    ss << OBF("a13: ") << (int)a13 << OBF("\n");
    ss << OBF("Complex Multi-Parameter String Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1007E4] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1007E4(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1007E4] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 2: sub_1011AC - Complex Multi-Parameter String Handler (Offset: 0x1011AC)
static __int64 __fastcall h_sub_1011AC(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("a3: ") << std::hex << a3 << OBF("\n");
    ss << OBF("a4: ") << std::hex << a4 << OBF("\n");
    ss << OBF("a5: ") << std::hex << a5 << OBF("\n");
    ss << OBF("a6: ") << std::hex << a6 << OBF("\n");
    ss << OBF("a7: ") << std::hex << a7 << OBF("\n");
    ss << OBF("a8: ") << std::hex << a8 << OBF("\n");
    ss << OBF("a9: ") << std::hex << a9 << OBF("\n");
    ss << OBF("a10: ") << std::hex << (uintptr_t)a10 << OBF("\n");
    ss << OBF("a11: ") << std::hex << a11 << OBF("\n");
    ss << OBF("a12: ") << std::hex << a12 << OBF("\n");
    ss << OBF("a13: ") << (int)a13 << OBF("\n");
    ss << OBF("Complex Multi-Parameter String Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1011AC] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1011AC(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1011AC] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 3: sub_100480 - Complex Multi-Parameter Handler (Offset: 0x100480)
static __int64 __fastcall h_sub_100480(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, char a13) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("a3: ") << std::hex << a3 << OBF("\n");
    ss << OBF("a4: ") << std::hex << a4 << OBF("\n");
    ss << OBF("a5: ") << std::hex << a5 << OBF("\n");
    ss << OBF("a6: ") << std::hex << a6 << OBF("\n");
    ss << OBF("a7: ") << std::hex << a7 << OBF("\n");
    ss << OBF("a8: ") << std::hex << a8 << OBF("\n");
    ss << OBF("a9: ") << std::hex << a9 << OBF("\n");
    ss << OBF("a10: ") << std::hex << a10 << OBF("\n");
    ss << OBF("a11: ") << std::hex << a11 << OBF("\n");
    ss << OBF("a12: ") << std::hex << a12 << OBF("\n");
    ss << OBF("a13: ") << (int)a13 << OBF("\n");
    ss << OBF("Complex Multi-Parameter Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100480] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100480(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100480] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_1004F0 - Complex Multi-Parameter String Handler (Offset: 0x1004F0)
static __int64 __fastcall h_sub_1004F0(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("a3: ") << std::hex << a3 << OBF("\n");
    ss << OBF("a4: ") << std::hex << a4 << OBF("\n");
    ss << OBF("a5: ") << std::hex << a5 << OBF("\n");
    ss << OBF("a6: ") << std::hex << a6 << OBF("\n");
    ss << OBF("a7: ") << std::hex << a7 << OBF("\n");
    ss << OBF("a8: ") << std::hex << a8 << OBF("\n");
    ss << OBF("a9: ") << std::hex << a9 << OBF("\n");
    ss << OBF("a10: ") << std::hex << (uintptr_t)a10 << OBF("\n");
    ss << OBF("a11: ") << std::hex << a11 << OBF("\n");
    ss << OBF("a12: ") << std::hex << a12 << OBF("\n");
    ss << OBF("a13: ") << (int)a13 << OBF("\n");
    ss << OBF("Complex Multi-Parameter String Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1004F0] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1004F0(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1004F0] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 5: sub_1013A8 - System State Function (Offset: 0x1013A8)
static __int64 __fastcall h_sub_1013A8() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("System State Function: YES\n");
    ss << OBF("No Parameters\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1013A8] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1013A8();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1013A8] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_100844 - System State Function (Offset: 0x100844)
static __int64 __fastcall h_sub_100844() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("System State Function: YES\n");
    ss << OBF("No Parameters\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100844] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100844();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100844] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_100A40 - Byte Processor (Offset: 0x100A40)
static __int64 __fastcall h_sub_100A40(_BYTE *a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("Byte Processor: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100A40] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100A40(a1);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100A40] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_100B68 - System State Function (Offset: 0x100B68)
static __int64 __fastcall h_sub_100B68() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("System State Function: YES\n");
    ss << OBF("No Parameters\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100B68] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100B68();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100B68] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 9: sub_100DE0 - System State Function (Offset: 0x100DE0)
static __int64 __fastcall h_sub_100DE0() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("System State Function: YES\n");
    ss << OBF("No Parameters\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100DE0] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100DE0();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100DE0] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 10: sub_1010AC - System State Function (Offset: 0x1010AC)
static __int64 __fastcall h_sub_1010AC() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        // Akan diisi berdasarkan hasil monitoring
    };

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
    ss << OBF("System State Function: YES\n");
    ss << OBF("No Parameters\n");

    info.string_param = ss.str();

    // Check blocked offsets
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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1010AC] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1010AC();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1010AC] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif
