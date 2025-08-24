#ifndef ARCAMOD_H_SUB_2DAB74_H
#define ARCAMOD_H_SUB_2DAB74_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

__int64 (*o_sub_2DAB74)(__int64 a1, __int64 a2);

static __int64 __fastcall h_sub_2DAB74(__int64 a1, __int64 a2) {
    const char *blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
        0x2dbda8,
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

    if (a1) {
        ss << OBF("a1+8: ") << std::hex << *(_QWORD * )(a1 + 8) << OBF("\n");
    }

    if (a2 > 0x10000 && a2 < 0x7FFFFFFFFFFF) {
        try {
            uint32_t* ptr = reinterpret_cast<uint32_t*>(a2);
            ss << OBF("a2+612: ") << std::dec << ptr[153] << OBF("\n");
            ss << OBF("a2+592: ") << std::dec << ptr[148] << OBF("\n");
            ss << OBF("a2+596: ") << std::dec << ptr[149] << OBF("\n");
        } catch (...) {
            ss << OBF("a2: (unreadable)\n");
        }
    }

    info.string_param = ss.str();

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

    for (size_t i = 0; i < sizeof(blocked_strings) / sizeof(blocked_strings[0]); ++i) {
        if (info.string_param.find(blocked_strings[i]) != std::string::npos) {
            info.was_blocked = true;
            LOGIO("[BLOCKED] Found suspicious string: %s", blocked_strings[i]);
            LOGIO("[BLOCKED] In call info:\n%s", info.string_param.c_str());
            LOGIO("[BLOCKED] Call from offset: 0x%lx", info.offset);

            monitoring_history.push_back(info);
            if (monitoring_history.size() > MAX_HISTORY) {
                monitoring_history.erase(monitoring_history.begin());
            }
            return 1; // Return success to avoid detection
        }
    }

    LOGIO(LOG_COLOR_RED "=== ALLOWED CALL DETAIL [sub_2DAB74] ===" LOG_COLOR_RESET);
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Call Info:\n%s", info.string_param.c_str());

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    __int64 result = o_sub_2DAB74(a1, a2);

    LOGIO("Result: 0x%llx", result);
    LOGIO(LOG_COLOR_RED "=== END DETAIL [sub_2DAB74] ===" LOG_COLOR_RESET "\n");

    return result;
}

#endif //ARCAMOD_H_SUB_2DAB74_H