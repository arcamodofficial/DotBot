// app/src/main/cpp/ARCAMOD/Hacks/Misc_Hooks/Hooks/Swim.h
#ifndef ARCAMOD_SWIM_H
#define ARCAMOD_SWIM_H

void HandleSwim() {
    // OPTIMIZED: Mengandalkan unified handler dari EGL.h - hapus crash tracking macro

    // Menangani fitur Swim - CENTRALIZED: Menggunakan MISC_Swim_Patch dari OffsetDefinitions.h
    if (Config.Misc.Swim) {
        if (!Config.MiscHook.SwimPatchReady) {
            PATCH("libunity.so", MISC_Swim_Patch, "C0 03 5F D6");
            Config.MiscHook.SwimPatchReady = true;
        }
    } else {
        if (Config.MiscHook.SwimPatchReady) {
            PATCH("libunity.so", MISC_Swim_Patch, "E9 23 BD 6D");
            Config.MiscHook.SwimPatchReady = false;
        }
    }
}

#endif //ARCAMOD_SWIM_H
