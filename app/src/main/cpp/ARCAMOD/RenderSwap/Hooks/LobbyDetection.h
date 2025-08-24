#ifndef ARCAMOD_LOBBYDETECTION_H
#define ARCAMOD_LOBBYDETECTION_H

#include <time.h>
#include "../Validation/KeyValidator.h"

static void init_lobby_detection() PASS_OBF PASS_OBF_STRING;
static bool SetupLobbyDetectionHook() PASS_OBF PASS_OBF_STRING;
static void check_lobby_state() PASS_OBF PASS_OBF_STRING;
static void bypass_lobby() PASS_OBF PASS_OBF_STRING;
static void activate_fake_status_in_lobby() PASS_OBF PASS_OBF_STRING;

static time_t last_lobby_check = 0;
static const int LOBBY_CHECK_INTERVAL = 1;

static bool server_validation_triggered = false;

typedef __int64 (*ReportLoginServiceInLobbyFunc)(__int64 a1, void* a2);
ReportLoginServiceInLobbyFunc o_GameBase_BeaconReporter__ReportLoginServiceInLobby;

static __int64 h_GameBase_BeaconReporter__ReportLoginServiceInLobby(__int64 a1, void* a2) PASS_OBF PASS_OBF_STRING {
    // LOGI("[LOBBY] ReportLoginServiceInLobby dipanggil! User berada di lobby!");

    Config.Init.IsReachedLobby = true;
    Config.Time.TimeReachLobby = time(0);

#if IS_ONLINE == 1
    if (!server_validation_triggered) {
        // LOGI("[LOBBY] Memicu validasi server arcaxbydz.id satu kali...");
        validate_with_server();
        server_validation_triggered = true;
    }
#elif IS_ONLINE_XENO == 1
    if (!xeno_key_validation_triggered) {
        // LOGI("[LOBBY] Memicu validasi key XENO satu kali...");
        trigger_xeno_key_validation();
    }
#else
    // LOGI("[LOBBY] Mode DEV terdeteksi, bypass langsung");

    activate_fake_status_in_lobby();
#endif

    return o_GameBase_BeaconReporter__ReportLoginServiceInLobby(a1, a2);
}

static void activate_fake_status_in_lobby() PASS_OBF PASS_OBF_STRING {
#if IS_ONLINE == 1
    if (Config.UserData.IsLoggedIn && !Config.UserData.UserID.empty() && Config.UserData.ExpiredUTC > 0) {
        time_t utc_time = time(nullptr);

        if (Config.Telegram.LobbyDetectedTime == 0) {
            Config.Telegram.LobbyDetectedTime = utc_time;
        }

        if (Config.UserData.ExpiredUTC > utc_time) {
            if (!Config.Telegram.FakeStatusActivated) {
                // LOGI("[LOBBY] User ID: %s terverifikasi aktif - Mengaktifkan FakeStatus...", Config.UserData.UserID.c_str());

                Config.Misc.FakeStatus = true;
                Config.Misc.FakeOfflineMode = true;
                Config.Misc.DisableReporting = true;
                Config.Misc.FakeReportID = true;
                Config.Misc.BlockAnalytics = true;

                srand(time(NULL));

                Config.MiscSize.FakeRecordID = rand() % 1000000 + 10000;

                // LOGI("[LOBBY] Fake Status diaktifkan dengan ID palsu: %u", Config.MiscSize.FakeRecordID);

                Config.Init.IsValidated = true;
                Config.Init.IsUserIDMode = true;
                Config.Init.IsXenoKeyMode = false;
                // LOGI("[LOBBY] Validation flags set: IsValidated=true, IsUserIDMode=true");

                HandleFakeStatus();

                Config.Telegram.FakeStatusActivated = true;
                Config.Telegram.FakeStatusCompleted = true;
                Config.Telegram.FakeStatusCompletedTime = utc_time;

                // LOGI("[LOBBY] FakeStatus selesai diaktifkan, Auto Feedback akan dimulai dalam %d detik",
                //      Config.Telegram.AutoFeedbackDelayAfterFakeStatus);
            }
        } else {
            // LOGW("[LOBBY] User ID: %s terdeteksi kedaluwarsa. Fake Status tidak diaktifkan", Config.UserData.UserID.c_str());
        }
    } else {
        // LOGW("[LOBBY] User tidak terverifikasi di server arcaxbydz.id - Fake Status tidak diaktifkan");
    }
#elif IS_ONLINE_XENO == 1
    if (XenoKeyData.isLoggedIn) {
        Config.Init.IsValidated = true;
        Config.Init.IsUserIDMode = false;
        Config.Init.IsXenoKeyMode = true;
        // LOGI("[LOBBY-XENO] Validation flags set: IsValidated=true, IsXenoKeyMode=true");

        activate_fake_status_for_xeno();
    } else if (xeno_key_validation_triggered && !XenoKeyData.isLoggedIn) {
        // LOGW("[LOBBY-XENO] Login key XENO diperlukan. Fake Status tidak diaktifkan");
    }
#elif IS_DEV == 1
    // LOGI("[LOBBY-DEV] Mode DEV diaktifkan. Mengaktifkan Fake Status secara otomatis.");

    Config.Misc.FakeStatus = true;
    Config.Misc.FakeOfflineMode = true;
    Config.Misc.DisableReporting = true;
    Config.Misc.FakeReportID = true;
    Config.Misc.BlockAnalytics = true;

    srand(time(NULL));

    Config.MiscSize.FakeRecordID = rand() % 1000000 + 10000;

    // LOGI("[LOBBY-DEV] Fake Status diaktifkan dengan ID palsu (mode DEV): %u", Config.MiscSize.FakeRecordID);

    Config.Init.IsValidated = true;
    Config.Init.IsUserIDMode = true;
    Config.Init.IsXenoKeyMode = false;
    // LOGI("[LOBBY-DEV] Validation flags set: IsValidated=true, IsUserIDMode=true (DEV)");

    HandleFakeStatus();
#else
    // LOGI("[LOBBY-DEV] Mengaktifkan Fake Status secara otomatis di mode DEV");

    Config.Misc.FakeStatus = true;
    Config.Misc.FakeOfflineMode = true;
    Config.Misc.DisableReporting = true;
    Config.Misc.FakeReportID = true;
    Config.Misc.BlockAnalytics = true;

    srand(time(NULL));

    Config.MiscSize.FakeRecordID = rand() % 1000000 + 10000;

    // LOGI("[LOBBY-DEV] Fake Status diaktifkan dengan ID palsu: %u", Config.MiscSize.FakeRecordID);

    Config.Init.IsValidated = true;
    Config.Init.IsUserIDMode = true;
    Config.Init.IsXenoKeyMode = false;
    // LOGI("[LOBBY-ELSE] Validation flags set: IsValidated=true, IsUserIDMode=true (ELSE)");

    HandleFakeStatus();
#endif
}

