#ifndef ARCAMOD_INFINITE_AMMO_H
#define ARCAMOD_INFINITE_AMMO_H

#include <cstdint>

typedef int64_t (*tAmmoCanFire)(int64_t* weapon);
typedef int64_t (*tConsumeAmmo)(int64_t weapon);
typedef int64_t (*tGetClipAmmoCount)(int64_t weapon, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);
typedef int64_t (*tGetInfiniteCarriedAmmo)(int64_t weapon, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);

tAmmoCanFire original_AmmoCanFire = nullptr;
tConsumeAmmo original_ConsumeAmmo = nullptr;
tGetClipAmmoCount original_GetClipAmmoCount = nullptr;
tGetInfiniteCarriedAmmo original_GetInfiniteCarriedAmmo = nullptr;

static int64_t AmmoCanFire_Hook(int64_t* weapon) {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        static int infiniteAmmoGameStateCounter = 0;
        if (++infiniteAmmoGameStateCounter % 600 == 0) {
            // LOGIO("InfiniteAmmoHook: Game tidak dalam pertandingan aktif (MatchInProgress=false). InfiniteAmmo Hook tidak aktif.");
            infiniteAmmoGameStateCounter = 0;
        }

        if (original_AmmoCanFire && weapon) {
            return original_AmmoCanFire(weapon);
        }
        return 1;
    }

    if (!Config.Weapon.InfiniteAmmo || !Config.Init.IL2CppReady) {
        static int infiniteAmmoFeatureCounter = 0;
        if (++infiniteAmmoFeatureCounter % 600 == 0) {
            // LOGIO("InfiniteAmmoHook: Fitur InfiniteAmmo dinonaktifkan atau IL2Cpp belum siap. InfiniteAmmo Hook tidak aktif.");
            infiniteAmmoFeatureCounter = 0;
        }

        if (original_AmmoCanFire && weapon) {
            return original_AmmoCanFire(weapon);
        }
        return 1;
    }

    if (weapon) {
        static int infiniteAmmoActiveCounter = 0;
        if (++infiniteAmmoActiveCounter % 900 == 0) {
            // LOGIO("InfiniteAmmoHook: InfiniteAmmo Hook aktif dalam pertandingan. Ammo selalu tersedia.");
            infiniteAmmoActiveCounter = 0;
        }
        return 1;
    }

    return 1;
}

static int64_t ConsumeAmmo_Hook(int64_t weapon) {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        if (original_ConsumeAmmo && weapon) {
            return original_ConsumeAmmo(weapon);
        }
        return 1;
    }

    if (!Config.Weapon.InfiniteAmmo || !Config.Init.IL2CppReady) {
        if (original_ConsumeAmmo && weapon) {
            return original_ConsumeAmmo(weapon);
        }
        return 1;
    }

    if (weapon) {
        return 1;
    }

    return 1;
}

static int64_t GetInfiniteCarriedAmmo_Hook(int64_t weapon, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8) {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        if (original_GetInfiniteCarriedAmmo) {
            return original_GetInfiniteCarriedAmmo(weapon, a2, a3, a4, a5, a6, a7, a8);
        }
        return 0;
    }

    if (!Config.Weapon.InfiniteAmmo || !Config.Init.IL2CppReady) {
        if (original_GetInfiniteCarriedAmmo) {
            return original_GetInfiniteCarriedAmmo(weapon, a2, a3, a4, a5, a6, a7, a8);
        }
        return 0;
    }

    return 1;
}

static void SetupInfiniteAmmoHooks() {
    const uintptr_t ammoCanFireAddr = Tools::GetRealOffsets(OBF("libunity.so"), OBF(WEAPON_AmmoCanFire));
    if (ammoCanFireAddr != 0) {
        original_AmmoCanFire = (tAmmoCanFire) ammoCanFireAddr;
        Tools::Hook((void *) ammoCanFireAddr, (void *) AmmoCanFire_Hook, (void **) &original_AmmoCanFire);
    }

    const uintptr_t consumeAmmoAddr = Tools::GetRealOffsets(OBF("libunity.so"), OBF(WEAPON_ConsumeAmmo));
    if (consumeAmmoAddr != 0) {
        original_ConsumeAmmo = (tConsumeAmmo) consumeAmmoAddr;
        Tools::Hook((void *) consumeAmmoAddr, (void *) ConsumeAmmo_Hook, (void **) &original_ConsumeAmmo);
    }

    const uintptr_t getInfiniteAmmoAddr = Tools::GetRealOffsets(OBF("libunity.so"), OBF(WEAPON_GetInfiniteCarriedAmmo));
    if (getInfiniteAmmoAddr != 0) {
        original_GetInfiniteCarriedAmmo = (tGetInfiniteCarriedAmmo) getInfiniteAmmoAddr;
        Tools::Hook((void *) getInfiniteAmmoAddr, (void *) GetInfiniteCarriedAmmo_Hook, (void **) &original_GetInfiniteCarriedAmmo);
    }
}

static void HandleInfiniteAmmo() {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        static int handleInfiniteAmmoGameStateCounter = 0;
        if (++handleInfiniteAmmoGameStateCounter % 900 == 0) {
            // LOGIO("HandleInfiniteAmmo: Game tidak dalam pertandingan aktif (MatchInProgress=false). HandleInfiniteAmmo tidak aktif.");
            handleInfiniteAmmoGameStateCounter = 0;
        }
        return;
    }

    if (!Config.Weapon.InfiniteAmmo || !Config.Init.IL2CppReady) {
        static int handleInfiniteAmmoFeatureCounter = 0;
        if (++handleInfiniteAmmoFeatureCounter % 900 == 0) {
            // LOGIO("HandleInfiniteAmmo: Fitur InfiniteAmmo dinonaktifkan atau IL2Cpp belum siap. HandleInfiniteAmmo tidak aktif.");
            handleInfiniteAmmoFeatureCounter = 0;
        }
        return;
    }

    static bool hookInitialized = false;

    if (Config.Weapon.InfiniteAmmo && !hookInitialized) {
        SetupInfiniteAmmoHooks();
        hookInitialized = true;
        Config.WeaponHook.InfiniteAmmoPatchReady = true;

        static int handleInfiniteAmmoSetupCounter = 0;
        if (++handleInfiniteAmmoSetupCounter % 900 == 0) {
            // LOGIO("HandleInfiniteAmmo: Berhasil memasang InfiniteAmmo Hook dalam pertandingan aktif.");
            handleInfiniteAmmoSetupCounter = 0;
        }
    } else if (!Config.Weapon.InfiniteAmmo && Config.WeaponHook.InfiniteAmmoPatchReady) {
        Config.WeaponHook.InfiniteAmmoPatchReady = false;
    }

    Config.WeaponHook.InfiniteAmmoReady = true;
}

#endif //ARCAMOD_INFINITE_AMMO_H