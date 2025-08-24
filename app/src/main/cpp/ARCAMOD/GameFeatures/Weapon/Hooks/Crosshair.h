// app/src/main/cpp/ARCAMOD/Hacks/Weapon_Hooks/Crosshair.h
#ifndef ARCAMOD_CROSSHAIR_H
#define ARCAMOD_CROSSHAIR_H

void HandleCrosshair() {
    // Menangani fitur Crosshair - CENTRALIZED: Menggunakan WEAPON_Crosshair_Patch dari OffsetDefinitions.h
    if (Config.Weapon.Crosshair) {
        if (!Config.WeaponHook.CrosshairPatchReady) {
            PATCH("libunity.so", WEAPON_Crosshair_Patch, "200080D2C0035FD6");
            Config.WeaponHook.CrosshairPatchReady = true;
        }
    } else {
        if (Config.WeaponHook.CrosshairPatchReady) {
            PATCH("libunity.so", WEAPON_Crosshair_Patch, "00 14 4A BD C0 03 5F D6");
            Config.WeaponHook.CrosshairPatchReady = false;
        }
    }
}

#endif //ARCAMOD_CROSSHAIR_H
