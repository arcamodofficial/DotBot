#ifndef ARCAMOD_H_MONITORING_HOOKS_37_H
#define ARCAMOD_H_MONITORING_HOOKS_37_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (1083C4, 106EF0, 119CCC, 1E2910, 200054, 10B130, 200178, 2002E4, 200234, 2003CC series)
bool (*o_sub_1083C4)(__int64 a1);
_QWORD *(*o_sub_106EF0)(_QWORD *result, _BYTE *a2);
_DWORD *(*o_sub_119CCC)();
size_t (*o_sub_1E2910)(__int64 a1, __int64 a2, size_t a3);
void (*o_sub_200054)();
unsigned __int8 *(*o_sub_10B130)(__int64 a1, unsigned __int64 a2);
__int64 (*o_sub_200178)(__int64 result, __int64 a2, char a3);
__int64 (*o_sub_2002E4)();
__int64 (*o_sub_200234)(__int64 a1, __int64 a2);
__int64 (*o_sub_2003CC)();

// Hook 1: sub_1083C4 - Bool Validator (Offset: 0x1083C4)
static bool __fastcall h_sub_1083C4(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x1cd1a4
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
    ss << OBF("Bool Validator: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1083C4] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_1083C4(a1);

    // // LOGIO("Result: %s", result ? "true" : "false");
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1083C4] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 2: sub_106EF0 - QWORD Pointer Return (Offset: 0x106EF0)
static _QWORD *__fastcall h_sub_106EF0(_QWORD *result, _BYTE *a2) {
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
    ss << OBF("result (QWORD*): ") << std::hex << (uintptr_t)result << OBF("\n");
    ss << OBF("a2 (BYTE*): ") << std::hex << (uintptr_t)a2 << OBF("\n");
    if (result) {
        ss << OBF("Result Value: ") << std::hex << *result << OBF("\n");
    }
    ss << OBF("QWORD Pointer Return: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_106EF0] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *res = o_sub_106EF0(result, a2);

    // // LOGIO("Result: 0x%llx", (uintptr_t)res);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_106EF0] ===" LOG_COLOR_RESET "\n");

    return res;
}

// Hook 3: sub_119CCC - DWORD Pointer Return (Offset: 0x119CCC)
static _DWORD *__fastcall h_sub_119CCC() {
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
    ss << OBF("DWORD Pointer Return: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_119CCC] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _DWORD *result = o_sub_119CCC();

    // // LOGIO("Result: 0x%llx", (uintptr_t)result);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_119CCC] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_1E2910 - Size_t Handler (Offset: 0x1E2910)
static size_t __fastcall h_sub_1E2910(__int64 a1, __int64 a2, size_t a3) {
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
    ss << OBF("a3 (size_t): ") << std::dec << a3 << OBF("\n");
    ss << OBF("Size_t Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1E2910] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    size_t result = o_sub_1E2910(a1, a2, a3);

    // // LOGIO("Result: %zu", result);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1E2910] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 5: sub_200054 - Void System Function (Offset: 0x200054)
static void __fastcall h_sub_200054() {
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
    ss << OBF("Void System Function: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200054] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_200054();

    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200054] ===" LOG_COLOR_RESET "\n");
}

// Hook 6: sub_10B130 - Unsigned Byte Pointer Return (Offset: 0x10B130)
static unsigned __int8 *__fastcall h_sub_10B130(__int64 a1, unsigned __int64 a2) {
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
    ss << OBF("a2 (unsigned): ") << std::dec << a2 << OBF("\n");
    ss << OBF("Unsigned Byte Pointer Return: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_10B130] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    unsigned __int8 *result = o_sub_10B130(a1, a2);

    // // LOGIO("Result: 0x%llx", (uintptr_t)result);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_10B130] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_200178 - Int64 Triple Parameter Handler (Offset: 0x200178)
static __int64 __fastcall h_sub_200178(__int64 result, __int64 a2, char a3) {
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
    ss << OBF("result: ") << std::hex << result << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("a3 (char): ") << std::dec << (int)a3 << OBF("\n");
    ss << OBF("Int64 Triple Parameter Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200178] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 res = o_sub_200178(result, a2, a3);

    // // LOGIO("Result: 0x%llx", res);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200178] ===" LOG_COLOR_RESET "\n");

    return res;
}

// Hook 8: sub_2002E4 - Int64 System State Function (Offset: 0x2002E4)
static __int64 __fastcall h_sub_2002E4() {
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
    ss << OBF("Int64 System State Function: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2002E4] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2002E4();

    // // LOGIO("Result: 0x%llx", result);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2002E4] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 9: sub_200234 - Int64 Dual Parameter Handler (Offset: 0x200234)
static __int64 __fastcall h_sub_200234(__int64 a1, __int64 a2) {
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
    ss << OBF("Int64 Dual Parameter Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200234] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_200234(a1, a2);

    // // LOGIO("Result: 0x%llx", result);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200234] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 10: sub_2003CC - Int64 System Function (Offset: 0x2003CC)
static __int64 __fastcall h_sub_2003CC() {
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
    ss << OBF("Int64 System Function: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    // // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2003CC] ===" LOG_COLOR_RESET);
    // // LOGIO("Timestamp: %lu", info.timestamp);
    // // LOGIO("Offset Call: 0x%lx", info.offset);
    // // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2003CC();

    // // LOGIO("Result: 0x%llx", result);
    // // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2003CC] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_37_H