#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#define TAG "arca"
#define APKS_MD5 "fef20f5ea05dc3fd65d14645b1e75bc3"

#define IS_DEV 0
#define IS_ONLINE 1
#define IS_ONLINE_XENO 0
#define IS_LOBBY 0
#define STYLE_DEF 0
#define SEND_FEATURE 0
#define ENABLE_SHORT_LABLE 1
#define ENABLE_THREAD_MODE_FEATURE 0

// DISABLED: Auto Feedback dinonaktifkan secara total
#define ENABLE_AUTO_SCREENSHOT 0
#define SEND_TO_ARCA_ASSIST_BOT 0
#define SEND_TO_CHANNEL 0

#if IS_ONLINE_XENO == 1
#define WINDOW_TITLE_NAME OBF("XENO-MODS v1.2")
#else
#define WINDOW_TITLE_NAME OBF("ARCAxBYDZ")
#endif

#if STYLE_DEF == 0
#define PANEL_URL OBF("arcaxbydz.id")
#endif

#ifdef DEBUG
#define DEBUG_LOG(fmt, ...) printf("[ARCAMOD DEBUG] " fmt "\n", ##__VA_ARGS__)
#define LOGGING_ENABLED 1
#else
#define DEBUG_LOG(fmt, ...)
#define LOGGING_ENABLED 0
#endif

#define PASS_OBF __attribute((__annotate__("fw"))) __attribute((__annotate__("split"))) __attribute((__annotate__("indibr")))
#define PASS_OBF_STRING __attribute((__annotate__("fco"))) __attribute((__annotate__("strenc")))

#if LOGGING_ENABLED
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO,  TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN,  TAG, __VA_ARGS__))
#define LOGDO(str, ...) LOGD(OBF(str), ##__VA_ARGS__)
#define LOGEO(str, ...) LOGE(OBF(str), ##__VA_ARGS__)
#define LOGIO(str, ...) LOGI(OBF(str), ##__VA_ARGS__)
#define LOGWO(str, ...) LOGW(OBF(str), ##__VA_ARGS__)
#else
#define LOGD(...) ((void)0)
#define LOGE(...) ((void)0)
#define LOGI(...) ((void)0)
#define LOGW(...) ((void)0)
#define LOGDO(str, ...) ((void)0)
#define LOGEO(str, ...) ((void)0)
#define LOGIO(str, ...) ((void)0)
#define LOGWO(str, ...) ((void)0)
#endif

struct eConf {
    struct eDisplay {
        std::string Lable = OBF("ARCAxBYDZ");
    } Display;

    struct eInit {
        bool Ready;
        bool Done;
        bool EGLReady;
        bool IL2CppReady;
        bool IsReachedLobby = false;
        bool IsLobbyBypassReady = false;
        bool IsBypassLobbyRunning = false;
        bool LobbyBypassed = false;
        bool SettingsLoaded;
        bool IsValidated = false;
        bool IsUserIDMode = false;
        bool IsXenoKeyMode = false;
        std::string hwid;
        std::string device_name;
        std::string package_name;
        std::string uuid;
    } Init;

    struct eTelegram {
        bool EnableScreenshotFeedback = false; // DISABLED: Auto Feedback dinonaktifkan secara total
        int ScreenshotInterval = 300;
        int ScreenshotQuality = 85;
        int ScreenshotResolution = 5;
        int AutoFeedbackDelayAfterFakeStatus = 12;
        bool SendToBothChannels = false;
        bool SendToThirdChannel = false;
        bool FakeStatusActivated = false;
        bool FakeStatusCompleted = false;
        bool AutoFeedbackStarted = false;
        bool ScreenshotInProgress = false;
        time_t LastScreenshotTime = 0;
        time_t LobbyDetectedTime = 0;
        time_t FakeStatusCompletedTime = 0;

        std::string TelegramBotUrl = OBF("https://api.telegram.org/bot");

        struct {
            std::string Token = OBF("7957490950:AAEnnQ-FZuVtn-PPrRaV6bS_m4ZJCJl6zwY");
            std::string PrivateChatId = OBF("1718025538");
            std::string ChannelId1 = OBF("-1002333248278");
            std::string ChannelId2 = OBF("-1002541256895");
        } ArcamodBot;

