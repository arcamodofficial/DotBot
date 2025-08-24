#ifndef ARCAMOD_SKYDIVING_H
#define ARCAMOD_SKYDIVING_H

#include <cstdint>
#include <ctime>

typedef float (*original_get_max_velocity_forward_func)(int64_t a1);
typedef float (*original_get_acceleration_forward_func)(int64_t a1);
typedef float (*original_get_max_velocity_speedup_func)(int64_t a1);
typedef float (*original_get_max_velocity_speeddown_func)(int64_t a1);
typedef float (*original_get_init_velocity_func)(int64_t a1);
typedef int64_t (*original_skydiving_tick_func)(int64_t thisPtr, float deltaTime);
typedef float (*original_get_forward_func)(int64_t thisPtr);
typedef void (*original_update_velocity_gravity_func)(int64_t thisPtr, float a2, float a3);
typedef void (*original_update_skydiving_stage_func)(int64_t thisPtr, float deltaTime);
typedef int64_t (*original_update_pawn_rotation_func)(int64_t thisPtr, float deltaTime);

original_get_max_velocity_forward_func originalGetMaxVelocityForward = nullptr;
original_get_acceleration_forward_func originalGetAccelerationForward = nullptr;
original_get_max_velocity_speedup_func originalGetMaxVelocitySpeedUp = nullptr;
original_get_max_velocity_speeddown_func originalGetMaxVelocitySpeedDown = nullptr;
original_get_init_velocity_func originalGetInitVelocity = nullptr;
original_skydiving_tick_func originalSkydivingTick = nullptr;
original_get_forward_func originalGetForward = nullptr;
original_update_velocity_gravity_func originalUpdateVelocityGravity = nullptr;
original_update_skydiving_stage_func originalUpdateSkydivingStage = nullptr;
original_update_pawn_rotation_func originalUpdatePawnRotation = nullptr;

static bool maxVelocityHookInstalled = false;
static bool accelerationHookInstalled = false;
static bool speedUpHookInstalled = false;
static bool speedDownHookInstalled = false;
static bool initVelocityHookInstalled = false;
static bool tickHookInstalled = false;
static bool forwardHookInstalled = false;
static bool gravityHookInstalled = false;
static bool stageHookInstalled = false;
static bool rotationHookInstalled = false;
static bool skyDivingActive = false;
static bool skyDivingLogPrinted = false;
static float lastPositionY = 0.0f;
static float lastUpdateTime = 0.0f;
static bool skyDivingInitialized = false;

static bool InstallMaxVelocityForwardHook();
static bool InstallAccelerationForwardHook();
static bool InstallMaxVelocitySpeedUpHook();
static bool InstallMaxVelocitySpeedDownHook();
static bool InstallInitVelocityHook();
static bool InstallSkydivingTickHook();
static bool InstallGetForwardHook();
static bool InstallUpdateVelocityGravityHook();
static bool InstallUpdateSkydivingStageHook();
static bool InstallUpdatePawnRotationHook();

static bool SetupSkyDivingHooks() {
    skyDivingLogPrinted = false;

    if (!maxVelocityHookInstalled) {
        if (!InstallMaxVelocityForwardHook()) {
            return false;
        }
    }

    if (!accelerationHookInstalled) {
        if (!InstallAccelerationForwardHook()) {
            return false;
        }
    }

    if (!speedUpHookInstalled) {
        if (!InstallMaxVelocitySpeedUpHook()) {
            return false;
        }
    }

    if (!speedDownHookInstalled) {
        if (!InstallMaxVelocitySpeedDownHook()) {
            return false;
        }
    }

    if (!initVelocityHookInstalled) {
        if (!InstallInitVelocityHook()) {
            return false;
        }
    }

    if (!tickHookInstalled) {
        if (!InstallSkydivingTickHook()) {
            return false;
        }
    }

    if (!forwardHookInstalled) {
        if (!InstallGetForwardHook()) {
            return false;
        }
    }

    if (!gravityHookInstalled) {
        if (!InstallUpdateVelocityGravityHook()) {
            return false;
        }
    }

    if (!stageHookInstalled) {
        if (!InstallUpdateSkydivingStageHook()) {
            return false;
        }
    }

    if (!rotationHookInstalled) {
        if (!InstallUpdatePawnRotationHook()) {
            return false;
        }
    }

    return true;
}

static float GetSystemTimeInSeconds() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + (ts.tv_nsec / 1000000000.0f);
}

