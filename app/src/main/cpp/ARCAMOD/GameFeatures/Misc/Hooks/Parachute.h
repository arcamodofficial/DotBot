#ifndef ARCAMOD_PARACHUTE_H
#define ARCAMOD_PARACHUTE_H

#include <cstdint>

#define OPEN_PARACHUTE_OFFSET OBF(MISC_Parachute_OpenParachute)

typedef int64_t (*original_open_parachute_func)(int64_t a1, char a2);

original_open_parachute_func originalOpenParachuteFunction = nullptr;

static bool parachuteHookInstalled = false;
static bool parachuteActive = false;
static bool parachuteLogPrinted = false;
static bool parachuteInitialized = false;

static int64_t OpenParachuteHook(int64_t a1, char a2) {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        static int parachuteGameStateCounter = 0;
        if (++parachuteGameStateCounter % 600 == 0) {
            // LOGIO("ParachuteHook: Game tidak dalam pertandingan aktif (MatchInProgress=false). Parachute Hook tidak aktif.");
            parachuteGameStateCounter = 0;
        }
        return originalOpenParachuteFunction(a1, a2);
    }

    if (!Config.Misc.Parachute || !Config.Init.IL2CppReady) {
        static int parachuteFeatureCounter = 0;
        if (++parachuteFeatureCounter % 600 == 0) {
            // LOGIO("ParachuteHook: Fitur Parachute dinonaktifkan atau IL2Cpp belum siap. Parachute Hook tidak aktif.");
            parachuteFeatureCounter = 0;
        }
        return originalOpenParachuteFunction(a1, a2);
    }

    if (parachuteActive) {
        static int parachuteHookCounter = 0;
        if (++parachuteHookCounter % 600 == 0) {
            // LOGIO("ParachuteHook: Parachute Hook aktif dalam pertandingan. No Parachute diaktifkan.");
            parachuteHookCounter = 0;
        }

        return 0;
    }

    return originalOpenParachuteFunction(a1, a2);
}

static bool InstallParachuteHook() {
    if (parachuteHookInstalled) {
        return true;
    }

    uintptr_t openParachuteAddr = Tools::GetRealOffsets(OBF("libunity.so"), OPEN_PARACHUTE_OFFSET);

    if (openParachuteAddr == 0) {
        return false;
    }

    originalOpenParachuteFunction = (original_open_parachute_func) openParachuteAddr;
    bool hookResult = Tools::Hook(
            (void *) openParachuteAddr,
            (void *) OpenParachuteHook,
            (void **) &originalOpenParachuteFunction
    );

    if (!hookResult) {
        return false;
    }

    parachuteHookInstalled = true;

    return true;
}

static void HandleParachute() {
    bool isInActiveMatch = false;

    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        static int handleParachuteGameStateCounter = 0;
        if (++handleParachuteGameStateCounter % 900 == 0) {
            // LOGIO("HandleParachute: Game tidak dalam pertandingan aktif (MatchInProgress=false). HandleParachute tidak aktif.");
            handleParachuteGameStateCounter = 0;
        }
        return;
    }

    if (!Config.Misc.Parachute || !Config.Init.IL2CppReady) {
        static int handleParachuteFeatureCounter = 0;
        if (++handleParachuteFeatureCounter % 900 == 0) {
            // LOGIO("HandleParachute: Fitur Parachute dinonaktifkan atau IL2Cpp belum siap. HandleParachute tidak aktif.");
            handleParachuteFeatureCounter = 0;
        }
        return;
    }

    if (Config.Misc.Parachute) {
        if (!parachuteInitialized) {
            if (InstallParachuteHook()) {
                parachuteInitialized = true;
                parachuteLogPrinted = false;

                static int handleParachuteSetupCounter = 0;
                if (++handleParachuteSetupCounter % 900 == 0) {
                    // LOGIO("HandleParachute: Berhasil memasang Parachute Hook dalam pertandingan aktif.");
                    handleParachuteSetupCounter = 0;
                }
            }
        }

        if (parachuteInitialized) {
            parachuteActive = true;
            Config.MiscHook.ParachutePatchReady = true;
        }
    } else {
        parachuteActive = false;
        Config.MiscHook.ParachutePatchReady = false;
    }
}

#endif //ARCAMOD_PARACHUTE_H