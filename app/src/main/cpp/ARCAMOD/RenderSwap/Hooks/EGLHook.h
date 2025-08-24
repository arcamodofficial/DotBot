#ifndef ARCAMOD_EGL_H
#define ARCAMOD_EGL_H

#include <time.h>
#include <signal.h>
#include <setjmp.h>
#include <stdexcept>
#include <exception>
#include "../UI/UIDrawExpired.h"
#include "../UI/UIDrawError.h"
#include "../UI/UIDrawLogin.h"
#include "../UI/UIDrawLoadingLobby.h"
#include "../UI/UICheckboxReset.h"
#include "LobbyDetection.h"
#include "LobbyBypassHook.h"
#include "../Validation/KeyValidator.h"

GLuint g_LogoTexture = 0;
GLuint g_XenoLogoTexture = 0;
int g_LogoWidth = 0;
int g_LogoHeight = 0;
int g_XenoLogoWidth = 0;
int g_XenoLogoHeight = 0;
bool g_LogoLoaded = false;
bool g_XenoLogoLoaded = false;
int g_CurrentDisplayType = 0;

static void CleanupTextures() {
    if (g_LogoLoaded && g_LogoTexture != 0) {
        glDeleteTextures(1, &g_LogoTexture);
        g_LogoTexture = 0;
        g_LogoLoaded = false;
        // LOGI("Logo texture cleaned up successfully");
    }
    if (g_XenoLogoLoaded && g_XenoLogoTexture != 0) {
        glDeleteTextures(1, &g_XenoLogoTexture);
        g_XenoLogoTexture = 0;
        g_XenoLogoLoaded = false;
        // LOGI("Xeno logo texture cleaned up successfully");
    }
}

static inline bool& GetLastFrameHadMenu() {
    static bool g_LastFrameHadMenu = false;
    return g_LastFrameHadMenu;
}

static inline int& GetFrameCount() {
    static int g_FrameCount = 0;
    return g_FrameCount;
}

static inline ImVec2& GetLastDisplaySize() {
    static ImVec2 g_LastDisplaySize(0.0f, 0.0f);
    return g_LastDisplaySize;
}

static inline time_t& GetLastStyleUpdateTime() {
    static time_t g_LastStyleUpdateTime = 0;
    return g_LastStyleUpdateTime;
}

static inline time_t& GetCurrentTime() {
    static time_t g_CurrentTime = 0;
    return g_CurrentTime;
}

static inline int& GetLastStyleMode() {
    static int g_LastStyleMode = 0;
    return g_LastStyleMode;
}

static inline ImVec4& GetDefaultBorderColor() {
    static ImVec4 g_DefaultBorderColor = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
    return g_DefaultBorderColor;
}

#define g_LastFrameHadMenu GetLastFrameHadMenu()
#define g_FrameCount GetFrameCount()
#define g_LastDisplaySize GetLastDisplaySize()
#define g_LastStyleUpdateTime GetLastStyleUpdateTime()
#define g_CurrentTime GetCurrentTime()
#define g_LastStyleMode GetLastStyleMode()
#define g_DefaultBorderColor GetDefaultBorderColor()

bool IsAnyESPFeatureActive() {
    return (Config.View.Line || Config.View.Box || Config.View.Health ||
            Config.View.Name || Config.View.Distance || Config.View.Skeleton ||
            Config.View.DetailedTeamInfo || Config.View.Vehicle.Enable);
}

static inline bool IsAnyWeaponFeatureActive() {
    return (Config.Weapon.Aim || Config.Weapon.Recoil || Config.Weapon.Scope ||
            Config.Weapon.Reload || Config.Weapon.Spread || Config.Weapon.InfiniteAmmo);
}

static inline bool ShouldCallWeaponHook() {
    return (IsAnyWeaponFeatureActive() ||
            Config.Weapon.Crosshair || Config.Weapon.HighDamage ||
            Config.WeaponHook.CrosshairPatchReady || Config.WeaponHook.HighDamagePatchReady);
}

static inline bool IsAnyMiscFeatureActive() {
    return (Config.Misc.Speed || Config.Misc.Parachute || Config.Misc.Slide ||
            Config.Misc.SkyDiving || Config.Misc.SkiingBoost || Config.Misc.UltraFPSGraphicUnlock ||
            Config.Misc.Spectate /* || Config.Misc.SmartFPS */); // DISABLED: SmartFPS
}

static inline bool ShouldCallMiscHook() {
    return (IsAnyMiscFeatureActive() ||
            Config.Misc.Jump || Config.Misc.Swim || Config.Misc.Tutorial ||
            Config.MiscHook.JumpPatchReady || Config.MiscHook.SwimPatchReady ||
            Config.MiscHook.TutorialPatchReady);
}

static inline bool IsAnyWallhackFeatureActive() {
    return (Config.View.Wallhack.Normal || Config.View.Wallhack.EspScale ||
            Config.View.Wallhack.EspNameHealthMP);
}

static inline bool ShouldCallWallhackHook() {
    return (IsAnyWallhackFeatureActive() ||
            Config.View.Wallhack.BoostFPS || Config.View.Wallhack.EspNameHealthBR ||
            Config.View.Wallhack.EspNameColorBR || Config.View.Wallhack.EspNameColorMP ||
            Config.View.WallhackHook.BoostFPSReady || Config.View.WallhackHook.EspNameHealthBRReady ||
            Config.View.WallhackHook.EspNameColorBRReady || Config.View.WallhackHook.EspNameColorMPReady);
}

