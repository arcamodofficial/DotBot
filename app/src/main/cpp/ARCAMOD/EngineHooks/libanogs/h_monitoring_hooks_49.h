#ifndef ARCAMOD_H_MONITORING_HOOKS_49_H
#define ARCAMOD_H_MONITORING_HOOKS_49_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

// Function pointers for 10 monitoring hooks (Series 49)
void (*o_sub_15BE14)(__int64 a1, __int64 a2);
void (*o_sub_15BF2C)(__int64 a1, __int64 a2, __int64 a3);
_QWORD *(*o_sub_15C034)(_QWORD *a1, __int64 a2);
_QWORD *(*o_sub_15C178)(_QWORD *a1);
__int64 (*o_sub_152004)(__int64 a1, __int64 a2);
__int64 (*o_sub_152178)(__int64 a1, __int64 a2, __int64 a3);
unsigned __int64 (*o_sub_25A144)(unsigned __int64 a1, unsigned __int64 a2);
unsigned __int64 (*o_sub_25A234)(unsigned __int64 a1);
bool (*o_sub_35F144)(bool a1, __int64 a2);
bool (*o_sub_35F234)(bool a1);

// Hook 1: sub_15BE14 - Dual Parameter Void Handler (Offset: 0x15BE14)
static void __fastcall h_sub_15BE14(__int64 a1, __int64 a2) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("Dual Parameter Void Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_15BE14] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_15BE14(a1, a2);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_15BE14] ===" LOG_COLOR_RESET "\n");
}

// Hook 2: sub_15BF2C - Triple Parameter Void Handler (Offset: 0x15BF2C)
static void __fastcall h_sub_15BF2C(__int64 a1, __int64 a2, __int64 a3) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n") << OBF("a3: ") << std::hex << a3 << OBF("\n");
    ss << OBF("Triple Parameter Void Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_15BF2C] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    o_sub_15BF2C(a1, a2, a3);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_15BF2C] ===" LOG_COLOR_RESET "\n");
}

// Hook 3: sub_15C034 - QWORD Dual Parameter Handler (Offset: 0x15C034)
static _QWORD *__fastcall h_sub_15C034(_QWORD *a1, __int64 a2) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << (uintptr_t)a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    if (a1) ss << OBF("QWORD Value: ") << std::hex << *a1 << OBF("\n");
    ss << OBF("QWORD Dual Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_15C034] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *result = o_sub_15C034(a1, a2);

    LOGIO("Result: 0x%llx", (uintptr_t)result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_15C034] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 4: sub_15C178 - QWORD Single Parameter Handler (Offset: 0x15C178)
static _QWORD *__fastcall h_sub_15C178(_QWORD *a1) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << (uintptr_t)a1 << OBF("\n");
    if (a1) ss << OBF("QWORD Value: ") << std::hex << *a1 << OBF("\n");
    ss << OBF("QWORD Single Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return nullptr;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_15C178] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    _QWORD *result = o_sub_15C178(a1);

    LOGIO("Result: 0x%llx", (uintptr_t)result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_15C178] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 5: sub_152004 - Int64 Dual Parameter Handler (Offset: 0x152004)
static __int64 __fastcall h_sub_152004(__int64 a1, __int64 a2) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("Int64 Dual Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_152004] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_152004(a1, a2);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_152004] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 6: sub_152178 - Int64 Triple Parameter Handler (Offset: 0x152178)
static __int64 __fastcall h_sub_152178(__int64 a1, __int64 a2, __int64 a3) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n") << OBF("a3: ") << std::hex << a3 << OBF("\n");
    ss << OBF("Int64 Triple Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_152178] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_152178(a1, a2, a3);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_152178] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 7: sub_25A144 - Unsigned Dual Parameter Handler (Offset: 0x25A144)
static unsigned __int64 __fastcall h_sub_25A144(unsigned __int64 a1, unsigned __int64 a2) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("Unsigned Dual Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_25A144] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    unsigned __int64 result = o_sub_25A144(a1, a2);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_25A144] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 8: sub_25A234 - Unsigned Single Parameter Handler (Offset: 0x25A234)
static unsigned __int64 __fastcall h_sub_25A234(unsigned __int64 a1) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << std::hex << a1 << OBF("\n");
    ss << OBF("Unsigned Single Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_25A234] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    unsigned __int64 result = o_sub_25A234(a1);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_25A234] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 9: sub_35F144 - Bool Dual Parameter Handler (Offset: 0x35F144)
static bool __fastcall h_sub_35F144(bool a1, __int64 a2) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << (a1 ? "true" : "false") << OBF("\n");
    ss << OBF("a2: ") << std::hex << a2 << OBF("\n");
    ss << OBF("Bool Dual Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_35F144] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_35F144(a1, a2);

    LOGIO("Result: %s", result ? "true" : "false");
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_35F144] ===" LOG_COLOR_RESET "\n");

    return result;
}

// Hook 10: sub_35F234 - Bool Single Parameter Handler (Offset: 0x35F234)
static bool __fastcall h_sub_35F234(bool a1) {
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
    ss << OBF("Parameters:\n") << OBF("a1: ") << (a1 ? "true" : "false") << OBF("\n");
    ss << OBF("Bool Single Parameter Handler: YES\n");
    info.string_param = ss.str();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (info.offset == blocked_offsets[i]) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Call from offset: 0x%lx", blocked_offsets[i]);
            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return false;
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_35F234] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    bool result = o_sub_35F234(a1);

    LOGIO("Result: %s", result ? "true" : "false");
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_35F234] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif // ARCAMOD_H_MONITORING_HOOKS_49_H