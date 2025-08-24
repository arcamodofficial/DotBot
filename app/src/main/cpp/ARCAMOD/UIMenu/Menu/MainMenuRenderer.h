#ifndef ARCAMOD_MAIN_MENU_RENDERER_H
#define ARCAMOD_MAIN_MENU_RENDERER_H

extern int g_CurrentDisplayType;

#ifdef RELEASE
#pragma clang optimize off
#pragma GCC optimize ("O0")
#pragma GCC push_options
#endif

#include <vector>

#if IS_ONLINE_XENO == 1
#include "../../RenderSwap/Validation/KeyValidator.h"
#endif

#include "UpdateStatusPanel.h"
#include "WelcomeMessagePanel.h"
#include "ESPPanel.h"
#include "WeaponsPanel.h"
#include "MiscPanel.h"
#include "SettingsPanel.h"
#include "MemoryPanel.h"
#include "InfoPanel.h"
#include "FeedbackPanel.h"

static int g_ChildWindowDepth = 0;
static int g_WindowDepth = 0;

static void ResetImGuiStackCounters() {
    if (g_ChildWindowDepth != 0 || g_WindowDepth != 0) {
        // LOGW("Resetting ImGui stack counters from Child=%d, Window=%d to 0",
        //      g_ChildWindowDepth, g_WindowDepth);
    }
    g_ChildWindowDepth = 0;
    g_WindowDepth = 0;
}

static void EnsureImGuiStackBalance() {
    while (g_ChildWindowDepth > 0) {
        ImGui::EndChild();
        g_ChildWindowDepth--;
        // LOGW("Memaksa EndChild() untuk menyeimbangkan ImGui stack");
    }

    while (g_WindowDepth > 0) {
        ImGui::End();
        g_WindowDepth--;
        // LOGW("Memaksa End() untuk menyeimbangkan ImGui stack");
    }
}

static bool SafeBeginChild(const char* str_id, const ImVec2& size = ImVec2(0, 0), bool border = false, ImGuiWindowFlags flags = 0) {
    bool result = ImGui::BeginChild(str_id, size, border, flags);
    if (result) {
        g_ChildWindowDepth++;
//        LOGD("BeginChild: %s, depth now: %d", str_id, g_ChildWindowDepth);
    }
    return result;
}

static void SafeEndChild() {
    if (g_ChildWindowDepth > 0) {
        ImGui::EndChild();
        g_ChildWindowDepth--;
//        LOGD("EndChild called, depth now: %d", g_ChildWindowDepth);
    } else {
//        LOGE("Attempted to call EndChild() with unbalanced stack");
    }
}

void optimizeImGuiStyle();

#define TEXT_WINDOW_NAME WINDOW_TITLE_NAME
#define TEXT_VISUAL OBF("Visual")
#define TEXT_MEMORY OBF("Memory")
#define TEXT_WEAPONS OBF("Weapons")
#define TEXT_MISC OBF("Misc")
#define TEXT_SETTINGS OBF("Settings")
#define TEXT_INFO OBF("INFO")
#define TEXT_READ OBF("READ")
#define TEXT_FEEDBACK OBF("FEEDBACK")

extern GLuint g_LogoTexture;
extern int g_LogoWidth;
extern int g_LogoHeight;
extern bool g_LogoLoaded;

extern GLuint g_XenoLogoTexture;
extern int g_XenoLogoWidth;
extern int g_XenoLogoHeight;
extern bool g_XenoLogoLoaded;

struct Particle {
    float x, y;
    float speed;
    float length;
    float wobbleSpeed;
    float wobbleAmount;
    float alpha;
    float size;
    float lifetime;
    float maxLifetime;
    ImVec4 color;
};

#define MAX_PARTICLES 50
static Particle particles[MAX_PARTICLES];
static bool particlesInitialized = false;

static bool useBurningEffect = false;
// static bool useRainEffect = false;
// static bool useSnowEffect = false;

