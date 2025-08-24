//
// Created by araiw on 1/24/2025.
//
#ifndef ARCAMOD_WALLHACKESPNAMECOLORMP_H
#define ARCAMOD_WALLHACKESPNAMECOLORMP_H

void HandleWallhackEspNameColorMP() {
    // Menangani fitur EspNameColorMP
    if (Config.View.Wallhack.EspNameColorMP) {
        if (!Config.View.WallhackHook.EspNameColorMPReady) {
            PATCH("libunity.so", "0x57B83FC", "1F0000F1");
            PATCH("libunity.so", "0x560B5F4", "1F0000F1");
            Config.View.WallhackHook.EspNameColorMPReady = true;
        }
    } else {
        if (Config.View.WallhackHook.EspNameColorMPReady) {
            PATCH("libunity.so", "0x57B83FC", "60010036");
            PATCH("libunity.so", "0x560B5F4", "20070036");
            Config.View.WallhackHook.EspNameColorMPReady = false;
        }
    }
}

#endif //ARCAMOD_WALLHACKESPNAMECOLORMP_H
//#ifndef ARCAMOD_WALLHACKESPNAMECOLORMP_H
//#define ARCAMOD_WALLHACKESPNAMECOLORMP_H
//
//#include <cstdint>
//#include <cstring>
//#include <unistd.h>
//#include <sys/mman.h>
//#include <dlfcn.h>
//#include <cstdio>
//
//// Offset target di libunity.so
//#define TARGET_OFFSET_1 0x5B0CF28  // Offset pertama
//#define TARGET_OFFSET_2 0x418897C  // Offset kedua
//#define TARGET_OFFSET_3 0x8151B00  // Offset ketiga
//
//void ApplyHook(uintptr_t targetAddr) {
//    // Mengatur proteksi memori agar dapat dimodifikasi
//    size_t pageSize = sysconf(_SC_PAGESIZE);
//    uintptr_t pageStart = targetAddr & ~(pageSize - 1);
//    mprotect((void*)pageStart, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);
//
//    // Simpan instruksi asli
//    memcpy(originalCode, (void*)targetAddr, sizeof(originalCode));
//
//    // Instruksi NOP untuk hook (gunakan varian NOP yang diinginkan)
//    uint8_t hookCode[] = { 0x1F, 0x00, 0x00, 0xF1 }; // NOP
//
//    // Pasang hook
//    memcpy((void*)targetAddr, hookCode, sizeof(hookCode));
//
//    // Sinkronisasi cache CPU
//    __builtin___clear_cache((char*)pageStart, (char*)(pageStart + pageSize));
//}
//
//void RemoveHook(uintptr_t targetAddr) {
//    // Mengatur proteksi memori agar dapat dimodifikasi
//    size_t pageSize = sysconf(_SC_PAGESIZE);
//    uintptr_t pageStart = targetAddr & ~(pageSize - 1);
//    mprotect((void*)pageStart, pageSize, PROT_READ | PROT_WRITE | PROT_EXEC);
//
//    // Kembalikan instruksi asli
//    memcpy((void*)targetAddr, originalCode, sizeof(originalCode));
//
//    // Sinkronisasi cache CPU
//    __builtin___clear_cache((char*)pageStart, (char*)(pageStart + pageSize));
//}
//
//void HandleWallhackEspNameColorMP() {
//    // Menangani fitur EspNameColorMP
//    if (Config.View.Wallhack.EspNameColorMP) {
//        if (!Config.View.WallhackHook.EspNameColorMPReady) {
//            // Ambil base address dari libunity.so
//            uintptr_t baseAddr = GetLibBase("libunity.so");
//            if (baseAddr) {
//                uintptr_t targetAddr_1 = baseAddr + TARGET_OFFSET_1;
//                uintptr_t targetAddr_2 = baseAddr + TARGET_OFFSET_2;
//                uintptr_t targetAddr_3 = baseAddr + TARGET_OFFSET_3;
//
//                // Terapkan hook pada setiap offset
//                ApplyHook(targetAddr_1);
//                ApplyHook(targetAddr_2);
//                ApplyHook(targetAddr_3);
//            }
//            Config.View.WallhackHook.EspNameColorMPReady = true;
//        }
//    } else {
//        if (Config.View.WallhackHook.EspNameColorMPReady) {
//            // Ambil base address dari libunity.so
//            uintptr_t baseAddr = GetLibBase("libunity.so");
//            if (baseAddr) {
//                uintptr_t targetAddr_1 = baseAddr + TARGET_OFFSET_1;
//                uintptr_t targetAddr_2 = baseAddr + TARGET_OFFSET_2;
//                uintptr_t targetAddr_3 = baseAddr + TARGET_OFFSET_3;
//
//                // Hapus hook pada setiap offset
//                RemoveHook(targetAddr_1);
//                RemoveHook(targetAddr_2);
//                RemoveHook(targetAddr_3);
//            }
//            Config.View.WallhackHook.EspNameColorMPReady = false;
//        }
//    }
//}
//
//#endif //ARCAMOD_WALLHACKESPNAMECOLORMP_H