static inline void ExecuteAllHooks(bool shouldCreateDrawList, ImDrawList* drawList) {
    if (shouldCreateDrawList && drawList && IsAnyESPFeatureActive()) {
        DrawESP(drawList);
    }

    if (ShouldCallWeaponHook()) {
        WeaponHook();
    }
    if (ShouldCallMiscHook()) {
        MiscHook();
    }
    if (ShouldCallWallhackHook()) {
        WallhackHook();
    }
}

// DISABLED: Auto Feedback dinonaktifkan
// bool g_TakeScreenshotThisFrame = false;

static void CleanupImGui() {
    if (ImGui::GetCurrentContext()) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplAndroid_Shutdown();
        ImGui::DestroyContext();
        // LOGI("ImGui context cleaned up successfully");
    }
}

static void CleanupResources() {
    // LOGI("Starting resource cleanup...");
    CleanupTextures();
    CleanupImGui();
    // LOGI("Resource cleanup completed");
}

static void InitLogo() {
    if (!g_LogoLoaded) {
        // LOGI("Attempting to load logo...");
        // LOGI("Logo data size: %d bytes", LOGO_DATA_SIZE);

        if (LOGO_DATA == nullptr || LOGO_DATA_SIZE <= 0) {
            // LOGE("Invalid logo data - data pointer is null or size is invalid");
            return;
        }

        int channels;
        unsigned char *logoData = stbi_load_from_memory(
                LOGO_DATA,
                LOGO_DATA_SIZE,
                &g_LogoWidth,
                &g_LogoHeight,
                &channels,
                4
        );

        if (logoData) {
            // LOGI("Logo data loaded successfully. Width: %d, Height: %d, Channels: %d", g_LogoWidth, g_LogoHeight, channels);

            if (g_LogoWidth <= 0 || g_LogoHeight <= 0 || g_LogoWidth > 4096 || g_LogoHeight > 4096) {
                // LOGE("Invalid texture dimensions: %dx%d", g_LogoWidth, g_LogoHeight);
                stbi_image_free(logoData);
                return;
            }

            glGenTextures(1, &g_LogoTexture);
            if (g_LogoTexture == 0) {
                // LOGE("Failed to generate OpenGL texture");
                stbi_image_free(logoData);
                return;
            }

            glBindTexture(GL_TEXTURE_2D, g_LogoTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_LogoWidth, g_LogoHeight, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, logoData);

            GLenum err = glGetError();
            if (err == GL_NO_ERROR) {
                // LOGI("Texture created successfully with ID: %u", g_LogoTexture);
                g_LogoLoaded = true;
            } else {
                // LOGE("Error creating texture: %d", err);
                glDeleteTextures(1, &g_LogoTexture);
                g_LogoTexture = 0;
            }

            stbi_image_free(logoData);
        } else {
            // LOGI("Failed to load logo data. stbi_failure_reason: %s", stbi_failure_reason());
        }
    }
}

static void InitXenoLogo() {
    if (!g_XenoLogoLoaded) {
        // LOGI("Attempting to load logo Xeno...");
        // LOGI("Logo Xeno data size: %d bytes", XENO_LOGO_DATA_SIZE);

        if (XENO_LOGO_DATA == nullptr || XENO_LOGO_DATA_SIZE <= 0) {
            // LOGE("Invalid Xeno logo data - data pointer is null or size is invalid");
            return;
        }

        int channels;
        unsigned char *logoData = stbi_load_from_memory(
                XENO_LOGO_DATA, XENO_LOGO_DATA_SIZE, &g_XenoLogoWidth, &g_XenoLogoHeight, &channels, 4);

        if (logoData) {
            // LOGI("Logo Xeno data loaded successfully. Width: %d, Height: %d, Channels: %d", g_XenoLogoWidth, g_XenoLogoHeight, channels);

            if (g_XenoLogoWidth <= 0 || g_XenoLogoHeight <= 0 || g_XenoLogoWidth > 4096 || g_XenoLogoHeight > 4096) {
                // LOGE("Invalid Xeno texture dimensions: %dx%d", g_XenoLogoWidth, g_XenoLogoHeight);
                stbi_image_free(logoData);
                return;
            }

            glGenTextures(1, &g_XenoLogoTexture);
            if (g_XenoLogoTexture == 0) {
                // LOGE("Failed to generate Xeno OpenGL texture");
                stbi_image_free(logoData);
                return;
            }

            glBindTexture(GL_TEXTURE_2D, g_XenoLogoTexture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, g_XenoLogoWidth, g_XenoLogoHeight, 0, GL_RGBA,
                         GL_UNSIGNED_BYTE, logoData);

            GLenum err = glGetError();
            if (err == GL_NO_ERROR) {
                // LOGI("Texture created successfully with ID: %u", g_XenoLogoTexture);
                g_XenoLogoLoaded = true;
            } else {
                // LOGE("Error creating Xeno texture: %d", err);
                glDeleteTextures(1, &g_XenoLogoTexture);
                g_XenoLogoTexture = 0;
            }

            stbi_image_free(logoData);
        } else {
            // LOGI("Failed to load logo Xeno data. stbi_failure_reason: %s", stbi_failure_reason());
        }
    }
}

static EGLBoolean (*o_eglSwapBuffers)(EGLDisplay dpy, EGLSurface srf);

static inline ImGuiStyle& GetBackupStyle() {
    static ImGuiStyle g_BackupStyle;
    return g_BackupStyle;
}