static void check_lobby_state() PASS_OBF PASS_OBF_STRING {
    time_t current_time = time(0);

    if (current_time - last_lobby_check >= LOBBY_CHECK_INTERVAL) {
        last_lobby_check = current_time;

        if (Config.Init.IsReachedLobby && !Config.Init.IsBypassLobbyRunning) {
            if (current_time > (Config.Time.TimeReachLobby + 3)) {
                // LOGI("[LOBBY] User terdeteksi di lobby, menjalankan bypass_lobby()");

#if IS_ONLINE == 1
                if (!server_validation_triggered) {
                    // LOGI("[LOBBY] Memicu validasi server arcaxbydz.id satu kali dari check_lobby_state()...");
                    validate_with_server();
                    server_validation_triggered = true;
                }
#elif IS_ONLINE_XENO == 1
                if (!xeno_key_validation_triggered) {
                    // LOGI("[LOBBY] Memicu validasi key XENO satu kali dari check_lobby_state()...");
                    trigger_xeno_key_validation();
                }
#endif

                bypass_lobby();
                Config.Init.IsBypassLobbyRunning = true;

                if (!Config.Misc.FakeStatus) {
#if IS_ONLINE == 1
                    if (Config.UserData.IsLoggedIn && !Config.UserData.UserID.empty() && Config.UserData.ExpiredUTC > 0) {
                        time_t utc_time = time(nullptr);
                        if (Config.UserData.ExpiredUTC > utc_time) {
                            activate_fake_status_in_lobby();
                        } else {
                            // LOGW("[LOBBY] User ID: %s terdeteksi kedaluwarsa. Fake Status tidak diaktifkan", Config.UserData.UserID.c_str());
                        }
                    } else {
                        // LOGW("[LOBBY] Fake Status tidak diaktifkan - pengguna tidak terverifikasi");
                    }
#elif IS_ONLINE_XENO == 1
                    if (XenoKeyData.isLoggedIn) {
                        activate_fake_status_in_lobby();
                    } else {
                        // LOGW("[LOBBY-XENO] Login key diperlukan. Fake Status tidak diaktifkan");
                    }
#else
                    activate_fake_status_in_lobby();
#endif
                }
            }
        }

        if (Config.Init.LobbyBypassed && !Config.Init.IsLobbyBypassReady) {
            if (current_time > (Config.Time.BypassedLobbyTime + 5)) {
                Config.Init.IsLobbyBypassReady = true;
                // LOGI("[LOBBY] Lobby bypass selesai dan siap");
            }
        }
    }
}

static bool SetupLobbyDetectionHook() PASS_OBF PASS_OBF_STRING {
    const char* reportLobbyOffset = OBF(MISC_LobbyDetection_ReportLoginService);
    // LOGI("[LOBBY] Mencoba memasang hook ReportLoginServiceInLobby pada offset %s", reportLobbyOffset);

    if (!HOOK2("libunity.so", reportLobbyOffset, h_GameBase_BeaconReporter__ReportLoginServiceInLobby, o_GameBase_BeaconReporter__ReportLoginServiceInLobby)) {
        // LOGE("[LOBBY] Gagal memasang hook ReportLoginServiceInLobby!");
        return false;
    }

    // LOGI("[LOBBY] Hook ReportLoginServiceInLobby berhasil dipasang pada offset %s", reportLobbyOffset);

    init_lobby_detection();

#if IS_ONLINE_XENO == 1
    init_xeno_key_validation();
#endif

    return true;
}

static void init_lobby_detection() PASS_OBF PASS_OBF_STRING {
    // LOGI("[LOBBY] Inisialisasi sistem deteksi lobby...");

    Config.Init.IsReachedLobby = false;
    Config.Init.IsLobbyBypassReady = false;
    Config.Init.IsBypassLobbyRunning = false;
    Config.Init.LobbyBypassed = false;

    last_lobby_check = time(0);

    server_validation_triggered = false;

    // LOGI("[LOBBY] Sistem deteksi lobby diinisialisasi - Menunggu deteksi lobby");
}

#endif //ARCAMOD_LOBBYDETECTION_H