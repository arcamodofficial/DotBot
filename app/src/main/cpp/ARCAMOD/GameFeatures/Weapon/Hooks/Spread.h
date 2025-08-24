#ifndef ARCAMOD_SPREAD_H
#define ARCAMOD_SPREAD_H

#ifdef RELEASE
#pragma clang optimize off
#pragma GCC optimize ("O0")
#pragma GCC push_options
#endif

#include <cstdint>

typedef float (*tGetRealSpreadModifier)(int64_t *a1);

tGetRealSpreadModifier original_GetRealSpreadModifier;

typedef void (*tCalcShotSpreadSize)(int64_t *a1);

tCalcShotSpreadSize original_CalcShotSpreadSize;

typedef void (*tRandomShotSpread)(float *a1);

tRandomShotSpread original_RandomShotSpread;

static float GetRealSpreadModifier_Hook(int64_t *a1) {
    float originalSpread = original_GetRealSpreadModifier(a1);

    if (Config.Weapon.Spread) {
        float factor = Config.WeaponSize.SpreadFactor;

        if (factor <= 0.2f) {
            return 0.0f;
        }

        float adjustedFactor = factor * factor;
        return originalSpread * adjustedFactor;
    }

    return originalSpread;
}

static void CalcShotSpreadSize_Hook(int64_t *a1) {
    original_CalcShotSpreadSize(a1);

    if (Config.Weapon.Spread && Config.WeaponSize.SpreadFactor <= 0.2f) {
        float *spreadValue = (float *) ((uintptr_t) a1 + 236 * 4);
        *spreadValue = 0.0f;
    }
}

static void RandomShotSpread_Hook(float *a1) {
    if (Config.Weapon.Spread && Config.WeaponSize.SpreadFactor <= 0.2f) {
        a1[237] = 0.0f;
        a1[238] = 0.0f;
        return;
    }

    original_RandomShotSpread(a1);
}

static void SetupSpreadHooks() {
    const uintptr_t getRealSpreadModifierAddr = Tools::GetRealOffsets(OBF("libunity.so"), OBF(WEAPON_GetRealSpreadModifier));
    if (getRealSpreadModifierAddr != 0) {
        original_GetRealSpreadModifier = (tGetRealSpreadModifier) getRealSpreadModifierAddr;
        Tools::Hook((void *) getRealSpreadModifierAddr, (void *) GetRealSpreadModifier_Hook,
                    (void **) &original_GetRealSpreadModifier);
    }

    const uintptr_t calcShotSpreadSizeAddr = Tools::GetRealOffsets(OBF("libunity.so"), OBF(WEAPON_CalcShotSpreadSize));
    if (calcShotSpreadSizeAddr != 0) {
        original_CalcShotSpreadSize = (tCalcShotSpreadSize) calcShotSpreadSizeAddr;
        Tools::Hook((void *) calcShotSpreadSizeAddr, (void *) CalcShotSpreadSize_Hook,
                    (void **) &original_CalcShotSpreadSize);
    }

    const uintptr_t randomShotSpreadAddr = Tools::GetRealOffsets(OBF("libunity.so"), OBF(WEAPON_RandomShotSpread));
    if (randomShotSpreadAddr != 0) {
        original_RandomShotSpread = (tRandomShotSpread) randomShotSpreadAddr;
        Tools::Hook((void *) randomShotSpreadAddr, (void *) RandomShotSpread_Hook,
                    (void **) &original_RandomShotSpread);
    }
}

static void HandleSpread() {
    static bool hookInitialized = false;

    if (Config.Weapon.Spread && !hookInitialized) {
        SetupSpreadHooks();
        hookInitialized = true;
        Config.WeaponHook.SpreadPatchReady = true;
    } else if (!Config.Weapon.Spread && Config.WeaponHook.SpreadPatchReady) {
        Config.WeaponHook.SpreadPatchReady = false;
    }

    Config.WeaponHook.SpreadReady = true;
}

#ifdef RELEASE
#pragma clang optimize on
#pragma GCC pop_options
#endif

#endif //ARCAMOD_SPREAD_H