static void ApplyXenoPurpleTheme(ImGuiStyle* style) {
    GetBackupStyle() = *style;

    ImVec4 purplePrimary = ImColor(165, 55, 253, 255);
    ImVec4 purpleSecondary = ImColor(120, 40, 200, 180);
    ImVec4 purpleDark = ImColor(80, 25, 150, 200);
    ImVec4 purpleBg = ImColor(40, 20, 60, 180);

    style->Colors[ImGuiCol_Border] = purplePrimary;
    style->Colors[ImGuiCol_WindowBg] = purpleBg;
    style->Colors[ImGuiCol_ChildBg] = ImColor(30, 15, 45, 150);
    style->Colors[ImGuiCol_FrameBg] = purpleDark;
    style->Colors[ImGuiCol_FrameBgHovered] = purpleSecondary;
    style->Colors[ImGuiCol_FrameBgActive] = purplePrimary;
    style->Colors[ImGuiCol_Button] = purpleDark;
    style->Colors[ImGuiCol_ButtonHovered] = purpleSecondary;
    style->Colors[ImGuiCol_ButtonActive] = purplePrimary;
    style->Colors[ImGuiCol_Header] = purpleDark;
    style->Colors[ImGuiCol_HeaderHovered] = purpleSecondary;
    style->Colors[ImGuiCol_HeaderActive] = purplePrimary;
    style->Colors[ImGuiCol_CheckMark] = purplePrimary;
    style->Colors[ImGuiCol_SliderGrab] = purpleSecondary;
    style->Colors[ImGuiCol_SliderGrabActive] = purplePrimary;
}

static void RestoreOriginalTheme(ImGuiStyle* style) {
    *style = GetBackupStyle();
}

static void SetBorderColorForMode(ImGuiStyle* style, int mode, bool forceUpdate = false) {
    if (mode != g_LastStyleMode || g_CurrentTime - g_LastStyleUpdateTime > 1 || forceUpdate) {
        switch (mode) {
            case 1:
                style->Colors[ImGuiCol_Border] = ImVec4(1.0f, 1.0f, 1.0f, 0.8f);
                break;
            case 2:
                style->Colors[ImGuiCol_Border] = ImColor(165, 55, 253, 255);
                break;
            case 3:
                style->Colors[ImGuiCol_Border] = ImColor(255, 0, 0, 255);
                break;
            case 4:
                style->Colors[ImGuiCol_Border] = ImColor(255, 0, 0, 255);
                break;
            case 0:
            default:
                style->Colors[ImGuiCol_Border] = g_DefaultBorderColor;
                break;
        }
        g_LastStyleMode = mode;
        g_LastStyleUpdateTime = g_CurrentTime;
    }
}

