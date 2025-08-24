#ifndef ARCAMOD_H_MONITORING_HOOKS_18_H
#define ARCAMOD_H_MONITORING_HOOKS_18_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (1xxxx and 2xxxx series)
__int64 (*o_sub_100098)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12);
__int64 (*o_sub_1000F8)();
__int64 (*o_sub_100550)();
__int64 (*o_sub_101054)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12);
__int64 (*o_sub_1019D0)(__int64 a1);
void (*o_sub_200A88)();
__int64 (*o_sub_204B68)();
bool (*o_sub_24ED48)(pthread_mutex_t *a1);
__int64 (*o_sub_284980)(__int64 a1);
void (*o_sub_295D00)(__int64 a1, __int64 a2, __int64 a3);

// Hook 1: sub_100098 - Complex Multi-Parameter Handler (Offset: 0x100098)
static __int64 __fastcall h_sub_100098(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12) {
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
    ss << OBF("a9: ") << std::hex << (uintptr_t)a9 << OBF("\n");
    ss << OBF("a10: ") << std::hex << a10 << OBF("\n");
    ss << OBF("a11: ") << std::hex << a11 << OBF("\n");
    ss << OBF("a12: ") << (int)a12 << OBF("\n");
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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100098] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100098(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100098] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 2: sub_1000F8 - System State Function (Offset: 0x1000F8)
static __int64 __fastcall h_sub_1000F8() {
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
    ss << OBF("System State Function: YES\n");

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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1000F8] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1000F8();

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1000F8] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 3: sub_100550 - System State Function (Offset: 0x100550)
static __int64 __fastcall h_sub_100550() {
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
    ss << OBF("System State Function: YES\n");

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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100550] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100550();

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100550] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 4: sub_101054 - Complex Multi-Parameter Handler (Offset: 0x101054)
static __int64 __fastcall h_sub_101054(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12) {
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
    ss << OBF("a9: ") << std::hex << (uintptr_t)a9 << OBF("\n");
    ss << OBF("a10: ") << std::hex << a10 << OBF("\n");
    ss << OBF("a11: ") << std::hex << a11 << OBF("\n");
    ss << OBF("a12: ") << (int)a12 << OBF("\n");
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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_101054] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_101054(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_101054] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 5: sub_1019D0 - Single Parameter Handler (Offset: 0x1019D0)
static __int64 __fastcall h_sub_1019D0(__int64 a1) {
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
    ss << OBF("Single Parameter Handler: YES\n");

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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1019D0] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1019D0(a1);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1019D0] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 6: sub_200A88 - System Function (Offset: 0x200A88)
static void __fastcall h_sub_200A88() {
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
    ss << OBF("System Function: YES\n");

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
            return; // Block execution
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200A88] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_200A88();

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200A88] ===" LOG_COLOR_RESET "\n");
}

// Hook 7: sub_204B68 - System State Getter (Offset: 0x204B68)
static __int64 __fastcall h_sub_204B68() {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x20c1fc,
        0x1fca04,
        0x1fcd18,
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
    ss << OBF("System State Getter: YES\n");

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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_204B68] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_204B68();

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_204B68] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 8: sub_24ED48 - Mutex Handler (Offset: 0x24ED48)
static bool __fastcall h_sub_24ED48(pthread_mutex_t *a1) {
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
    ss << OBF("Mutex Handler: YES\n");

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
            return false; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_24ED48] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_24ED48(a1);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_24ED48] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 9: sub_284980 - Resource Manager (Offset: 0x284980)
static __int64 __fastcall h_sub_284980(__int64 a1) {
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
    ss << OBF("Resource Manager: YES\n");

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
            return 0; // Return safe value
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_284980] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_284980(a1);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_284980] ===" LOG_COLOR_RESET "\n");
    return result;
}

// Hook 10: sub_295D00 - Triple Parameter Handler (Offset: 0x295D00)
static void __fastcall h_sub_295D00(__int64 a1, __int64 a2, __int64 a3) {
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
    ss << OBF("Triple Parameter Handler: YES\n");

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
            return; // Block execution
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_295D00] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_295D00(a1, a2, a3);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_295D00] ===" LOG_COLOR_RESET "\n");
}

#endif //ARCAMOD_H_MONITORING_HOOKS_18_H
