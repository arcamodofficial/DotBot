#ifndef ARCAMOD_SPECTATE_H
#define ARCAMOD_SPECTATE_H

#include <cstdint> // Untuk tipe data int64_t

// ===========================================================================================
// SPECTATOR NO DELAY HOOKS - Hanya Hook yang Bekerja (2 hooks)
// ===========================================================================================

// Definisi tipe fungsi asli untuk Hook yang Bekerja (2 functions)
typedef void (*original_observer_tick_func)(int64_t instance, float deltaTime);
typedef bool (*original_need_delay_process_func)(int64_t instance);

// Fungsi asli yang akan disimpan setelah hook (2 functions yang bekerja)
original_observer_tick_func originalObserverTickFunc = nullptr;
original_need_delay_process_func originalNeedDelayProcessFunc = nullptr;

// Flag untuk menandai apakah hook pernah dilakukan
static bool spectateHooksInstalled = false;
static bool spectateInitialized = false;

// ===========================================================================================
// HOOK IMPLEMENTATIONS - Hanya 2 Hook yang Bekerja
// ===========================================================================================

// Hook untuk GameBase_ObserverDelayManager__Tick (0x904D450)
void ObserverTickHook(int64_t instance, float deltaTime) {
    // CRITICAL: Safety check untuk prevent crash
    if (instance == 0) {
        if (originalObserverTickFunc) originalObserverTickFunc(instance, deltaTime);
        return;
    }

    // VALIDASI: Cek apakah dalam pertandingan aktif
    bool isInActiveMatch = false;
    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch || !Config.Misc.Spectate || !Config.Init.IL2CppReady) {
        if (originalObserverTickFunc) originalObserverTickFunc(instance, deltaTime);
        return;
    }

    // Panggil fungsi asli terlebih dahulu
    if (originalObserverTickFunc) originalObserverTickFunc(instance, deltaTime);

    // ENHANCED POST-COUNTDOWN MANIPULATION: Persistent flag enforcement
    // POST-COUNTDOWN PHASE: PERSISTENT manipulation untuk maintain no delay
    // AGGRESSIVE: Continuous flag manipulation untuk prevent system reset
    if (instance + 144 < instance + 200) {
        *((unsigned char*)(instance + 144)) = 0; // Disable delay flag 1
    }
    if (instance + 145 < instance + 200) {
        *((unsigned char*)(instance + 145)) = 1; // Set countdown finished flag
    }
    if (instance + 146 < instance + 200) {
        *((unsigned char*)(instance + 146)) = 0; // Disable delay flag 2
    }

    // ADDITIONAL: Reset delay values untuk force instant processing
    if (instance + 124 < instance + 200) {
        *((float*)(instance + 124)) = 0.0f; // Force delay countdown to 0
    }
    if (instance + 128 < instance + 200) {
        *((int*)(instance + 128)) = 0; // Reset delay time
    }

    // Debug logging untuk monitor tick manipulation
    static int tickLogCounter = 0;
    if (++tickLogCounter % 600 == 0) { // Log setiap 600 calls (~20 detik)
        // LOGIO("SPECTATE: ObserverTick POST-COUNTDOWN - persistent flag manipulation active");
        tickLogCounter = 0;
    }
}

// Hook untuk GameBase_ObserverDelayManager__NeedDelayProcess (0x904DD18)
bool NeedDelayProcessHook(int64_t instance) {
    // CRITICAL: Safety check untuk prevent crash
    if (instance == 0) {
        return originalNeedDelayProcessFunc ? originalNeedDelayProcessFunc(instance) : false;
    }

    // VALIDASI: Cek apakah dalam pertandingan aktif
    bool isInActiveMatch = false;
    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch || !Config.Misc.Spectate || !Config.Init.IL2CppReady) {
        return originalNeedDelayProcessFunc ? originalNeedDelayProcessFunc(instance) : false;
    }

    // ENHANCED POST-COUNTDOWN LOGIC: Aggressive approach setelah countdown
    // AGGRESSIVE: Return false untuk force no delay setelah countdown

    // Enhanced flag manipulation dengan multiple attempts
    if (instance + 144 < instance + 200) {
        *((unsigned char*)(instance + 144)) = 0; // Disable delay flag 1
    }
    if (instance + 145 < instance + 200) {
        *((unsigned char*)(instance + 145)) = 1; // Set countdown finished flag
    }
    if (instance + 146 < instance + 200) {
        *((unsigned char*)(instance + 146)) = 0; // Disable delay flag 2
    }

    // ADDITIONAL: Reset delay countdown value untuk force instant
    if (instance + 124 < instance + 200) {
        *((float*)(instance + 124)) = 0.0f; // Force countdown to 0
    }

    // Debug logging untuk monitor post-countdown behavior
    static int postCountdownLogCounter = 0;
    if (++postCountdownLogCounter % 300 == 0) {
        // LOGIO("SPECTATE: POST-COUNTDOWN NeedDelayProcess - forcing no delay, flags: %d,%d,%d",
              // *((unsigned char*)(instance + 144)),
              // *((unsigned char*)(instance + 145)),
              // *((unsigned char*)(instance + 146)));
        postCountdownLogCounter = 0;
    }

    // AGGRESSIVE: Return false untuk force no delay
    return false;
}

