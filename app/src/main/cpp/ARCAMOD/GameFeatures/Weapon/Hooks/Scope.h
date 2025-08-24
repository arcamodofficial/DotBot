#ifndef ARCAMOD_SCOPE_H
#define ARCAMOD_SCOPE_H

#ifdef RELEASE
#pragma clang optimize off
#pragma GCC optimize ("O0")
#pragma GCC push_options
#endif

#include <cstdint>

#define ADDR_GETAIMINGTIME OBF(WEAPON_GetAimingTime)

typedef float (*tGetAimingTime)(int64_t a1);

tGetAimingTime original_GetAimingTime;

static float GetAimingTime_Hook(int64_t a1) {
    float originalAimTime = original_GetAimingTime(a1);

    if (Config.Weapon.Scope) {
        return originalAimTime * Config.WeaponSize.ScopeFactor;
    }

    return originalAimTime;
}

static void SetupScopeHook() {
    const uintptr_t aimingTimeAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GETAIMINGTIME);

    if (aimingTimeAddr == 0) {
        return;
    }

    original_GetAimingTime = (tGetAimingTime) aimingTimeAddr;
    bool hookResult = Tools::Hook((void *) aimingTimeAddr, (void *) GetAimingTime_Hook,
                                  (void **) &original_GetAimingTime);

    if (!hookResult) {
    }
}

static void HandleScope() {
    static bool hookInitialized = false;

    if (Config.Weapon.Scope && !hookInitialized) {
        SetupScopeHook();
        hookInitialized = true;
        Config.WeaponHook.ScopePatchReady = true;
    } else if (!Config.Weapon.Scope && Config.WeaponHook.ScopePatchReady) {
        Config.WeaponHook.ScopePatchReady = false;
    }

    Config.WeaponHook.ScopeReady = true;

    // Implementasi lama (disimpan sebagai referensi)
    /*
    if (Config.Weapon.Scope) {
        if (!Config.WeaponHook.ScopePatchReady) {
            PATCH(OBF("libunity.so"), "0x84E114C", "0020201E");
            Config.WeaponHook.ScopePatchReady = true;
        }
    } else {
        if (Config.WeaponHook.ScopePatchReady) {
            PATCH(OBF("libunity.so"), "0x84E114C", "2020201E");
            Config.WeaponHook.ScopePatchReady = false;
        }
    }
    Config.WeaponHook.ScopeReady = true;
    */
}

#ifdef RELEASE
#pragma clang optimize on
#pragma GCC pop_options
#endif

#endif //ARCAMOD_SCOPE_H