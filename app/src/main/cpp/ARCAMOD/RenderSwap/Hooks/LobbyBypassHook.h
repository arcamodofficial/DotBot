#ifndef ARCAMOD_LOBBYBYPASS_H
#define ARCAMOD_LOBBYBYPASS_H

static void bypass_lobby() PASS_OBF PASS_OBF_STRING {
    // LOGI("Menjalankan bypass untuk fitur di lobby...");

    // Implementasi bypass lobby di sini
    // Misal: menonaktifkan deteksi, membuka fitur tertentu, dll

    Config.Init.LobbyBypassed = true;
    Config.Time.BypassedLobbyTime = time(0);

    // LOGI("Lobby bypass berhasil dijalankan");
}

#endif //ARCAMOD_LOBBYBYPASS_H