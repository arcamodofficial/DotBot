#ifndef ARCAMOD_SETTINGS_H
#define ARCAMOD_SETTINGS_H

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <chrono>
#include <vector>
#include <exception>
#include <functional>
#include "ConfigManager.h"
#include "../../RenderSwap/Validation/KeyValidator.h"

// ❌ DISABLED: SmartFPS completely disabled for testing
/*
namespace SmartFPS {
    extern bool enabled;
}
*/

// namespace ResourceOptimization {
//     extern bool highQualityMode;
//     extern void SetHighQualityMode(bool enable);
//     extern void SetOptimizationMode(bool enable);
// }

using json = nlohmann::json;

class Settings {
private:
    static const std::string SETTINGS_FILE;

    static std::vector<std::string> getSettingsFilePaths() {
        return {
                OBF("/data/data/com.garena.game.codm/files/.cache_x64"),
                OBF("/data/data/com.garena.game.codm/files/.runtime_config"),
                OBF("/data/data/com.garena.game.codm/files/.system_data"),
                OBF("/data/data/com.garena.game.codm/files/.cache_prefs")
        };
    }

    static std::string getActiveSettingsFile() {
        auto paths = getSettingsFilePaths();

        for (const auto& path : paths) {
            if (fileExists(path)) {
                return path;
            }
        }

        static int rotationIndex = 0;
        rotationIndex = (rotationIndex + 1) % paths.size();
        return paths[rotationIndex];
    }

    static void rotateSettingsFile() {
        auto paths = getSettingsFilePaths();
        std::string currentFile = getActiveSettingsFile();

        for (size_t i = 0; i < paths.size(); i++) {
            if (fileExists(paths[i])) {
                size_t nextIndex = (i + 1) % paths.size();
                std::string nextFile = paths[nextIndex];

                std::ifstream src(paths[i], std::ios::binary);
                std::ofstream dst(nextFile, std::ios::binary);
                dst << src.rdbuf();
                src.close();
                dst.close();

                remove(paths[i].c_str());

                // LOGIO("RotateSettings: File rotated from %zu to %zu", i, nextIndex);
                break;
            }
        }
    }

    static bool fileExists(const std::string &filename) {
        struct stat buffer;
        return (stat(filename.c_str(), &buffer) == 0);
    }

    static std::string generateDeviceSignature() {
        std::string signature;

        // LOGIO("DeviceSignature: DeviceID = '%s'", Config.UserData.DeviceID.c_str());
        // LOGIO("DeviceSignature: UserID = '%s'", Config.UserData.UserID.c_str());
        // LOGIO("DeviceSignature: ExpiredUTC = %ld", Config.UserData.ExpiredUTC);

        if (!Config.UserData.DeviceID.empty()) {
            signature += Config.UserData.DeviceID;
        } else {
            signature += OBF("UNKNOWN_DEVICE");
            // LOGIO("DeviceSignature: Using UNKNOWN_DEVICE fallback");
        }

        if (!Config.UserData.UserID.empty()) {
            signature += Config.UserData.UserID;
        } else {
            signature += OBF("UNKNOWN_USER");
            // LOGIO("DeviceSignature: Using UNKNOWN_USER fallback");
        }

        signature += std::to_string(Config.UserData.ExpiredUTC);
        signature += OBF("ARCAMOD_v1.6.51.8_9847");

        // LOGIO("DeviceSignature: Raw signature = '%s'", signature.c_str());

        std::hash<std::string> hasher;
        std::string hashed = std::to_string(hasher(signature));
        // LOGIO("DeviceSignature: Hashed signature = '%s'", hashed.c_str());
        return hashed;
    }

    static std::string generateStableDeviceSignature() {
        std::string signature;

        signature += OBF("ARCAMOD_STABLE_");

        if (!Config.UserData.UserID.empty()) {
            signature += Config.UserData.UserID;
        } else {
            signature += OBF("UNKNOWN_USER");
        }

        signature += OBF("_");
        signature += Config.Init.device_name.empty() ? OBF("UNKNOWN_DEVICE") : Config.Init.device_name;
        signature += OBF("_v1.6.51.8_9847");

        // LOGIO("StableSignature: Raw = '%s'", signature.c_str());

        std::hash<std::string> hasher;
        std::string result = std::to_string(hasher(signature));
        // LOGIO("StableSignature: Hashed = '%s'", result.c_str());
        return result;
    }

    static long long getCurrentTimestamp() {
        return std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::system_clock::now().time_since_epoch()
        ).count();
    }

    static std::string GetAimStrengthLabel(float aimSpeed) {
        if (aimSpeed >= 6.0f) {
            return OBF("EXTREME");
        } else if (aimSpeed >= 4.0f) {
            return OBF("ULTRA");
        } else if (aimSpeed >= 3.0f) {
            return OBF("HIGH");
        } else if (aimSpeed >= 2.0f) {
            return OBF("MEDIUM");
        } else {
            return OBF("LOW");
        }
    }