static void initBurningParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = static_cast<float>(rand() % (int)(glWidth));
        particles[i].y = glHeight + static_cast<float>(rand() % 100);
        particles[i].speed = 1.0f + static_cast<float>(rand() % 100) / 100.0f * 3.0f;
        particles[i].size = 2.0f + static_cast<float>(rand() % 100) / 100.0f * 6.0f;
        particles[i].wobbleSpeed = 0.1f + static_cast<float>(rand() % 100) / 100.0f * 0.5f;
        particles[i].wobbleAmount = 0.5f + static_cast<float>(rand() % 100) / 100.0f * 2.0f;
        particles[i].alpha = 0.5f + static_cast<float>(rand() % 100) / 100.0f * 0.5f;
        particles[i].lifetime = 0.0f;
        particles[i].maxLifetime = 2.0f + static_cast<float>(rand() % 100) / 100.0f * 3.0f;

        float r = 1.0f;
        float g = 0.3f + static_cast<float>(rand() % 100) / 100.0f * 0.7f;
        float b = 0.0f;
        particles[i].color = ImVec4(r, g, b, particles[i].alpha);
    }
    particlesInitialized = true;
}

/*
// Fungsi untuk inisialisasi partikel hujan (disimpan sebagai komentar)
void initRainParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = static_cast<float>(rand() % (int)(glWidth));
        particles[i].y = static_cast<float>(rand() % (int)(glHeight) - glHeight);
        particles[i].speed = 5.0f + static_cast<float>(rand() % 100) / 100.0f * 10.0f; // Hujan lebih cepat
        particles[i].length = 10.0f + static_cast<float>(rand() % 100) / 100.0f * 30.0f; // Panjang garis hujan
        particles[i].wobbleSpeed = 0.05f + static_cast<float>(rand() % 100) / 100.0f * 0.1f; // Sedikit bergoyang
        particles[i].wobbleAmount = 0.5f + static_cast<float>(rand() % 100) / 100.0f * 1.0f; // Sedikit bergoyang
        particles[i].alpha = 0.3f + static_cast<float>(rand() % 100) / 100.0f * 0.5f; // Transparansi hujan
    }
    particlesInitialized = true;
}
*/

/*
// Fungsi untuk inisialisasi partikel salju (disimpan sebagai komentar)
void initSnowParticles() {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].x = static_cast<float>(rand() % (int)(glWidth));
        particles[i].y = static_cast<float>(rand() % (int)(glHeight) - glHeight);
        particles[i].speed = 0.5f + static_cast<float>(rand() % 100) / 100.0f * 2.0f;
        particles[i].length = 2.0f + static_cast<float>(rand() % 100) / 100.0f * 5.0f; // Untuk salju, length = ukuran
        particles[i].wobbleSpeed = 0.1f + static_cast<float>(rand() % 100) / 100.0f * 0.5f;
        particles[i].wobbleAmount = 1.0f + static_cast<float>(rand() % 100) / 100.0f * 5.0f;
        particles[i].alpha = 0.5f + static_cast<float>(rand() % 100) / 100.0f * 0.5f;
    }
    particlesInitialized = true;
}
*/

