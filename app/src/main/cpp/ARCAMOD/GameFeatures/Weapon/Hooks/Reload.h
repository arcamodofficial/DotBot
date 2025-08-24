#ifndef ARCAMOD_RELOAD_H
#define ARCAMOD_RELOAD_H

#include <cstdint>

#define ADDR_GETCHANGECLIPTIME OBF(WEAPON_GetChangeClipTime)

typedef float (*tGetChangeClipTime)(int64_t a1);

tGetChangeClipTime original_GetChangeClipTime;

static float GetChangeClipTime_Hook(int64_t a1) {
    float originalClipTime = original_GetChangeClipTime(a1);

    if (Config.Weapon.Reload) {
        return originalClipTime * Config.WeaponSize.ReloadFactor;
    }

    return originalClipTime;
}

static void SetupReloadHook() {
    const uintptr_t changeClipTimeAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GETCHANGECLIPTIME);

    if (changeClipTimeAddr == 0) {
        return;
    }

    original_GetChangeClipTime = (tGetChangeClipTime) changeClipTimeAddr;
    bool hookResult = Tools::Hook((void *) changeClipTimeAddr, (void *) GetChangeClipTime_Hook,
                                  (void **) &original_GetChangeClipTime);

    if (!hookResult) {
    }
}

static void HandleReload() {
    static bool hookInitialized = false;

    if (Config.Weapon.Reload && !hookInitialized) {
        SetupReloadHook();
        hookInitialized = true;
        Config.WeaponHook.ReloadPatchReady = true;
    } else if (!Config.Weapon.Reload && Config.WeaponHook.ReloadPatchReady) {
        Config.WeaponHook.ReloadPatchReady = false;
    }

    Config.WeaponHook.ReloadReady = true;

    // Implementasi lama (disimpan sebagai referensi)
    /*
    if (Config.Weapon.Reload) {
        if (!Config.WeaponHook.ReloadPatchReady) {
            PATCH(OBF("libunity.so"), "0x99EF608", "200080D2C0035FD6");
            Config.WeaponHook.ReloadPatchReady = true;
        }
    } else {
        if (Config.WeaponHook.ReloadPatchReady) {
            PATCH(OBF("libunity.so"), "0x99EF608", "E80F1DFCF44F01A9");
            Config.WeaponHook.ReloadPatchReady = false;
        }
    }
    Config.WeaponHook.ReloadReady = true;
    */
}

#endif //ARCAMOD_RELOAD_H