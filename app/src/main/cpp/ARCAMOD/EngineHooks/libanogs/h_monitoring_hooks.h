#ifndef ARCAMOD_H_MONITORING_HOOKS_H
#define ARCAMOD_H_MONITORING_HOOKS_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for all monitoring hooks
__int64 (*o_sub_11A7D8)(__int64 a1);
__int64 (*o_sub_11A814)(__int64 result);
__int64 (*o_sub_11637C)(__int64 a1, _OWORD *a2, unsigned __int64 a3);
__int64 (*o_sub_116780)(__int64 a1, _OWORD *a2, unsigned __int64 a3);
__int64 (*o_sub_1167C8)(__int64 a1, _BYTE *a2, __int64 a3);
__int64 (*o_sub_1169A0)(__int64 a1);
__int64 (*o_sub_116364)(__int64 a1);

// Hook 1: sub_11A7D8 - Counter Management dengan Limit
static __int64 __fastcall h_sub_11A7D8(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x11b43c,  // Caller yang terdeteksi aktif dari monitoring
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

    if (a1) {
        // Monitor counter at offset 116
        int counter_value = *(_DWORD *)(a1 + 116);
        ss << OBF("Counter (a1+116): ") << std::dec << counter_value << OBF("\n");
        ss << OBF("Counter Check: ") << (counter_value <= 2 ? "PASS" : "FAIL") << OBF("\n");
        ss << OBF("a1+128: ") << std::hex << *(_QWORD *)(a1 + 128) << OBF("\n");
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
            return 1; // Return success to avoid detection
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_11A7D8] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_11A7D8(a1);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_11A7D8] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 2: sub_11A814 - Similar Counter Pattern
static __int64 __fastcall h_sub_11A814(__int64 result) {
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

    if (result) {
        // Monitor counter at offset 116
        int counter_value = *(_DWORD *)(result + 116);
        ss << OBF("Counter (result+116): ") << std::dec << counter_value << OBF("\n");
        ss << OBF("Counter Check: ") << (counter_value <= 2 ? "PASS" : "FAIL") << OBF("\n");
        ss << OBF("result+128: ") << std::hex << *(_QWORD *)(result + 128) << OBF("\n");
    }

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
            return result; // Return original value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_11A814] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 hook_result = o_sub_11A814(result);

    LOGIO("Result: 0x%llx", hook_result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_11A814] ===" LOG_COLOR_RESET "\n");

    return hook_result;
}

// Hook 3: sub_11637C - Buffer Validation
static __int64 __fastcall h_sub_11637C(__int64 a1, _OWORD *a2, unsigned __int64 a3) {
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
    ss << OBF("a2: ") << std::hex << (uintptr_t)a2 << OBF("\n");
    ss << OBF("a3: ") << std::dec << a3 << OBF("\n");

    if (a1) {
        ss << OBF("a1+360: ") << std::hex << *(_QWORD *)(a1 + 360) << OBF("\n");
    }

    if (a2) {
        ss << OBF("Buffer Valid: YES\n");
        ss << OBF("Size Check: ") << (a3 >= 0x10 ? "PASS (>=16)" : "FAIL (<16)") << OBF("\n");
    } else {
        ss << OBF("Buffer Valid: NO (NULL)\n");
    }

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
            return 0; // Return success to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_11637C] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_11637C(a1, a2, a3);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_11637C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_116780 - Global State Access
static __int64 __fastcall h_sub_116780(__int64 a1, _OWORD *a2, unsigned __int64 a3) {
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
    ss << OBF("a2: ") << std::hex << (uintptr_t)a2 << OBF("\n");
    ss << OBF("a3: ") << std::dec << a3 << OBF("\n");

    if (a2) {
        ss << OBF("Buffer Valid: YES\n");
        ss << OBF("Size Check: ") << (a3 >= 0x10 ? "PASS (>=16)" : "FAIL (<16)") << OBF("\n");
        ss << OBF("Global State Access: YES (sub_1110D8)\n");
    } else {
        ss << OBF("Buffer Valid: NO (NULL)\n");
    }

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
            return 0; // Return success to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_116780] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_116780(a1, a2, a3);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_116780] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 5: sub_1167C8 - Memory Copy Operation
static __int64 __fastcall h_sub_1167C8(__int64 a1, _BYTE *a2, __int64 a3) {
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
    ss << OBF("a2: ") << std::hex << (uintptr_t)a2 << OBF("\n");
    ss << OBF("a3: ") << std::dec << a3 << OBF("\n");

    if (a2) {
        ss << OBF("Buffer Valid: YES\n");
        ss << OBF("Size Check: ") << (a3 > 0 ? "PASS (>0)" : "FAIL (=0)") << OBF("\n");
        ss << OBF("Memory Copy: YES (sub_3EE1A0)\n");
        ss << OBF("Global State Access: YES (sub_1110D8)\n");
    } else {
        ss << OBF("Buffer Valid: NO (NULL)\n");
    }

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
            return 0xFFFFFFFFLL; // Return error to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1167C8] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1167C8(a1, a2, a3);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1167C8] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_1169A0 - Virtual Function Call
static __int64 __fastcall h_sub_1169A0(__int64 a1) {
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

    if (a1) {
        ss << OBF("VTable Ptr: ") << std::hex << *(_QWORD *)a1 << OBF("\n");
        ss << OBF("VTable+128: ") << std::hex << *(_QWORD *)(*(_QWORD *)a1 + 128) << OBF("\n");
        ss << OBF("Virtual Call: YES\n");
        ss << OBF("Pre-calls: sub_117378, sub_117F50\n");
    }

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
            return 1; // Return success to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1169A0] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1169A0(a1);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1169A0] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_116364 - Simple Getter
static __int64 __fastcall h_sub_116364(__int64 a1) {
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

    if (a1) {
        unsigned int value = *(unsigned int *)(a1 + 304);
        ss << OBF("Value (a1+304): ") << std::dec << value << OBF("\n");
        ss << OBF("Simple Getter: YES\n");
    }

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
            return 0; // Return fake value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_116364] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_116364(a1);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_116364] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_H