// ===========================================================================================
// SETUP FUNCTIONS - Hook Installation (Hanya 2 Hook yang Bekerja)
// ===========================================================================================

// Fungsi untuk memasang 2 hook spectator yang bekerja (dipanggil hanya sekali)
bool InstallSpectateHooks() {
    if (spectateHooksInstalled) {
        return true;
    }

    // LOGIO("SPECTATE: Starting hook installation...");
    bool hookSuccessful = true;
    int successfulHooks = 0;

    // HANYA 2 HOOK YANG BEKERJA BERDASARKAN LOG

    // 1. Hook Observer Tick - MISC_Spectate_ObserverTick ⭐ CRITICAL
    uintptr_t observerTickAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Spectate_ObserverTick);
    if (observerTickAddr != 0) {
        originalObserverTickFunc = (original_observer_tick_func) observerTickAddr;
        if (Tools::Hook((void *) observerTickAddr, (void *) ObserverTickHook, (void **) &originalObserverTickFunc)) {
            successfulHooks++;
            // LOGIO("SPECTATE: ✅ ObserverTick hook installed successfully at 0x%lx", observerTickAddr);
        } else {
            hookSuccessful = false; // Critical hook failed
            // LOGIO("SPECTATE: ❌ ObserverTick hook FAILED at 0x%lx", observerTickAddr);
        }
    } else {
        // LOGIO("SPECTATE: ❌ ObserverTick address not found (MISC_Spectate_ObserverTick)");
    }

    // 2. Hook Need Delay Process - MISC_Spectate_NeedDelayProcess ⭐ CRITICAL
    uintptr_t needDelayAddr = Tools::GetRealOffsets(OBF("libunity.so"), MISC_Spectate_NeedDelayProcess);
    if (needDelayAddr != 0) {
        originalNeedDelayProcessFunc = (original_need_delay_process_func) needDelayAddr;
        if (Tools::Hook((void *) needDelayAddr, (void *) NeedDelayProcessHook, (void **) &originalNeedDelayProcessFunc)) {
            successfulHooks++;
            // LOGIO("SPECTATE: ✅ NeedDelayProcess hook installed successfully at 0x%lx", needDelayAddr);
        } else {
            hookSuccessful = false; // Critical hook failed
            // LOGIO("SPECTATE: ❌ NeedDelayProcess hook FAILED at 0x%lx", needDelayAddr);
        }
    } else {
        // LOGIO("SPECTATE: ❌ NeedDelayProcess address not found (MISC_Spectate_NeedDelayProcess)");
    }

    // ===========================================================================================
    // INSTALLATION SUMMARY & RESULT
    // ===========================================================================================

    // Minimal requirement: At least 2 hooks must succeed
    bool minimalRequirementMet = (successfulHooks >= 2);

    if (hookSuccessful && minimalRequirementMet) {
        spectateHooksInstalled = true;
        // LOGIO("SPECTATE: ✅ Successfully installed %d/2 hooks. No Delay Spectating ready!", successfulHooks);
        return true;
    } else {
        // LOGIO("SPECTATE: ❌ Failed to install hooks. Only %d/2 hooks installed.", successfulHooks);
        return false;
    }
}

// ===========================================================================================
// MAIN HANDLER FUNCTION
// ===========================================================================================

// Fungsi utama untuk menangani No Delay Spectate (dipanggil setiap frame)
void HandleSpectate() {
    // VALIDASI: Cek apakah dalam pertandingan aktif
    bool isInActiveMatch = false;
    void* preCheckMatchGame = GamePlay$$get_MatchGame();

    if (preCheckMatchGame) {
        unsigned char *matchInProgressPtr = (unsigned char*)((uintptr_t)preCheckMatchGame + Offsets::BaseGame::MatchInProgress);
        if (matchInProgressPtr) {
            isInActiveMatch = (*matchInProgressPtr != 0);
        }
    }

    if (!isInActiveMatch) {
        // LOGGING: Monitor game state
        static int gameStateCounter = 0;
        if (++gameStateCounter % 900 == 0) { // Log setiap 900 frame (~30 detik pada 30fps)
            // LOGIO("SPECTATE: Game not in active match (MatchInProgress=false). Spectate inactive.");
            gameStateCounter = 0;
        }
        return;
    }

    // Menangani fitur No Delay Spectate
    if (Config.Misc.Spectate) {
        // Jika belum diinisialisasi, setup hooks
        if (!spectateInitialized) {
            if (InstallSpectateHooks()) {
                spectateInitialized = true;
                // LOGIO("SPECTATE: ✅ Hooks installed successfully in active match.");
            } else {
                // LOGIO("SPECTATE: ❌ Failed to install hooks. Some hooks may not be installed.");
            }
        }

        // SIMPLE: Hanya log status tanpa memory manipulation
        static int statusLogCounter = 0;
        if (++statusLogCounter % 900 == 0) { // Log setiap 30 detik
            // LOGIO("SPECTATE: HandleSpectate active - hooks installed and running");
            statusLogCounter = 0;
        }
    }
}

#endif // ARCAMOD_SPECTATE_H
