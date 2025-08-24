#ifndef ARCAMOD_WALLHACKNORMAL_H
#define ARCAMOD_WALLHACKNORMAL_H

#include <cstdint>

typedef int64_t (*original_on_respawn_player_func)(int64_t *a1, long double a2, long double a3,
                                                   long double a4);
typedef int64_t (*original_show_occlusion_effect_func)(int64_t *a1, char a2);

original_on_respawn_player_func originalOnRespawnPlayerFunction = nullptr;
original_show_occlusion_effect_func originalShowOcclusionEffectFunction = nullptr;

static bool wallhackNormalHooksInstalled = false;
static bool wallhackNormalActive = false;
static bool wallhackNormalInitialized = false;
static bool wallhackLogged = false;

#define ON_RESPAWN_PLAYER_OFFSET OBF(WALLHACK_Normal_OnRespawnPlayer)
#define SHOW_OCCLUSION_EFFECT_OFFSET OBF(WALLHACK_Normal_ShowOcclusionEffect)

static int64_t ShowOcclusionEffectHook(int64_t *a1, char a2) {
    if (!a1 || !originalShowOcclusionEffectFunction) {
        return 0;
    }

    int64_t result = 0;

    if (wallhackNormalActive) {
        static bool hookCalled = false;
        if (!hookCalled) {
            hookCalled = true;
        }

        result = originalShowOcclusionEffectFunction(a1, 1);
    } else {
        result = originalShowOcclusionEffectFunction(a1, a2);
    }

    return result;
}

static int64_t OnRespawnPlayerHook(int64_t *a1, long double a2, long double a3, long double a4) {
    if (!a1 || !originalOnRespawnPlayerFunction) {
        return 0;
    }

    int64_t result = 0;

    if (wallhackNormalActive) {
        static bool hookCalled = false;
        if (!hookCalled) {
            hookCalled = true;
        }

        result = originalOnRespawnPlayerFunction(a1, a2, a3, a4);

        if (originalShowOcclusionEffectFunction != nullptr && a1 != nullptr) {
            originalShowOcclusionEffectFunction(a1, 1);
        }
    } else {
        result = originalOnRespawnPlayerFunction(a1, a2, a3, a4);
    }

    return result;
}

static bool SetupWallhackNormalHooks() {
    if (wallhackNormalHooksInstalled) {
        return true;
    }

    bool hookSuccessful = false;
    int successCount = 0;

    uintptr_t showOcclusionEffectAddr = Tools::GetRealOffsets(OBF("libunity.so"),
                                                              SHOW_OCCLUSION_EFFECT_OFFSET);

    if (showOcclusionEffectAddr != 0) {
        originalShowOcclusionEffectFunction = (original_show_occlusion_effect_func) showOcclusionEffectAddr;

        bool occlusionHookResult = Tools::Hook(
                (void *) showOcclusionEffectAddr,
                (void *) ShowOcclusionEffectHook,
                (void **) &originalShowOcclusionEffectFunction
        );

        if (occlusionHookResult) {
            successCount++;
        } else {
            // LOGEO("WallhackNormal: Hook #1 gagal (ShowOcclusionEffect)");
        }
    }

    uintptr_t onRespawnPlayerAddr = Tools::GetRealOffsets(OBF("libunity.so"), ON_RESPAWN_PLAYER_OFFSET);

    if (onRespawnPlayerAddr != 0) {
        originalOnRespawnPlayerFunction = (original_on_respawn_player_func) onRespawnPlayerAddr;

        bool respawnHookResult = Tools::Hook(
                (void *) onRespawnPlayerAddr,
                (void *) OnRespawnPlayerHook,
                (void **) &originalOnRespawnPlayerFunction
        );

        if (respawnHookResult) {
            successCount++;
        } else {
            // LOGEO("WallhackNormal: Hook #2 gagal (OnRespawnPlayer)");
        }
    }

    hookSuccessful = (successCount > 0);
    wallhackNormalHooksInstalled = hookSuccessful;

    return hookSuccessful;
}

static int frameCounter = 0;

static void HandleWallhackNormal() {
    frameCounter++;

    if (Config.View.Wallhack.Normal) {
        if (!wallhackNormalInitialized) {
            if (SetupWallhackNormalHooks()) {
                wallhackNormalInitialized = true;
            }
        }

        wallhackNormalActive = true;
        Config.View.WallhackHook.Normal = true;

        if (!wallhackLogged && frameCounter % 300 == 0) {
            wallhackLogged = true;
        }
    } else {
        wallhackNormalActive = false;
        Config.View.WallhackHook.Normal = false;

        if (wallhackLogged && frameCounter % 300 == 0) {
            wallhackLogged = false;
        }
    }

    if (frameCounter >= 1800) {
        frameCounter = 0;
    }
}

#endif //ARCAMOD_WALLHACKNORMAL_H