EGLBoolean h_eglSwapBuffers(EGLDisplay dpy, EGLSurface srf) PASS_OBF PASS_OBF_STRING {
#ifdef DEBUG
    static int eglFrameLogCounter = 0;
    if (++eglFrameLogCounter % 1800 == 0) {
        // LOGIO("h_eglSwapBuffers: Frame %d", g_FrameCount);
        eglFrameLogCounter = 0;
    }
#endif

    ResetImGuiStackCounters();
    g_FrameCount++;

    static time_t cachedTime = 0;
    if (g_FrameCount % 15 == 0 || cachedTime == 0) {
        cachedTime = time(0);
    }
    g_CurrentTime = cachedTime;

    if (!Config.Init.IL2CppReady) {
#ifdef DEBUG
        static int il2cppNotReadyCounter = 0;
        if (++il2cppNotReadyCounter % 1800 == 0) {
            // LOGIO("h_eglSwapBuffers: IL2Cpp belum siap, early return - frame %d", g_FrameCount);
            il2cppNotReadyCounter = 0;
        }
#endif
        return o_eglSwapBuffers(dpy, srf);
    }

    if (g_FrameCount % 60 == 0) {
        g_LastStyleMode = 0;
        g_LastStyleUpdateTime = 0;
    }

    static int cachedHeight = -1;
    static int cachedWidth = -1;
    static int lastQueryFrame = -1;
    bool surfaceSizeChanged = false;

    if (cachedHeight <= 0 || cachedWidth <= 0 || (g_FrameCount - lastQueryFrame) >= 60) {
        eglQuerySurface(dpy, srf, EGL_HEIGHT, &glHeight);
        eglQuerySurface(dpy, srf, EGL_WIDTH, &glWidth);

        if (glHeight != cachedHeight || glWidth != cachedWidth) {
            surfaceSizeChanged = true;
            cachedHeight = glHeight;
            cachedWidth = glWidth;
        }
        lastQueryFrame = g_FrameCount;
    } else {
        glHeight = cachedHeight;
        glWidth = cachedWidth;
    }

    if (glHeight < 0 || glWidth < 0) {
#ifdef DEBUG
        static int invalidDimensionCounter = 0;
        if (++invalidDimensionCounter % 900 == 0) {
            // LOGIO("h_eglSwapBuffers: Dimensi permukaan tidak valid - width=%d, height=%d", glWidth, glHeight);
            invalidDimensionCounter = 0;
        }
#endif
        return o_eglSwapBuffers(dpy, srf);
    }

    // DISABLED: Auto Feedback dinonaktifkan secara total
#if IS_ONLINE == 1
    /*
    if (ENABLE_AUTO_SCREENSHOT && Config.Init.IL2CppReady && Config.Telegram.EnableScreenshotFeedback) {
        // Hanya jalankan fungsi screenshot feedback jika sudah terdeteksi di lobby
        if (Config.Init.IsReachedLobby) {
            // Set waktu lobby detection pertama kali
            if (Config.Telegram.LobbyDetectedTime == 0) {
                Config.Telegram.LobbyDetectedTime = g_CurrentTime;
            }

            // Tunggu sampai FakeStatus selesai, lalu tunggu delay tambahan
            if (!Config.Telegram.AutoFeedbackStarted) {
                if (Config.Telegram.FakeStatusCompleted && Config.Telegram.FakeStatusCompletedTime > 0) {
                    // Tunggu 10-15 detik setelah FakeStatus selesai
                    if (g_CurrentTime - Config.Telegram.FakeStatusCompletedTime >= Config.Telegram.AutoFeedbackDelayAfterFakeStatus) {
                        Config.Telegram.AutoFeedbackStarted = true;
                        #ifdef DEBUG
                        // LOGI("[AUTO-FEEDBACK] Memulai Auto Feedback setelah FakeStatus selesai + delay %d detik", Config.Telegram.AutoFeedbackDelayAfterFakeStatus);
                        #endif
                    }
                }
            }

            // Hanya jalankan screenshot jika FakeStatus sudah selesai dan delay tercapai
            if (Config.Telegram.AutoFeedbackStarted) {
                // DISABLED: ScreenshotFeedback class tidak di-include
                // if (ScreenshotFeedback::getInstance().shouldTakeScreenshot(g_CurrentTime)) {
                //     g_TakeScreenshotThisFrame = true;
                //     Config.Telegram.ScreenshotInProgress = true;
                // }
            }
        }
    }
    */
#elif IS_DEV == 1
    // Auto screenshot untuk mode DEV (sama seperti IS_ONLINE - dengan lobby detection dan FakeStatus)
    // DISABLED: Auto Feedback dinonaktifkan secara total
    /*
    if (ENABLE_AUTO_SCREENSHOT && Config.Init.IL2CppReady && Config.Telegram.EnableScreenshotFeedback) {
        // Hanya jalankan fungsi screenshot feedback jika sudah terdeteksi di lobby
        if (Config.Init.IsReachedLobby) {
            // Set waktu lobby detection pertama kali
            if (Config.Telegram.LobbyDetectedTime == 0) {
                Config.Telegram.LobbyDetectedTime = g_CurrentTime;
            }

            // Tunggu sampai FakeStatus selesai, lalu tunggu delay tambahan (sama seperti IS_ONLINE)
            if (!Config.Telegram.AutoFeedbackStarted) {
                if (Config.Telegram.FakeStatusCompleted && Config.Telegram.FakeStatusCompletedTime > 0) {
                    // Tunggu 10-15 detik setelah FakeStatus selesai
                    if (g_CurrentTime - Config.Telegram.FakeStatusCompletedTime >= Config.Telegram.AutoFeedbackDelayAfterFakeStatus) {
                        Config.Telegram.AutoFeedbackStarted = true;
                        #ifdef DEBUG
                        // LOGI("[AUTO-FEEDBACK] Auto Feedback diaktifkan untuk mode DEV setelah FakeStatus selesai + delay %d detik", Config.Telegram.AutoFeedbackDelayAfterFakeStatus);
                        #endif
                    }
                }
            }

            // Hanya jalankan screenshot jika FakeStatus sudah selesai dan delay tercapai
            if (Config.Telegram.AutoFeedbackStarted) {
                // DISABLED: ScreenshotFeedback class tidak di-include
                // if (ScreenshotFeedback::getInstance().shouldTakeScreenshot(g_CurrentTime)) {
                //     g_TakeScreenshotThisFrame = true;
                //     Config.Telegram.ScreenshotInProgress = true;
                // }
            }
        }
    }
    */
#endif

    static float cachedDensity = -1.0f;
    static int lastDensityQueryFrame = -1;
    if (cachedDensity < 0 || (g_FrameCount - lastDensityQueryFrame) >= 120) {
        density = Screen$$get_dpi();
        if (density > 0) {
            cachedDensity = density;
            lastDensityQueryFrame = g_FrameCount;
        }

        if (density < 0) {
            return o_eglSwapBuffers(dpy, srf);
        }
    } else {
        density = cachedDensity;
    }

    if (g_FrameCount % 30 == 0) {
        check_lobby_state();
    }

    if (!Config.Init.Done) {
#ifdef DEBUG
        // LOGIO("h_eglSwapBuffers: Memulai inisialisasi ImGui - frame %d", g_FrameCount);
#endif

        ImGui::CreateContext();
        ImGuiStyle *style = Style::Default();
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init(OBF("#version 300 es"));

        ImGuiIO *io = &ImGui::GetIO();
        io->DisplaySize = ImVec2((float) glWidth, (float) glHeight);
        io->ConfigWindowsMoveFromTitleBarOnly = true;
        io->IniFilename = NULL;
        io->Fonts->ClearFonts();

        ImFontConfig font_cfg;
        static const ImWchar icons_ranges[] = {0xf000, 0xf3ff, 0};

        ImFontConfig CustomFont;
        CustomFont.FontDataOwnedByAtlas = false;
        ImFontConfig icons_config;
        icons_config.MergeMode = true;
        icons_config.PixelSnapH = true;
        icons_config.OversampleH = 2.5;
        icons_config.OversampleV = 2.5;

        io->Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 28.5f, &font_cfg);
        io->Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 28.5f,
                                                  &icons_config, icons_ranges);
        io->Fonts->AddFontFromMemoryTTF(&Font, sizeof Font, 20.0f, &font_cfg);
        io->Fonts->AddFontDefault(&font_cfg);

        optimizeImGuiStyle();

        // ARCAMOD: Initialize OpenGL optimizations
        ArcamodPerformance::OptimizeOpenGL();

        Config.Init.Done = true;
