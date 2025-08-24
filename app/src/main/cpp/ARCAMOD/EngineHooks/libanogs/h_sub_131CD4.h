#ifndef ARCAMOD_H_SUB_131CD4_H
#define ARCAMOD_H_SUB_131CD4_H

#include <string>
#include <vector>
#include <sstream>
#include <ctime>

__int64 (*o_sub_131CD4)(int a1, int a2, __int64 a3, unsigned __int64 a4, int a5, int a6, int a7, unsigned int a8, char *filename);

static __int64 __fastcall h_sub_131CD4(int a1, int a2, __int64 a3, unsigned __int64 a4, int a5, int a6, int a7, unsigned int a8, char *filename) {
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
    ss << OBF("width: ") << a1 << OBF("\n");
    ss << OBF("height: ") << a2 << OBF("\n");
    ss << OBF("image_data: 0x") << std::hex << a3 << OBF("\n");
    ss << OBF("size: ") << std::dec << a4 << OBF("\n");
    ss << OBF("param5: ") << a5 << OBF("\n");
    ss << OBF("param6: ") << a6 << OBF("\n");
    ss << OBF("format: ") << a7 << OBF("\n");
    ss << OBF("quality: ") << a8 << OBF("\n");
    ss << OBF("filename: ") << (filename ? filename : "NULL") << OBF("\n");

    info.string_param = ss.str();

    // Simple bypass conditions - uncomment to enable
    /*
    // Bypass if quality > 100
    if (a8 > 100) {
        info.was_blocked = true;
        LOGIO("[BYPASSED] sub_131CD4 - Quality too high: %u", a8);
        LOGIO("[BYPASSED] Call from offset: 0x%lx", info.offset);
        monitoring_history.push_back(info);
        return 1; // Return success
    }

    // Bypass if invalid parameters
    if (a1 < 1 || a2 < 1 || !a3 || !a4) {
        info.was_blocked = true;
        LOGIO("[BYPASSED] sub_131CD4 - Invalid parameters");
        LOGIO("[BYPASSED] Call from offset: 0x%lx", info.offset);
        monitoring_history.push_back(info);
        return 1; // Return success
    }

    // Bypass if null filename
    if (!filename) {
        info.was_blocked = true;
        LOGIO("[BYPASSED] sub_131CD4 - NULL filename");
        LOGIO("[BYPASSED] Call from offset: 0x%lx", info.offset);
        monitoring_history.push_back(info);
        return 1; // Return success
    }
    */

    // Call original function
    __int64 result = o_sub_131CD4(a1, a2, a3, a4, a5, a6, a7, a8, filename);

    LOGIO("=== ALLOWED CALL [sub_131CD4] ===");
    LOGIO("Timestamp: %lu", info.timestamp);
    LOGIO("Offset Call: 0x%lx", info.offset);
    LOGIO("Result: %lld", result);
    LOGIO("Parameters:\n%s", info.string_param.c_str());
    LOGIO("=== END [sub_131CD4] ===\n");

    monitoring_history.push_back(info);
    if (monitoring_history.size() > MAX_HISTORY) {
        monitoring_history.erase(monitoring_history.begin());
    }

    return result;
}

#endif //ARCAMOD_H_SUB_131CD4_H
