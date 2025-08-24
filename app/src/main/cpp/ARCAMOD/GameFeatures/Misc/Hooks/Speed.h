#ifndef ARCAMOD_SPEED_H
#define ARCAMOD_SPEED_H

#include <cstdint>

#define ADDR_MAXMOVESPEED OBF(MISC_Speed_MaxMoveSpeed)
#define ADDR_CALCFINALMOVESCALE OBF(MISC_Speed_CalcFinalMoveScale)

typedef float (*original_maxmove_speed_func)(int64_t a1);
typedef long double (*original_calcfinal_move_scale_func)(int64_t a1);

original_maxmove_speed_func originalMaxMoveSpeedFunction = nullptr;
original_calcfinal_move_scale_func originalCalcFinalMoveScaleFunction = nullptr;

static bool logOnce = false;
static bool speedHooksInstalled = false;
static bool speedActive = false;
static bool speedInitialized = false;

static float MaxMoveSpeedHook(int64_t a1) {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    float originalSpeed = originalMaxMoveSpeedFunction(a1);

    if (!isInActiveMatch) {
        static int speedMaxMoveGameStateCounter = 0;
        if (++speedMaxMoveGameStateCounter % 600 == 0) {
            // LOGIO("MaxMoveSpeedHook: Game tidak dalam pertandingan aktif (MatchInProgress=false). Speed MaxMoveSpeed Hook tidak aktif.");
            speedMaxMoveGameStateCounter = 0;
        }
        return originalSpeed;
    }

    if (!Config.Misc.Speed || !Config.Init.IL2CppReady) {
        static int speedMaxMoveFeatureCounter = 0;
        if (++speedMaxMoveFeatureCounter % 600 == 0) {
            // LOGIO("MaxMoveSpeedHook: Fitur Speed dinonaktifkan atau IL2Cpp belum siap. Speed MaxMoveSpeed Hook tidak aktif.");
            speedMaxMoveFeatureCounter = 0;
        }
        return originalSpeed;
    }

    if (speedActive) {
        float modifiedSpeed = originalSpeed * Config.MiscSize.Speed;

        static int speedMaxMoveHookCounter = 0;
        if (++speedMaxMoveHookCounter % 600 == 0) {
            // LOGIO("MaxMoveSpeedHook: Speed MaxMoveSpeed Hook aktif dalam pertandingan. Faktor speed: %.2f", Config.MiscSize.Speed);
            speedMaxMoveHookCounter = 0;
        }

        return modifiedSpeed;
    }

    return originalSpeed;
}

static long double CalcFinalMoveScaleHook(int64_t a1) {
    bool isInActiveMatch = false;
    void* preCheckMatchGame = GamePlay$$get_MatchGame();
    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    long double originalScale = originalCalcFinalMoveScaleFunction(a1);

    if (!isInActiveMatch || !Config.Misc.Speed || !Config.Init.IL2CppReady) {
        return originalScale;
    }

    if (speedActive) {
        float modifiedScale = *(float *) &originalScale * Config.MiscSize.Speed;
        return *(long double *) &modifiedScale;
    }

    return originalScale;
}

static bool SetupSpeedHooks() {
    if (speedHooksInstalled) {
        // LOGIO("Speed hooks already installed, skipping");
        return true;
    }

    bool hookSuccessful = true;

    uintptr_t maxSpeedAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MAXMOVESPEED);

    if (maxSpeedAddr == 0) {
        // LOGEO("Failed to get address for MaxMoveSpeed");
        hookSuccessful = false;
    } else {
        originalMaxMoveSpeedFunction = (original_maxmove_speed_func) maxSpeedAddr;
        bool maxSpeedHookResult = Tools::Hook((void *) maxSpeedAddr, (void *) MaxMoveSpeedHook,
                                              (void **) &originalMaxMoveSpeedFunction);

        if (!maxSpeedHookResult) {
            // LOGEO("Failed to hook MaxMoveSpeed function");
            hookSuccessful = false;
        }
    }

    uintptr_t moveScaleAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_CALCFINALMOVESCALE);

    if (moveScaleAddr == 0) {
        // LOGEO("Failed to get address for CalcFinalMoveScale");
        hookSuccessful = false;
    } else {
        originalCalcFinalMoveScaleFunction = (original_calcfinal_move_scale_func) moveScaleAddr;
        bool moveScaleHookResult = Tools::Hook((void *) moveScaleAddr,
                                               (void *) CalcFinalMoveScaleHook,
                                               (void **) &originalCalcFinalMoveScaleFunction);

        if (!moveScaleHookResult) {
            // LOGEO("Failed to hook CalcFinalMoveScale function");
            hookSuccessful = false;
        }
    }

    speedHooksInstalled = hookSuccessful;

    if (hookSuccessful) {
        // LOGIO("Speed hooks installed successfully");
    } else {
        // LOGEO("Failed to install some Speed hooks");
    }

    return hookSuccessful;
}

static void HandleSpeed() {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        static int handleSpeedGameStateCounter = 0;
        if (++handleSpeedGameStateCounter % 900 == 0) {
            // LOGIO("HandleSpeed: Game tidak dalam pertandingan aktif (MatchInProgress=false). HandleSpeed tidak aktif.");
            handleSpeedGameStateCounter = 0;
        }
        return;
    }

    if (!Config.Misc.Speed || !Config.Init.IL2CppReady) {
        static int handleSpeedFeatureCounter = 0;
        if (++handleSpeedFeatureCounter % 900 == 0) {
            // LOGIO("HandleSpeed: Fitur Speed dinonaktifkan atau IL2Cpp belum siap. HandleSpeed tidak aktif.");
            handleSpeedFeatureCounter = 0;
        }
        return;
    }

    if (Config.Misc.Speed) {
        if (!speedInitialized) {
            if (SetupSpeedHooks()) {
                speedInitialized = true;

                static int handleSpeedSetupCounter = 0;
                if (++handleSpeedSetupCounter % 900 == 0) {
                    // LOGIO("HandleSpeed: Berhasil memasang Speed Hook dalam pertandingan aktif.");
                    handleSpeedSetupCounter = 0;
                }
            }
        }

        speedActive = true;
        Config.MiscHook.SpeedPatchReady = true;

        static float lastSpeedValue = 0.0f;
        if (lastSpeedValue != Config.MiscSize.Speed) {
            // LOGIO("HandleSpeed: Speed value changed to %.2f", Config.MiscSize.Speed);
            lastSpeedValue = Config.MiscSize.Speed;
            logOnce = false;
        }
    } else {
        speedActive = false;
        Config.MiscHook.SpeedPatchReady = false;
    }
}

#endif //ARCAMOD_SPEED_H