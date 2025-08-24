//
// Created by araiw on 1/24/2025.
//

#ifndef ARCAMOD_WALLHACKESPNAMEHEALTHBR_H
#define ARCAMOD_WALLHACKESPNAMEHEALTHBR_H

void HandleWallhackEspNameHealthBR() {
    // Menangani fitur EspNameHealthBR - CENTRALIZED: Menggunakan WALLHACK_EspNameHealthBR_* dari OffsetDefinitions.h
    if (Config.View.Wallhack.EspNameHealthBR) {
        if (!Config.View.WallhackHook.EspNameHealthBRReady) {
            PATCH("libunity.so", WALLHACK_EspNameHealthBR_Patch1, "35008052");
            PATCH("libunity.so", WALLHACK_EspNameHealthBR_Patch2, "1F0000F1");
            Config.View.WallhackHook.EspNameHealthBRReady = true;
        }
    } else {
        if (Config.View.WallhackHook.EspNameHealthBRReady) {
            PATCH("libunity.so", WALLHACK_EspNameHealthBR_Patch1, "F5 03 00 2A");
            PATCH("libunity.so", WALLHACK_EspNameHealthBR_Patch2, "9A 11 EA 96");
            Config.View.WallhackHook.EspNameHealthBRReady = false;
        }
    }
}

#endif //ARCAMOD_WALLHACKESPNAMEHEALTHBR_H
