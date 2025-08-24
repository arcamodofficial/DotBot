#ifndef ARCAMOD_RECOIL_H
#define ARCAMOD_RECOIL_H

#ifdef RELEASE
#pragma clang optimize off
#pragma GCC optimize ("O0")
#pragma GCC push_options
#endif

#include <cstdint>

#define ADDR_GETSCALERECOIL OBF(WEAPON_GetScaleRecoil)

typedef float (*tGetScaleRecoil)(int64_t a1);

tGetScaleRecoil original_GetScaleRecoil;

static float GetScaleRecoil_Hook(int64_t a1) {
    float originalRecoil = original_GetScaleRecoil(a1);

    if (Config.Weapon.Recoil) {
        return originalRecoil * Config.WeaponSize.RecoilFactor;
    }

    return originalRecoil;
}

static void SetupRecoilHook() {
    const uintptr_t getScaleRecoilAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GETSCALERECOIL);

    if (getScaleRecoilAddr == 0) {
        return;
    }

    original_GetScaleRecoil = (tGetScaleRecoil) getScaleRecoilAddr;
    bool hookResult = Tools::Hook((void *) getScaleRecoilAddr, (void *) GetScaleRecoil_Hook,
                                  (void **) &original_GetScaleRecoil);

    if (!hookResult) {
    }
}

static void HandleRecoil() {
    static bool hookInitialized = false;

    if (Config.Weapon.Recoil && !hookInitialized) {
        SetupRecoilHook();
        hookInitialized = true;
    }

    /*
    if (Config.Weapon.Recoil) {
        if (!Config.WeaponHook.RecoilPatchReady) {
            PATCH(OBF("libunity.so"), "0x85BB9F0", "204C40BCC0035FD6");
            Config.WeaponHook.RecoilPatchReady = true;
        }
    } else {
        if (Config.WeaponHook.RecoilPatchReady) {
            PATCH(OBF("libunity.so"), "0x85BB9F0", "E80F1DFCF44F01A9");
            Config.WeaponHook.RecoilPatchReady = false;
        }
    }
    */
}

#ifdef RELEASE
#pragma clang optimize on
#pragma GCC pop_options
#endif

#endif //ARCAMOD_RECOIL_H