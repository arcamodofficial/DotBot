#ifndef ARCAMOD_H_MONITORING_HOOKS_32_H
#define ARCAMOD_H_MONITORING_HOOKS_32_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (100A7C, 100B08, 100D88, 101210, 101348, 1014DC, 101540, 1018AC, 101910, 101A14 series)
__int64 (*o_sub_100A7C)(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, __int64 a12, unsigned __int64 a13, __int64 a14, __int64 a15);
__int64 (*o_sub_100B08)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12);
__int64 (*o_sub_100D88)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_101210)();
__int64 (*o_sub_101348)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_1014DC)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12);
__int64 (*o_sub_101540)();
__int64 (*o_sub_1018AC)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13);
__int64 (*o_sub_101910)();
__int64 (*o_sub_101A14)(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17);

// Hook 1: sub_100A7C - Multi-Parameter Integer Handler (Offset: 0x100A7C)
static __int64 __fastcall h_sub_100A7C(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10, int a11, __int64 a12, unsigned __int64 a13, __int64 a14, __int64 a15) {
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
    ss << OBF("a1-a11: ") << std::dec << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << "," << a9 << "," << a10 << "," << a11 << OBF("\n");
    ss << OBF("a12: ") << std::hex << a12 << OBF("\n");
    ss << OBF("a13: ") << std::hex << a13 << OBF("\n");
    ss << OBF("a14: ") << std::hex << a14 << OBF("\n");
    ss << OBF("a15: ") << std::hex << a15 << OBF("\n");
    ss << OBF("Multi-Parameter Integer Handler: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100A7C] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100A7C(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100A7C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 2: sub_100B08 - Complex Multi-Parameter String Handler (Offset: 0x100B08)
static __int64 __fastcall h_sub_100B08(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12) {
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
    ss << OBF("a1-a8: ") << std::hex << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << OBF("\n");
    ss << OBF("a9 (string): ") << (a9 ? a9 : "NULL") << OBF("\n");
    ss << OBF("a10-a11: ") << std::hex << a10 << "," << a11 << OBF("\n");
    ss << OBF("a12 (char): ") << (int)a12 << OBF("\n");
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
            return 0; // Return fake value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100B08] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100B08(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100B08] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 3: sub_100D88 - Complex Multi-Parameter String Handler (Offset: 0x100D88)
static __int64 __fastcall h_sub_100D88(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13) {
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
    ss << OBF("a1-a9: ") << std::hex << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << "," << a9 << OBF("\n");
    ss << OBF("a10 (string): ") << (a10 ? a10 : "NULL") << OBF("\n");
    ss << OBF("a11-a12: ") << std::hex << a11 << "," << a12 << OBF("\n");
    ss << OBF("a13 (char): ") << (int)a13 << OBF("\n");
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
            return 0; // Return fake value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_100D88] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_100D88(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_100D88] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_101210 - Simple System State Function (Offset: 0x101210)
static __int64 __fastcall h_sub_101210() {
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
    ss << OBF("Simple System State Function: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_101210] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_101210();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_101210] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 5: sub_101348 - Complex Multi-Parameter String Handler (Offset: 0x101348)
static __int64 __fastcall h_sub_101348(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13) {
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
    ss << OBF("a1-a9: ") << std::hex << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << "," << a9 << OBF("\n");
    ss << OBF("a10 (string): ") << (a10 ? a10 : "NULL") << OBF("\n");
    ss << OBF("a11-a12: ") << std::hex << a11 << "," << a12 << OBF("\n");
    ss << OBF("a13 (char): ") << (int)a13 << OBF("\n");
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
            return 0; // Return fake value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_101348] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_101348(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_101348] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_1014DC - Complex Multi-Parameter String Handler (Offset: 0x1014DC)
static __int64 __fastcall h_sub_1014DC(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, char *a9, __int64 a10, __int64 a11, char a12) {
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
    ss << OBF("a1-a8: ") << std::hex << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << OBF("\n");
    ss << OBF("a9 (string): ") << (a9 ? a9 : "NULL") << OBF("\n");
    ss << OBF("a10-a11: ") << std::hex << a10 << "," << a11 << OBF("\n");
    ss << OBF("a12 (char): ") << (int)a12 << OBF("\n");
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
            return 0; // Return fake value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1014DC] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1014DC(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1014DC] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_101540 - Simple System State Function (Offset: 0x101540)
static __int64 __fastcall h_sub_101540() {
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
    ss << OBF("Simple System State Function: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_101540] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_101540();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_101540] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_1018AC - Complex Multi-Parameter String Handler (Offset: 0x1018AC)
static __int64 __fastcall h_sub_1018AC(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, char *a10, __int64 a11, __int64 a12, char a13) {
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
    ss << OBF("a1-a9: ") << std::hex << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << "," << a9 << OBF("\n");
    ss << OBF("a10 (string): ") << (a10 ? a10 : "NULL") << OBF("\n");
    ss << OBF("a11-a12: ") << std::hex << a11 << "," << a12 << OBF("\n");
    ss << OBF("a13 (char): ") << (int)a13 << OBF("\n");
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
            return 0; // Return fake value to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1018AC] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_1018AC(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1018AC] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 9: sub_101910 - Simple System State Function (Offset: 0x101910)
static __int64 __fastcall h_sub_101910() {
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
    ss << OBF("Simple System State Function: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_101910] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_101910();

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_101910] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 10: sub_101A14 - Extended Parameter Handler (Offset: 0x101A14)
static __int64 __fastcall h_sub_101A14(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9, __int64 a10, __int64 a11, __int64 a12, __int64 a13, __int64 a14, __int64 a15, __int64 a16, __int64 a17) {
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
    ss << OBF("a1-a8: ") << std::hex << a1 << "," << a2 << "," << a3 << "," << a4 << "," << a5 << "," << a6 << "," << a7 << "," << a8 << OBF("\n");
    ss << OBF("a9-a17: ") << std::hex << a9 << "," << a10 << "," << a11 << "," << a12 << "," << a13 << "," << a14 << "," << a15 << "," << a16 << "," << a17 << OBF("\n");
    ss << OBF("Extended Parameter Handler: YES\n");

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

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_101A14] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_101A14(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15, a16, a17);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_101A14] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_32_H