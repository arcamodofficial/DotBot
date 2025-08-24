#ifndef ARCAMOD_H_MONITORING_HOOKS_29_H
#define ARCAMOD_H_MONITORING_HOOKS_29_H

// Function pointers for 10 monitoring hooks (228, 24E, 293, 1C5, 28B series)
void (*o_sub_228048)();
void (*o_sub_228094)(__int64 a1);
__int64 (*o_sub_24E028)();
void (*o_sub_24E0A0)(__int64 a1);
bool (*o_sub_24E210)(__int64 a1, __int64 a2, unsigned __int16 *a3);
__int64 (*o_sub_29300C)(pthread_mutex_t *a1, _DWORD *a2);
__int64 (*o_sub_293710)(void *a1);
_QWORD *(*o_sub_1C5138)(_QWORD *result, __int64 *a2);
__int64 (*o_sub_1C54E8)();
__int64 (*o_sub_28B140)();

// Hook 1: sub_228048 - System Cleanup Handler (Offset: 0x228048)
static void __fastcall h_sub_228048() {
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
    ss << OBF("System Cleanup Handler: YES\n");
    ss << OBF("Return Type: void\n");

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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_228048] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_228048();

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_228048] ===" LOG_COLOR_RESET "\n");
}

// Hook 2: sub_228094 - Component Initializer (Offset: 0x228094)
static void __fastcall h_sub_228094(__int64 a1) {
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
    ss << OBF("Component Initializer: YES\n");

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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_228094] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_228094(a1);

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_228094] ===" LOG_COLOR_RESET "\n");
}

// Hook 3: sub_24E028 - State Getter (Offset: 0x24E028)
static __int64 __fastcall h_sub_24E028() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x24db3c
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
    ss << OBF("State Getter: YES\n");
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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_24E028] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_24E028();

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_24E028] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_24E0A0 - Data Processor (Offset: 0x24E0A0)
static void __fastcall h_sub_24E0A0(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x24db74
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
    ss << OBF("Data Processor: YES\n");

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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_24E0A0] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_24E0A0(a1);

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_24E0A0] ===" LOG_COLOR_RESET "\n");
}

// Hook 5: sub_24E210 - Data Validator (Offset: 0x24E210)
static bool __fastcall h_sub_24E210(__int64 a1, __int64 a2, unsigned __int16 *a3) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x256fc8,
        0x24dd34
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
    ss << OBF("a3: ") << std::hex << (uintptr_t)a3 << OBF("\n");

    if (a3) {
        ss << OBF("Data Validator: YES\n");
        ss << OBF("UINT16 Value: ") << *a3 << OBF("\n");
    }

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
            return false; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_24E210] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_24E210(a1, a2, a3);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_24E210] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_29300C - Mutex Handler (Offset: 0x29300C)
static __int64 __fastcall h_sub_29300C(pthread_mutex_t *a1, _DWORD *a2) {
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
    ss << OBF("a2: ") << std::hex << (uintptr_t)a2 << OBF("\n");

    if (a1) {
        ss << OBF("Mutex Handler: YES\n");
    }
    if (a2) {
        ss << OBF("DWORD Value: ") << *a2 << OBF("\n");
    }

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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_29300C] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_29300C(a1, a2);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_29300C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_293710 - Generic Handler (Offset: 0x293710)
static __int64 __fastcall h_sub_293710(void *a1) {
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
    ss << OBF("Generic Handler: YES\n");

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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_293710] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_293710(a1);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_293710] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_1C5138 - QWORD Pointer Manager (Offset: 0x1C5138)
static _QWORD *__fastcall h_sub_1C5138(_QWORD *result, __int64 *a2) {
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

    if (result) {
        ss << OBF("QWORD Pointer Manager: YES\n");
        ss << OBF("Result Value: ") << std::hex << *result << OBF("\n");
    }
    if (a2) {
        ss << OBF("A2 Value: ") << std::hex << *a2 << OBF("\n");
    }

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
            return nullptr; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1C5138] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *final_result = o_sub_1C5138(result, a2);

    // LOGIO("Result: 0x%llx", (uintptr_t)final_result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1C5138] ===" LOG_COLOR_RESET "\n");

    return final_result;
}

// Hook 9: sub_1C54E8 - State Manager (Offset: 0x1C54E8)
static __int64 __fastcall h_sub_1C54E8() {
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
    ss << OBF("State Manager: YES\n");
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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1C54E8] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1C54E8();

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1C54E8] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 10: sub_28B140 - Memory Manager (Offset: 0x28B140)
static __int64 __fastcall h_sub_28B140() {
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
    ss << OBF("Memory Manager: YES\n");
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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_28B140] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_28B140();

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_28B140] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_29_H