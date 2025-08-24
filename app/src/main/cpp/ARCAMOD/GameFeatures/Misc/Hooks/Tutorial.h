// app/src/main/cpp/ARCAMOD/Hacks/Misc_Hooks/Tutorial.h
#ifndef ARCAMOD_TUTORIAL_H
#define ARCAMOD_TUTORIAL_H

void HandleTutorial() {
    // OPTIMIZED: Mengandalkan unified handler dari EGL.h - hapus crash tracking macro

    // Menangani fitur Tutorial - CENTRALIZED: Menggunakan MISC_Tutorial_Patch dari OffsetDefinitions.h
    if (Config.Misc.Tutorial) {
        if (!Config.MiscHook.TutorialPatchReady) {
            PATCH("libunity.so", MISC_Tutorial_Patch, "000080D2C0035FD6");
            Config.MiscHook.TutorialPatchReady = true;
        }
    } else {
        if (Config.MiscHook.TutorialPatchReady) {
            PATCH("libunity.so", MISC_Tutorial_Patch, "F3 0F 1E F8 FD 7B 01 A9");
            Config.MiscHook.TutorialPatchReady = false;
        }
    }
}

#endif //ARCAMOD_TUTORIAL_H
