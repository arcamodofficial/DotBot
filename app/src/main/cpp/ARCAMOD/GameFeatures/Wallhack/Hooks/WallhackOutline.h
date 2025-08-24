//
// Created by araiw on 1/24/2025.
//

#ifndef ARCAMOD_WALLHACKOUTLINE_H
#define ARCAMOD_WALLHACKOUTLINE_H

void HandleWallhackOutline() {
    // Menangani fitur Outline - CENTRALIZED: Menggunakan WALLHACK_Outline_Patch dari OffsetDefinitions.h
    if (Config.View.Wallhack.Outline) {
        if (!Config.View.WallhackHook.OutlineReady) {
            PATCH("libunity.so", WALLHACK_Outline_Patch, "200080D2C0035FD6");
            Config.View.WallhackHook.OutlineReady = true;
        }
    } else {
        if (Config.View.WallhackHook.OutlineReady) {
            PATCH("libunity.so", WALLHACK_Outline_Patch, "F5 0F 1D F8 F4 4F 01 A9");
            Config.View.WallhackHook.OutlineReady = false;
        }
    }
}

#endif //ARCAMOD_WALLHACKOUTLINE_H
