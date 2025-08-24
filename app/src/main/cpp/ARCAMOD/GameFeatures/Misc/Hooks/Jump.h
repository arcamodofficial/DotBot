// app/src/main/cpp/ARCAMOD/Hacks/Misc_Hooks/Hooks/Jump.h
#ifndef ARCAMOD_JUMP_H
#define ARCAMOD_JUMP_H

void HandleJump() {
    // OPTIMIZED: Mengandalkan unified handler dari EGL.h - hapus crash tracking macro

    // Menangani fitur Jump - CENTRALIZED: Menggunakan MISC_Jump_* dari OffsetDefinitions.h
    if (Config.Misc.Jump) {
        if (!Config.MiscHook.JumpPatchReady) {
            PATCH("libunity.so", MISC_Jump_Patch1, "00D0251EC0035FD6");
            PATCH("libunity.so", MISC_Jump_Patch2, "00D0251EC0035FD6");
            PATCH("libunity.so", MISC_Jump_Patch3, "00D0251EC0035FD6");
            PATCH("libunity.so", MISC_Jump_Patch4, "00D0251EC0035FD6");
            PATCH("libunity.so", MISC_Jump_Patch5, "00D0251EC0035FD6");
            PATCH("libunity.so", MISC_Jump_Patch6, "1F2003D5C0035FD6");
            Config.MiscHook.JumpPatchReady = true;
        }
    } else {
        if (Config.MiscHook.JumpPatchReady) {
            PATCH("libunity.so", MISC_Jump_Patch1, "F3 0F 1E F8 FD 7B 01 A9");
            PATCH("libunity.so", MISC_Jump_Patch2, "00 8C 52 BD C0 03 5F D6");
            PATCH("libunity.so", MISC_Jump_Patch3, "E8 0F 1D FC F4 4F 01 A9");
            PATCH("libunity.so", MISC_Jump_Patch4, "E8 0F 1E FC FD 7B 01 A9");
            PATCH("libunity.so", MISC_Jump_Patch5, "E8 0F 1E FC F3 07 00 F9");
            PATCH("libunity.so", MISC_Jump_Patch6, "E8 0F 1E FC F3 07 00 F9");
            Config.MiscHook.JumpPatchReady = false;
        }
    }
}

#endif //ARCAMOD_JUMP_H