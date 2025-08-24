#ifndef ARCAMOD_H_MONITORING_HOOKS_4_H
#define ARCAMOD_H_MONITORING_HOOKS_4_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (13, 2A, 22 series)
void (*o_sub_130238)(_QWORD **a1);
void (*o_sub_1301C4)(char **a1, void **a2);
__int64 (*o_sub_13185C)(__int64 *a1, _BYTE **a2);
void (*o_sub_1318F0)(char **a1, __int64 a2);
__int64 (*o_sub_2A0048)(__int64 a1, __int64 a2, __int64 a3, __int64 a4);
__int64 (*o_sub_2A0090)(__int64 a1, _QWORD *a2, int a3, __int64 a4, __int64 a5);
__int64 (*o_sub_2ADDA0)(__int64 a1);
void (*o_sub_2AE920)();
void (*o_sub_220090)(__int64 *a1);
__int64 (*o_sub_2212A4)(__int64 a1, void *a2, unsigned int a3);

// Hook 1: sub_130238 - QWORD Array Cleanup (Offset: 0x130238)
static void __fastcall h_sub_130238(_QWORD **a1) {
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

    if (a1) {
        ss << OBF("QWORD Array Cleanup: YES\n");
        ss << OBF("Array Processing: YES\n");
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
            return; // Block execution
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_130238] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_130238(a1);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_130238] ===" LOG_COLOR_RESET "\n");
}

// Hook 2: sub_1301C4 - String Array Processing (Offset: 0x1301C4)
static void __fastcall h_sub_1301C4(char **a1, void **a2) {
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

    if (a1 && a2) {
        ss << OBF("String Array Processing: YES\n");
        ss << OBF("Dual Array Operation: YES\n");
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
            return; // Block execution
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1301C4] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_1301C4(a1, a2);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1301C4] ===" LOG_COLOR_RESET "\n");
}

// Hook 3: sub_13185C - Byte Array Processing (Offset: 0x13185C)
static __int64 __fastcall h_sub_13185C(__int64 *a1, _BYTE **a2) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x415f7c,  // Caller aktif dari monitoring (~5 calls)
        0x13267c,  // Caller sangat aktif dari monitoring (~600+ calls)
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

    if (a1 && a2) {
        ss << OBF("Byte Array Processing: YES\n");
        ss << OBF("Return Type: __int64\n");
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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_13185C] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_13185C(a1, a2);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_13185C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_1318F0 - String Processing (Offset: 0x1318F0)
static void __fastcall h_sub_1318F0(char **a1, __int64 a2) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x415ee4,  // Caller aktif dari monitoring (~3 calls)
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
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");

    if (a1) {
        ss << OBF("String Processing: YES\n");
        ss << OBF("String Array Operation: YES\n");
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
            return; // Block execution
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1318F0] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_1318F0(a1, a2);

    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1318F0] ===" LOG_COLOR_RESET "\n");
}

// Hook 5: sub_2A0048 - Virtual Function Call (Offset: 0x2A0048)
static __int64 __fastcall h_sub_2A0048(__int64 a1, __int64 a2, __int64 a3, __int64 a4) {
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
    ss << OBF("Virtual Function Call: YES\n");

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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2A0048] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2A0048(a1, a2, a3, a4);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2A0048] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_2A0090 - Complex Virtual Function (Offset: 0x2A0090)
static __int64 __fastcall h_sub_2A0090(__int64 a1, _QWORD *a2, int a3, __int64 a4, __int64 a5) {
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
    ss << OBF("a4: ") << std::hex << a4 << OBF("\n");
    ss << OBF("a5: ") << std::hex << a5 << OBF("\n");
    ss << OBF("Complex Virtual Function: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2A0090] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2A0090(a1, a2, a3, a4, a5);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2A0090] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_2ADDA0 - Single Parameter Function (Offset: 0x2ADDA0)
static __int64 __fastcall h_sub_2ADDA0(__int64 a1) {
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
    ss << OBF("Single Parameter Function: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2ADDA0] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2ADDA0(a1);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2ADDA0] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_2AE920 - No Parameter Function (Offset: 0x2AE920)
static void __fastcall h_sub_2AE920() {
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
    ss << OBF("No Parameter Function: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2AE920] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_2AE920();

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2AE920] ===" LOG_COLOR_RESET "\n");
}

// Hook 9: sub_220090 - Pointer Array Cleanup (Offset: 0x220090)
static void __fastcall h_sub_220090(__int64 *a1) {
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

    if (a1) {
        ss << OBF("Pointer Array Cleanup: YES\n");
        ss << OBF("Array Management: YES\n");
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
            return; // Block execution
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_220090] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_220090(a1);

    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_220090] ===" LOG_COLOR_RESET "\n");
}

// Hook 10: sub_2212A4 - Memory Copy Operation (Offset: 0x2212A4)
static __int64 __fastcall h_sub_2212A4(__int64 a1, void *a2, unsigned int a3) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x21f74c,  // Caller paling aktif dari monitoring (~500+ calls)
        0x22661c,  // Caller aktif dari monitoring (~50+ calls)
        0x22663c,  // Caller aktif dari monitoring (~50+ calls)
        0x25b928,  // Caller aktif dari monitoring (large size operations ~30+ calls)
        0x2207f8,  // Caller aktif dari monitoring (~20+ calls)
        0x415f7c,  // Caller aktif dari monitoring (~5 calls)
        0x415ee4,  // Caller aktif dari monitoring (~5 calls)
        0x13267c,  // Caller sangat aktif dari monitoring (~600+ calls)
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
    ss << OBF("a3: ") << std::dec << a3 << OBF(" bytes\n");

    if (a2 && a3 > 0) {
        ss << OBF("Memory Copy Operation: YES\n");
        ss << OBF("Size: ") << std::dec << a3 << OBF(" bytes\n");
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

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2212A4] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2212A4(a1, a2, a3);

    // LOGIO("Result: 0x%llx", result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2212A4] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_4_H
