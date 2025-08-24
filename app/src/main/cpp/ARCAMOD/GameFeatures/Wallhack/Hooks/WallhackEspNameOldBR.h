//
// Created by araiw on 1/24/2025.
//

//#ifndef ARCAMOD_WALLHACKESPNAMEOLDBR_H
//#define ARCAMOD_WALLHACKESPNAMEOLDBR_H
//void HandleWallhackEspNameOldBR() {
//    // Menangani EspNameOldBR
//    if (Config.View.Wallhack.EspNameOldBR) {
//        if (!Config.View.WallhackHook.EspNameOldBRReady) {
//            PATCH("libunity.so", "0x5719920", "35008052");
//            PATCH("libunity.so", "0x65C31E4", "1F0000F1");
//            Config.View.WallhackHook.EspNameOldBRReady = true;
//        }
//    } else {
//        if (Config.View.WallhackHook.EspNameOldBRReady) {
//            PATCH("libunity.so", "0x5719920", "F503002A");
//            PATCH("libunity.so", "0x65C31E4", "C00E0036");
//            Config.View.WallhackHook.EspNameOldBRReady = false;
//        }
//    }
//}
//#endif //ARCAMOD_WALLHACKESPNAMEOLDBR_H

#ifndef ARCAMOD_WALLHACKESPNAMEOLDBR_H
#define ARCAMOD_WALLHACKESPNAMEOLDBR_H

// Include standard C libraries
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// Pattern untuk mencari fungsi BRAzurGameUIScene
const char *PATTERN_BRAZUR = "\x00\x00\x80\x52\x00\x00\x00\x14\x00\x00\x80\x52\x00\x00\x00\x14";
const char *MASK_BRAZUR = "xxxxxxxxxxxxxxxx";

// Pattern untuk mencari fungsi PawnTopNameHUD
const char *PATTERN_PAWN = "\x00\x00\x80\x52\x00\x00\x00\x14\x00\x00\x80\x52\x00\x00\x00\x14";
const char *MASK_PAWN = "xxxxxxxxxxxxxxxx";

// Offset untuk BRAzurGameUIScene._LBP_OnPawnTopNameHudAdd
const uint32_t OFFSET_BRAZUR_FUNC = 0x15C;
// Offset untuk PawnTopNameHUD.Spawn
const uint32_t OFFSET_PAWN_FUNC = 0x3F0;

// Konstanta untuk patch
const char *ENABLE_CODE1 = "35008052";
const char *ENABLE_CODE2 = "1F0000F1";
const char *DISABLE_CODE1 = "F503002A";
const char *DISABLE_CODE2 = "88000036";

// Default offset untuk fallback - CENTRALIZED: Menggunakan WALLHACK_EspNameOldBR_* dari OffsetDefinitions.h
#define DEFAULT_BRAZUR_OFFSET WALLHACK_EspNameOldBR_DefaultBrazur
#define DEFAULT_PAWN_OFFSET WALLHACK_EspNameOldBR_DefaultPawn


// Debug log tag
#define WALLHACK_TAG "ARCAMOD_WALLHACK"

// Enable atau disable log (0 = disable, 1 = enable)
#define ENABLE_WALLHACK_LOG 0

#if ENABLE_WALLHACK_LOG
// Implementasi fungsi log kustom yang hanya menggunakan printf untuk debugging
void WallhackLog(const char* format, ...) {
    // Buffer untuk pesan
    char buffer[1024];

    // Format dengan tag
    snprintf(buffer, sizeof(buffer), "[%s] ", WALLHACK_TAG);
    size_t prefix_len = strlen(buffer);

    // Format pesan utama
    va_list args;
    va_start(args, format);
    vsnprintf(buffer + prefix_len, sizeof(buffer) - prefix_len, format, args);
    va_end(args);

    // Output ke logcat via printf (akan diarahkan ke logcat di Android)
    printf("%s\n", buffer);

    // Juga simpan ke file log jika perlu
    FILE* logFile = fopen(OBF("/data/data/com.garena.game.codm/files/wallhack_log.txt"), "a");
    if (logFile) {
        fprintf(logFile, "%s\n", buffer);
        fclose(logFile);
    }
}
#else
// Dummy function yang tidak melakukan apa-apa saat logging dinonaktifkan
#define WallhackLog(...) ((void)0)
#endif