        struct {
            std::string Token = OBF("7885749276:AAF8hj1nR9D0kw7A2vYa0XPdbZ0tRHwlRfI");
            std::string ChannelId = OBF("-1002899876402");
        } SpmfitbekarcaBot;

        std::string TelegramBotToken1 = ArcamodBot.Token;
        std::string TelegramBotToken2 = SpmfitbekarcaBot.Token;
        std::string TelegramBotToken = ArcamodBot.Token;
        std::string TelegramBotChatId = ArcamodBot.PrivateChatId;
        std::string TelegramChannelId1 = ArcamodBot.ChannelId1;
        std::string TelegramChannelId2 = SpmfitbekarcaBot.ChannelId;
        std::string TelegramChannelId3 = ArcamodBot.ChannelId2;
        std::string TelegramChannelId = SpmfitbekarcaBot.ChannelId;
        std::string TelegramChatId = SpmfitbekarcaBot.ChannelId;

        std::string GetActiveChatId() const {
#if SEND_TO_ARCA_ASSIST_BOT && SEND_TO_CHANNEL
            return TelegramChannelId;
#elif SEND_TO_ARCA_ASSIST_BOT
            return TelegramBotChatId;
#elif SEND_TO_CHANNEL
            return TelegramChannelId;
#else
            return TelegramBotChatId;
#endif
        }

        std::string GetTokenForChatId(const std::string& chatId) const {
            if (chatId == ArcamodBot.PrivateChatId ||
                chatId == ArcamodBot.ChannelId1 ||
                chatId == ArcamodBot.ChannelId2) {
                return ArcamodBot.Token;
            }
            else if (chatId == SpmfitbekarcaBot.ChannelId) {
                return SpmfitbekarcaBot.Token;
            }
            return SpmfitbekarcaBot.Token;
        }
    } Telegram;

    struct eView {
        bool Line = false;
        bool Box = false;
        bool Health = false;
        bool Name = false;
        bool Signal = false;
        bool Cooldown;
        bool Distance = false;
        bool Alert;
        bool Skeleton;
        bool WeaponInfo;
        bool EnableBoxFill;
        bool DisableBoxFill = false;
        bool DetailedTeamInfo = false;
        bool SmoothFPS;
        bool ESPNameOldBR;

        struct eVehicleESP {
            bool Enable = false;
            bool Line = false;
            bool Box = false;
            bool Distance = false;
            bool Health = false;
        } Vehicle;

        struct eWallhack {
            bool EspNameOldBR;
            bool Normal = false;
            bool EspNameHealthBR;
            bool EspNameColorBR;
            bool EspNameColorMP;
            bool EspNameHealthMP;
            bool Outline;
            bool BoostFPS = false;
            bool EspScale = false;
        } Wallhack;

        // Status hook Wallhack
        struct eWallhackHook {
            bool EspNameOldBR;
            bool EspNameOldBRReady;
            bool Normal;
            bool NormalReady;
            bool EspNameHealthBR;
            bool EspNameHealthBRReady;
            bool EspNameColorBR;
            bool EspNameColorBRReady;
            bool EspNameColorMP;
            bool EspNameColorMPReady;
            bool EspNameHealthMP;
            bool EspNameHealthMPReady;
            bool Outline;
            bool OutlineReady;
            bool BoostFPS;
            bool BoostFPSReady;
            bool EspScale;
            bool EspScaleReady;
        } WallhackHook;
    } View;

    struct eViewHook {
        bool SmoothFPS;
        bool SmoothFPSReady;
        bool ESPNameOldBR;
        bool ESPNameOldBRReady;
    } ViewHook;

    struct eWeapon {
        bool Aim;
        bool Bullet;
        bool Reload;
        bool Crosshair = false;
        bool Recoil = false;
        bool Scope;
        bool Spread;
        bool Switch;
        bool Overheat;
        bool Hitbox;
        bool HighDamage;
        bool AimCloseBoost = true;
        bool AimPrecision = false;
        bool InfiniteAmmo = false;
    } Weapon;

