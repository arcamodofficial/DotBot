#ifndef ARCAMOD_ULTRAFPSGRAPHICUNLOCK_H
#define ARCAMOD_ULTRAFPSGRAPHICUNLOCK_H

#include <time.h>

namespace UltraFPSGraphicUnlock {
    bool enabled = false;
    bool hooksInitialized = false;
    uintptr_t unity_base = 0;

    typedef int64_t (*GetMaxSupportedFrameRateLevel_t)(int64_t a1, unsigned int a2);
    typedef int64_t (*GetMaxGraphicLevelByFrameRateLevel_t)(unsigned int *a1, int a2);
    typedef int64_t (*ApplyFrameRateWhenCurQTooHigh_t)(int64_t a1, unsigned int a2, unsigned int a3);
    typedef int64_t (*SetupProperGraphicSettingForFrameRateLevel_t)(int64_t a1, unsigned int a2);
    typedef int32_t* (*GetAppliedUltraFrameRateValues_t)(int64_t a1);

    GetMaxSupportedFrameRateLevel_t original_GetMaxSupportedFrameRateLevel = nullptr;
    GetMaxGraphicLevelByFrameRateLevel_t original_GetMaxGraphicLevelByFrameRateLevel = nullptr;
    ApplyFrameRateWhenCurQTooHigh_t original_ApplyFrameRateWhenCurQTooHigh = nullptr;
    SetupProperGraphicSettingForFrameRateLevel_t original_SetupProperGraphicSettingForFrameRateLevel = nullptr;
    GetAppliedUltraFrameRateValues_t original_GetAppliedUltraFrameRateValues = nullptr;

    static bool IsValidContext(void* context) {
        return context != nullptr && (uintptr_t)context > 0x1000;
    }


    static int64_t hook_GetMaxSupportedFrameRateLevel(int64_t a1, unsigned int a2) {
        if (!enabled || original_GetMaxSupportedFrameRateLevel == nullptr) {
            return original_GetMaxSupportedFrameRateLevel(a1, a2);
        }

        return 6;
    }

    static int64_t hook_GetMaxGraphicLevelByFrameRateLevel(unsigned int *a1, int a2) {
        if (!enabled || original_GetMaxGraphicLevelByFrameRateLevel == nullptr) {
            return original_GetMaxGraphicLevelByFrameRateLevel(a1, a2);
        }

        if (a2 >= 5) {
            return 4;
        }

        return original_GetMaxGraphicLevelByFrameRateLevel(a1, a2);
    }

    static int64_t hook_ApplyFrameRateWhenCurQTooHigh(int64_t a1, unsigned int a2, unsigned int a3) {
        if (!enabled || original_ApplyFrameRateWhenCurQTooHigh == nullptr) {
            return original_ApplyFrameRateWhenCurQTooHigh(a1, a2, a3);
        }

        if (!IsValidContext((void*)a1)) {
            return original_ApplyFrameRateWhenCurQTooHigh(a1, a2, a3);
        }

        if (a2 >= 3 && a3 >= 5) {
            return 0;
        }

        return original_ApplyFrameRateWhenCurQTooHigh(a1, a2, a3);
    }

    static int64_t hook_SetupProperGraphicSettingForFrameRateLevel(int64_t a1, unsigned int a2) {
        if (!enabled || original_SetupProperGraphicSettingForFrameRateLevel == nullptr) {
            return original_SetupProperGraphicSettingForFrameRateLevel(a1, a2);
        }

        if (!IsValidContext((void*)a1)) {
            return original_SetupProperGraphicSettingForFrameRateLevel(a1, a2);
        }

        return original_SetupProperGraphicSettingForFrameRateLevel(a1, a2);
    }

    static int32_t* hook_GetAppliedUltraFrameRateValues(int64_t a1) {
        if (!enabled || original_GetAppliedUltraFrameRateValues == nullptr) {
            return original_GetAppliedUltraFrameRateValues(a1);
        }

        return original_GetAppliedUltraFrameRateValues(a1);
    }

    static void InitializeHooks() {
        if (hooksInitialized) {
            return;
        }

        unity_base = Tools::GetBaseAddress(OBF("libunity.so"));
        if (unity_base == 0) {
            // LOGIO("UltraFPSGraphicUnlock: Failed to get Unity base address!");
            return;
        }

        int result;
        bool anyHookFailed = false;

        void *addr1 = (void *)(unity_base + Offsets::Functions::GetMaxSupportedFrameRateLevel);
        result = DobbyHook(addr1, (void *)hook_GetMaxSupportedFrameRateLevel, (void **)&original_GetMaxSupportedFrameRateLevel);
        if (result != 0) anyHookFailed = true;

        void *addr2 = (void *)(unity_base + Offsets::Functions::GetMaxGraphicLevelByFrameRateLevel);
        result = DobbyHook(addr2, (void *)hook_GetMaxGraphicLevelByFrameRateLevel, (void **)&original_GetMaxGraphicLevelByFrameRateLevel);
        if (result != 0) anyHookFailed = true;

        void *addr3 = (void *)(unity_base + Offsets::Functions::ApplyFrameRateWhenCurQTooHigh_Settings);
        result = DobbyHook(addr3, (void *)hook_ApplyFrameRateWhenCurQTooHigh, (void **)&original_ApplyFrameRateWhenCurQTooHigh);
        if (result != 0) anyHookFailed = true;

        void *addr4 = (void *)(unity_base + Offsets::Functions::SetupProperGraphicSettingForFrameRateLevel_Settings);
        result = DobbyHook(addr4, (void *)hook_SetupProperGraphicSettingForFrameRateLevel, (void **)&original_SetupProperGraphicSettingForFrameRateLevel);
        if (result != 0) anyHookFailed = true;

        void *addr5 = (void *)(unity_base + Offsets::Functions::GetAppliedUltraFrameRateValues);
        result = DobbyHook(addr5, (void *)hook_GetAppliedUltraFrameRateValues, (void **)&original_GetAppliedUltraFrameRateValues);
        if (result != 0) anyHookFailed = true;

        hooksInitialized = true;
    }

    static void Enable() {
        enabled = true;
        // LOGIO("UltraFPSGraphicUnlock: ENABLED - High Graphic + Ultra FPS unlocked!");
    }

    static void Disable() {
        enabled = false;
        // LOGIO("UltraFPSGraphicUnlock: DISABLED");
    }

    static bool IsEnabled() {
        return enabled;
    }

    static bool IsInitialized() {
        return hooksInitialized;
    }
}

#endif //ARCAMOD_ULTRAFPSGRAPHICUNLOCK_H