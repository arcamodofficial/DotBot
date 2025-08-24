// Created by @arcamod on 31/12/2024.
// EmulatorHooks.h - Optimasi untuk emulator

#ifndef ARCAMOD_EMULATORHOOKS_H
#define ARCAMOD_EMULATORHOOKS_H

// Original function pointers
void* o_EmulatorManager__IsEmulator;
void* o_EmulatorManager__IsValidEmulatorOrDevice;
void* o_PlatformWrapper_Android__GetEmulatorQualityLevel;
void* o_PlatformWrapper_Android__GetEmulatorFrameRateLevel;
void* o_PlatformWrapper_Android__GetEmulatorResolutionHeight;
void* o_GameUI_Room_RoomBaseController__IsEmulatorLimit;
void* o_GameUI_Room_RoomDataStore__CheckEmulatorPlayers;
void* o_GameEngine_SystemSetting__DetectedMemoryCritical;
void* o_GameEngine_SystemSetting__IsMemoryDangerous;
void* o_GameEngine_SystemSetting__IsRuntimeMemoryDangerous;
void* o_GameEngine_SystemSetting__IsLowMemoryDevice;
void* o_GameEngine_DeviceUtil__GetMemorySize;
void* o_UnityEngine_Application__add_lowMemory;

// Hook untuk EmulatorManager__IsEmulator - Nonaktifkan deteksi emulator
long long h_EmulatorManager__IsEmulator(long long a1) {
    // Return false (0) untuk menonaktifkan deteksi emulator
    return 0;
}

// Hook untuk EmulatorManager__IsValidEmulatorOrDevice - Semua emulator valid
long long h_EmulatorManager__IsValidEmulatorOrDevice(long long a1) {
    // Return true (1) untuk memperbolehkan semua emulator
    return 1;
}

// Hook untuk PlatformWrapper_Android__GetEmulatorQualityLevel - Kualitas maksimum
long long h_PlatformWrapper_Android__GetEmulatorQualityLevel(long long a1) {
    // Return 3 untuk kualitas maksimum
    LOGI("[EMULATOR] Setting max quality level");
    return 3;
}

// Hook untuk PlatformWrapper_Android__GetEmulatorFrameRateLevel - FPS tinggi
long long h_PlatformWrapper_Android__GetEmulatorFrameRateLevel(long long a1) {
    // Return 4 untuk framerate maksimum (120fps)
    LOGI("[EMULATOR] Setting max framerate level");
    return 4;
}

// Hook untuk PlatformWrapper_Android__GetEmulatorResolutionHeight - Resolusi tinggi
long long h_PlatformWrapper_Android__GetEmulatorResolutionHeight(long long a1) {
    // Return 1080 untuk resolusi HD
    LOGI("[EMULATOR] Setting high resolution");
    return 1080;
}

// Hook untuk GameUI_Room_RoomBaseController__IsEmulatorLimit - Hilangkan batasan level
long long h_GameUI_Room_RoomBaseController__IsEmulatorLimit(long long a1) {
    // Return false (0) untuk menghilangkan batasan level
    return 0;
}

// Hook untuk GameUI_Room_RoomDataStore__CheckEmulatorPlayers - Bypass pemeriksaan emulator
long long h_GameUI_Room_RoomDataStore__CheckEmulatorPlayers(long long a1) {
    // Hindari pemeriksaan pemain emulator
    // Setel flag "HasEmulatorPlayers" ke false (0)
    if (a1) {
        *((char*)(a1 + 376)) = 0;
    }
    return 0;
}

// Hook untuk GameEngine_SystemSetting__DetectedMemoryCritical - Mencegah deteksi memori kritis
long long h_GameEngine_SystemSetting__DetectedMemoryCritical() {
    // Return false (0) untuk menghindari deteksi memori kritis
    LOGI("[MEMORY] Memori kritis diabaikan (mencegah crash)");
    return 0;
}

// Hook untuk GameEngine_SystemSetting__IsMemoryDangerous - Mencegah deteksi memori berbahaya
long long h_GameEngine_SystemSetting__IsMemoryDangerous(long long a1) {
    // Return false (0) untuk menghindari deteksi memori berbahaya
    return 0;
}

// Hook untuk GameEngine_SystemSetting__IsRuntimeMemoryDangerous - Mencegah deteksi memori runtime berbahaya
long long h_GameEngine_SystemSetting__IsRuntimeMemoryDangerous(long long a1) {
    // Return false (0) untuk menghindari deteksi memori runtime berbahaya
    return 0;
}

// Hook untuk GameEngine_SystemSetting__IsLowMemoryDevice - Mencegah deteksi perangkat dengan memori rendah
long long h_GameEngine_SystemSetting__IsLowMemoryDevice() {
    // Return false (0) untuk menonaktifkan deteksi memori rendah
    return 0;
}

// Hook untuk GameEngine_DeviceUtil__GetMemorySize - Laporkan memori sistem yang besar
long long h_GameEngine_DeviceUtil__GetMemorySize() {
    // Return 8192 (8GB) untuk melaporkan ukuran memori yang besar
    LOGI("[MEMORY] Melaporkan memori sistem tinggi: 8192MB");
    return 8192;
}

// Hook untuk UnityEngine_Application__add_lowMemory - Mencegah pendaftaran callback memori rendah
long long h_UnityEngine_Application__add_lowMemory(long long a1, long long a2) {
    // Biarkan pendaftaran terjadi tapi jangan ijinkan callback dipanggil
    LOGI("[MEMORY] Mencegah callback memori rendah");
    // Kembalikan a1 sebagai dummy, tanpa benar-benar memanggil fungsi asli
    return a1;
}

