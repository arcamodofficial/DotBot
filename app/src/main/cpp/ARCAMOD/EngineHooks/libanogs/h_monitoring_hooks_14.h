#ifndef ARCAMOD_H_MONITORING_HOOKS_14_H
#define ARCAMOD_H_MONITORING_HOOKS_14_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (1D9, 1C5, 205, 22B, 25E series)
void (*o_sub_1D9040)(__int64 a1, __int64 a2, __int64 a3, _BYTE *a4);
__int64 (*o_sub_1D9098)();
void (*o_sub_1D91B4)(__int64 a1, __int64 a2);
_QWORD *(*o_sub_1C50F4)(_QWORD *result, __int64 *a2);
void (*o_sub_1C5494)();
void (*o_sub_205084)(__int64 a1);
__int64 (*o_sub_205624)(__int64 a1);
__int64 (*o_sub_22B024)();
void (*o_sub_22B0D4)();
__int64 (*o_sub_25E34C)(__int64 a1, __int64 a2, char a3, const void *a4, __int64 a5, __int64 a6);

// Hook 1: sub_1D9040 - Buffer Handler (Offset: 0x1D9040)
static void __fastcall h_sub_1D9040(__int64 a1, __int64 a2, __int64 a3, _BYTE *a4) {
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
    ss << OBF("a4: ") << std::hex << (uintptr_t)a4 << OBF("\n");
    ss << OBF("Buffer Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1D9040] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_1D9040(a1, a2, a3, a4);

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1D9040] ===" LOG_COLOR_RESET "\n");
}

// Hook 2: sub_1D9098 - System Controller (Offset: 0x1D9098)
static __int64 __fastcall h_sub_1D9098() {
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
    ss << OBF("Parameters: None\n");
    ss << OBF("System Controller: YES\n");
    ss << OBF("Return Type: __int64\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0; // Return fake value to avoid detection
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1D9098] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1D9098();

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1D9098] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 3: sub_1D91B4 - Communication Handler (Offset: 0x1D91B4)
static void __fastcall h_sub_1D91B4(__int64 a1, __int64 a2) {
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
    ss << OBF("Communication Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1D91B4] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_1D91B4(a1, a2);

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1D91B4] ===" LOG_COLOR_RESET "\n");
}

// Hook 4: sub_1C50F4 - Pointer Manager (Offset: 0x1C50F4)
static _QWORD *__fastcall h_sub_1C50F4(_QWORD *result, __int64 *a2) {
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
    ss << OBF("result: ") << std::hex << (uintptr_t)result << OBF("\n");
    ss << OBF("a2: ") << std::hex << (uintptr_t)a2 << OBF("\n");
    if (a2) ss << OBF("*a2: ") << std::hex << *a2 << OBF("\n");
    ss << OBF("Pointer Manager: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr; // Return fake value to avoid detection
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1C50F4] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *ret = o_sub_1C50F4(result, a2);

    // LOGIO("Result: 0x%llx", (uintptr_t)ret);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1C50F4] ===" LOG_COLOR_RESET "\n");

    return ret;
}

// Hook 5: sub_1C5494 - Thread Synchronizer (Offset: 0x1C5494)
static void __fastcall h_sub_1C5494() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x11a6c0
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
    ss << OBF("Parameters: None\n");
    ss << OBF("Thread Synchronizer: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1C5494] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_1C5494();

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1C5494] ===" LOG_COLOR_RESET "\n");
}

// Hook 6: sub_205084 - Resource Initializer (Offset: 0x205084)
static void __fastcall h_sub_205084(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x204d00
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
    ss << OBF("Resource Initializer: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_205084] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_205084(a1);

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_205084] ===" LOG_COLOR_RESET "\n");
}

// Hook 7: sub_205624 - Status Checker (Offset: 0x205624)
static __int64 __fastcall h_sub_205624(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x1fd22c
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
    ss << OBF("Status Checker: YES\n");
    ss << OBF("Return Type: __int64\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0; // Return fake value to avoid detection
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_205624] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_205624(a1);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_205624] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_22B024 - Memory Allocator (Offset: 0x22B024)
static __int64 __fastcall h_sub_22B024() {
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
    ss << OBF("Parameters: None\n");
    ss << OBF("Memory Allocator: YES\n");
    ss << OBF("Return Type: __int64\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0; // Return fake value to avoid detection
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_22B024] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_22B024();

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_22B024] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 9: sub_22B0D4 - Allocation Controller (Offset: 0x22B0D4)
static void __fastcall h_sub_22B0D4() {
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
    ss << OBF("Parameters: None\n");
    ss << OBF("Allocation Controller: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_22B0D4] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_22B0D4();

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_22B0D4] ===" LOG_COLOR_RESET "\n");
}

// Hook 10: sub_25E34C - Advanced Crypto Handler (Offset: 0x25E34C)
static __int64 __fastcall h_sub_25E34C(__int64 a1, __int64 a2, char a3, const void *a4, __int64 a5, __int64 a6) {
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
    ss << OBF("a3: ") << std::dec << (int)a3 << OBF("\n");
    ss << OBF("a4: ") << std::hex << (uintptr_t)a4 << OBF("\n");
    ss << OBF("a5: ") << std::hex << a5 << OBF("\n");
    ss << OBF("a6: ") << std::hex << a6 << OBF("\n");
    ss << OBF("Advanced Crypto Handler: YES\n");

    info.string_param = ss.str();

    // Check blocked offsets
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0; // Return fake value to avoid detection
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_25E34C] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_25E34C(a1, a2, a3, a4, a5, a6);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_25E34C] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_14_H