// Fungsi untuk mencari offset menggunakan pattern assembly
uintptr_t FindOffsetByAssemblyPattern(const char *pattern, const char *mask) {
    uintptr_t libBase = GetLibBase(OBF("libunity.so"));
    if (!libBase) {
        WallhackLog(OBF("Gagal mendapatkan base address libunity.so"));
        return 0;
    }

    WallhackLog(OBF("Base Address libunity.so: 0x%lx"), libBase);

    FILE *fp = fopen(OBF("/proc/self/mem"), "r");
    if (!fp) {
        WallhackLog(OBF("Gagal membuka /proc/self/mem"));
        return 0;
    }

    uintptr_t offset = 0;
    char buffer[4096];
    uintptr_t currentAddr = libBase;
    size_t patternLen = strlen(mask);

    WallhackLog(OBF("Memulai pencarian pattern..."));

    while (fread(buffer, 1, sizeof(buffer), fp) > 0) {
        for (size_t i = 0; i < sizeof(buffer) - patternLen; i++) {
            bool found = true;
            for (size_t j = 0; j < patternLen; j++) {
                if (mask[j] == 'x' && buffer[i + j] != pattern[j]) {
                    found = false;
                    break;
                }
            }
            if (found) {
                offset = currentAddr + i;
                WallhackLog(OBF("Pattern ditemukan di alamat: 0x%lx"), offset);
                fclose(fp);
                return offset;
            }
        }
        currentAddr += sizeof(buffer);
    }
    WallhackLog(OBF("Pattern tidak ditemukan"));
    fclose(fp);
    return 0;
}

void HandleWallhackEspNameOldBR() {
    // Variabel statis untuk menyimpan offset yang ditemukan
    static uintptr_t baseOffset1 = 0;
    static uintptr_t baseOffset2 = 0;
    static char offsetStr1[32] = DEFAULT_BRAZUR_OFFSET;
    static char offsetStr2[32] = DEFAULT_PAWN_OFFSET;
    static bool initialized = false;

    // Cari dan persiapkan offset hanya sekali
    if (!initialized) {
        WallhackLog(OBF("Inisialisasi WallhackEspNameOldBR..."));

        baseOffset1 = FindOffsetByAssemblyPattern(PATTERN_BRAZUR, MASK_BRAZUR);
        baseOffset2 = FindOffsetByAssemblyPattern(PATTERN_PAWN, MASK_PAWN);

        if (baseOffset1) {
            snprintf(offsetStr1, sizeof(offsetStr1), "0x%lx", baseOffset1 + OFFSET_BRAZUR_FUNC);
            WallhackLog(OBF("BRAzurGameUIScene offset: %s (base: 0x%lx + 0x%x)"),
                        offsetStr1, baseOffset1, OFFSET_BRAZUR_FUNC);
        } else {
            WallhackLog(OBF("Menggunakan default BRAzurGameUIScene offset: %s"), offsetStr1);
        }

        if (baseOffset2) {
            snprintf(offsetStr2, sizeof(offsetStr2), "0x%lx", baseOffset2 + OFFSET_PAWN_FUNC);
            WallhackLog(OBF("PawnTopNameHUD offset: %s (base: 0x%lx + 0x%x)"),
                        offsetStr2, baseOffset2, OFFSET_PAWN_FUNC);
        } else {
            WallhackLog(OBF("Menggunakan default PawnTopNameHUD offset: %s"), offsetStr2);
        }

        initialized = true;
        WallhackLog(OBF("Inisialisasi WallhackEspNameOldBR selesai"));
    }

    if (Config.View.Wallhack.EspNameOldBR) {
        if (!Config.View.WallhackHook.EspNameOldBRReady) {
            // Gunakan Tools::Patch langsung alih-alih makro PATCH
            WallhackLog(OBF("Mengaktifkan EspNameOldBR..."));
            bool patch1 = Tools::Patch(OBF("libunity.so"), offsetStr1, ENABLE_CODE1);
            bool patch2 = Tools::Patch(OBF("libunity.so"), offsetStr2, ENABLE_CODE2);

            if (patch1 && patch2) {
                WallhackLog(OBF("EspNameOldBR berhasil diaktifkan"));
                Config.View.WallhackHook.EspNameOldBRReady = true;
            } else {
                WallhackLog(OBF("Gagal mengaktifkan EspNameOldBR (Patch1: %s, Patch2: %s)"),
                            patch1 ? OBF("Berhasil") : OBF("Gagal"),
                            patch2 ? OBF("Berhasil") : OBF("Gagal"));
            }
        }
    } else {
        if (Config.View.WallhackHook.EspNameOldBRReady) {
            // Gunakan Tools::Patch langsung alih-alih makro PATCH
            WallhackLog(OBF("Menonaktifkan EspNameOldBR..."));
            bool patch1 = Tools::Patch(OBF("libunity.so"), offsetStr1, DISABLE_CODE1);
            bool patch2 = Tools::Patch(OBF("libunity.so"), offsetStr2, DISABLE_CODE2);

            if (patch1 && patch2) {
                WallhackLog(OBF("EspNameOldBR berhasil dinonaktifkan"));
                Config.View.WallhackHook.EspNameOldBRReady = false;
            } else {
                WallhackLog(OBF("Gagal menonaktifkan EspNameOldBR (Patch1: %s, Patch2: %s)"),
                            patch1 ? OBF("Berhasil") : OBF("Gagal"),
                            patch2 ? OBF("Berhasil") : OBF("Gagal"));
            }
        }
    }
}

#endif //ARCAMOD_WALLHACKESPNAMEOLDBR_H