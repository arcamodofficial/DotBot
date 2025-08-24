//
// Created by araiw on 1/24/2025.
//

#ifndef ARCAMOD_WALLHACKBOOSTFPS_H
#define ARCAMOD_WALLHACKBOOSTFPS_H

void HandleWallhackBoostFPS() {
    // Menangani fitur BoostFPS - CENTRALIZED: Menggunakan WALLHACK_BoostFPS_* dari OffsetDefinitions.h
    if (Config.View.Wallhack.BoostFPS) {
        if (!Config.View.WallhackHook.BoostFPSReady) {
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch1, "200080D2C0035FD6");
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch2, "200080D2C0035FD6");
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch3, "C00080D2C0035FD6");
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch4, "002480D2C0035FD6");
            Config.View.WallhackHook.BoostFPSReady = true;
        }
    } else {
        if (Config.View.WallhackHook.BoostFPSReady) {
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch1, "F30F1EF8FD7B01A9");
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch2, "087840B91F0D0071");
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch3, "F30F1EF8FD7B01A9");
            PATCH("libunity.so", WALLHACK_BoostFPS_Patch4, "FF4301D1F70B00F9");
            Config.View.WallhackHook.BoostFPSReady = false;
        }
    }
}

#endif //ARCAMOD_WALLHACKBOOSTFPS_H