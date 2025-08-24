#ifndef ARCAMOD_SLIDE_H
#define ARCAMOD_SLIDE_H

#include <cstdint>

typedef float (*original_slide_accel_func)(int64_t a1);
typedef float (*original_slide_speed_func)(int64_t a1);
typedef int64_t (*original_max_speed_func)(int64_t a1);
typedef void (*original_super_slide_rate_func)(int64_t a1);
typedef int64_t (*original_tick_player_func)(int64_t a1, long double a2);

original_slide_accel_func originalSlideAccelFunction = nullptr;
original_slide_speed_func originalSlideSpeedFunction = nullptr;
original_max_speed_func originalMaxSpeedFunction = nullptr;
original_super_slide_rate_func originalSuperSlideRateFunction = nullptr;
original_tick_player_func originalTickPlayerFunction = nullptr;

static float SlideAccelHook(int64_t a1) {
    float originalAccel = originalSlideAccelFunction(a1);

    if (Config.Misc.Slide) {
        float modifiedAccel = originalAccel * Config.MiscSize.Slide;
        return modifiedAccel;
    }

    return originalAccel;
}

static float SlideSpeedHook(int64_t a1) {
    float originalSpeed = originalSlideSpeedFunction(a1);

    if (Config.Misc.Slide) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.Slide;
        return modifiedSpeed;
    }

    return originalSpeed;
}

static int64_t MaxSpeedHook(int64_t a1) {
    int64_t originalValue = originalMaxSpeedFunction(a1);

    if (Config.Misc.Slide) {
        int64_t newValue = originalValue;
        if (Config.MiscSize.Slide > 1.0f) {
            newValue = originalValue * Config.MiscSize.Slide;
        }
        return newValue;
    }

    return originalValue;
}

static void SuperSlideRateHook(int64_t a1) {
    if (Config.Misc.Slide) {
        originalSuperSlideRateFunction(a1);
    } else {
        originalSuperSlideRateFunction(a1);
    }
}

static int64_t TickPlayerHook(int64_t a1, long double a2) {
    if (Config.Misc.Slide) {
        long double modifiedDeltaTime = a2 * Config.MiscSize.Slide;
        return originalTickPlayerFunction(a1, modifiedDeltaTime);
    }

    return originalTickPlayerFunction(a1, a2);
}

static bool slideInitialized = false;

static bool SetupSlideHooks() {
    bool hookSuccessful = true;

    uintptr_t slideAccelAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Slide_SlideAccel);

    if (slideAccelAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSlideAccelFunction = (original_slide_accel_func) slideAccelAddr;
        bool accelHookResult = Tools::Hook((void *) slideAccelAddr, (void *) SlideAccelHook,
                                           (void **) &originalSlideAccelFunction);

        if (!accelHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t slideSpeedAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Slide_SlideSpeed);

    if (slideSpeedAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSlideSpeedFunction = (original_slide_speed_func) slideSpeedAddr;
        bool speedHookResult = Tools::Hook((void *) slideSpeedAddr, (void *) SlideSpeedHook,
                                           (void **) &originalSlideSpeedFunction);

        if (!speedHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t maxSpeedAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Slide_MaxSpeed);

    if (maxSpeedAddr == 0) {
        hookSuccessful = false;
    } else {
        originalMaxSpeedFunction = (original_max_speed_func) maxSpeedAddr;
        bool maxSpeedHookResult = Tools::Hook((void *) maxSpeedAddr, (void *) MaxSpeedHook,
                                              (void **) &originalMaxSpeedFunction);

        if (!maxSpeedHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t superSlideAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Slide_SuperSlideRate);

    if (superSlideAddr == 0) {
        hookSuccessful = false;
    } else {
        originalSuperSlideRateFunction = (original_super_slide_rate_func) superSlideAddr;
        bool superSlideHookResult = Tools::Hook((void *) superSlideAddr,
                                                (void *) SuperSlideRateHook,
                                                (void **) &originalSuperSlideRateFunction);

        if (!superSlideHookResult) {
            hookSuccessful = false;
        }
    }

    uintptr_t tickPlayerAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Slide_TickLocalPlayer);

    if (tickPlayerAddr == 0) {
        hookSuccessful = false;
    } else {
        originalTickPlayerFunction = (original_tick_player_func) tickPlayerAddr;
        bool tickPlayerHookResult = Tools::Hook((void *) tickPlayerAddr, (void *) TickPlayerHook,
                                                (void **) &originalTickPlayerFunction);

        if (!tickPlayerHookResult) {
            hookSuccessful = false;
        }
    }

    return hookSuccessful;
}

static void HandleSlide() {
    if (Config.Misc.Slide) {
        if (!slideInitialized) {
            if (SetupSlideHooks()) {
                slideInitialized = true;
                Config.MiscHook.SlidePatchReady = true;
            }
        }
    } else {
        if (Config.MiscHook.SlidePatchReady) {
            Config.MiscHook.SlidePatchReady = false;
        }
    }
}

#endif //ARCAMOD_SLIDE_H