static void drawBurningEffect(ImDrawList* drawList) {
    if (!particlesInitialized) {
        initBurningParticles();
    }

    float deltaTime = ImGui::GetIO().DeltaTime;
    float time = ImGui::GetTime();

    for (int i = 0; i < MAX_PARTICLES; i++) {
        particles[i].lifetime += deltaTime;

        float lifeFactor = 1.0f - (particles[i].lifetime / particles[i].maxLifetime);
        particles[i].alpha = lifeFactor * 0.8f;

        float g = 0.3f + lifeFactor * 0.7f;
        particles[i].color = ImVec4(1.0f, g, 0.0f, particles[i].alpha);

        particles[i].y -= particles[i].speed * deltaTime * 50.0f;
        particles[i].x += sin(time * particles[i].wobbleSpeed) * particles[i].wobbleAmount * deltaTime;

        float currentSize = particles[i].size * lifeFactor;

        if (particles[i].lifetime >= particles[i].maxLifetime || particles[i].y < -50.0f) {
            particles[i].x = static_cast<float>(rand() % (int)(glWidth));
            particles[i].y = glHeight + static_cast<float>(rand() % 50);
            particles[i].speed = 1.0f + static_cast<float>(rand() % 100) / 100.0f * 3.0f;
            particles[i].size = 2.0f + static_cast<float>(rand() % 100) / 100.0f * 6.0f;
            particles[i].lifetime = 0.0f;
            particles[i].maxLifetime = 2.0f + static_cast<float>(rand() % 100) / 100.0f * 3.0f;
            particles[i].alpha = 0.8f;
            continue;
        }

        ImVec2 pos(particles[i].x, particles[i].y);
        ImU32 col = ImGui::ColorConvertFloat4ToU32(particles[i].color);
        drawList->AddCircleFilled(pos, currentSize, col);

        if (rand() % 10 == 0) {
            float sparkX = particles[i].x + static_cast<float>(rand() % 5) - 2.5f;
            float sparkY = particles[i].y - static_cast<float>(rand() % 5);
            float sparkSize = currentSize * 0.3f;
            ImU32 sparkCol = IM_COL32(255, 255, 200, (int)(particles[i].alpha * 255));
            drawList->AddCircleFilled(ImVec2(sparkX, sparkY), sparkSize, sparkCol);
        }
    }
}

/*
// Fungsi untuk menggambar efek hujan (disimpan sebagai komentar)
void drawRainEffect(ImDrawList* drawList) {
    if (!particlesInitialized) {
        initRainParticles();
    }

    float deltaTime = ImGui::GetIO().DeltaTime;
    float time = ImGui::GetTime();

    for (int i = 0; i < MAX_PARTICLES; i++) {
        // Update posisi
        particles[i].y += particles[i].speed * deltaTime * 50.0f;
        particles[i].x += sin(time * particles[i].wobbleSpeed) * particles[i].wobbleAmount * deltaTime;

        // Reset jika keluar layar
        if (particles[i].y > glHeight) {
            particles[i].y = -10.0f;
            particles[i].x = static_cast<float>(rand() % (int)(glWidth));
        }

        // Gambar hujan (garis miring dengan gradien warna biru-putih)
        ImVec2 start(particles[i].x, particles[i].y);
        ImVec2 end(particles[i].x - 1.0f, particles[i].y + particles[i].length); // Sedikit miring ke kiri

        // Warna hujan - biru muda semi transparan
        ImU32 col = IM_COL32(180, 220, 255, (int)(particles[i].alpha * 255));
        drawList->AddLine(start, end, col, 1.0f); // Garis tipis
    }
}
*/

/*
// Fungsi untuk menggambar efek salju (disimpan sebagai komentar)
void drawSnowEffect(ImDrawList* drawList) {
    if (!particlesInitialized) {
        initSnowParticles();
    }

    float deltaTime = ImGui::GetIO().DeltaTime;
    float time = ImGui::GetTime();

    for (int i = 0; i < MAX_PARTICLES; i++) {
        // Update posisi
        particles[i].y += particles[i].speed * deltaTime * 50.0f;
        particles[i].x += sin(time * particles[i].wobbleSpeed) * particles[i].wobbleAmount * deltaTime;

        // Reset jika keluar layar
        if (particles[i].y > glHeight) {
            particles[i].y = -10.0f;
            particles[i].x = static_cast<float>(rand() % (int)(glWidth));
        }

        // Gambar salju (lingkaran putih transparan)
        ImVec2 pos(particles[i].x, particles[i].y);
        ImU32 col = IM_COL32(255, 255, 255, (int)(particles[i].alpha * 255));
        drawList->AddCircleFilled(pos, particles[i].length, col);
    }
}
*/
// -- Akhir kode tambahan untuk efek partikel --