#ifdef DEBUG
        // LOGIO("h_eglSwapBuffers: Config.Init.Done = true, inisialisasi ImGui selesai");
#endif

        InitLogo();
#if IS_ONLINE_XENO == 1
        InitXenoLogo();
        init_xeno_key_validation();
#endif
    }

    ImGuiIO *io = &ImGui::GetIO();

    if (surfaceSizeChanged || io->DisplaySize.x != glWidth || io->DisplaySize.y != glHeight) {
        io->DisplaySize = ImVec2((float) glWidth, (float) glHeight);
        g_LastDisplaySize = io->DisplaySize;
    }

    int touchCount = Input$$get_touchCount();
    if (touchCount > 0) {
        bool isTouchSupported = Input$$get_touchSupported();
        if (isTouchSupported) {
            Touch touchInfo;

            static jmp_buf jump;
            static sighandler_t handler = [](int) { longjmp(jump, 1); };
            sighandler_t old_handler_SIGSEGV = signal(SIGSEGV, handler);
            sighandler_t old_handler_SIGABRT = signal(SIGABRT, handler);

            if (!setjmp(jump)) {
                int touchInt = 0;
                touchInfo = Input$$GetTouch(touchInfo, touchInt);
            }

            signal(SIGSEGV, old_handler_SIGSEGV);
            signal(SIGABRT, old_handler_SIGABRT);

            switch (touchInfo.m_Phase) {
                case TouchPhase::Began:
                    io->MouseDown[0] = false;
                    break;
                case TouchPhase::Stationary:
                case TouchPhase::Moved:
                    io->MousePos = ImVec2(touchInfo.m_Position.x,
                                          io->DisplaySize.y - touchInfo.m_Position.y);
                    io->MouseDown[0] = true;
                    break;
                case TouchPhase::Ended:
                case TouchPhase::Canceled:
                default:
                    io->MouseDown[0] = false;
                    break;
            }
        }
    }

#ifdef DEBUG
    static int newFrameLogCounter = 0;
    if (++newFrameLogCounter % 1800 == 0) {
        // LOGIO("h_eglSwapBuffers: Memulai ImGui NewFrame sequence - frame %d", g_FrameCount);
        newFrameLogCounter = 0;
    }
#endif

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    if (g_FrameCount % 60 == 0) {
        g_LastStyleMode = 0;
    }

    ImDrawList* drawList = nullptr;
    bool shouldCreateDrawList = IsAnyESPFeatureActive();

    if (shouldCreateDrawList) {
        drawList = ImGui::GetBackgroundDrawList();

        if (!drawList) {
#ifdef DEBUG
            static int invalidDrawListCounter = 0;
            if (++invalidDrawListCounter % 900 == 0) {
                // LOGIO("h_eglSwapBuffers: Invalid drawList detected, skipping ESP rendering - frame %d", g_FrameCount);
                invalidDrawListCounter = 0;
            }
#endif
        }
    } else {
#ifdef DEBUG
        static int espDisabledCounter = 0;
        if (++espDisabledCounter % 3600 == 0) {
            // LOGIO("h_eglSwapBuffers: Semua ESP features dinonaktifkan, skip drawList creation - frame %d", g_FrameCount);
            espDisabledCounter = 0;
        }
#endif
    }

    if (Config.Settings.ShowFpsInScreen && ImGui::GetCurrentContext() && Config.Init.Done) {
        ImDrawList* fpsDrawList = ImGui::GetBackgroundDrawList();

        if (fpsDrawList) {
            static char fps_buffer[64] = {0};
            static int last_fps = 0;
            static int fps_update_counter = 0;

            if (++fps_update_counter >= 15) {
                fps_update_counter = 0;

                ImGuiIO& io = ImGui::GetIO();
                float framerate = io.Framerate;

                if (framerate > 0.0f && framerate < 1000.0f) {
                    int current_fps = static_cast<int>(framerate);

                    if (abs(current_fps - last_fps) > 2) {
                        int result = snprintf(fps_buffer, sizeof(fps_buffer), "%s%d", OBF("FPS : "), current_fps);
                        if (result > 0 && result < sizeof(fps_buffer)) {
                            last_fps = current_fps;
                        }
                    }
                } else {
#ifdef DEBUG
                    static int invalidFpsCounter = 0;
                    if (++invalidFpsCounter % 900 == 0) {
                        // LOGIO("FPS Display: Invalid framerate detected: %.2f", framerate);
                        invalidFpsCounter = 0;
                    }
#endif
                }
            }

            if (fps_buffer[0] != '\0') {
                fpsDrawList->AddText(NULL, 40.0f, ImVec2(15, 15), ImColor(150, 255, 20, 255), fps_buffer);
            }
        }
    }

    bool shouldRenderFullUI = true;

    if (Config.Settings.HideMenu && g_LastFrameHadMenu == false && g_FrameCount % 3 != 0) {
        shouldRenderFullUI = false;
    }

    if (touchCount > 0) {
        shouldRenderFullUI = true;
    }