// Inisialisasi hook emulator
bool SetupEmulatorOptimizationHooks() {
    LOGI("[EMULATOR] Setting up emulator optimization hooks");
    bool success = true;

    // Hook EmulatorManager
    if (!HOOK2("libunity.so", OBF("0x4E75F58"), h_EmulatorManager__IsEmulator, o_EmulatorManager__IsEmulator)) {
        LOGE("[EMULATOR] Failed to hook EmulatorManager__IsEmulator");
        success = false;
    }

    // Hook IsValidEmulatorOrDevice
    if (!HOOK2("libunity.so", OBF("0x4E76CEC"), h_EmulatorManager__IsValidEmulatorOrDevice, o_EmulatorManager__IsValidEmulatorOrDevice)) {
        LOGE("[EMULATOR] Failed to hook EmulatorManager__IsValidEmulatorOrDevice");
        success = false;
    }

    // Hook QualityLevel
    if (!HOOK2("libunity.so", OBF("0x5D3E020"), h_PlatformWrapper_Android__GetEmulatorQualityLevel, o_PlatformWrapper_Android__GetEmulatorQualityLevel)) {
        LOGE("[EMULATOR] Failed to hook PlatformWrapper_Android__GetEmulatorQualityLevel");
        success = false;
    }

    // Hook FrameRateLevel
    if (!HOOK2("libunity.so", OBF("0x5D3E0D0"), h_PlatformWrapper_Android__GetEmulatorFrameRateLevel, o_PlatformWrapper_Android__GetEmulatorFrameRateLevel)) {
        LOGE("[EMULATOR] Failed to hook PlatformWrapper_Android__GetEmulatorFrameRateLevel");
        success = false;
    }

    // Hook Resolution
    if (!HOOK2("libunity.so", OBF("0x5D3E180"), h_PlatformWrapper_Android__GetEmulatorResolutionHeight, o_PlatformWrapper_Android__GetEmulatorResolutionHeight)) {
        LOGE("[EMULATOR] Failed to hook PlatformWrapper_Android__GetEmulatorResolutionHeight");
        success = false;
    }

    // Hook RoomLevelLimit
    if (!HOOK2("libunity.so", OBF("0x7EAABA4"), h_GameUI_Room_RoomBaseController__IsEmulatorLimit, o_GameUI_Room_RoomBaseController__IsEmulatorLimit)) {
        LOGE("[EMULATOR] Failed to hook GameUI_Room_RoomBaseController__IsEmulatorLimit");
        success = false;
    }
    
    // Hook CheckEmulatorPlayers
    if (!HOOK2("libunity.so", OBF("0x976E548"), h_GameUI_Room_RoomDataStore__CheckEmulatorPlayers, o_GameUI_Room_RoomDataStore__CheckEmulatorPlayers)) {
        LOGE("[EMULATOR] Failed to hook GameUI_Room_RoomDataStore__CheckEmulatorPlayers");
        success = false;
    }
    
    // MEMORY PROTECTION HOOKS - Anti-Crash
    
    // Hook DetectedMemoryCritical
    if (!HOOK2("libunity.so", OBF("0x6BBCF78"), h_GameEngine_SystemSetting__DetectedMemoryCritical, o_GameEngine_SystemSetting__DetectedMemoryCritical)) {
        LOGE("[MEMORY] Failed to hook GameEngine_SystemSetting__DetectedMemoryCritical");
        success = false;
    }
    
    // Hook IsMemoryDangerous
    if (!HOOK2("libunity.so", OBF("0x6BB17AC"), h_GameEngine_SystemSetting__IsMemoryDangerous, o_GameEngine_SystemSetting__IsMemoryDangerous)) {
        LOGE("[MEMORY] Failed to hook GameEngine_SystemSetting__IsMemoryDangerous");
        success = false;
    }
    
    // Hook IsRuntimeMemoryDangerous
    if (!HOOK2("libunity.so", OBF("0x6BBF880"), h_GameEngine_SystemSetting__IsRuntimeMemoryDangerous, o_GameEngine_SystemSetting__IsRuntimeMemoryDangerous)) {
        LOGE("[MEMORY] Failed to hook GameEngine_SystemSetting__IsRuntimeMemoryDangerous");
        success = false;
    }
    
    // Hook IsLowMemoryDevice
    if (!HOOK2("libunity.so", OBF("0x6B9D230"), h_GameEngine_SystemSetting__IsLowMemoryDevice, o_GameEngine_SystemSetting__IsLowMemoryDevice)) {
        LOGE("[MEMORY] Failed to hook GameEngine_SystemSetting__IsLowMemoryDevice");
        success = false;
    }
    
    // Hook GetMemorySize
    if (!HOOK2("libunity.so", OBF("0x5158DD0"), h_GameEngine_DeviceUtil__GetMemorySize, o_GameEngine_DeviceUtil__GetMemorySize)) {
        LOGE("[MEMORY] Failed to hook GameEngine_DeviceUtil__GetMemorySize");
        success = false;
    }
    
    // Hook add_lowMemory
    if (!HOOK2("libunity.so", OBF("0xAA6288C"), h_UnityEngine_Application__add_lowMemory, o_UnityEngine_Application__add_lowMemory)) {
        LOGE("[MEMORY] Failed to hook UnityEngine_Application__add_lowMemory");
        success = false;
    }

    if (success) {
        LOGI("[EMULATOR] All emulator optimization and anti-crash hooks successfully installed");
    } else {
        LOGE("[EMULATOR] Some emulator optimization or anti-crash hooks failed to install");
    }

    return success;
}

#endif //ARCAMOD_EMULATORHOOKS_H 