// Fungsi utama untuk merender menu UI
void renderMainMenu() PASS_OBF PASS_OBF_STRING {
    // LOGGING: Monitor main menu activity
    static int menuMainLogCounter = 0;
    if (++menuMainLogCounter % 1800 == 0) { // Log setiap 1800 frame (~60 detik pada 30fps)
        // LOGIO("Menu Main: renderMainMenu() dipanggil - frame %d", menuMainLogCounter);
        menuMainLogCounter = 0;
    }

    // Set tampilan saat ini ke normal menu
    g_CurrentDisplayType = 0;

    // ARCAMOD: Apply performance optimizations for menu rendering
    static bool performance_initialized = false;
    if (!performance_initialized) {
        ArcamodPerformance::SetOptimizedStyle();
        performance_initialized = true;
    }

    ResetImGuiStackCounters();

    ImGuiIO& io = ImGui::GetIO();
    ImVec2 screenSize = io.DisplaySize;

    static int menuImGuiLogCounter = 0;
    if (++menuImGuiLogCounter % 3600 == 0) {
        // LOGIO("Menu Main: ImGui IO operations - screen size: %.1fx%.1f", screenSize.x, screenSize.y);
        menuImGuiLogCounter = 0;
    }

    ImFont* smallerFont = io.Fonts->Fonts[1];

    ImVec2 panelLeftPos = ImGui::GetCursorScreenPos();
    ImVec2 panelLeftSize = ImVec2(screenSize.x * 0.20f, screenSize.y);

    ImVec2 panelRightPos = ImVec2(panelLeftPos.x + panelLeftSize.x, panelLeftPos.y);
    ImVec2 panelRightSize = ImVec2(screenSize.x * 0.80f, screenSize.y);

    static bool visualMode = false;
    static bool memoryMode = false;
    static bool weaponsMode = false;
    static bool miscMode = false;
    static bool settingsMode = false;
    static bool infoMode = false;

    static bool first_time = true;
    if (first_time) {
        // LOGIO("Menu Main: First time initialization - setting window size: %.1fx%.1f", glWidth * 0.38f, glHeight * 0.54f);
        ImGui::SetNextWindowSize(ImVec2(glWidth * 0.38f, glHeight * 0.54f), ImGuiCond_Once);
        first_time = false;
    }

    float padding = 10.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding, padding));

    ImGui::Begin(TEXT_WINDOW_NAME, nullptr, ImGuiWindowFlags_None);
    g_WindowDepth++;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 8.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 5.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 5.0f));
    ImGui::Dummy(ImVec2(0, 5.0f));

    // ImGui::Dummy(ImVec2(0, 20.0f)); // Ganti 20.0f dengan nilai yang diinginkan untuk ruang kosong

    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize(OBF("PLAY TIME : %s   - DATE : %s   - CLOCK : %s   - FPS : %.1f")).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

    float duration = ImGui::GetTime();
    int hours = static_cast<int>(duration / 3600);
    int minutes = static_cast<int>((duration - hours * 3600) / 60);
    int seconds = static_cast<int>(duration - hours * 3600 - minutes * 60);

    char timeString[9];
    std::sprintf(timeString, OBF("%02d:%02d:%02d"), hours, minutes, seconds);

    std::time_t currentTime = std::time(nullptr);
    struct tm *localTime = std::localtime(&currentTime);

    char dateString[11];
    std::strftime(dateString, sizeof(dateString), OBF("%Y-%m-%d"), localTime);

    char currentTimeString[9];
    std::strftime(currentTimeString, sizeof(currentTimeString), OBF("%H:%M:%S"), std::localtime(&currentTime));

    if (smallerFont) {
        ImGui::PushFont(smallerFont);
    }

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 0.8f, 1.0f));
    ImGui::Text(OBF("PLAY TIME : %s   - DATE : %s   - TIME : %s   - FPS : %.1f"), timeString, dateString, currentTimeString, ImGui::GetIO().Framerate);
    ImGui::PopStyleColor();

    if (smallerFont) {
        ImGui::PopFont();
    }

    ImVec2 window_size = ImGui::GetContentRegionAvail();
    ImGui::Columns(2, NULL, false);

    {
        ImGui::SetColumnWidth(0, window_size.x * 0.20f);
        float tambahan_tinggi_atas = 20.0f;
        float margin_bawah = 8.0f;
        float tinggi_panel = window_size.y - margin_bawah + tambahan_tinggi_atas;
        if (tinggi_panel > window_size.y) {
            tinggi_panel = window_size.y;
        }
        ImVec2 panelSize(0, tinggi_panel);

        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
        SafeBeginChild(OBF("PanelKiri"), panelSize, true);
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, 5.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);  // ARCAMOD: More rounded checkboxes - Better visible curves

        float time = ImGui::GetTime();
        float intensityFactor = 0.4f;
        float red = (sin(time * 2.0f) * 0.5f + 0.5f) * intensityFactor;
        float green = (sin(time * 2.0f + 2.0f) * 0.5f + 0.5f) * intensityFactor;
        float blue = (sin(time * 2.0f + 4.0f) * 0.5f + 0.5f) * intensityFactor;
        ImVec4 borderColor(red, green, blue, 1.0f);

        ImGui::PushStyleColor(ImGuiCol_Border, borderColor);
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.6f, 1.0f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.3f, 1.0f, 0.3f, 0.7f));

        const char* buttonLabels[] = {TEXT_VISUAL, TEXT_MEMORY, TEXT_WEAPONS, TEXT_MISC, TEXT_SETTINGS, TEXT_INFO};
        bool* buttonStates[] = {&visualMode, &memoryMode, &weaponsMode, &miscMode, &settingsMode, &infoMode};

        for (int i = 0; i < 6; ++i) {
            float buttonHeight = 45.0f;
            float buttonWidth = ImGui::GetContentRegionAvail().x - 10.0f;

            float cursorPosX = ImGui::GetCursorPosX();
            float centerPosX = cursorPosX + (ImGui::GetContentRegionAvail().x - buttonWidth) * 0.5f;
            ImGui::SetCursorPosX(centerPosX);

            ImVec2 textSize = ImGui::CalcTextSize(buttonLabels[i]);
            float textOffsetY = (buttonHeight - textSize.y) * 0.5f;

            if (i == 5) {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, textOffsetY));

                if (ImGui::Button(TEXT_INFO, ImVec2(buttonWidth, buttonHeight))) {
                    for (int j = 0; j < 6; ++j) {
                        *buttonStates[j] = (i == j);
                    }
                }

                ImGui::PopStyleVar();

                ImVec2 buttonPos = ImGui::GetItemRectMin();
                ImVec2 buttonMax = ImGui::GetItemRectMax();
                ImDrawList* drawList = ImGui::GetWindowDrawList();

                float time = ImGui::GetTime();
                float pulseFactor = (sin(time * 4.0f) * 0.5f + 0.5f);
                ImVec2 newBadgePos = ImVec2(buttonMax.x - 30.0f, buttonPos.y - 8.0f);
                ImVec4 newBadgeColor = ImVec4(1.0f, 0.0f, 0.0f, pulseFactor); // Merah dengan pulsasi

                drawList->AddRectFilled(
                        ImVec2(newBadgePos.x - 2.0f, newBadgePos.y - 2.0f),
                        ImVec2(newBadgePos.x + 24.0f, newBadgePos.y + 14.0f),
                        ImGui::ColorConvertFloat4ToU32(newBadgeColor),
                        4.0f
                );

                if (smallerFont) ImGui::PushFont(smallerFont);
                drawList->AddText(
                        ImVec2(newBadgePos.x + 2.0f, newBadgePos.y),
                        IM_COL32(50, 255, 50, (int)(255 * pulseFactor)),
                        TEXT_READ
                );
                if (smallerFont) ImGui::PopFont();
            }
            else {
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10.0f, textOffsetY));
                if (ImGui::Button(buttonLabels[i], ImVec2(buttonWidth, buttonHeight))) {
                    for (int j = 0; j < 6; ++j) {
                        *buttonStates[j] = (i == j);
                    }
                }
                ImGui::PopStyleVar();
            }

            if (ImGui::IsItemHovered()) {
                ImVec2 buttonPos = ImGui::GetItemRectMin();
                ImVec2 buttonSize = ImGui::GetItemRectMax();
                ImVec2 shadowOffset(5.0f, 5.0f);

                ImDrawList* drawList = ImGui::GetWindowDrawList();
                drawList->AddRectFilled(
                        ImVec2(buttonPos.x + shadowOffset.x, buttonPos.y + shadowOffset.y),
                        ImVec2(buttonSize.x + shadowOffset.x, buttonSize.y + shadowOffset.y),
                        IM_COL32(0, 0, 0, 100), 5.0f
                );
            }

            ImGui::Dummy(ImVec2(0, 1.0f));
        }

        ImGui::Dummy(ImVec2(0, 15.0f));