#if IS_ONLINE == 1
    time_t utc_time = time(nullptr);
    tm *local_tm = localtime(&utc_time);
    time_t local_time = mktime(local_tm);
    if (Config.UserData.IsLoggedIn) {
        if (!Config.UserData.UserID.empty() && Config.Message.Error.empty()) {
            time_t remainingTime = getRemainingLicenseTime();

            if (remainingTime <= 0) {
                static bool hasReset = false;
                if (!hasReset) {
                    // LOGI("Lisensi berakhir: ExpiredUTC=%ld, Current UTC=%ld", Config.UserData.ExpiredUTC, utc_time);
                    resetAllCheckboxes();
                    hasReset = true;
                }
            }
            else if (isLicenseAboutToExpire()) {
                static time_t lastWarningTime = 0;
                if (utc_time - lastWarningTime > 60) {
                    // LOGI("PERINGATAN: Lisensi akan berakhir dalam %ld menit", remainingTime / 60);
                    lastWarningTime = utc_time;

                    ImDrawList* warningDrawList = ImGui::GetBackgroundDrawList();
                    if (warningDrawList) {
                        const char* warningText = OBF("PERINGATAN: LISENSI AKAN BERAKHIR SEGERA! HARAP PERPANJANG SEGERA");
                        ImVec2 textSize = ImGui::CalcTextSize(warningText);
                        float textX = glWidth/2 - textSize.x/2;
                        warningDrawList->AddText(NULL, 30.0f, ImVec2(textX, 50),
                                                 ImColor(255, 0, 0, 255),
                                                 warningText);
                    }
                }

                // Tetap menjalankan fitur selama belum benar-benar expired
                ExecuteAllHooks(shouldCreateDrawList, drawList);
            }
                // Jika masih ada banyak waktu tersisa
            else {
                // Log sisa waktu setiap menit
                static time_t last_log_time = 0;
                if (utc_time - last_log_time > 60) { // Log setiap menit
                    // LOGI("Waktu tersisa: %ld jam %ld menit", remainingTime / 3600, (remainingTime % 3600) / 60);
                    last_log_time = utc_time;
                }

                // Jalankan fitur normal
                ExecuteAllHooks(shouldCreateDrawList, drawList);
            }
        }
    }
#endif

#if IS_LOBBY == 1
    // Optimasi kode lobby checks - jalankan hanya sekali setiap beberapa frame
    static time_t lastLobbyTimeCheck = 0;

    // Lakukan validasi hanya setiap 1 detik
    if (g_CurrentTime > lastLobbyTimeCheck + 1) {
        lastLobbyTimeCheck = g_CurrentTime;

        if (!Config.Init.IsReachedLobby) {
            // Panggil check_lobby_state alih-alih menggunakan pendekatan lama
            check_lobby_state();
        }

        if (!Config.Init.IsLobbyBypassReady) {
            if (Config.Init.IsReachedLobby) {
                if (g_CurrentTime > (Config.Time.TimeReachLobby + 3) && !Config.Init.IsBypassLobbyRunning) {
                    // LOGI("Mendeteksi sudah di lobby, menjalankan bypass_lobby()");
                    bypass_lobby();
                    Config.Init.IsBypassLobbyRunning = true;
                }
            }

            if (Config.Init.LobbyBypassed) {
                if (g_CurrentTime > (Config.Time.BypassedLobbyTime + 5)) {
                    Config.Init.IsLobbyBypassReady = true;
                    // LOGI("Lobby bypass selesai dan siap");
                }
            }
        }
    }
