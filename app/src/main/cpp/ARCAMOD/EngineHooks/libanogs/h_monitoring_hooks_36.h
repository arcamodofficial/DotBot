#ifndef ARCAMOD_H_MONITORING_HOOKS_36_H
#define ARCAMOD_H_MONITORING_HOOKS_36_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (200D74, 200E4C, 200ED8, 200F30, 200FDC, 201200, 20128C, 20164C, 2020D0, 203400 series)
bool (*o_sub_200D74)(_QWORD *a1, _QWORD *a2);
bool (*o_sub_200E4C)(__int64 a1, _DWORD *a2);
bool (*o_sub_200ED8)(__int64 a1, __int64 a2, _DWORD *a3);
_QWORD *(*o_sub_200F30)(_QWORD *result, __int64 a2);
bool (*o_sub_200FDC)(_QWORD *a1, _QWORD *a2);
_QWORD *(*o_sub_201200)(__int64 a1);
_QWORD *(*o_sub_20128C)(_QWORD *a1);
bool (*o_sub_20164C)(__int64 a1, const void *a2, unsigned int a3);
bool (*o_sub_2020D0)(int *a1, int a2, const char *a3);
bool (*o_sub_203400)(__int64 a1, __int64 a2);

// Hook 1: sub_200D74 - Bool Validator (Offset: 0x200D74)
static bool __fastcall h_sub_200D74(_QWORD *a1, _QWORD *a2) {
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
    ss << OBF("a1 (QWORD*): ") << std::hex << (uintptr_t)a1 << OBF("\n");
    ss << OBF("a2 (QWORD*): ") << std::hex << (uintptr_t)a2 << OBF("\n");
    if (a1) {
        ss << OBF("Value a1: ") << std::hex << *a1 << OBF("\n");
    }
    if (a2) {
        ss << OBF("Value a2: ") << std::hex << *a2 << OBF("\n");
    }
    ss << OBF("Bool Validator: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200D74] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_200D74(a1, a2);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200D74] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 2: sub_200E4C - Bool with DWORD Validator (Offset: 0x200E4C)
static bool __fastcall h_sub_200E4C(__int64 a1, _DWORD *a2) {
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
    ss << OBF("a2 (DWORD*): ") << std::hex << (uintptr_t)a2 << OBF("\n");
    if (a2) {
        ss << OBF("DWORD Value: ") << std::dec << *a2 << OBF("\n");
    }
    ss << OBF("Bool with DWORD Validator: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200E4C] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_200E4C(a1, a2);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200E4C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 3: sub_200ED8 - Bool Triple Parameter Handler (Offset: 0x200ED8)
static bool __fastcall h_sub_200ED8(__int64 a1, __int64 a2, _DWORD *a3) {
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
    ss << OBF("a3 (DWORD*): ") << std::hex << (uintptr_t)a3 << OBF("\n");
    if (a3) {
        ss << OBF("DWORD Value: ") << std::dec << *a3 << OBF("\n");
    }
    ss << OBF("Bool Triple Parameter Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200ED8] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_200ED8(a1, a2, a3);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200ED8] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_200F30 - QWORD Pointer Return (Offset: 0x200F30)
static _QWORD *__fastcall h_sub_200F30(_QWORD *result, __int64 a2) {
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
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    if (result) {
        ss << OBF("Result Value: ") << std::hex << *result << OBF("\n");
    }
    ss << OBF("QWORD Pointer Return: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200F30] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *res = o_sub_200F30(result, a2);

    // LOGIO("Result: 0x%llx", (uintptr_t)res);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200F30] ===" LOG_COLOR_RESET "\n");

    return res;
}

// Hook 5: sub_200FDC - Bool Validator (Offset: 0x200FDC)
static bool __fastcall h_sub_200FDC(_QWORD *a1, _QWORD *a2) {
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
    ss << OBF("a1 (QWORD*): ") << std::hex << (uintptr_t)a1 << OBF("\n");
    ss << OBF("a2 (QWORD*): ") << std::hex << (uintptr_t)a2 << OBF("\n");
    if (a1) {
        ss << OBF("Value a1: ") << std::hex << *a1 << OBF("\n");
    }
    if (a2) {
        ss << OBF("Value a2: ") << std::hex << *a2 << OBF("\n");
    }
    ss << OBF("Bool Validator: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_200FDC] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_200FDC(a1, a2);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_200FDC] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_201200 - QWORD Pointer Return (Offset: 0x201200)
static _QWORD *__fastcall h_sub_201200(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x2e6c00
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
    ss << OBF("QWORD Pointer Return: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_201200] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *result = o_sub_201200(a1);

    // LOGIO("Result: 0x%llx", (uintptr_t)result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_201200] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_20128C - QWORD Pointer Manager (Offset: 0x20128C)
static _QWORD *__fastcall h_sub_20128C(_QWORD *a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x201234
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
    ss << OBF("a1 (QWORD*): ") << std::hex << (uintptr_t)a1 << OBF("\n");
    if (a1) {
        ss << OBF("Value: ") << std::hex << *a1 << OBF("\n");
    }
    ss << OBF("QWORD Pointer Manager: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_20128C] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *result = o_sub_20128C(a1);

    // LOGIO("Result: 0x%llx", (uintptr_t)result);
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_20128C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_20164C - Bool with Memory Validator (Offset: 0x20164C)
static bool __fastcall h_sub_20164C(__int64 a1, const void *a2, unsigned int a3) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x2d543c
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
    ss << OBF("a2 (const void*): ") << std::hex << (uintptr_t)a2 << OBF("\n");
    ss << OBF("a3 (unsigned): ") << std::dec << a3 << OBF("\n");
    ss << OBF("Bool with Memory Validator: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_20164C] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_20164C(a1, a2, a3);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_20164C] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 9: sub_2020D0 - Bool String Handler (Offset: 0x2020D0)
static bool __fastcall h_sub_2020D0(int *a1, int a2, const char *a3) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x20252c,
        0x20253c,
        0x20254c,
        0x20255c
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
    ss << OBF("a1 (int*): ") << std::hex << (uintptr_t)a1 << OBF("\n");
    if (a1) {
        ss << OBF("Int Value: ") << std::dec << *a1 << OBF("\n");
    }
    ss << OBF("a2 (int): ") << std::dec << a2 << OBF("\n");
    ss << OBF("a3 (string): ") << (a3 ? a3 : "NULL") << OBF("\n");
    ss << OBF("Bool String Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2020D0] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_2020D0(a1, a2, a3);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2020D0] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 10: sub_203400 - Bool Dual Parameter Handler (Offset: 0x203400)
static bool __fastcall h_sub_203400(__int64 a1, __int64 a2) {
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
    ss << OBF("Bool Dual Parameter Handler: YES\n");

    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            // LOGIO("[BLOCKED] Call info:\n%s", info.string_param.c_str());

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    // LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_203400] ===" LOG_COLOR_RESET);
    // LOGIO("Timestamp: %lu", info.timestamp);
    // LOGIO("Offset Call: 0x%lx", info.offset);
    // LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_203400(a1, a2);

    // LOGIO("Result: %s", result ? "true" : "false");
    // LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_203400] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_MONITORING_HOOKS_36_H