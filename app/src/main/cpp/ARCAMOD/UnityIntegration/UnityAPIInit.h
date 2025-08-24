#ifndef ARCAMOD_UNITY_IMPL_H
#define ARCAMOD_UNITY_IMPL_H

#include <fstream>
#include <string>

typedef Vector3 (*Transform_get_position_t)(void *);
typedef void *(*Camera_get_main_t)();
typedef Vector3 (*Camera_WorldToScreenPoint_t)(void *, Vector3);
typedef void *(*GamePlay_get_MatchGame_t)();
typedef void *(*Pawn_GetRootTransform_t)(void *);
typedef void *(*Pawn_GetHeadTransform_t)(void *);
typedef void *(*Component_get_transform_t)(void *);
typedef int (*Screen_get_height_t)();
typedef int (*Screen_get_width_t)();
typedef float (*Screen_get_dpi_t)();
typedef int (*Input_get_touchCount_t)();
typedef bool (*Input_get_touchSupported_t)();
typedef Touch (*Input_GetTouch_t)(Touch, int);
typedef bool (*Input_GetKeyDownInt_t)(void *, int);

typedef System$$StringStruct* (*SystemInfo_get_deviceUniqueIdentifier_t)();
typedef System$$StringStruct* (*SystemInfo_get_deviceName_t)();
typedef System$$StringStruct* (*SystemInfo_get_deviceModel_t)();

static SystemInfo_get_deviceUniqueIdentifier_t SystemInfo$$get_deviceUniqueIdentifier;
static SystemInfo_get_deviceName_t SystemInfo$$get_deviceName;
static SystemInfo_get_deviceModel_t SystemInfo$$get_deviceModel;

static bool server_validation_complete = false;

static uintptr_t get_module_base(const char *module_name) {
    char line[512];
    uintptr_t base_addr = 0;
    FILE *fp = fopen(OBF("/proc/self/maps"), "r");
    if (fp) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, module_name)) {
                base_addr = strtoul(line, NULL, 16);
                break;
            }
        }
        fclose(fp);
    }
    return base_addr;
}

void validate_with_server() {
    if (server_validation_complete) {
        return;
    }

    // LOGI("[SERVER] Memulai validasi server dari lobby...");
    json device_data;

#if IS_DEV == 0
    device_data[(OBF("uuid"))] = Config.Init.uuid;
    device_data[(OBF("device"))] = Config.Init.device_name;
    device_data[(OBF("game"))] = Config.Init.package_name;

    Config.UserData.DeviceInfo = BydzPanel::GetUserInfo(PANEL_URL, device_data);
    if (Config.UserData.DeviceInfo.contains(OBF("code"))) {
        int response_code = -1;
        try {
            response_code = Config.UserData.DeviceInfo[(OBF("code"))].get<int>();
        } catch (json::exception e) {
            Config.Message.Code = -1;
            Config.Message.Error = OBF("Error when getting response code from server.");
        }
        time_t utc_time = time(nullptr);
        tm *local_tm = localtime(&utc_time);
        time_t local_time = mktime(local_tm);
        if (response_code == 0) {
            try {
                Config.UserData.UserID = Config.UserData.DeviceInfo[(OBF("id"))].get<std::string>();
                Config.UserData.ExpiredUTC = std::stoll(
                        Config.UserData.DeviceInfo[(OBF("exp"))].get<std::string>());
                if (Config.UserData.ExpiredUTC > utc_time) {
                    Config.UserData.Token = Config.UserData.DeviceInfo[(OBF(
                            "token"))].get<std::string>();
                }
            } catch (json::exception e) {
                Config.Message.Code = -1;
                Config.Message.Error = OBF("Error when getting device data from server.");
            }
            struct tm *utc_to_local = localtime(&Config.UserData.ExpiredUTC);
            if (utc_to_local != nullptr) {
                Config.UserData.ExpiredLocal = std::mktime(utc_to_local);
            }
            if (!Config.UserData.UserID.empty() && Config.Message.Error.empty()) {
                if (Config.UserData.ExpiredLocal > local_time &&
                    Config.UserData.ExpiredUTC > utc_time) {
                    Config.Display.Lable += OBF(" | ");
                    Config.Display.Lable += BydzPanel::STATUS::GetStatus();
                } else {
                    Config.Display.Lable += OBF(" | EXPIRED");
                }
            } else {
                Config.Display.Lable += OBF(" | Not Logged In");
            }
        } else {
            Config.Message.Code = Config.UserData.DeviceInfo[(OBF("code"))].get<int>();
            Config.Message.Error = Config.UserData.DeviceInfo[(OBF("message"))].get<std::string>();
        }
        Config.UserData.IsLoggedIn = true;
    }
#else
    Config.UserData.UserID = OBF("0");
    Config.UserData.ExpiredUTC = 0;
    Config.UserData.ExpiredLocal = 0;
#endif

    device_data.clear();

    server_validation_complete = true;
    // LOGI("[SERVER] Validasi server selesai - tidak akan melakukan validasi lagi");
}

