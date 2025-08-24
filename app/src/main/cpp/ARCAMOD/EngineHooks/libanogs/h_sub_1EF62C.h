#ifndef ARCAMOD_H_SUB_1EF62C_H
#define ARCAMOD_H_SUB_1EF62C_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

__int64 (*o_sub_1EF62C)(__int64 a1);

static __int64 __fastcall h_sub_1EF62C(__int64 a1) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
//            0x1ef54c,
//            0x1efe78,
//            0x1f00d8,
            0x1f1300,
            0x1f1548
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
        ss << OBF("a1+8: ") << std::hex << *(_QWORD * )(a1 + 8) << OBF("\n");
    }

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
            return 0;
        }
    }

    for (size_t i = 0; i < sizeof(blocked_strings) / sizeof(blocked_strings[0]); ++i) {
        if (info.string_param.find(blocked_strings[i]) != std::string::npos) {
            info.was_blocked = true;
            // LOGIO("[BLOCKED] Found suspicious string: %s", blocked_strings[i]);
            // LOGIO("[BLOCKED] In call info:\n%s", info.string_param.c_str());
            // LOGIO("[BLOCKED] Call from offset: 0x%lx", info.offset);

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 0;
        }
    }

//    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_1EF62C] ===" LOG_COLOR_RESET);
//    LOGIO("Timestamp: %lu", info.timestamp);
//    LOGIO("Offset Call: 0x%lx", info.offset);
//    LOGIO("Call Info:\n%s", info.string_param.c_str());
//    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_1EF62C] ===" LOG_COLOR_RESET "\n");

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }
/*
    static auto print_history = []() {
        LOGIO("\n=== ALLOWED CALLS HISTORY ===");
        for (const auto& hist : monitoring_history) {
            if (!hist.was_blocked) {
                LOGIO("Time: %lu | Offset: 0x%lx | Info:\n%s",
                      hist.timestamp,
                      hist.offset,
                      hist.string_param.c_str());
            }
        }
        LOGIO("=== END HISTORY ===\n");
    };

    if (monitoring_history.size() % 10 == 0) {
        print_history();
    }
*/
    __int64 result = o_sub_1EF62C(a1);

//    LOGIO("Result: 0x%llx", result);

    return result;
}

#endif //ARCAMOD_H_SUB_1EF62C_H