    struct eWeaponHook {
        bool Aim;
        bool AimReady;
        bool AimPatchReady;
        bool Reload;
        bool ReloadReady;
        bool ReloadPatchReady;
        bool Bullet;
        bool BulletReady;
        bool InfiniteAmmo;
        bool InfiniteAmmoReady;
        bool InfiniteAmmoPatchReady;
        bool Crosshair;
        bool CrosshairReady;
        bool CrosshairPatchReady;
        bool Recoil;
        bool RecoilReady;
        bool RecoilPatchReady;
        bool Scope;
        bool ScopeReady;
        bool ScopePatchReady;
        bool Spread;
        bool SpreadReady;
        bool SpreadPatchReady;
        bool Switch;
        bool SwitchReady;
        bool SwitchPatchReady;
        bool Overheat;
        bool OverheatReady;
        bool Hitbox;
        bool HighDamage;
        bool HighDamageReady;
        bool HighDamagePatchReady;
        bool AimCloseBoost;
        bool AimPrecision;
        float LastAimValue = 1.0f;
    } WeaponHook;

    struct eWeaponSize {
        float Aim = 1.0f;
        float BulletPOV = 120.0f;
        float ReloadPercent = 0;
        float ReloadFactor = 0.5f;
        float ScopePercent = 0;
        float ScopeFactor = 0.5f;
        float CrosshairSize = 0;
        float RecoilPercent = 0;
        float RecoilFactor = 0.3f;
        float SpreadFactor = 0.5f;
        float SwitchPercent = 0;
    } WeaponSize;

    struct eBullet {
        bool POV;
        bool Distance = false;
        bool Head = false;
        bool Chest;
        bool Body;
        bool HidePOV = false;
    } Bullet;

    struct eMisc {
        bool Jump;
        bool Speed;
        bool Spectate;
        bool Parachute;
        bool Slide;
        bool Swim;
        bool HighDamage;
        bool Tutorial = false;
        bool ResourceOptimization = false;
        bool SkyDiving = false;
        bool SmartFPS = false; // DISABLED: SmartFPS completely disabled for testing
        bool UltraFPSGraphicUnlock = false;
        bool FakeStatus = false;
        bool SkiingBoost = false;
        bool FakeOfflineMode = false;
        bool DisableReporting = false;
        bool FakeReportID = false;
        bool BlockAnalytics = false;
    } Misc;

    struct eMiscHook {
        bool Jump;
        bool JumpReady;
        bool JumpPatchReady;
        bool Speed;
        bool SpeedReady;
        bool SpeedPatchReady;
        bool Spectate;
        bool SpectateReady;
        bool SpectatePatchReady;
        bool Parachute;
        bool ParachuteReady;
        bool ParachutePatchReady;
        bool Slide;
        bool SlideReady;
        bool SlidePatchReady;
        bool Swim;
        bool SwimReady;
        bool SwimPatchReady;
        bool HighDamage;
        bool HighDamageReady;
        bool Tutorial;
        bool TutorialReady;
        bool TutorialPatchReady;
        bool ResourceOptimization;
        bool ResourceOptimizationReady;
        bool ResourceOptimizationPatchReady;
        bool SkyDiving;
        bool SkyDivingReady;
        bool SkyDivingPatchReady;
        bool SmartFPS; // DISABLED: SmartFPS - DISABLED FOR TESTING
        bool SmartFPSReady; // DISABLED: SmartFPS - DISABLED FOR TESTING
        bool SmartFPSPatchReady; // DISABLED: SmartFPS - DISABLED FOR TESTING
        bool UltraFPSGraphicUnlock;
        bool UltraFPSGraphicUnlockReady;
        bool FakeStatus;
        bool FakeStatusReady;
        bool SkiingBoost;
        bool SkiingBoostReady;
        bool SkiingBoostPatchReady;
    } MiscHook;

