#ifndef ARCAMOD_SKIINGBOOST_H
#define ARCAMOD_SKIINGBOOST_H

#include <cstdint>

typedef float (*original_skiing_max_speed_func)(int64_t a1);
typedef float (*original_skiing_slop_max_speed_func)(int64_t a1);
typedef float (*original_skiing_speedup_func)(int64_t a1);
typedef float (*original_skiing_move_max_speed_func)(int64_t a1);
typedef float (*original_skiing_speed_kph_func)(int64_t a1);

original_skiing_max_speed_func originalSkiingMaxSpeedFunc = nullptr;
original_skiing_slop_max_speed_func originalSkiingSlopMaxSpeedFunc = nullptr;
original_skiing_speedup_func originalSkiingSpeedUpFunc = nullptr;
original_skiing_move_max_speed_func originalSkiingMoveMaxSpeedFunc = nullptr;
original_skiing_speed_kph_func originalSkiingSpeedKphFunc = nullptr;

static float SkiingMaxSpeedHook(int64_t a1) {
    float originalSpeed = originalSkiingMaxSpeedFunc(a1);

    if (Config.Misc.SkiingBoost) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.SkiingBoost;
        return modifiedSpeed;
    }

    return originalSpeed;
}

static float SkiingSlopMaxSpeedHook(int64_t a1) {
    float originalSpeed = originalSkiingSlopMaxSpeedFunc(a1);

    if (Config.Misc.SkiingBoost) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.SkiingBoost;
        return modifiedSpeed;
    }

    return originalSpeed;
}

static float SkiingSpeedUpHook(int64_t a1) {
    float originalSpeed = originalSkiingSpeedUpFunc(a1);

    if (Config.Misc.SkiingBoost) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.SkiingBoost;
        return modifiedSpeed;
    }

    return originalSpeed;
}

static float SkiingMoveMaxSpeedHook(int64_t a1) {
    float originalSpeed = originalSkiingMoveMaxSpeedFunc(a1);

    if (Config.Misc.SkiingBoost) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.SkiingBoost;
        return modifiedSpeed;
    }

    return originalSpeed;
}

static float SkiingSpeedKphHook(int64_t a1) {
    float originalSpeed = originalSkiingSpeedKphFunc(a1);

    if (Config.Misc.SkiingBoost) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.SkiingBoost;
        return modifiedSpeed;
    }

    return originalSpeed;
}

static bool skiingBoostInitialized = false;

static bool SetupSkiingBoostHooks() {
    bool hookSuccessful = true;

    uintptr_t skiingMaxSpeedAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkiingBoost_MaxSpeed);
    if (skiingMaxSpeedAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSkiingMaxSpeedFunc = (original_skiing_max_speed_func) skiingMaxSpeedAddr;
        bool maxSpeedHookResult = Tools::Hook((void *) skiingMaxSpeedAddr, (void *) SkiingMaxSpeedHook,
                                              (void **) &originalSkiingMaxSpeedFunc);
        if (!maxSpeedHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t skiingSlopMaxSpeedAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkiingBoost_SlopMaxSpeed);
    if (skiingSlopMaxSpeedAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSkiingSlopMaxSpeedFunc = (original_skiing_slop_max_speed_func) skiingSlopMaxSpeedAddr;
        bool slopMaxSpeedHookResult = Tools::Hook((void *) skiingSlopMaxSpeedAddr, (void *) SkiingSlopMaxSpeedHook,
                                                  (void **) &originalSkiingSlopMaxSpeedFunc);
        if (!slopMaxSpeedHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t skiingSpeedUpAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkiingBoost_SpeedUp);
    if (skiingSpeedUpAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSkiingSpeedUpFunc = (original_skiing_speedup_func) skiingSpeedUpAddr;
        bool speedUpHookResult = Tools::Hook((void *) skiingSpeedUpAddr, (void *) SkiingSpeedUpHook,
                                             (void **) &originalSkiingSpeedUpFunc);
        if (!speedUpHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t skiingMoveMaxSpeedAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkiingBoost_MoveMaxSpeed);
    if (skiingMoveMaxSpeedAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSkiingMoveMaxSpeedFunc = (original_skiing_move_max_speed_func) skiingMoveMaxSpeedAddr;
        bool moveMaxSpeedHookResult = Tools::Hook((void *) skiingMoveMaxSpeedAddr, (void *) SkiingMoveMaxSpeedHook,
                                                  (void **) &originalSkiingMoveMaxSpeedFunc);
        if (!moveMaxSpeedHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t skiingSpeedKphAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkiingBoost_SpeedKph);
    if (skiingSpeedKphAddr == 0) {
        // Ini optional, jadi tidak mempengaruhi hookSuccessful
    } else {
        originalSkiingSpeedKphFunc = (original_skiing_speed_kph_func) skiingSpeedKphAddr;
        Tools::Hook((void *) skiingSpeedKphAddr, (void *) SkiingSpeedKphHook,
                    (void **) &originalSkiingSpeedKphFunc);
    }

    return hookSuccessful;
}

static void HandleSkiingBoost() {
    if (Config.Misc.SkiingBoost) {
        if (!skiingBoostInitialized) {
            if (SetupSkiingBoostHooks()) {
                skiingBoostInitialized = true;
                Config.MiscHook.SkiingBoostPatchReady = true;
            }
        }
    } else {
        if (Config.MiscHook.SkiingBoostPatchReady) {
            Config.MiscHook.SkiingBoostPatchReady = false;
        }
    }
}

#endif //ARCAMOD_SKIINGBOOST_H