JavaVM *jvm;

extern "C" {
JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;
    JNIEnv *env;

    vm->GetEnv((void **) &env, JNI_VERSION_1_6);
    return JNI_VERSION_1_6;
    }
}

inline void init_unity() {
    uintptr_t g_base = get_module_base(OBF("libunity.so"));

    Transform$$get_position = (Transform_get_position_t) (g_base + Offsets::Functions::Transform_get_position);
    Camera$$get_main = (Camera_get_main_t) (g_base + Offsets::Functions::Camera_get_main);
    Camera$$WorldToScreenPoint = (Camera_WorldToScreenPoint_t) (g_base + Offsets::Functions::Camera_WorldToScreenPoint);
    GamePlay$$get_MatchGame = (GamePlay_get_MatchGame_t) (g_base + Offsets::Functions::GamePlay_get_MatchGame);
    Pawn$$GetRootTransform = (Pawn_GetRootTransform_t) (g_base + Offsets::Functions::Pawn_GetRootTransform);
    Pawn$$GetHeadTransform = (Pawn_GetHeadTransform_t) (g_base + Offsets::Functions::Pawn_GetHeadTransform);
    Component$$get_transform = (Component_get_transform_t) (g_base + Offsets::Functions::Component_get_transform);

    Screen$$get_height = (Screen_get_height_t) (g_base + Offsets::Functions::Screen_get_height);
    Screen$$get_width = (Screen_get_width_t) (g_base + Offsets::Functions::Screen_get_width);
    Screen$$get_dpi = (Screen_get_dpi_t) (g_base + Offsets::Functions::Screen_get_dpi);
    Input$$get_touchCount = (Input_get_touchCount_t) (g_base + Offsets::Functions::Input_get_touchCount);
    Input$$get_touchSupported = (Input_get_touchSupported_t) (g_base + Offsets::Functions::Input_get_touchSupported);
    Input$$GetTouch = reinterpret_cast<Input_GetTouch_t>(g_base + Offsets::Functions::Input_GetTouch);
    Input$$GetKeyDownInt = reinterpret_cast<Input_GetKeyDownInt_t>(g_base + Offsets::Functions::Input_GetKeyDownInt);

    SystemInfo$$get_deviceUniqueIdentifier = reinterpret_cast<SystemInfo_get_deviceUniqueIdentifier_t>(g_base + Offsets::Functions::SystemInfo_get_deviceUniqueIdentifier);
    SystemInfo$$get_deviceName = reinterpret_cast<SystemInfo_get_deviceName_t>(g_base + Offsets::Functions::SystemInfo_get_deviceName);
    SystemInfo$$get_deviceModel = reinterpret_cast<SystemInfo_get_deviceModel_t>(g_base + Offsets::Functions::SystemInfo_get_deviceModel);

    auto uuidFromIl2cpp = SystemInfo$$get_deviceUniqueIdentifier();
    auto deviceModel = SystemInfo$$get_deviceModel();

    std::string strUUID = "";
    std::string strDeviceModel = "";

    if (uuidFromIl2cpp != nullptr && uuidFromIl2cpp->length > 0) {
        strUUID = Tools::Il2CppToString(&uuidFromIl2cpp->start_char, uuidFromIl2cpp->length);
    } else {
        strUUID = OBF("device-id-not-available");
    }

    if (deviceModel != nullptr && deviceModel->length > 0) {
        strDeviceModel = Tools::Il2CppToString(&deviceModel->start_char, deviceModel->length);
    } else {
        strDeviceModel = OBF("unknown-device");
    }

    Config.Init.uuid += strUUID;
    Config.Init.device_name += strDeviceModel;
    Config.Init.package_name += CALL(&KittyMemory::getProcessName);

    Config.Init.IL2CppReady = true;
}

#endif