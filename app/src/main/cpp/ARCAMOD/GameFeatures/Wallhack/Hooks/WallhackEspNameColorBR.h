//
// Created by araiw on 1/24/2025.
//
#ifndef ARCAMOD_WALLHACKESPNAMECOLORBR_H
#define ARCAMOD_WALLHACKESPNAMECOLORBR_H

void HandleWallhackEspNameColorBR() {
    // Menangani fitur EspNameColorBR - CENTRALIZED: Menggunakan WALLHACK_EspNameColorBR_* dari OffsetDefinitions.h
    if (Config.View.Wallhack.EspNameColorBR) {
        if (!Config.View.WallhackHook.EspNameColorBRReady) {
            PATCH("libunity.so", WALLHACK_EspNameColorBR_Patch1, "35008052");
            Config.View.WallhackHook.EspNameColorBRReady = true;
        }
    } else {
        if (Config.View.WallhackHook.EspNameColorBRReady) {
            PATCH("libunity.so", WALLHACK_EspNameColorBR_Patch1, "F5 03 00 2A");
            Config.View.WallhackHook.EspNameColorBRReady = false;
        }
    }
}

#endif //ARCAMOD_WALLHACKESPNAMECOLORBR_H
//#ifndef ARCAMOD_WALLHACKESPNAMECOLORBR_H
//#define ARCAMOD_WALLHACKESPNAMECOLORBR_H
//
//// Instruksi untuk hook
//#define HOOK_CODE_1 { 0x35, 0x00, 0x80, 0x52 } // Offset 0x4C03FC8
//#define HOOK_CODE_2 { 0x1F, 0x00, 0x00, 0xF1 } // Offset 0x5B0BA8C
//
//// Menyimpan instruksi asli sebelum dipasang hook
//uint8_t originalCode1[4] = {0};
//uint8_t originalCode2[4] = {0};
//
//void HandleWallhackEspNameColorBR() {
//    // Menangani fitur EspNameColorBR
//    if (Config.View.Wallhack.EspNameColorBR) {
//        if (!Config.View.WallhackHook.EspNameColorBRReady) {
//            // Apply hook pada offset pertama (0x4C03FC8)
//            uintptr_t baseAddr = GetLibBase("libunity.so");
//            if (baseAddr) {
//                uintptr_t targetAddr1 = baseAddr + 0x4C03FC8;
//                // Mengatur proteksi memori agar dapat dimodifikasi
//                size_t pageSize = sysconf(_SC_PAGESIZE);
//                uintptr_t pageStart = targetAddr1 & ~(pageSize - 1);
//                mprotect((void*)pageStart, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);
//
//                // Simpan instruksi asli sebelum memasang hook
//                memcpy(originalCode1, (void*)targetAddr1, sizeof(originalCode1));
//
//                // Pasang hook pertama (35008052)
//                uint8_t hookCode1[] = HOOK_CODE_1;
//                memcpy((void*)targetAddr1, hookCode1, sizeof(hookCode1));
//
//                // Sinkronisasi cache CPU
//                __builtin___clear_cache((char*)pageStart, (char*)(pageStart + pageSize));
//            }
//
//            // Apply hook pada offset kedua (0x5B0BA8C)
//            if (baseAddr) {
//                uintptr_t targetAddr2 = baseAddr + 0x5B0BA8C;
//                // Mengatur proteksi memori agar dapat dimodifikasi
//                size_t pageSize = sysconf(_SC_PAGESIZE);
//                uintptr_t pageStart2 = targetAddr2 & ~(pageSize - 1);
//                mprotect((void*)pageStart2, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);
//
//                // Simpan instruksi asli sebelum memasang hook
//                memcpy(originalCode2, (void*)targetAddr2, sizeof(originalCode2));
//
//                // Pasang hook kedua (1F0000F1)
//                uint8_t hookCode2[] = HOOK_CODE_2;
//                memcpy((void*)targetAddr2, hookCode2, sizeof(hookCode2));
//
//                // Sinkronisasi cache CPU
//                __builtin___clear_cache((char*)pageStart2, (char*)(pageStart2 + pageSize));
//            }
//
//            // Tandai hook telah siap
//            Config.View.WallhackHook.EspNameColorBRReady = true;
//        }
//    } else {
//        if (Config.View.WallhackHook.EspNameColorBRReady) {
//            // Menonaktifkan hook jika fitur dimatikan
//            uintptr_t baseAddr = GetLibBase("libunity.so");
//            if (baseAddr) {
//                uintptr_t targetAddr1 = baseAddr + 0x4C03FC8;
//                size_t pageSize = sysconf(_SC_PAGESIZE);
//                uintptr_t pageStart = targetAddr1 & ~(pageSize - 1);
//                mprotect((void*)pageStart, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);
//
//                // Kembalikan instruksi asli pada offset pertama
//                memcpy((void*)targetAddr1, originalCode1, sizeof(originalCode1));  // Menggunakan originalCode1
//                __builtin___clear_cache((char*)pageStart, (char*)(pageStart + pageSize));
//
//                uintptr_t targetAddr2 = baseAddr + 0x5B0BA8C;
//                uintptr_t pageStart2 = targetAddr2 & ~(pageSize - 1);
//                mprotect((void*)pageStart2, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);
//
//                // Kembalikan instruksi asli pada offset kedua
//                memcpy((void*)targetAddr2, originalCode2, sizeof(originalCode2));  // Menggunakan originalCode2
//                __builtin___clear_cache((char*)pageStart2, (char*)(pageStart2 + pageSize));
//            }
//
//            // Tandai hook telah dinonaktifkan
//            Config.View.WallhackHook.EspNameColorBRReady = false;
//        }
//    }
//}
//
//#endif // ARCAMOD_WALLHACKESPNAMECOLORBR_H