static float GetMaxVelocityForwardHook(int64_t a1) {
    float originalVelocity = originalGetMaxVelocityForward(a1);

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalVelocity;
    }

    if (skyDivingActive) {
        static int skyDivingMaxVelHookCounter = 0;
        if (++skyDivingMaxVelHookCounter % 600 == 0) {
            // LOGIO("SkyDivingMaxVelocityHook: SkyDiving MaxVelocity Hook aktif dalam pertandingan. Faktor fall speed: %.2f", Config.MiscSize.FallSpeed);
            skyDivingMaxVelHookCounter = 0;
        }

        float factor = Config.MiscSize.FallSpeed * Config.MiscSize.FallSpeed;
        return fmax(originalVelocity * factor, originalVelocity + 50.0f);
    }

    return originalVelocity;
}

static float GetAccelerationForwardHook(int64_t a1) {
    float originalAcceleration = originalGetAccelerationForward(a1);

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalAcceleration;
    }

    if (skyDivingActive) {
        float factor = Config.MiscSize.FallSpeed * Config.MiscSize.FallSpeed;
        return fmax(originalAcceleration * factor, originalAcceleration + 30.0f);
    }

    return originalAcceleration;
}

static float GetMaxVelocitySpeedUpHook(int64_t a1) {
    float originalVelocity = originalGetMaxVelocitySpeedUp(a1);

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalVelocity;
    }

    if (skyDivingActive) {
        float factor = Config.MiscSize.FallSpeed * Config.MiscSize.FallSpeed;
        return fmax(originalVelocity * factor, originalVelocity + 70.0f);
    }

    return originalVelocity;
}

static float GetMaxVelocitySpeedDownHook(int64_t a1) {
    float originalVelocity = originalGetMaxVelocitySpeedDown(a1);

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalVelocity;
    }

    if (skyDivingActive) {
        float factor = Config.MiscSize.FallSpeed * Config.MiscSize.FallSpeed;
        return fmax(originalVelocity * factor, originalVelocity + 60.0f);
    }

    return originalVelocity;
}

static float GetInitVelocityHook(int64_t a1) {
    float originalVelocity = originalGetInitVelocity(a1);

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalVelocity;
    }

    if (skyDivingActive) {
        float factor = Config.MiscSize.FallSpeed * Config.MiscSize.FallSpeed;
        return fmax(originalVelocity * factor, originalVelocity + 80.0f);
    }

    return originalVelocity;
}

static int64_t SkydivingTickHook(int64_t thisPtr, float deltaTime) {
    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalSkydivingTick(thisPtr, deltaTime);
    }

    if (skyDivingActive) {
        deltaTime *= 0.2f;
    }

    return originalSkydivingTick(thisPtr, deltaTime);
}

static float GetForwardHook(int64_t thisPtr) {
    float originalForward = originalGetForward(thisPtr);

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        return originalForward;
    }

    if (skyDivingActive) {
        return originalForward * (Config.MiscSize.FallSpeed * 1.5f);
    }

    return originalForward;
}

static void UpdateVelocityGravityHook(int64_t thisPtr, float a2, float a3) {
    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        originalUpdateVelocityGravity(thisPtr, a2, a3);
        return;
    }

    if (skyDivingActive) {
        float gravityFactor = Config.MiscSize.FallSpeed * 2.0f;
        a2 *= gravityFactor;

        // DISABLED: Fitur ekstrem gravitasi dinonaktifkan karena menyebabkan crash
        if (Config.MiscSize.FallSpeed > 5.0f) {
            float *currentGravity = (float *) (thisPtr + 420);
            *currentGravity = 1000.0f * (Config.MiscSize.FallSpeed - 4.0f);
        }
    }

    originalUpdateVelocityGravity(thisPtr, a2, a3);
}

static void UpdateSkydivingStageHook(int64_t thisPtr, float deltaTime) {
    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        originalUpdateSkydivingStage(thisPtr, deltaTime);
        return;
    }

    // DISABLED: Fitur ekstrem phase control dinonaktifkan karena menyebabkan crash
    if (skyDivingActive && Config.MiscSize.FallSpeed > 6.0f) {
        if (deltaTime > 0.05f) deltaTime = 0.05f;

        int *currentPhase = (int *) (thisPtr + 272);
        *currentPhase = 1;

        *(bool *) (thisPtr + 328) = false;
        *(bool *) (thisPtr + 349) = false;
        *(bool *) (thisPtr + 364) = true;
    }

    originalUpdateSkydivingStage(thisPtr, deltaTime);

    // DISABLED: Verifikasi fase ekstrem dinonaktifkan karena menyebabkan crash
    if (skyDivingActive && Config.MiscSize.FallSpeed > 6.0f) {
        int *currentPhase = (int *) (thisPtr + 272);
        if (*currentPhase != 1) {
            *currentPhase = 1;
        }
    }
}

