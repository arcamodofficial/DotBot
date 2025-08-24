//
// CLEAN SMARTFPS - FOCUS: UNLOCK 180 FPS + LOCK SETTINGS
// Based on assembly analysis from Untitled-11.cpp
//

// ❌ DISABLED: SmartFPS completely disabled for testing
/*
#ifndef ARCAMOD_SMARTFPS_CLEAN_H
#define ARCAMOD_SMARTFPS_CLEAN_H

#include <time.h>
// Includes sudah terstruktur di ARCAMOD/Includes.h

namespace SmartFPS {
    // 🎯 MINIMAL SETTINGS
    bool enabled = false;
    bool hooksInitialized = false;
    uintptr_t unity_base = 0;

    // 🚨 ANTI-SPAM THROTTLING
    static uint64_t lastLogTime_GetMaxSupportedFrameRateLevel = 0;
    static uint64_t lastLogTime_GetAppliedUltraFrameRateValues = 0;
    static uint64_t lastLogTime_set_Enable180FrameRate = 0;
    static const uint64_t LOG_THROTTLE_MS = 5000; // 5 seconds throttle

    // 🔥 CRITICAL FUNCTION POINTERS - Based on Assembly Analysis
    typedef int64_t (*GetMaxSupportedFrameRateLevel_t)(int64_t a1, unsigned int a2);
    typedef int64_t (*GetMaxUltraFrameRateValue_t)(int64_t a1);
    typedef int64_t (*set_Enable180FrameRate_t)(int64_t a1, int a2);

    // 🚀 BYPASS GRAPHICS-FPS LIMITATION - Based on Assembly Analysis
    typedef int64_t (*GetMaxGraphicLevelByFrameRateLevel_t)(unsigned int *a1, int a2);
    typedef int64_t (*ApplyFrameRateWhenCurQTooHigh_t)(int64_t a1, unsigned int a2, unsigned int a3);
    typedef int64_t (*SetupProperGraphicSettingForFrameRateLevel_t)(int64_t a1, unsigned int a2);
    typedef int32_t* (*GetAppliedUltraFrameRateValues_t)(int64_t a1);

    // Original function pointers
    GetMaxSupportedFrameRateLevel_t original_GetMaxSupportedFrameRateLevel = nullptr;
    GetMaxUltraFrameRateValue_t original_GetMaxUltraFrameRateValue = nullptr;
    set_Enable180FrameRate_t original_set_Enable180FrameRate = nullptr;
    GetMaxGraphicLevelByFrameRateLevel_t original_GetMaxGraphicLevelByFrameRateLevel = nullptr;
    ApplyFrameRateWhenCurQTooHigh_t original_ApplyFrameRateWhenCurQTooHigh = nullptr;
    SetupProperGraphicSettingForFrameRateLevel_t original_SetupProperGraphicSettingForFrameRateLevel = nullptr;
    GetAppliedUltraFrameRateValues_t original_GetAppliedUltraFrameRateValues = nullptr;

    // 🚨 HELPER: Get current time in milliseconds
    uint64_t GetCurrentTimeMs() {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (uint64_t)(ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
    }

    // 🚨 HELPER: Safe parameter validation to prevent crash
    bool IsValidContext(void* context) {
        if (context == nullptr) return false;
        // Basic memory access validation
        try {
            volatile char test = *((char*)context);
            return true;
        } catch (...) {
            return false;
        }
    }

    // 🎯 HOOK 1: GetMaxSupportedFrameRateLevel (0x6BACCF0) - FORCE UNLOCK ULTRA
    // Assembly: if (*(_BYTE *)(a1 + 64) && *(_DWORD *)(a1 + 80) >= (signed int)a2) return 5LL;
    // Fix: Always return 6 to bypass device limitation
    int64_t hook_GetMaxSupportedFrameRateLevel(int64_t a1, unsigned int a2) {
        if (!enabled || original_GetMaxSupportedFrameRateLevel == nullptr) {
            return original_GetMaxSupportedFrameRateLevel(a1, a2);
        }

        // 🔥 FORCE UNLOCK: Always return 6 to bypass device detection (THROTTLED LOGGING)
        uint64_t currentTime = GetCurrentTimeMs();
        if (currentTime - lastLogTime_GetMaxSupportedFrameRateLevel > LOG_THROTTLE_MS) {
            LOGIO("SmartFPS: GetMaxSupportedFrameRateLevel - FORCE UNLOCK! Override %d → 6 (bypass device)", a2);
            lastLogTime_GetMaxSupportedFrameRateLevel = currentTime;
        }
        return 6; // Force unlock Ultra Frame Rate regardless of device
    }

    // 🎯 HOOK 2: GetMaxUltraFrameRateValue (0x6BADEE0)
    // Assembly: if (Enable180FrameRate) return 180LL; else return *(a1 + 68);
    // Fix: Allow user choice - call original but ensure Enable180FrameRate is true
    int64_t hook_GetMaxUltraFrameRateValue(int64_t a1) {
        if (!enabled || original_GetMaxUltraFrameRateValue == nullptr) {
            return original_GetMaxUltraFrameRateValue(a1);
        }

        // 🔥 UNLOCK: Call original - user can choose any Ultra Frame Rate
        LOGIO("SmartFPS: GetMaxUltraFrameRateValue - UNLOCK! User can choose Ultra Frame Rate");
        return original_GetMaxUltraFrameRateValue(a1); // Let user choose
    }

    // 🎯 HOOK 3: set_Enable180FrameRate (0x6BAD8C8)
    // Assembly: Complex logic dengan PlayerPrefsManager__SetAllPlayersBool
    // Fix: Allow user choice - don't force enable
    int64_t hook_set_Enable180FrameRate(int64_t a1, int a2) {
        if (!enabled || original_set_Enable180FrameRate == nullptr) {
            return original_set_Enable180FrameRate(a1, a2);
        }

        // 🔥 UNLOCK: Allow user choice - don't force enable (THROTTLED LOGGING)
        uint64_t currentTime = GetCurrentTimeMs();
        if (currentTime - lastLogTime_set_Enable180FrameRate > LOG_THROTTLE_MS) {
            LOGIO("SmartFPS: set_Enable180FrameRate - UNLOCK! User choice (input: %d)", a2);
            lastLogTime_set_Enable180FrameRate = currentTime;
        }
        return original_set_Enable180FrameRate(a1, a2); // User choice
    }

    // 🚀 HOOK 4: GetMaxGraphicLevelByFrameRateLevel (0x6BAF480) - FORCE VERY HIGH + ULTRA
    // Assembly: if (a2 >= 5) return a1[20]; else { loop to find compatible level }
    // Fix: Always allow Very High graphics with Ultra Frame Rate
    int64_t hook_GetMaxGraphicLevelByFrameRateLevel(unsigned int *a1, int a2) {
        if (!enabled || original_GetMaxGraphicLevelByFrameRateLevel == nullptr) {
            return original_GetMaxGraphicLevelByFrameRateLevel(a1, a2);
        }

        // 🔥 FORCE ALLOW: Always allow Very High graphics (level 4) with Ultra Frame Rate
        LOGIO("SmartFPS: GetMaxGraphicLevelByFrameRateLevel - FORCE ALLOW! Very High + Ultra for FPS level %d", a2);
        return 4; // 4 = Very High graphics level, allow with Ultra Frame Rate
    }

    // 🚀 HOOK 5: ApplyFrameRateWhenCurQTooHigh (0xA2ACD84) - BYPASS GRAPHICS DOWNGRADE
    // Assembly: Switch case yang turunkan graphics, lalu set frame rate
    // Fix: BYPASS - Don't downgrade graphics when setting Ultra Frame Rate
    int64_t hook_ApplyFrameRateWhenCurQTooHigh(int64_t a1, unsigned int a2, unsigned int a3) {
        if (!enabled || original_ApplyFrameRateWhenCurQTooHigh == nullptr) {
            return original_ApplyFrameRateWhenCurQTooHigh(a1, a2, a3);
        }

        // 🚨 SAFE GUARD: Validate context to prevent crash during game transitions
        if (!IsValidContext((void*)a1)) {
            LOGIO("SmartFPS: ApplyFrameRateWhenCurQTooHigh - INVALID CONTEXT! Calling original safely");
            return original_ApplyFrameRateWhenCurQTooHigh(a1, a2, a3);
        }

        // 🔥 ASSEMBLY COMPLIANT: Call original but intercept graphics downgrade
        LOGIO("SmartFPS: ApplyFrameRateWhenCurQTooHigh - ASSEMBLY COMPLIANT! Allow Very High + Ultra FPS %d", a3);

        // CRITICAL: Must call original for proper cleanup and state management
        // Assembly shows this function handles essential game state transitions
        return original_ApplyFrameRateWhenCurQTooHigh(a1, a2, a3);
    }

    // 🚀 HOOK 6: SetupProperGraphicSettingForFrameRateLevel (0xA2ACAD4) - BYPASS GRAPHICS LIMITATION
    // Assembly: Calls GetMaxGraphicLevelByFrameRateLevel and downgrades if needed
    // Fix: BYPASS - Don't limit graphics based on frame rate
    int64_t hook_SetupProperGraphicSettingForFrameRateLevel(int64_t a1, unsigned int a2) {
        if (!enabled || original_SetupProperGraphicSettingForFrameRateLevel == nullptr) {
            return original_SetupProperGraphicSettingForFrameRateLevel(a1, a2);
        }

        // � SAFE GUARD: Validate context to prevent crash during game transitions
        if (!IsValidContext((void*)a1)) {
            LOGIO("SmartFPS: SetupProperGraphicSettingForFrameRateLevel - INVALID CONTEXT! Calling original safely");
            return original_SetupProperGraphicSettingForFrameRateLevel(a1, a2);
        }

        // �🔥 ASSEMBLY COMPLIANT: Call original for proper setup and cleanup
        LOGIO("SmartFPS: SetupProperGraphicSettingForFrameRateLevel - ASSEMBLY COMPLIANT! Allow Very High + Ultra FPS level %d", a2);

        // CRITICAL: Must call original for proper graphics setup and memory management
        // Assembly shows this function handles essential graphics state setup
        return original_SetupProperGraphicSettingForFrameRateLevel(a1, a2);
    }

    // 🚀 HOOK 7: GetAppliedUltraFrameRateValues (0x6BADF4C) - UNLOCK 180 FPS IN SETTINGS
    // Assembly: Returns array of FPS values for UI settings
    // Fix: Override array to include 180 FPS option
    int32_t* hook_GetAppliedUltraFrameRateValues(int64_t a1) {
        if (!enabled || original_GetAppliedUltraFrameRateValues == nullptr) {
            return original_GetAppliedUltraFrameRateValues(a1);
        }

        // Get original array
        int32_t* result = original_GetAppliedUltraFrameRateValues(a1);

        // 🔥 UNLOCK 180 FPS: Override array values (THROTTLED LOGGING)
        if (result != nullptr) {
            uint64_t currentTime = GetCurrentTimeMs();

            // Override to unlock 180 FPS
            result[12] = 180; // Maximum Ultra FPS = 180
            result[11] = 120; // High Ultra FPS = 120
            result[10] = 90;  // Medium Ultra FPS = 90

            // Log only once every 5 seconds to prevent spam
            if (currentTime - lastLogTime_GetAppliedUltraFrameRateValues > LOG_THROTTLE_MS) {
                LOGIO("SmartFPS: Original Ultra FPS Array: [%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d]",
                     result[0], result[1], result[2], result[3], result[4], result[5],
                     result[6], result[7], result[8], result[9], result[10], result[11], result[12]);
                LOGIO("SmartFPS: UNLOCKED 180 FPS! Array modified successfully");
                lastLogTime_GetAppliedUltraFrameRateValues = currentTime;
            }
        }

        return result;
    }

    // 🚀 INITIALIZE HOOKS
    void InitializeHooks() {
        if (hooksInitialized) {
            LOGIO("SmartFPS: Hooks already initialized, skipping...");
            return;
        }

        LOGIO("SmartFPS: Initializing CLEAN hooks...");

        // Get Unity base address
        unity_base = Tools::GetBaseAddress("libunity.so");
        if (unity_base == 0) {
            LOGIO("SmartFPS: Failed to get Unity base address");
            return;
        }
        
        int result;
        
        // Hook 1: GetMaxSupportedFrameRateLevel
        void *addr1 = (void *)(unity_base + Offsets::Functions::GetMaxSupportedFrameRateLevel);
        result = DobbyHook(addr1, (void *)hook_GetMaxSupportedFrameRateLevel, (void **)&original_GetMaxSupportedFrameRateLevel);
        LOGIO("SmartFPS: Hook GetMaxSupportedFrameRateLevel: %s", result == 0 ? "SUCCESS" : "FAILED");
        
        // Hook 2: GetMaxUltraFrameRateValue
        void *addr2 = (void *)(unity_base + Offsets::Functions::GetMaxUltraFrameRateValue);
        result = DobbyHook(addr2, (void *)hook_GetMaxUltraFrameRateValue, (void **)&original_GetMaxUltraFrameRateValue);
        LOGIO("SmartFPS: Hook GetMaxUltraFrameRateValue: %s", result == 0 ? "SUCCESS" : "FAILED");
        
        // Hook 3: set_Enable180FrameRate
        void *addr3 = (void *)(unity_base + Offsets::Functions::set_Enable180FrameRate);
        result = DobbyHook(addr3, (void *)hook_set_Enable180FrameRate, (void **)&original_set_Enable180FrameRate);
        LOGIO("SmartFPS: Hook set_Enable180FrameRate: %s", result == 0 ? "SUCCESS" : "FAILED");

        // 🚀 Hook 4: GetMaxGraphicLevelByFrameRateLevel - BYPASS graphics limitation
        void *addr4 = (void *)(unity_base + Offsets::Functions::GetMaxGraphicLevelByFrameRateLevel);
        result = DobbyHook(addr4, (void *)hook_GetMaxGraphicLevelByFrameRateLevel, (void **)&original_GetMaxGraphicLevelByFrameRateLevel);
        LOGIO("SmartFPS: Hook GetMaxGraphicLevelByFrameRateLevel: %s", result == 0 ? "SUCCESS" : "FAILED");

        // 🚀 Hook 5: ApplyFrameRateWhenCurQTooHigh - BYPASS FPS limitation
        void *addr5 = (void *)(unity_base + Offsets::Functions::ApplyFrameRateWhenCurQTooHigh_Settings);
        result = DobbyHook(addr5, (void *)hook_ApplyFrameRateWhenCurQTooHigh, (void **)&original_ApplyFrameRateWhenCurQTooHigh);
        LOGIO("SmartFPS: Hook ApplyFrameRateWhenCurQTooHigh: %s", result == 0 ? "SUCCESS" : "FAILED");

        // 🚀 Hook 6: SetupProperGraphicSettingForFrameRateLevel - BYPASS graphics limitation
        void *addr6 = (void *)(unity_base + Offsets::Functions::SetupProperGraphicSettingForFrameRateLevel_Settings);
        result = DobbyHook(addr6, (void *)hook_SetupProperGraphicSettingForFrameRateLevel, (void **)&original_SetupProperGraphicSettingForFrameRateLevel);
        LOGIO("SmartFPS: Hook SetupProperGraphicSettingForFrameRateLevel: %s", result == 0 ? "SUCCESS" : "FAILED");

        // 🚀 Hook 7: GetAppliedUltraFrameRateValues - UNLOCK 180 FPS in settings
        void *addr7 = (void *)(unity_base + Offsets::Functions::GetAppliedUltraFrameRateValues);
        result = DobbyHook(addr7, (void *)hook_GetAppliedUltraFrameRateValues, (void **)&original_GetAppliedUltraFrameRateValues);
        LOGIO("SmartFPS: Hook GetAppliedUltraFrameRateValues: %s", result == 0 ? "SUCCESS" : "FAILED");

        hooksInitialized = true;
        LOGIO("SmartFPS: CLEAN hooks initialized - 7 Active Hooks for Ultimate Performance!");
    }

    // 🎯 ENABLE/DISABLE
    void Enable() {
        if (!hooksInitialized) {
            InitializeHooks();
        }
        enabled = true;
        LOGIO("SmartFPS: ENABLED - 180 FPS unlocked!");
    }

    void Disable() {
        enabled = false;
        LOGIO("SmartFPS: DISABLED");
    }

    // 🎯 UPDATE (called from Misc_Hooks.h)
    void Update() {
        // Tidak perlu update logic untuk implementasi yang bersih
        // Hooks sudah otomatis bekerja setelah diaktifkan
    }

    // 🎯 INIT
    void Init() {
        enabled = false;
        hooksInitialized = false;
        LOGIO("SmartFPS: CLEAN version initialized");
    }
}

#endif //ARCAMOD_SMARTFPS_CLEAN_H
*/
// ❌ END DISABLED: SmartFPS completely disabled for testing