public:
    static void ApplyGraphicsSettings() {
        // DISABLED: ResourceOptimization dinonaktifkan
        // if (ResourceOptimization::highQualityMode) {
        //     ResourceOptimization::SetHighQualityMode(true);
        // }
    }

    static bool DeleteSettings() {
        auto paths = getSettingsFilePaths();
        bool anyDeleted = false;

        for (const auto& path : paths) {
            if (fileExists(path)) {
                if (remove(path.c_str()) == 0) {
                    anyDeleted = true;
                    // LOGIO("DeleteSettings: Berhasil hapus file: %s", path.c_str());
                }
            }
        }

        return anyDeleted;
    }

    static bool SaveSettings() {
        // LOGIO("SaveSettings: Memulai proses save settings...");

        // LOGIO("SaveSettings: Config.Init.Done = %s", Config.Init.Done ? "true" : "false");
        // LOGIO("SaveSettings: Config.Init.IsValidated = %s", Config.Init.IsValidated ? "true" : "false");
        // LOGIO("SaveSettings: Config.Init.IsUserIDMode = %s", Config.Init.IsUserIDMode ? "true" : "false");
        // LOGIO("SaveSettings: Config.Init.IsXenoKeyMode = %s", Config.Init.IsXenoKeyMode ? "true" : "false");
        // LOGIO("SaveSettings: XenoKeyData.isValidated = %s", XenoKeyData.isValidated ? "true" : "false");
        // LOGIO("SaveSettings: XenoKeyData.isLoggedIn = %s", XenoKeyData.isLoggedIn ? "true" : "false");

        bool canSaveSettings = false;

#ifdef DEV_MODE
        canSaveSettings = true;
            // LOGIO("SaveSettings: DEV_MODE aktif - save settings diizinkan");
#else
        if (Config.Init.IsUserIDMode && Config.Init.IsValidated) {
            canSaveSettings = true;
            // LOGIO("SaveSettings: User ID mode tervalidasi - save settings diizinkan");
        } else if (Config.Init.IsXenoKeyMode && Config.Init.IsValidated) {
            canSaveSettings = true;
            // LOGIO("SaveSettings: Xeno Key mode tervalidasi - save settings diizinkan");
        } else if (Config.Init.IsXenoKeyMode && XenoKeyData.isValidated) {
            canSaveSettings = true;
            // LOGIO("SaveSettings: Xeno Key mode tervalidasi (fallback) - save settings diizinkan");
        } else {
            // LOGIO("SaveSettings: Tidak ada mode validation yang aktif");
        }
#endif

        if (!Config.Init.Done) {
            // LOGIO("SaveSettings: Config.Init.Done false, tapi tetap mencoba save untuk compatibility");
            canSaveSettings = true;
        }

        if (!canSaveSettings) {
            // LOGIO("SaveSettings: Device tidak memiliki izin untuk save settings");
            return false;
        }

        json settings;

        settings[OBF("Visual")] = {
                {OBF("Line"),          Config.View.Line},
                {OBF("Box"),           Config.View.Box},
                {OBF("Health"),        Config.View.Health},
                {OBF("Name"),          Config.View.Name},
                {OBF("Distance"),      Config.View.Distance},
                // {OBF("Signal"),        Config.View.Signal},
                {OBF("BoxFill"),       Config.View.EnableBoxFill},
                {OBF("Skeleton"),      Config.View.Skeleton},
                {OBF("VehicleEnable"), Config.View.Vehicle.Enable},
                {OBF("VehicleLine"),   Config.View.Vehicle.Line},
                {OBF("VehicleBox"),    Config.View.Vehicle.Box},
                {OBF("VehicleDistance"), Config.View.Vehicle.Distance},
                {OBF("VehicleHealth"), Config.View.Vehicle.Health},
                {OBF("TeamInfo"),      Config.View.DetailedTeamInfo},
                {OBF("WallHack"),      Config.View.Wallhack.Normal},
                {OBF("EspDistanceBR"), Config.View.Wallhack.EspNameColorBR},
                {OBF("EspOldBR"),      Config.View.Wallhack.EspNameOldBR},
                {OBF("EspHealthBR"),   Config.View.Wallhack.EspNameHealthBR},
                {OBF("EspColorMP"),    Config.View.Wallhack.EspNameColorMP},
                {OBF("EspHealthMP"),   Config.View.Wallhack.EspNameHealthMP},
                {OBF("EspScale"),      Config.View.Wallhack.EspScale},
                {OBF("BoostFPS"),      Config.View.Wallhack.BoostFPS}
        };

        settings[OBF("Weapon")] = {
                {OBF("Reload"),    Config.Weapon.Reload},
                {OBF("Scope"),     Config.Weapon.Scope},
                {OBF("CrossHair"), Config.Weapon.Crosshair},
                {OBF("Recoil"),    Config.Weapon.Recoil},
                {OBF("Aim"),       Config.Weapon.Aim},
                {OBF("Spread"),    Config.Weapon.Spread},
                {OBF("Damage"),    Config.Weapon.HighDamage},
                {OBF("InfiniteAmmo"), Config.Weapon.InfiniteAmmo}
        };

        settings[OBF("AimSettings")] = {
                {OBF("AimSpeed"),         Config.WeaponSize.Aim},
                {OBF("AimCloseBoost"),    Config.Weapon.AimCloseBoost},
                {OBF("AimPrecision"),     Config.Weapon.AimPrecision},
                {OBF("AimStrengthLabel"), GetAimStrengthLabel(Config.WeaponSize.Aim)}
        };

        settings[OBF("WeaponSize")] = {
                {OBF("SpreadFactor"), Config.WeaponSize.SpreadFactor},
                {OBF("ReloadFactor"), Config.WeaponSize.ReloadFactor},
                {OBF("ScopeFactor"),  Config.WeaponSize.ScopeFactor},
                {OBF("RecoilFactor"), Config.WeaponSize.RecoilFactor}
        };

        settings[OBF("Misc")] = {
                {OBF("Jump"),                 Config.Misc.Jump},
                {OBF("Speed"),                Config.Misc.Speed},
                {OBF("Spectate"),             Config.Misc.Spectate},
                {OBF("Slide"),                Config.Misc.Slide},
                {OBF("Parachute"),            Config.Misc.Parachute},
                {OBF("Swim"),                 Config.Misc.Swim},
                {OBF("Tutorial"),             Config.Misc.Tutorial},
                {OBF("ResourceOptimization"), Config.Misc.ResourceOptimization},
                {OBF("SkyDiving"),            Config.Misc.SkyDiving},
                {OBF("SmartFPS"),             Config.Misc.SmartFPS},
                {OBF("UltraFPSGraphicUnlock"), Config.Misc.UltraFPSGraphicUnlock},
                {OBF("SkiingBoost"),          Config.Misc.SkiingBoost}
                /* FakeStatus features disabled - must be enabled manually each time
                {OBF("FakeStatus"),           Config.Misc.FakeStatus},
                {OBF("FakeOfflineMode"),      Config.Misc.FakeOfflineMode},
                {OBF("DisableReporting"),     Config.Misc.DisableReporting},
                {OBF("FakeReportID"),         Config.Misc.FakeReportID},
                {OBF("BlockAnalytics"),       Config.Misc.BlockAnalytics}
                */
        };

        settings[OBF("GraphicsSettings")] = {
                {OBF("OptimizationLevel"),    Config.MiscSize.OptimizationLevel}
                // DISABLED: ResourceOptimization dinonaktifkan
                // {OBF("ResourceOptimization"), Config.Misc.ResourceOptimization},
                // {OBF("HDRMode"),              ResourceOptimization::highQualityMode}
        };

        // ❌ DISABLED: SmartFPS completely disabled for testing
        /*
        if (Config.Misc.SmartFPS) {
            settings[OBF("SmartFPS")] = {
                    {OBF("Enabled"), SmartFPS::enabled}
            };
        }
        */

        settings[OBF("MiscSize")] = {
                {OBF("SlideValue"),        Config.MiscSize.Slide},
                {OBF("SpeedValue"),        Config.MiscSize.Speed},
                {OBF("JumpValue"),         Config.MiscSize.Jump},
                {OBF("SwimValue"),         Config.MiscSize.Swim},
                {OBF("FallSpeed"),         Config.MiscSize.FallSpeed},
                {OBF("OptimizationLevel"), Config.MiscSize.OptimizationLevel},
                {OBF("EspScale"),          Config.MiscSize.EspScale},
                {OBF("SkiingBoost"),       Config.MiscSize.SkiingBoost},
                /* FakeStatus related settings disabled
                {OBF("FakeStageType"),     Config.MiscSize.FakeStageType},
                {OBF("FakeRecordID"),      Config.MiscSize.FakeRecordID},
                */
                {OBF("SmartFPS"),          Config.Misc.SmartFPS}
        };

        settings[OBF("Settings")] = {
                {OBF("ShowFpsInName"),   Config.Settings.ShowFpsInName},
                {OBF("ShowFpsOnScreen"), Config.Settings.ShowFpsInScreen},
                {OBF("HideMenu"),        Config.Settings.HideMenu}
        };

        /*if (Config.Misc.FakeStatus) {
            settings[OBF("FakeStatus")] = {
                    {OBF("FakeStageType"), Config.MiscSize.FakeStageType},
                    {OBF("FakeRecordID"),  Config.MiscSize.FakeRecordID}
            };
        }*/

        // LOGIO("SaveSettings: Membuat JSON string dari settings...");
        std::string jsonString = settings.dump(4);
        // LOGIO("SaveSettings: JSON string berhasil dibuat, size: %zu", jsonString.length());

        // LOGIO("SaveSettings: Generating device signature...");
        std::string deviceSignature = generateStableDeviceSignature();
        // LOGIO("SaveSettings: Stable device signature berhasil dibuat");

        json secureSettings;
        secureSettings[OBF("data")] = jsonString;
        secureSettings[OBF("signature")] = deviceSignature;
        secureSettings[OBF("timestamp")] = getCurrentTimestamp();
        // LOGIO("SaveSettings: Secure settings structure berhasil dibuat");

        std::string encryptedData = secureSettings.dump();
        // LOGIO("SaveSettings: Data prepared for saving");

        // LOGIO("SaveSettings: Mendapatkan active file path...");
        std::string activeFilePath = getActiveSettingsFile();
        // LOGIO("SaveSettings: Active file path: %s", activeFilePath.c_str());

        // LOGIO("SaveSettings: Membuka file untuk writing...");
        std::ofstream file(activeFilePath);
        if (!file.is_open()) {
            // LOGIO("SaveSettings: GAGAL membuka file untuk writing: %s", activeFilePath.c_str());
            return false;
        }

        // LOGIO("SaveSettings: Menulis data ke file...");
        file << encryptedData;
        file.close();
        // LOGIO("SaveSettings: Data berhasil ditulis ke file");

        static int saveCounter = 0;
        saveCounter++;
        if (saveCounter % 5 == 0) {
            rotateSettingsFile();
        }

        // LOGIO("SaveSettings: Settings berhasil disimpan dengan encryption");
        return true;
    }

    static bool SaveSettingsSimple() {
        // LOGIO("SaveSettingsSimple: Menggunakan fallback save tanpa encryption...");

        json settings;

        settings[OBF("Visual")] = {
                {OBF("Line"),          Config.View.Line},
                {OBF("Box"),           Config.View.Box},
                {OBF("Health"),        Config.View.Health},
                {OBF("Name"),          Config.View.Name}
        };

        settings[OBF("Misc")] = {
                {OBF("Jump"),          Config.Misc.Jump},
                {OBF("Speed"),         Config.Misc.Speed},
                {OBF("Spectate"),      Config.Misc.Spectate}
        };

        std::string jsonString = settings.dump(4);
        std::string filePath = OBF("/data/data/com.garena.game.codm/files/.simple_settings");

        std::ofstream file(filePath);
        if (!file.is_open()) {
            // LOGIO("SaveSettingsSimple: Gagal membuka file: %s", filePath.c_str());
            return false;
        }

        file << jsonString;
        file.close();

        // LOGIO("SaveSettingsSimple: Settings berhasil disimpan tanpa encryption");
        return true;
    }

    static bool LoadSettings() {
        std::string activeFilePath = getActiveSettingsFile();

        if (!fileExists(activeFilePath)) {
            return false;
        }

        if (!Config.Init.Done || !Config.Init.IsValidated) {
            // LOGIO("LoadSettings: Device belum tervalidasi, load settings ditolak");
            return false;
        }

        bool canLoadSettings = false;

#ifdef DEV_MODE
        canLoadSettings = true;
#else
        if (Config.Init.IsUserIDMode && Config.Init.IsValidated) {
            canLoadSettings = true;
        } else if (Config.Init.IsXenoKeyMode && XenoKeyData.isValidated) {
            canLoadSettings = true;
        }
#endif

        if (!canLoadSettings) {
            // LOGIO("LoadSettings: Device tidak memiliki izin untuk load settings");
            return false;
        }

        std::ifstream file(activeFilePath);
        if (!file.is_open()) {
            return false;
        }

        std::string encryptedData;
        std::string line;
        while (std::getline(file, line)) {
            encryptedData += line;
        }
        file.close();

        if (encryptedData.empty()) {
            // LOGIO("LoadSettings: File settings kosong");
            return false;
        }

        std::string decryptedData = encryptedData;

        if (decryptedData.empty()) {
            // LOGIO("LoadSettings: Data kosong setelah decrypt");
            return false;
        }

        json secureSettings = json::parse(decryptedData);

        if (!secureSettings.contains(OBF("data")) ||
            !secureSettings.contains(OBF("signature")) ||
            !secureSettings.contains(OBF("timestamp"))) {
            // LOGIO("LoadSettings: Settings structure invalid - missing security fields");
            return false;
        }

        std::string savedSignature = secureSettings[OBF("signature")];
        // LOGIO("LoadSettings: Saved signature = '%s'", savedSignature.c_str());

        bool skipSignatureValidation = false;
#ifdef DEV_MODE
        skipSignatureValidation = true;
#endif

        skipSignatureValidation = true;

        if (skipSignatureValidation) {
            // LOGIO("LoadSettings: Signature validation disabled (DEV mode)");
        } else {
            // LOGIO("LoadSettings: Generating current signature for comparison...");

            std::string stableSignature = generateStableDeviceSignature();
            // LOGIO("LoadSettings: Stable signature = '%s'", stableSignature.c_str());

            if (savedSignature == stableSignature) {
                // LOGIO("LoadSettings: Stable signature validation passed");
            } else {
                std::string currentSignature = generateDeviceSignature();
                // LOGIO("LoadSettings: Current signature = '%s'", currentSignature.c_str());

                if (savedSignature != currentSignature) {
                    // LOGIO("LoadSettings: Dynamic signature juga mismatch");
                    // LOGIO("LoadSettings: Saved:   '%s'", savedSignature.c_str());
                    // LOGIO("LoadSettings: Current: '%s'", currentSignature.c_str());

#ifdef DEV_MODE
                    // LOGIO("LoadSettings: DEV_MODE aktif - mengabaikan signature mismatch");
#else
                    // LOGIO("LoadSettings: Production mode - semua signature mismatch ditolak");
                    return false;
#endif
                } else {
                    // LOGIO("LoadSettings: Dynamic signature validation passed");
                }
            }
        }

        std::string settingsData = secureSettings[OBF("data")];
        json settings = json::parse(settingsData);

        // Memuat pengaturan Visual
        if (settings.contains(OBF("Visual"))) {
            auto &visual = settings[OBF("Visual")];

            // CRASH PREVENTION: Tambahkan safety checks untuk semua loading
            if (visual.contains(OBF("Line")))
                Config.View.Line = visual[OBF("Line")];
            if (visual.contains(OBF("Box")))
                Config.View.Box = visual[OBF("Box")];
            if (visual.contains(OBF("Health")))
                Config.View.Health = visual[OBF("Health")];
            if (visual.contains(OBF("Name")))
                Config.View.Name = visual[OBF("Name")];
            if (visual.contains(OBF("Distance")))
                Config.View.Distance = visual[OBF("Distance")];

            // Signal ESP dinonaktifkan - tidak dibutuhkan
            // if (visual.contains(OBF("Signal")))
            //     Config.View.Signal = visual[OBF("Signal")];

            // CRASH PREVENTION: Safety checks untuk BoxFill
            if (visual.contains(OBF("BoxFill"))) {
                Config.View.EnableBoxFill = visual[OBF("BoxFill")];
                Config.View.DisableBoxFill = !visual[OBF("BoxFill")];
            }

            // Memuat pengaturan Skeleton jika ada
            if (visual.contains(OBF("Skeleton")))
                Config.View.Skeleton = visual[OBF("Skeleton")];

            // ESP VEHICLE SYSTEM - REIMPLEMENTED dengan assembly-based approach
            if (visual.contains(OBF("VehicleEnable")))
                Config.View.Vehicle.Enable = visual[OBF("VehicleEnable")];
            if (visual.contains(OBF("VehicleLine")))
                Config.View.Vehicle.Line = visual[OBF("VehicleLine")];
            if (visual.contains(OBF("VehicleBox")))
                Config.View.Vehicle.Box = visual[OBF("VehicleBox")];
            if (visual.contains(OBF("VehicleDistance")))
                Config.View.Vehicle.Distance = visual[OBF("VehicleDistance")];
            if (visual.contains(OBF("VehicleHealth")))
                Config.View.Vehicle.Health = visual[OBF("VehicleHealth")];

            // Memuat pengaturan Team Info jika ada
            if (visual.contains(OBF("TeamInfo")))
                Config.View.DetailedTeamInfo = visual[OBF("TeamInfo")];

            // Memuat pengaturan Wallhack dari bagian Visual
            if (visual.contains(OBF("WallHack")))
                Config.View.Wallhack.Normal = visual[OBF("WallHack")];
            if (visual.contains(OBF("EspDistanceBR")))
                Config.View.Wallhack.EspNameColorBR = visual[OBF("EspDistanceBR")];
            if (visual.contains(OBF("EspOldBR")))
                Config.View.Wallhack.EspNameOldBR = visual[OBF("EspOldBR")];
            if (visual.contains(OBF("EspHealthBR")))
                Config.View.Wallhack.EspNameHealthBR = visual[OBF("EspHealthBR")];
            if (visual.contains(OBF("EspColorMP")))
                Config.View.Wallhack.EspNameColorMP = visual[OBF("EspColorMP")];
            if (visual.contains(OBF("EspHealthMP")))
                Config.View.Wallhack.EspNameHealthMP = visual[OBF("EspHealthMP")];
            if (visual.contains(OBF("EspScale")))
                Config.View.Wallhack.EspScale = visual[OBF("EspScale")];
            if (visual.contains(OBF("BoostFPS")))
                Config.View.Wallhack.BoostFPS = visual[OBF("BoostFPS")]; // Memuat pengaturan BoostFPS
        }

        // Untuk kompatibilitas dengan file pengaturan lama yang masih memiliki bagian Memory
        if (settings.contains(OBF("Memory"))) {
            auto &memory = settings[OBF("Memory")];

            // CRASH PREVENTION: Safety checks untuk Memory section
            if (memory.contains(OBF("WallHack")))
                Config.View.Wallhack.Normal = memory[OBF("WallHack")];
            if (memory.contains(OBF("EspDistanceBR")))
                Config.View.Wallhack.EspNameColorBR = memory[OBF("EspDistanceBR")];
            if (memory.contains(OBF("EspOldBR")))
                Config.View.Wallhack.EspNameOldBR = memory[OBF("EspOldBR")];
            if (memory.contains(OBF("EspHealthBR")))
                Config.View.Wallhack.EspNameHealthBR = memory[OBF("EspHealthBR")];
            if (memory.contains(OBF("EspColorMP")))
                Config.View.Wallhack.EspNameColorMP = memory[OBF("EspColorMP")];
            if (memory.contains(OBF("EspHealthMP")))
                Config.View.Wallhack.EspNameHealthMP = memory[OBF("EspHealthMP")];
        }

        // Memuat pengaturan Weapon
        if (settings.contains(OBF("Weapon"))) {
            auto &weapon = settings[OBF("Weapon")];

            // CRASH PREVENTION: Safety checks untuk Weapon section
            if (weapon.contains(OBF("Reload")))
                Config.Weapon.Reload = weapon[OBF("Reload")];
            if (weapon.contains(OBF("Scope")))
                Config.Weapon.Scope = weapon[OBF("Scope")];
            if (weapon.contains(OBF("CrossHair")))
                Config.Weapon.Crosshair = weapon[OBF("CrossHair")];
            if (weapon.contains(OBF("Recoil")))
                Config.Weapon.Recoil = weapon[OBF("Recoil")];
            if (weapon.contains(OBF("Aim")))
                Config.Weapon.Aim = weapon[OBF("Aim")];
            if (weapon.contains(OBF("Spread")))
                Config.Weapon.Spread = weapon[OBF("Spread")];
            if (weapon.contains(OBF("Damage")))
                Config.Weapon.HighDamage = weapon[OBF("Damage")];
            if (weapon.contains(OBF("InfiniteAmmo")))
                Config.Weapon.InfiniteAmmo = weapon[OBF("InfiniteAmmo")];
        }

        // Memuat pengaturan ResourceOptimization dan HDRGraphics
        if (settings.contains(OBF("GraphicsSettings"))) {
            auto &graphicsSettings = settings[OBF("GraphicsSettings")];

            if (graphicsSettings.contains(OBF("OptimizationLevel"))) {
                Config.MiscSize.OptimizationLevel = graphicsSettings[OBF("OptimizationLevel")];
                // Pastikan nilai OptimizationLevel berada dalam range yang valid
                if (Config.MiscSize.OptimizationLevel < 0.0f)
                    Config.MiscSize.OptimizationLevel = 0.0f;
                if (Config.MiscSize.OptimizationLevel > 1.0f)
                    Config.MiscSize.OptimizationLevel = 1.0f;
            }

            // DISABLED: Memuat pengaturan ResourceOptimization
            // if (graphicsSettings.contains(OBF("ResourceOptimization"))) {
            //     bool optimizationEnabled = graphicsSettings[OBF("ResourceOptimization")];
            //     // Hanya update config status tanpa memanggil SetOptimizationMode
            //     Config.Misc.ResourceOptimization = optimizationEnabled;
            //     if (optimizationEnabled) {
            //     }
            // }

            // DISABLED: Memuat status HDR mode dari file tanpa langsung mengaktifkannya
            // if (graphicsSettings.contains(OBF("HDRMode"))) {
            //     bool hdrEnabled = graphicsSettings[OBF("HDRMode")];
            //     // Hanya update status global tanpa memanggil SetHighQualityMode
            //     ResourceOptimization::highQualityMode = hdrEnabled;
            //     if (hdrEnabled) {
            //     }
            // }
        }

        // Memuat pengaturan Aim
        if (settings.contains(OBF("AimSettings"))) {
            auto &aimSettings = settings[OBF("AimSettings")];
            // Memuat pengaturan AimSpeed jika ada, dengan range nilai 0.1f sampai 8.0f
            if (aimSettings.contains(OBF("AimSpeed"))) {
                Config.WeaponSize.Aim = aimSettings[OBF("AimSpeed")];
                // Pastikan nilai Aim berada dalam range yang valid (sesuai slider di Draw_Menu.h)
                if (Config.WeaponSize.Aim < 0.1f) Config.WeaponSize.Aim = 0.1f;
                if (Config.WeaponSize.Aim > 8.0f) Config.WeaponSize.Aim = 8.0f;
            }

            if (aimSettings.contains(OBF("AimCloseBoost")))
                Config.Weapon.AimCloseBoost = aimSettings[OBF("AimCloseBoost")];

            if (aimSettings.contains(OBF("AimPrecision")))
                Config.Weapon.AimPrecision = aimSettings[OBF("AimPrecision")];
        }

        // Memuat pengaturan WeaponSize untuk slider
        if (settings.contains(OBF("WeaponSize"))) {
            auto &weaponSize = settings[OBF("WeaponSize")];

            if (weaponSize.contains(OBF("SpreadFactor")))
                Config.WeaponSize.SpreadFactor = weaponSize[OBF("SpreadFactor")];

            if (weaponSize.contains(OBF("ReloadFactor")))
                Config.WeaponSize.ReloadFactor = weaponSize[OBF("ReloadFactor")];

            if (weaponSize.contains(OBF("ScopeFactor")))
                Config.WeaponSize.ScopeFactor = weaponSize[OBF("ScopeFactor")];

            if (weaponSize.contains(OBF("RecoilFactor")))
                Config.WeaponSize.RecoilFactor = weaponSize[OBF("RecoilFactor")];
        }

        // Memuat pengaturan Misc
        if (settings.contains(OBF("Misc"))) {
            auto &misc = settings[OBF("Misc")];

            // CRASH PREVENTION: Safety checks untuk Misc section
            if (misc.contains(OBF("Jump")))
                Config.Misc.Jump = misc[OBF("Jump")];
            if (misc.contains(OBF("Speed")))
                Config.Misc.Speed = misc[OBF("Speed")];
            if (misc.contains(OBF("Spectate")))
                Config.Misc.Spectate = misc[OBF("Spectate")];
            if (misc.contains(OBF("Slide")))
                Config.Misc.Slide = misc[OBF("Slide")];
            if (misc.contains(OBF("Parachute")))
                Config.Misc.Parachute = misc[OBF("Parachute")];
            if (misc.contains(OBF("Swim")))
                Config.Misc.Swim = misc[OBF("Swim")];

            // Memuat pengaturan Tutorial jika ada
            if (misc.contains(OBF("Tutorial")))
                Config.Misc.Tutorial = misc[OBF("Tutorial")];

            // Memuat pengaturan SkyDiving jika ada
            if (misc.contains(OBF("SkyDiving")))
                Config.Misc.SkyDiving = misc[OBF("SkyDiving")];

            // Memuat pengaturan SmartFPS jika ada
            if (misc.contains(OBF("SmartFPS")))
                Config.Misc.SmartFPS = misc[OBF("SmartFPS")];

            // Memuat pengaturan UltraFPSGraphicUnlock jika ada
            if (misc.contains(OBF("UltraFPSGraphicUnlock")))
                Config.Misc.UltraFPSGraphicUnlock = misc[OBF("UltraFPSGraphicUnlock")];

            // Memuat pengaturan SkiingBoost jika ada
            if (misc.contains(OBF("SkiingBoost")))
                Config.Misc.SkiingBoost = misc[OBF("SkiingBoost")];

            // Memuat pengaturan FakeStatus jika ada - dinonaktifkan
            /*if (misc.contains(OBF("FakeStatus")))
                Config.Misc.FakeStatus = misc[OBF("FakeStatus")];*/

            // Memuat pengaturan FakeOfflineMode jika ada
            /*if (misc.contains(OBF("FakeOfflineMode")))
                Config.Misc.FakeOfflineMode = misc[OBF("FakeOfflineMode")];

            // Memuat pengaturan DisableReporting jika ada
            if (misc.contains(OBF("DisableReporting")))
                Config.Misc.DisableReporting = misc[OBF("DisableReporting")];

            // Memuat pengaturan FakeReportID jika ada
            if (misc.contains(OBF("FakeReportID")))
                Config.Misc.FakeReportID = misc[OBF("FakeReportID")];

            // Memuat pengaturan BlockAnalytics jika ada
            if (misc.contains(OBF("BlockAnalytics")))
                Config.Misc.BlockAnalytics = misc[OBF("BlockAnalytics")];*/
        }

        // Memuat pengaturan MiscSize untuk slider
        if (settings.contains(OBF("MiscSize"))) {
            auto &miscSize = settings[OBF("MiscSize")];

            if (miscSize.contains(OBF("SlideValue"))) {
                Config.MiscSize.Slide = miscSize[OBF("SlideValue")];
                // Pastikan nilai Slide berada dalam range yang valid
                if (Config.MiscSize.Slide < 2.2f) Config.MiscSize.Slide = 2.2f;
                if (Config.MiscSize.Slide > 2.7f) Config.MiscSize.Slide = 2.7f;
            }

            if (miscSize.contains(OBF("SpeedValue"))) {
                Config.MiscSize.Speed = miscSize[OBF("SpeedValue")];
                // Pastikan nilai Speed berada dalam range yang valid
                if (Config.MiscSize.Speed < 1.1f) Config.MiscSize.Speed = 1.1f;
                if (Config.MiscSize.Speed > 1.4f) Config.MiscSize.Speed = 1.4f;
            }

            if (miscSize.contains(OBF("JumpValue")))
                Config.MiscSize.Jump = miscSize[OBF("JumpValue")];

            if (miscSize.contains(OBF("SwimValue")))
                Config.MiscSize.Swim = miscSize[OBF("SwimValue")];

            // Memuat pengaturan FallSpeed jika ada
            if (miscSize.contains(OBF("FallSpeed"))) {
                Config.MiscSize.FallSpeed = miscSize[OBF("FallSpeed")];
                // Pastikan nilai FallSpeed berada dalam range yang valid (untuk Sky Diving)
                if (Config.MiscSize.FallSpeed < 1.0f) Config.MiscSize.FallSpeed = 1.0f;
                if (Config.MiscSize.FallSpeed > 10.0f) Config.MiscSize.FallSpeed = 10.0f;
            }

            // Memuat pengaturan OptimizationLevel jika ada
            if (miscSize.contains(OBF("OptimizationLevel"))) {
                Config.MiscSize.OptimizationLevel = miscSize[OBF("OptimizationLevel")];
                // Pastikan nilai OptimizationLevel berada dalam range yang valid
                if (Config.MiscSize.OptimizationLevel < 0.0f)
                    Config.MiscSize.OptimizationLevel = 0.0f;
                if (Config.MiscSize.OptimizationLevel > 1.0f)
                    Config.MiscSize.OptimizationLevel = 1.0f;
            }

            // Memuat pengaturan EspScale jika ada
            if (miscSize.contains(OBF("EspScale"))) {
                Config.MiscSize.EspScale = miscSize[OBF("EspScale")];
                // Pastikan nilai EspScale berada dalam range yang valid
                if (Config.MiscSize.EspScale < 1.0f)
                    Config.MiscSize.EspScale = 1.0f;
                if (Config.MiscSize.EspScale > 5.0f)
                    Config.MiscSize.EspScale = 5.0f;
            }

            // Memuat pengaturan SkiingBoost jika ada
            if (miscSize.contains(OBF("SkiingBoost"))) {
                Config.MiscSize.SkiingBoost = miscSize[OBF("SkiingBoost")];
                // Pastikan nilai SkiingBoost berada dalam range yang valid
                if (Config.MiscSize.SkiingBoost < 1.0f) Config.MiscSize.SkiingBoost = 1.0f;
                if (Config.MiscSize.SkiingBoost > 8.0f) Config.MiscSize.SkiingBoost = 8.0f;
            }

            // Memuat pengaturan FakeStatus dari MiscSize - dinonaktifkan
            /*
            // Memuat pengaturan FakeStageType jika ada
            if (miscSize.contains(OBF("FakeStageType")))
                Config.MiscSize.FakeStageType = miscSize[OBF("FakeStageType")];

            // Memuat pengaturan FakeRecordID jika ada
            if (miscSize.contains(OBF("FakeRecordID")))
                Config.MiscSize.FakeRecordID = miscSize[OBF("FakeRecordID")];
            */

            // 🎯 CLEAN SmartFPS - Tidak perlu load setting tambahan
        }

        // Memuat pengaturan umum
        if (settings.contains(OBF("Settings"))) {
            auto &general = settings[OBF("Settings")];

            if (general.contains(OBF("ShowFpsInName")))
                Config.Settings.ShowFpsInName = general[OBF("ShowFpsInName")];

            if (general.contains(OBF("ShowFpsOnScreen")))
                Config.Settings.ShowFpsInScreen = general[OBF("ShowFpsOnScreen")];

            if (general.contains(OBF("HideMenu")))
                Config.Settings.HideMenu = general[OBF("HideMenu")];
        }

        // ❌ DISABLED: SmartFPS completely disabled for testing
        /*
        // 🎯 CLEAN SmartFPS - Load hanya status enabled
        if (settings.contains(OBF("SmartFPS"))) {
            auto &smartFPS = settings[OBF("SmartFPS")];
            if (smartFPS.contains(OBF("Enabled"))) {
                SmartFPS::enabled = smartFPS[OBF("Enabled")];
            }
        }
        */

        // 🎯 CLEAN SmartFPS Mode - Tidak diperlukan lagi

        // Bagian Load Settings untuk XenoKey telah dihapus

        // Memuat pengaturan FakeStatus detail jika ada
        /*if (settings.contains(OBF("FakeStatus"))) {
            auto &fakeStatus = settings[OBF("FakeStatus")];

            if (fakeStatus.contains(OBF("FakeStageType")))
                Config.MiscSize.FakeStageType = fakeStatus[OBF("FakeStageType")];

            if (fakeStatus.contains(OBF("FakeRecordID")))
                Config.MiscSize.FakeRecordID = fakeStatus[OBF("FakeRecordID")];
        }*/

        return true;
    }
};

const std::string Settings::SETTINGS_FILE = OBF(
        "/data/data/com.garena.game.codm/files/.cache_x64");

#endif // ARCAMOD_SETTINGS_H