#endif

    // Menangani pengaturan FPS
    bool lastFpsIsInName = Config.Settings.ShowFpsInName;
    bool lastHideMenu = Config.Settings.HideMenu;

    // Perbarui status g_LastFrameHadMenu
    g_LastFrameHadMenu = !Config.Settings.HideMenu;

    if (shouldRenderFullUI && !Config.Settings.HideMenu) {
        // Panggil fungsi menu sesuai dengan kondisi
#if IS_ONLINE == 1
        time_t utc_time = time(nullptr);

        if (Config.UserData.IsLoggedIn) {
            if (!Config.UserData.UserID.empty() && Config.Message.Error.empty()) {
                time_t remainingTime = getRemainingLicenseTime();

                bool updateStyle = (g_CurrentTime - g_LastStyleUpdateTime) > 1;
                if (updateStyle) {
                    g_LastStyleUpdateTime = g_CurrentTime;
                }

                if (remainingTime <= 0) {
                    static bool hasResetUI = false;
                    if (!hasResetUI) {
                        // LOGI("UI: Lisensi berakhir, menonaktifkan menu. ExpiredUTC=%ld, Current UTC=%ld", Config.UserData.ExpiredUTC, utc_time);
                        resetAllCheckboxes();
                        hasResetUI = true;
                    }

                    if (updateStyle) {
                        ImGuiStyle* style = &ImGui::GetStyle();
                        SetBorderColorForMode(style, 4);
                    }

                    drawExpired();
                }
                else if (isLicenseAboutToExpire()) {
                    if (updateStyle) {
                        ImGuiStyle* style = &ImGui::GetStyle();
                        SetBorderColorForMode(style, 4);
                    }

#if IS_LOBBY == 1
                    if (!Config.Init.IsLobbyBypassReady) {
                        ImGui::SetNextWindowSize(ImVec2(glWidth * 0.38f, glHeight * 0.54f), ImGuiCond_Once);
                        drawOnLoadingLobby(g_CurrentTime);
                    } else {
#endif
                    renderMainMenu();

                    ImDrawList* menuWarningDrawList = ImGui::GetBackgroundDrawList();
                    if (menuWarningDrawList) {
                        ImVec2 textSize = ImGui::CalcTextSize(OBF("PERINGATAN: LISENSI AKAN BERAKHIR DALAM 00 MENIT! HARAP PERPANJANG SEGERA"));
                        float textX = glWidth/2 - textSize.x/2;
                        menuWarningDrawList->AddText(NULL, 30.0f, ImVec2(textX, 20),
                                                     ImColor(255, 0, 0, 255),
                                                     (OBF("PERINGATAN: LISENSI AKAN BERAKHIR DALAM ") + std::to_string(remainingTime / 60) + OBF(" MENIT! HARAP PERPANJANG SEGERA")).c_str());
                    }
#if IS_LOBBY == 1
                    }
#endif
                }
                else {
#if IS_LOBBY == 1
                    if (!Config.Init.IsLobbyBypassReady) {
                        ImGuiStyle* style = &ImGui::GetStyle();
                        SetBorderColorForMode(style, 2);

                        drawOnLoadingLobby(g_CurrentTime);
                    } else {
#endif
                    static time_t lastResetTime = 0;
                    if (g_CurrentTime - lastResetTime > 1) {
                        g_LastStyleMode = 0;
                        lastResetTime = g_CurrentTime;
                    }

                    ImGuiStyle* style = &ImGui::GetStyle();
                    SetBorderColorForMode(style, 1, true);

                    // SetCrashContext(UNIFIED_CONTEXT_MENU_TRANSITION); // DISABLED
                    renderMainMenu();
#if IS_LOBBY == 1
                    }
#endif
                }
            } else {
                ImGuiStyle* style = &ImGui::GetStyle();
                SetBorderColorForMode(style, 2);

                drawError();
            }
        } else {
            ImGuiStyle* style = &ImGui::GetStyle();
            SetBorderColorForMode(style, 2);

            drawOnLogin();
        }
#elif IS_ONLINE_XENO == 1
        bool updateStyle = (g_CurrentTime - g_LastStyleUpdateTime) > 1;
        if (updateStyle) {
            ImGuiStyle* style = &ImGui::GetStyle();
            SetBorderColorForMode(style, 2);
        }

        static bool last// LOGInState = false;
        static time_t lastLogTime = 0;

#if IS_DEV == 1
        ExecuteAllHooks(shouldCreateDrawList, drawList);

        if (!last// LOGInState || g_CurrentTime - lastLogTime > 30) {
            // LOGI("[EGL] Menjalankan hooks dalam mode DEV tanpa validasi key");
            last// LOGInState = true;
            lastLogTime = g_CurrentTime;
        }
#else
        if (XenoKeyData.isLoggedIn) {
            ExecuteAllHooks(shouldCreateDrawList, drawList);

            if (!last// LOGInState) {
                // LOGI("[EGL] Menjalankan hooks karena key XENO sudah tervalidasi");
                last// LOGInState = true;
            }
        } else {
            if (!last// LOGInState && g_CurrentTime - lastLogTime > 10) {
                // LOGI("[EGL] Hooks tidak dijalankan karena key XENO belum tervalidasi");
                lastLogTime = g_CurrentTime;
            }
            last// LOGInState = false;
        }
#endif

        if (Config.Init.IsReachedLobby) {
            if (xeno_key_validation_triggered) {
                if (XenoKeyData.isLoggedIn) {
                    if (!xeno_fake_status_activated) {
                        activate_fake_status_for_xeno();
                        // LOGI("[XENO] FakeStatus diaktifkan untuk Xeno Key mode (tanpa Auto Feedback)");
                    }

                    ImGuiStyle* style = &ImGui::GetStyle();
                    ApplyXenoPurpleTheme(style);

                    // SetCrashContext(UNIFIED_CONTEXT_MENU_TRANSITION); // DISABLED
                    renderMainMenu();

                    RestoreOriginalTheme(style);
                } else {
                    ImGui::SetNextWindowSize(ImVec2(glWidth * 0.38f, glHeight * 0.3f), ImGuiCond_Once);
                    DrawXenoKey// LOGInMenu();
                }
            } else {
                drawOnLoadingLobby(g_CurrentTime);
            }
        } else {
            drawOnLoadingLobby(g_CurrentTime);
        }
#else
        if (g_CurrentTime - g_LastStyleUpdateTime > 1) {
            ImGuiStyle* style = &ImGui::GetStyle();
            SetBorderColorForMode(style, 3);
        }

        ExecuteAllHooks(shouldCreateDrawList, drawList);

        // SetCrashContext(UNIFIED_CONTEXT_MENU_TRANSITION); // DISABLED
        renderMainMenu();
#endif
    }

    if (Config.Settings.ShowFpsInScreen && lastFpsIsInName) {
        Config.Settings.ShowFpsInName = false;
    } else if (Config.Settings.ShowFpsInName && !lastFpsIsInName) {
        Config.Settings.ShowFpsInScreen = false;
    }

    if (Config.Weapon.Bullet && Config.Bullet.POV && !Config.Bullet.HidePOV) {
        static ImVec2 screenCenter;
        if (surfaceSizeChanged || g_FrameCount % 30 == 0) {
            screenCenter = ImVec2(glWidth / 2, glHeight / 2);
        }

        drawList->AddCircle(
                screenCenter,
                Config.WeaponSize.BulletPOV,
                ImColor(255, 255, 255, 255),
                100
        );
    }

    if (Config.Settings.HideMenu) {
        static jmp_buf jump;
        static sighandler_t handler = [](int) { longjmp(jump, 1); };
        sighandler_t old_handler_SIGSEGV = signal(SIGSEGV, handler);
        sighandler_t old_handler_SIGABRT = signal(SIGABRT, handler);

        if (!setjmp(jump)) {
            if (Input$$GetKeyDownInt(nullptr, KeyCode::Escape)) {
                Config.Settings.ClickedToShowMenu++;
            }
        }

        signal(SIGSEGV, old_handler_SIGSEGV);
        signal(SIGABRT, old_handler_SIGABRT);

        if (Config.Settings.ClickedToShowMenu >= 4) {
            Config.Settings.HideMenu = false;
            Config.Settings.ClickedToShowMenu = 0;
        }
    }