    struct eMiscSize {
        float Jump = 2;
        float Speed = 1.2;
        float Slide = 2.4;
        float Swim = 2;
        float FallSpeed = 3.0;
        float OptimizationLevel = 0.7f;
        int FakeStageType = 1;
        unsigned int FakeRecordID = 0;
        float EspScale = 2.0f;
        float SkiingBoost = 2.0f;
    } MiscSize;

    struct ePointer {
        struct eStart {
            uintptr_t ANOGS;
        } Start;
        struct eEnd {
            uintptr_t ANOGS;
        } End;
    } Pointer;

    struct eSettings {
        bool ShowFpsInName = true;
        bool ShowFpsInScreen = false;
        bool HideMenu = false;
        ImGuiWindowFlags ImGuiFlags = 0;
        int ClickedToShowMenu = 0;
    } Settings;

    struct eTime {
        time_t TimeReachLobby = 0;
        time_t BypassedLobbyTime = 0;
    } Time;

    struct uUserData {
        json DeviceInfo;
        std::string UserID;
        std::string DeviceID;
        std::string Token;
        time_t ExpiredUTC;
        time_t ExpiredLocal;
        bool IsValidSession;
        bool IsLoggedIn;
        bool IsOnLogin;
        bool IsRechecked;
        bool IsOnRecheck;
    } UserData;

    struct eMessage {
        int Code;
        std::string Error;
    } Message;

    struct eJni {
        JavaVM *VM;
        JNIEnv *ENV;
    } Jni;

    struct eSpecial {
        std::string Message;
    } Special;
} Config;

static void optimizeImGuiStyle() {
    ImGuiStyle *style = &ImGui::GetStyle();
    style->AntiAliasedLines = true;
    style->AntiAliasedFill = true;
    style->WindowRounding = 5.0f;
    style->FrameRounding = 5.0f;
    style->ChildRounding = 5.0f;
    style->FrameBorderSize = 1.5f;
    style->ChildBorderSize = 1.0f;
    style->WindowBorderSize = 1.0f;
    style->WindowPadding = ImVec2(8, 4);
    style->FramePadding = ImVec2(8, 3);
    style->Alpha = 0.95f;
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.95f);
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.05f, 0.05f, 0.07f, 0.90f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.10f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.20f, 0.20f, 0.24f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.15f, 0.20f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 0.98f);
    style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.50f);
}

namespace Style {
    static ImGuiStyle *Default();
}

static ImGuiStyle *Style::Default() {
    ImGuiStyle *style = &ImGui::GetStyle();
    style->AntiAliasedLines = true;
    style->AntiAliasedFill = true;
    style->WindowPadding = ImVec2(10, 5);
    style->WindowRounding = 5.0f;
    style->FramePadding = ImVec2(12, 4);
    style->FrameRounding = 5.0f;
    style->ChildRounding = 5.0f;
    style->FrameBorderSize = 2.5f;
    style->ChildBorderSize = 1.5f;
    style->WindowBorderSize = 2.0f;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->ButtonTextAlign = ImVec2(0.5, 0.5);
    style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
    style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
    style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
    style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 120);
    style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
    style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
    style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Separator] = ImVec4(0.20f, 0.25f, 0.29f, 1.00f);
    style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.10f, 0.40f, 0.75f, 0.78f);
    style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.10f, 0.40f, 0.75f, 1.00f);
    style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
    style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
    style->Colors[ImGuiCol_Tab] = ImColor(0, 0, 255, 150);
    style->Colors[ImGuiCol_TabHovered] = ImColor(0, 0, 255, 150);
    style->Colors[ImGuiCol_TabActive] = ImColor(58, 58, 255, 255);
    style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
    style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
    style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
    style->Colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
    style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
    style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
    style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
    style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);

    // Pengaturan khusus untuk slider dan elemen lainnya
    style->Colors[ImGuiCol_SliderGrab] = ImColor(210, 210, 210, 255);
    style->Colors[ImGuiCol_SliderGrabActive] = ImColor(255, 255, 255, 255);
    style->Alpha = 0.9f;
    style->Colors[ImGuiCol_ChildBg] = ImVec4(0.06f, 0.05f, 0.07f, 0.5f);

    return style;
}

#endif