static int64_t UpdatePawnRotationHook(int64_t thisPtr, float deltaTime) {
    // DISABLED: Pawn rotation ekstrem dinonaktifkan karena menyebabkan crash
    if (skyDivingActive && Config.MiscSize.FallSpeed > 6.0f) {
        float currentTime = GetSystemTimeInSeconds();
        float frameDelta = currentTime - lastUpdateTime;
        lastUpdateTime = currentTime;

        if (frameDelta > 0.1f) frameDelta = 0.1f;
        if (frameDelta < 0.001f) frameDelta = 0.016f;

        deltaTime = frameDelta;

        int64_t *pawnPtr = (int64_t *) (thisPtr + 48);
        if (pawnPtr && *pawnPtr) {
            int64_t transformObj = *(_QWORD *) (*pawnPtr + 1528);

            if (transformObj) {
                float *position = (float *) (transformObj + 16);
                float posY = *(position + 1);

                if (lastPositionY != 0.0f) {
                    float deltaY = posY - lastPositionY;

                    float maxDeltaY = 50.0f * deltaTime * Config.MiscSize.FallSpeed;
                    if (fabs(deltaY) > maxDeltaY) {
                        *(position + 1) = lastPositionY - maxDeltaY;

                        if (!skyDivingLogPrinted) {
                            skyDivingLogPrinted = true;
                        }
                    }
                }

                lastPositionY = *(position + 1);
            }
        }
    } else {
        lastPositionY = 0.0f;
        lastUpdateTime = 0.0f;
    }

    return originalUpdatePawnRotation(thisPtr, deltaTime);
}

static bool InstallMaxVelocityForwardHook() {
    if (maxVelocityHookInstalled) {
        return true;
    }

    uintptr_t maxVelocityAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_MaxVelocityForward);

    if (maxVelocityAddr == 0) {
        return false;
    }

    originalGetMaxVelocityForward = (original_get_max_velocity_forward_func) maxVelocityAddr;
    bool hookResult = Tools::Hook(
            (void *) maxVelocityAddr,
            (void *) GetMaxVelocityForwardHook,
            (void **) &originalGetMaxVelocityForward
    );

    if (!hookResult) {
        return false;
    }

    maxVelocityHookInstalled = true;

    return true;
}

static bool InstallAccelerationForwardHook() {
    if (accelerationHookInstalled) {
        return true;
    }

    uintptr_t accelerationAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_AccelerationForward);

    if (accelerationAddr == 0) {
        return false;
    }

    originalGetAccelerationForward = (original_get_acceleration_forward_func) accelerationAddr;
    bool hookResult = Tools::Hook(
            (void *) accelerationAddr,
            (void *) GetAccelerationForwardHook,
            (void **) &originalGetAccelerationForward
    );

    if (!hookResult) {
        return false;
    }

    accelerationHookInstalled = true;

    return true;
}

static bool InstallMaxVelocitySpeedUpHook() {
    if (speedUpHookInstalled) {
        return true;
    }

    uintptr_t speedUpAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_MaxVelocitySpeedUp);

    if (speedUpAddr == 0) {
        return false;
    }

    originalGetMaxVelocitySpeedUp = (original_get_max_velocity_speedup_func) speedUpAddr;
    bool hookResult = Tools::Hook(
            (void *) speedUpAddr,
            (void *) GetMaxVelocitySpeedUpHook,
            (void **) &originalGetMaxVelocitySpeedUp
    );

    if (!hookResult) {
        return false;
    }

    speedUpHookInstalled = true;

    return true;
}

static bool InstallMaxVelocitySpeedDownHook() {
    if (speedDownHookInstalled) {
        return true;
    }

    uintptr_t speedDownAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_MaxVelocitySpeedDown);

    if (speedDownAddr == 0) {
        return false;
    }

    originalGetMaxVelocitySpeedDown = (original_get_max_velocity_speeddown_func) speedDownAddr;
    bool hookResult = Tools::Hook(
            (void *) speedDownAddr,
            (void *) GetMaxVelocitySpeedDownHook,
            (void **) &originalGetMaxVelocitySpeedDown
    );

    if (!hookResult) {
        return false;
    }

    speedDownHookInstalled = true;

    return true;
}

static bool InstallInitVelocityHook() {
    if (initVelocityHookInstalled) {
        return true;
    }

    uintptr_t initVelocityAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_InitVelocity);

    if (initVelocityAddr == 0) {
        return false;
    }

    originalGetInitVelocity = (original_get_init_velocity_func) initVelocityAddr;
    bool hookResult = Tools::Hook(
            (void *) initVelocityAddr,
            (void *) GetInitVelocityHook,
            (void **) &originalGetInitVelocity
    );

    if (!hookResult) {
        return false;
    }

    initVelocityHookInstalled = true;

    return true;
}