#ifdef DEBUG
    static int stackValidationLogCounter = 0;
    if (++stackValidationLogCounter % 1800 == 0) {
        // LOGIO("h_eglSwapBuffers: Memulai ImGui stack validation - frame %d", g_FrameCount);
        stackValidationLogCounter = 0;
    }
#endif

    if (g_ChildWindowDepth != 0 || g_WindowDepth != 0) {
#ifdef DEBUG
        // LOGIO("h_eglSwapBuffers: UNBALANCED STACK DETECTED - ChildDepth=%d, WindowDepth=%d", g_ChildWindowDepth, g_WindowDepth);
        // LOGW("Unbalanced ImGui stack detected before rendering: ChildDepth=%d, WindowDepth=%d", g_ChildWindowDepth, g_WindowDepth);
#endif
        EnsureImGuiStackBalance();
    }

#ifdef DEBUG
    static int renderLogCounter = 0;
    if (++renderLogCounter % 1800 == 0) {
        // LOGIO("h_eglSwapBuffers: Memulai ImGui Render sequence - frame %d", g_FrameCount);
        renderLogCounter = 0;
    }
#endif

    if (ImGui::GetCurrentContext() != nullptr) {
        ArcamodPerformance::BeginOptimizedFrame();

        // ARCAMOD: Frame rate limiting untuk mencegah FPS drop
        static int frameCounter = 0;
        if (++frameCounter % 2 == 0) {
            ArcamodPerformance::LimitFrameRate(60.0f);
        }

        ImGui::Render();

        ImDrawData* drawData = ImGui::GetDrawData();
        if (drawData != nullptr && drawData->CmdListsCount > 0) {
            bool dataValid = true;
            for (int i = 0; i < drawData->CmdListsCount && dataValid; i++) {
                if (drawData->CmdLists[i] == nullptr) {
                    dataValid = false;
                }
            }

            if (dataValid) {
                static jmp_buf render_jump;
                static sighandler_t render_handler = [](int) { longjmp(render_jump, 1); };
                sighandler_t old_render_SIGSEGV = signal(SIGSEGV, render_handler);
                sighandler_t old_render_SIGABRT = signal(SIGABRT, render_handler);

                if (!setjmp(render_jump)) {
                    if (drawData->DisplaySize.x > 0 && drawData->DisplaySize.y > 0 &&
                        drawData->DisplayPos.x > -10000 && drawData->DisplayPos.x < 10000 &&
                        drawData->DisplayPos.y > -10000 && drawData->DisplayPos.y < 10000) {

                        ImGui_ImplOpenGL3_RenderDrawData(drawData);

#ifdef DEBUG
                        static int successRenderCounter = 0;
                        if (++successRenderCounter % 3600 == 0) {
                            // LOGIO("h_eglSwapBuffers: ImGui render successful - frame %d", g_FrameCount);
                            successRenderCounter = 0;
                        }
#endif
                    }
                }
#ifdef DEBUG
                else {
                    static int renderFailCounter = 0;
                    if (++renderFailCounter % 300 == 0) {
                        // LOGIO("h_eglSwapBuffers: OpenGL render failed, skipping frame %d", g_FrameCount);
                        renderFailCounter = 0;
                    }
                }
#endif

                signal(SIGSEGV, old_render_SIGSEGV);
                signal(SIGABRT, old_render_SIGABRT);
            }
        }

        // ARCAMOD: Memory optimization setiap 60 frame (1 detik pada 60 FPS)
        static int memoryOptimizeCounter = 0;
        if (++memoryOptimizeCounter % 60 == 0) {
            ArcamodPerformance::OptimizeMemory();
            memoryOptimizeCounter = 0;
        }

        ArcamodPerformance::EndOptimizedFrame();
    }

    // DISABLED: Auto Feedback dinonaktifkan secara total
    /*
    if (g_TakeScreenshotThisFrame) {
        // Ambil screenshot dari frame saat ini
        GLint viewport[4];
        glGetIntegerv(GL_VIEWPORT, viewport);
        int width = viewport[2];
        int height = viewport[3];

        if (width > 0 && height > 0) {
            ScreenshotFeedback::getInstance().captureScreenshot(width, height);
            #ifdef DEBUG
            // LOGI("[AUTO-FEEDBACK] Screenshot diambil: %dx%d", width, height);
            #endif
        }

        g_TakeScreenshotThisFrame = false;
        Config.Telegram.ScreenshotInProgress = false;
    }
    */

#ifdef DEBUG
    static int eglSuccessCounter = 0;
    if (++eglSuccessCounter % 7200 == 0) {
        // LOGIO("h_eglSwapBuffers: Successful completion - frame %d", g_FrameCount);
        eglSuccessCounter = 0;
    }
#endif

    return o_eglSwapBuffers(dpy, srf);
}

static EGLBoolean h_fake_eglSwapBuffers(EGLDisplay dpy, EGLSurface srf) __attribute__((__annotate__("indibr"))) {
    return h_eglSwapBuffers(dpy, srf);
}

#endif //ARCAMOD_EGL_H