#if IS_ONLINE_XENO == 1
        if (XenoKeyData.isLoggedIn && g_XenoLogoLoaded && g_XenoLogoTexture != 0) {
            float logoWidth = 100.0f;
            float logoHeight = 100.0f;

            float windowWidth = ImGui::GetContentRegionAvail().x;
            float centerPosX = (windowWidth - logoWidth) * 0.5f;

            ImVec2 logoPos = ImGui::GetCursorScreenPos();
            logoPos.x += centerPosX;
#else
        if (g_LogoLoaded && g_LogoTexture != 0) {
            float logoWidth = 100.0f;
            float logoHeight = 100.0f;

            float windowWidth = ImGui::GetContentRegionAvail().x;
            float centerPosX = (windowWidth - logoWidth) * 0.5f;

            ImVec2 logoPos = ImGui::GetCursorScreenPos();
            logoPos.x += centerPosX;
#endif

            float time = ImGui::GetTime();
            float rotationAngle = time * 1.5f;

            float scaleX = cos(rotationAngle) * 0.5f + 0.5f;

            ImVec2 center(logoPos.x + logoWidth / 2, logoPos.y + logoHeight / 2);

            float scaledWidth = logoWidth * scaleX;
            float scaledHeight = logoHeight;

            ImVec2 newPos(
                    center.x - (scaledWidth / 2),
                    center.y - (scaledHeight / 2)
            );

            ImDrawList* drawList = ImGui::GetWindowDrawList();
            float shadowOffset = 5.0f * (1.0f - scaleX);
            drawList->AddRectFilled(
                    ImVec2(newPos.x + shadowOffset, newPos.y + shadowOffset),
                    ImVec2(newPos.x + scaledWidth + shadowOffset, newPos.y + scaledHeight + shadowOffset),
                    IM_COL32(0, 0, 0, 100 * (1.0f - scaleX))
            );

            float lightIntensity = (sin(time * 3.0f) * 0.5f + 0.5f);
            ImVec4 lightColor = ImVec4(1.0f, 1.0f, 0.8f, lightIntensity * 0.5f);

            float glowRadius = 10.0f + (lightIntensity * 5.0f);
            for (int i = 0; i < 3; i++) {
                float alpha = (3 - i) / 3.0f * lightIntensity * 0.3f;
                drawList->AddRect(
                        ImVec2(newPos.x - glowRadius * i, newPos.y - glowRadius * i),
                        ImVec2(newPos.x + scaledWidth + glowRadius * i, newPos.y + scaledHeight + glowRadius * i),
                        ImGui::ColorConvertFloat4ToU32(ImVec4(lightColor.x, lightColor.y, lightColor.z, alpha)),
                        8.0f, 0, 2.0f
                );
            }

            float highlightAngle = time * 2.0f;
            ImVec2 highlightStart(
                    newPos.x + (cos(highlightAngle) * scaledWidth),
                    newPos.y
            );
            ImVec2 highlightEnd(
                    newPos.x + (cos(highlightAngle + 3.14159f/4) * scaledWidth),
                    newPos.y + scaledHeight
            );
            drawList->AddLine(
                    highlightStart,
                    highlightEnd,
                    ImGui::ColorConvertFloat4ToU32(ImVec4(1.0f, 1.0f, 1.0f, lightIntensity * 0.5f)),
                    2.0f
            );

#if IS_ONLINE_XENO == 1
            if (XenoKeyData.isLoggedIn && g_XenoLogoLoaded) {
                ImGui::SetCursorPosX(centerPosX + (logoWidth - scaledWidth) / 2);
                ImGui::Image(
                        (void*)(intptr_t)g_XenoLogoTexture,
                        ImVec2(scaledWidth, scaledHeight),
                        ImVec2(0, 0),
                        ImVec2(1, 1),
                        ImVec4(1, 1, 1, 1)
                );
            } else {
                ImGui::SetCursorPosX(centerPosX + (logoWidth - scaledWidth) / 2);
                ImGui::Image(
                        (void*)(intptr_t)g_LogoTexture,
                        ImVec2(scaledWidth, scaledHeight),
                        ImVec2(0, 0),
                        ImVec2(1, 1),
                        ImVec4(1, 1, 1, 1)
                );
            }
#else
            ImGui::SetCursorPosX(centerPosX + (logoWidth - scaledWidth) / 2);
            ImGui::Image(
                    (void*)(intptr_t)g_LogoTexture,
                    ImVec2(scaledWidth, scaledHeight),
                    ImVec2(0, 0),
                    ImVec2(1, 1),
                    ImVec4(1, 1, 1, 1)
            );
#endif

            ImGui::Dummy(ImVec2(0, 10.0f));
        }

        ImGui::PopStyleVar(3);
        ImGui::PopStyleColor(4);
        SafeEndChild();
    }

    SafeEndChild();

    {
        ImGui::NextColumn();
        ImVec4 carbonPurpleRed(0.2f, 0.1f, 0.15f, 0.5f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, carbonPurpleRed);

        if (!settingsMode) {
            ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 1.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
        }

        SafeBeginChild(OBF("PanelKanan"), ImVec2(0, window_size.y), true);
        // g_ChildWindowDepth++; // Increment child window depth
        ImGui::SetCursorPos(ImVec2(0, -40.0f));

        if (!visualMode && !memoryMode && !weaponsMode && !miscMode && !settingsMode && !infoMode) {
            displayWelcomeText();
        }

        if (visualMode) {
            displayESPMenu();
        }

        if (memoryMode) {
            displayMemoryMenu();
        }

        if (weaponsMode) {
            displayWeaponsMenu();
        }

        if (miscMode) {
            displayMiscMenu();
        }

        if (settingsMode) {
            displaySettingsMenu();
        }

        if (infoMode) {
            displayInfoMenu();
        }

        SafeEndChild();

        if (!settingsMode) {
            ImGui::PopStyleVar(3);
        }

        ImGui::PopStyleColor();
    }

    ImGui::Columns(1);
    ImGui::PopStyleVar(3);

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    if (useBurningEffect) {
        drawBurningEffect(drawList);
    }
    /* Untuk menggunakan efek hujan, aktifkan kode ini dan matikan efek burning
    else if (useRainEffect) {
        drawRainEffect(drawList);
    }
    */
    /* Untuk menggunakan efek salju, aktifkan kode ini dan matikan efek lainnya
    else if (useSnowEffect) {
        drawSnowEffect(drawList);
    }
    */

    if (g_ChildWindowDepth != 0) {
        // LOGW("Unbalanced child window depth (%d) before End(), forcing balance", g_ChildWindowDepth);
        EnsureImGuiStackBalance();
    }

    ImGui::End();
    g_WindowDepth--;
    ImGui::PopStyleVar();
}

#ifdef RELEASE
#pragma clang optimize on
#pragma GCC pop_options
#endif

#endif // ARCAMOD_MAIN_MENU_RENDERER_H