// app/src/main/cpp/ARCAMOD/Hacks/Weapon_Hooks/HighDamage.h
#ifndef ARCAMOD_HIGHDAMAGE_H
#define ARCAMOD_HIGHDAMAGE_H

void HandleHighDamage() {
    // Menangani fitur HighDamage - CENTRALIZED: Menggunakan WEAPON_HighDamage_Patch dari OffsetDefinitions.h
    if (Config.Weapon.HighDamage) {
        if (!Config.WeaponHook.HighDamagePatchReady) {
            PATCH("libunity.so", WEAPON_HighDamage_Patch, "200080D2C0035FD6");
            Config.WeaponHook.HighDamagePatchReady = true;
        }
    } else {
        if (Config.WeaponHook.HighDamagePatchReady) {
            PATCH("libunity.so", WEAPON_HighDamage_Patch, "EE 0F 18 FC ED 33 01 6D");
            Config.WeaponHook.HighDamagePatchReady = false;
        }
    }
}

#endif //ARCAMOD_HIGHDAMAGE_H
