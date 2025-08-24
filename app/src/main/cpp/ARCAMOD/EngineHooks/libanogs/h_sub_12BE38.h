#ifndef ARCAMOD_H_SUB_12BE38_H
#define ARCAMOD_H_SUB_12BE38_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

__int64 (*o_sub_12BE38)(__int64 a1);

static __int64 __fastcall h_sub_12BE38(__int64 a1) {
    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    MonitoringInfo info;
    info.timestamp = std::time(nullptr);
    info.was_blocked = false;

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    info.offset = pointer_call - base_address;

    // Build parameter info string
    std::stringstream ss;
    ss << OBF("Parameters:\n");
    ss << OBF("a1: 0x") << std::hex << a1 << OBF("\n");

    info.string_param = ss.str();

    // Simple bypass conditions - uncomment to enable
    /*
    // Bypass if null parameter
    if (!a1) {
        info.was_blocked = true;
        LOGIO("[BYPASSED] sub_12BE38 - NULL parameter");
        LOGIO("[BYPASSED] Call from offset: 0x%lx", info.offset);
        monitoring_history.push_back(info);
        return 0; // Return success
    }

    // Bypass if invalid memory address
    if (a1 < 0x10000 || a1 > 0x7FFFFFFFFFFF) {
        info.was_blocked = true;
        LOGIO("[BYPASSED] sub_12BE38 - Invalid memory address");
        LOGIO("[BYPASSED] Call from offset: 0x%lx", info.offset);
        monitoring_history.push_back(info);
        return 0; // Return success
    }
    */

    // Call original function
    __int64 result = o_sub_12BE38(a1);

    LOGIO("=== ALLOWED CALL [sub_12BE38] ===");
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Result: %lld", result);
    LOGIO("Parameters:\n%s", info.string_param.c_str());
    LOGIO("=== END [sub_12BE38] ===\n");

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    return result;
}

#endif //ARCAMOD_H_SUB_12BE38_H