static bool InstallSkydivingTickHook() {
    if (tickHookInstalled) {
        return true;
    }

    uintptr_t tickAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_Tick);

    if (tickAddr == 0) {
        return false;
    }

    originalSkydivingTick = (original_skydiving_tick_func) tickAddr;
    bool hookResult = Tools::Hook(
            (void *) tickAddr,
            (void *) SkydivingTickHook,
            (void **) &originalSkydivingTick
    );

    if (!hookResult) {
        return false;
    }

    tickHookInstalled = true;

    return true;
}

static bool InstallGetForwardHook() {
    if (forwardHookInstalled) {
        return true;
    }

    uintptr_t forwardAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_GetForward);

    if (forwardAddr == 0) {
        return false;
    }

    originalGetForward = (original_get_forward_func) forwardAddr;
    bool hookResult = Tools::Hook(
            (void *) forwardAddr,
            (void *) GetForwardHook,
            (void **) &originalGetForward
    );

    if (!hookResult) {
        return false;
    }

    forwardHookInstalled = true;

    return true;
}

static bool InstallUpdateVelocityGravityHook() {
    if (gravityHookInstalled) {
        return true;
    }

    uintptr_t gravityAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_UpdateVelocityGravity);

    if (gravityAddr == 0) {
        return false;
    }

    originalUpdateVelocityGravity = (original_update_velocity_gravity_func) gravityAddr;
    bool hookResult = Tools::Hook(
            (void *) gravityAddr,
            (void *) UpdateVelocityGravityHook,
            (void **) &originalUpdateVelocityGravity
    );

    if (!hookResult) {
        return false;
    }

    gravityHookInstalled = true;

    return true;
}

static bool InstallUpdateSkydivingStageHook() {
    if (stageHookInstalled) {
        return true;
    }

    uintptr_t stageAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_UpdateSkydivingStage);

    if (stageAddr == 0) {
        return false;
    }

    originalUpdateSkydivingStage = (original_update_skydiving_stage_func) stageAddr;
    bool hookResult = Tools::Hook(
            (void *) stageAddr,
            (void *) UpdateSkydivingStageHook,
            (void **) &originalUpdateSkydivingStage
    );

    if (!hookResult) {
        return false;
    }

    stageHookInstalled = true;

    return true;
}

static bool InstallUpdatePawnRotationHook() {
    if (rotationHookInstalled) {
        return true;
    }

    uintptr_t rotationAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_SkyDiving_UpdatePawnRotation);

    if (rotationAddr == 0) {
        return false;
    }

    originalUpdatePawnRotation = (original_update_pawn_rotation_func) rotationAddr;
    bool hookResult = Tools::Hook(
            (void *) rotationAddr,
            (void *) UpdatePawnRotationHook,
            (void **) &originalUpdatePawnRotation
    );

    if (!hookResult) {
        return false;
    }

    rotationHookInstalled = true;

    return true;
}

static void HandleSkyDiving() {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        static int handleSkyDivingGameStateCounter = 0;
        if (++handleSkyDivingGameStateCounter % 900 == 0) {
            // LOGIO("HandleSkyDiving: Game tidak dalam pertandingan aktif (MatchInProgress=false). HandleSkyDiving tidak aktif.");
            handleSkyDivingGameStateCounter = 0;
        }
        return;
    }

    if (!Config.Misc.SkyDiving || !Config.Init.IL2CppReady) {
        static int handleSkyDivingFeatureCounter = 0;
        if (++handleSkyDivingFeatureCounter % 900 == 0) {
            // LOGIO("HandleSkyDiving: Fitur SkyDiving dinonaktifkan atau IL2Cpp belum siap. HandleSkyDiving tidak aktif.");
            handleSkyDivingFeatureCounter = 0;
        }
        return;
    }

    if (Config.Misc.SkyDiving) {
        if (!skyDivingInitialized) {
            if (SetupSkyDivingHooks()) {
                skyDivingInitialized = true;

                static int handleSkyDivingSetupCounter = 0;
                if (++handleSkyDivingSetupCounter % 900 == 0) {
                    // LOGIO("HandleSkyDiving: Berhasil memasang SkyDiving Hook dalam pertandingan aktif.");
                    handleSkyDivingSetupCounter = 0;
                }
            }
        }

        if (skyDivingInitialized) {
            skyDivingActive = true;
            Config.MiscHook.SkyDivingPatchReady = true;
        }
    } else {
        skyDivingActive = false;
        Config.MiscHook.SkyDivingPatchReady = false;
    }
}

#endif //ARCAMOD_SKYDIVING_H