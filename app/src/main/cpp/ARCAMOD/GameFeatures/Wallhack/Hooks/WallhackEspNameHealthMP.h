//
// Created by araiw on 1/24/2025.
//

#ifndef ARCAMOD_WALLHACKESPNAMEHEALTHMP_H
#define ARCAMOD_WALLHACKESPNAMEHEALTHMP_H

// Definisi tipe fungsi untuk GameBase_MatchGameUIScene__NeedShowName
typedef int64_t (*original_match_need_show_name_func)(int64_t a1, _QWORD *a2);

// Pointer fungsi asli
original_match_need_show_name_func originalMatchNeedShowNameFunction = nullptr;

// Flag untuk status hook dan aktivasi
static bool espNameHealthHooksInstalled = false;
static bool espNameHealthActive = false;
static bool espNameHealthInitialized = false;
static bool espNameHealthLogged = false; // Mencegah log berulang

// Offset untuk EspNameHealth - CENTRALIZED: Menggunakan WALLHACK_EspNameHealthMP_Hook dari OffsetDefinitions.h
#define MATCH_NEED_SHOW_NAME_OFFSET OBF(WALLHACK_EspNameHealthMP_Hook)

// Variabel untuk kontrol ESP
static bool debugModeEsp = true; // Set true untuk melihat log diagnostik

// Fungsi untuk memeriksa apakah nama pemain tertentu harus ditampilkan
int64_t MatchNeedShowNameHook(int64_t a1, _QWORD *a2) {
    // Jika a2 null, return 0 seperti pada fungsi asli
    if (a2 == nullptr) {
        return 0;
    }

    // Jika fitur ESP tidak aktif, panggil fungsi asli saja
    if (!espNameHealthActive) {
        return originalMatchNeedShowNameFunction(a1, a2);
    }

    // Log untuk debug
    static bool firstCall = true;
    if (firstCall && debugModeEsp) {
        // LOGIO("EspNameHealth: MatchNeedShowName hooked, mengaktifkan tampilan nama");
        firstCall = false;
    }

    // Dapatkan hasil fungsi asli terlebih dahulu untuk keamanan
    int64_t originalResult = originalMatchNeedShowNameFunction(a1, a2);

    // Jika originalResult adalah 1, fungsi asli sudah menentukan nama harus ditampilkan
    if (originalResult == 1) {
        return 1;
    }

    // Sebelum memaksakan nilai, periksa dulu jika a2 adalah pointer valid
    // Ini sangat penting untuk menghindari crash
    int64_t a2Val = (int64_t) a2;
    if (a2Val <= 0 || a2Val > 0x7FFFFFFFFFFFFFFF) {
        if (debugModeEsp) {
            // LOGEO("EspNameHealth: Invalid a2 pointer detected, returning original result");
        }
        return originalResult;
    }

    // Opsi paling aman: selalu tampilkan nama (return 1)
    return 1;
}

// Fungsi untuk memasang hook
bool SetupEspNameHealthHooks() {
    if (espNameHealthHooksInstalled) {
        return true;
    }

    bool hookSuccessful = false;

    // Hook untuk GameBase_MatchGameUIScene__NeedShowName
    uintptr_t matchNeedShowNameAddr = Tools::GetRealOffsets(OBF("libunity.so"),
                                                            MATCH_NEED_SHOW_NAME_OFFSET);

    if (matchNeedShowNameAddr != 0) {
        // Simpan fungsi asli
        originalMatchNeedShowNameFunction = (original_match_need_show_name_func) matchNeedShowNameAddr;

        // Coba pasang hook
        bool nameHookResult = Tools::Hook(
                (void *) matchNeedShowNameAddr,
                (void *) MatchNeedShowNameHook,
                (void **) &originalMatchNeedShowNameFunction
        );

        if (nameHookResult) {
            // LOGIO("EspNameHealth: Hook berhasil (MatchNeedShowName 0x6410248)");
            hookSuccessful = true;
        } else {
            // LOGEO("EspNameHealth: Hook gagal (MatchNeedShowName)");
        }
    }

    // Set flag bahwa hook telah terpasang
    espNameHealthHooksInstalled = hookSuccessful;

    // LOGIO("EspNameHealth: Total %d/1 hooks berhasil dipasang", hookSuccessful ? 1 : 0);

    return hookSuccessful;
}

// Counter untuk mencegah pemeriksaan berulang
static int espFrameCounter = 0;

void HandleWallhackEspNameHealthMP() {
    // Hanya periksa setiap 300 frame untuk mengurangi log spam
    espFrameCounter++;
    if (espFrameCounter < 300 && espNameHealthInitialized) {
        return;
    }
    espFrameCounter = 0; // Reset counter

    // Menangani fitur EspNameHealthMP
    if (Config.View.Wallhack.EspNameHealthMP) {
        // Setup hooks hanya jika belum diinisialisasi
        if (!espNameHealthInitialized) {
            if (SetupEspNameHealthHooks()) {
                espNameHealthInitialized = true;
                // LOGIO("EspNameHealth: Inisialisasi berhasil - fokus pada tampilan nama");
            } else {
                // LOGEO("EspNameHealth: Gagal menginisialisasi hook");
            }
        }

        // Aktifkan fitur EspNameHealth
        espNameHealthActive = true;
        Config.View.WallhackHook.EspNameHealthMPReady = true;

        // Log hanya sekali
        if (!espNameHealthLogged) {
            // LOGIO("EspNameHealth: Fitur diaktifkan - menampilkan nama pemain");
            espNameHealthLogged = true;
        }
    } else {
        // Nonaktifkan fitur EspNameHealth
        espNameHealthActive = false;
        Config.View.WallhackHook.EspNameHealthMPReady = false;

        // Log hanya sekali
        if (espNameHealthLogged) {
            // LOGIO("EspNameHealth: Fitur dinonaktifkan");
            espNameHealthLogged = false;
        }
    }
}

#endif //ARCAMOD_WALLHACKESPNAMEHEALTHMP_H
