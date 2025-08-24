#ifndef ARCAMOD_MISC_PANEL_H
#define ARCAMOD_MISC_PANEL_H

// ❌ DISABLED: SmartFPS completely disabled for testing
/*
// 🎯 CLEAN SmartFPS - Forward declaration
namespace SmartFPS {
    extern bool enabled;
    void Enable();
    void Disable();
}
*/

#define TEXT_MISC_MENU OBF("MISC MENU")
#define TEXT_JUMP OBF("Jump")
#define TEXT_SPEED OBF("Speed")
#define TEXT_SPECTATE OBF("Spectate")
#define TEXT_PARACHUTE OBF("Parachute")
#define TEXT_SLIDE OBF("Slide")
#define TEXT_SWIM OBF("Swim")
#define TEXT_JUMP_HEIGHT OBF("Jump Height")
#define TEXT_SPEED_BOOST OBF("Speed Boost")
#define TEXT_SLIDE_DIST OBF("Slide Distance")
#define TEXT_SWIM_SPEED OBF("Swim Speed")

static void displayMiscMenu() {
    static int miscMenuLogCounter = 0;
    if (++miscMenuLogCounter % 3600 == 0) {
        // LOGIO("Misc Menu: displayMiscMenu() dipanggil - frame %d", miscMenuLogCounter);
        miscMenuLogCounter = 0;
    }

    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();
    ImVec2 textSizeMisc = ImGui::CalcTextSize(TEXT_MISC_MENU);

    ImVec2 textPosMisc = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeMisc.x) * 0.5f,
                                panelCenter.y + (panelSizeAvail.y - textSizeMisc.y) * 0.15f);
    ImGui::SetCursorScreenPos(textPosMisc);
    ImGui::Text(OBF("%s"), TEXT_MISC_MENU);

    ImGui::Dummy(ImVec2(0.0f, 40.0f));

    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    float totalWidth = panelSizeAvail.x;
    float checkboxWidth = 100.0f;
    float spaceBetweenHorizontal = 80.0f;
    float spaceBetweenVertical = 5.0f;
    float totalCheckBoxWidth = 3 * checkboxWidth + 2 * spaceBetweenHorizontal;
    float startX = (totalWidth - totalCheckBoxWidth) / 2.0f - 20.0f;

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y));
    ImGui::Checkbox(TEXT_JUMP, &Config.Misc.Jump);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y));
    ImGui::Checkbox(TEXT_SPEED, &Config.Misc.Speed);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y));
    ImGui::Checkbox(TEXT_SPECTATE, &Config.Misc.Spectate);

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_SLIDE, &Config.Misc.Slide);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_PARACHUTE, &Config.Misc.Parachute);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_SWIM, &Config.Misc.Swim);

    ImGui::NewLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    ImGui::Checkbox(OBF("Sky Diving"), &Config.Misc.SkyDiving);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    ImGui::Checkbox(OBF("Skiing Boost"), &Config.Misc.SkiingBoost);

    // ❌ DISABLED: SmartFPS completely disabled for testing
    /*
    // Smart FPS checkbox - DIAKTIFKAN
    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    ImGui::Checkbox(OBF("Smart FPS"), &Config.Misc.SmartFPS);
    */

    // Tambahkan kode yang dikomentari sesuai permintaan
    // Tambahkan FakeStatus pada baris baru, posisi pertama
    //ImGui::NewLine();
    //ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + 3 * (checkboxWidth + spaceBetweenVertical)));
    /*ImGui::Checkbox(OBF("Fake Status"), &Config.Misc.FakeStatus);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + 3 * (checkboxWidth + spaceBetweenVertical)));
    */
    /*
    ImGui::PushStyleColor(ImGuiCol_CheckMark, ImVec4(0.9f, 0.5f, 0.1f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.2f, 0.1f, 0.05f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.3f, 0.15f, 0.1f, 0.6f));

    bool wasHDREnabled = ResourceOptimization::highQualityMode;
    if (ImGui::Checkbox(OBF("HDR Graphics"), &ResourceOptimization::highQualityMode)) {
        ResourceOptimization::SetHighQualityMode(ResourceOptimization::highQualityMode);
    }
    ImGui::PopStyleColor(3);

    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(OBF("Mode kualitas tinggi untuk grafis yang lebih tajam dengan efek HDR-like"));
    }
*/
    /*if (Config.Misc.FakeStatus) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        const char *fakeStatusText = OBF("MANIPULASI STATUS GAME");
        ImVec2 textSize = ImGui::CalcTextSize(fakeStatusText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), fakeStatusText);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        ImGui::Checkbox(OBF("Mode Offline"), &Config.Misc.FakeOfflineMode);
        ImGui::Checkbox(OBF("Nonaktifkan Pelaporan"), &Config.Misc.DisableReporting);
        ImGui::Checkbox(OBF("ID Rekaman Palsu"), &Config.Misc.FakeReportID);

        if (Config.Misc.FakeReportID) {
            char idBuffer[32];
            snprintf(idBuffer, sizeof(idBuffer), OBF("ID Palsu: %u"), Config.MiscSize.FakeRecordID);
            ImGui::Text("%s", idBuffer);
            if (ImGui::Button(OBF("Generate ID Baru"), ImVec2(ImGui::GetContentRegionAvail().x * 0.5f, 0))) {
                Config.MiscSize.FakeRecordID = rand() % 1000000 + 10000;
            }
        }

        ImGui::Checkbox(OBF("Blokir Analitik"), &Config.Misc.BlockAnalytics);
        if (ImGui::IsItemHovered()) {
            ImGui::SetTooltip(OBF("Mencegah pelaporan data pemain ke server analitik Tencent"));
        }

        const char* stageTypeLabel;
        if (Config.MiscSize.FakeStageType == 1) {
            stageTypeLabel = OBF("LOBBY");
        } else if (Config.MiscSize.FakeStageType == 4) {
            stageTypeLabel = OBF("TRAINING");
        } else {
            stageTypeLabel = OBF("CUSTOM");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%d)"), stageTypeLabel, Config.MiscSize.FakeStageType);

        if (ImGui::SliderInt(OBF("##stage_type"), &Config.MiscSize.FakeStageType, 1, 4, buffer)) {
        }

        ImGui::PopItemWidth();

        ImGui::Spacing();
        ImGui::TextColored(ImVec4(1.0f, 0.4f, 0.4f, 1.0f), OBF("RISIKO TINGGI!"));
    }*/

    if (Config.Misc.SkyDiving) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        const char *fallSpeedText = OBF("FALL SPEED");
        ImVec2 textSize = ImGui::CalcTextSize(fallSpeedText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), fallSpeedText);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        const char* strengthLabel;
        if (Config.MiscSize.FallSpeed < 2.0f) {
            strengthLabel = OBF("LAMBAT");
        } else if (Config.MiscSize.FallSpeed < 3.5f) {
            strengthLabel = OBF("NORMAL");
        } else {
            strengthLabel = OBF("CEPAT");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1fx)"), strengthLabel, Config.MiscSize.FallSpeed);

        if (ImGui::SliderFloat(OBF("##fall_speed"), &Config.MiscSize.FallSpeed, 1.0f, 4.9f, buffer)) {
            if (Config.MiscHook.SkyDivingPatchReady) {
                // LOGIO("Fall speed slider changed to %.2f", Config.MiscSize.FallSpeed);
            }
        }

        ImGui::PopItemWidth();
    }

    if (Config.Misc.SkiingBoost) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        const char *skiingBoostText = OBF("SKIING SPEED");
        ImVec2 textSize = ImGui::CalcTextSize(skiingBoostText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), skiingBoostText);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        const char* strengthLabel;
        if (Config.MiscSize.SkiingBoost < 2.0f) {
            strengthLabel = OBF("NORMAL");
        } else if (Config.MiscSize.SkiingBoost < 4.0f) {
            strengthLabel = OBF("CEPAT");
        } else if (Config.MiscSize.SkiingBoost < 6.0f) {
            strengthLabel = OBF("SANGAT CEPAT");
        } else {
            strengthLabel = OBF("TURBO");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1fx)"), strengthLabel, Config.MiscSize.SkiingBoost);

        if (ImGui::SliderFloat(OBF("##skiing_boost"), &Config.MiscSize.SkiingBoost, 1.0f, 8.0f, buffer)) {
            if (Config.MiscHook.SkiingBoostReady) {
                // LOGIO("Skiing speed slider changed to %.2f", Config.MiscSize.SkiingBoost);
            }
        }

        ImGui::PopItemWidth();
    }

    if (Config.Misc.Speed) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        ImVec2 textSize = ImGui::CalcTextSize(TEXT_SPEED_BOOST);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), TEXT_SPEED_BOOST);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        const char* strengthLabel;
        if (Config.MiscSize.Speed < 1.2f) {
            strengthLabel = OBF("LAMBAT");
        } else if (Config.MiscSize.Speed < 1.3f) {
            strengthLabel = OBF("NORMAL");
        } else {
            strengthLabel = OBF("CEPAT");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1fx)"), strengthLabel, Config.MiscSize.Speed);

        float oldSpeedValue = Config.MiscSize.Speed;
        if (ImGui::SliderFloat(OBF("##speed_boost"), &Config.MiscSize.Speed, 1.1f, 1.4f, buffer)) {
            if (oldSpeedValue != Config.MiscSize.Speed) {
                // LOGIO("Speed slider changed to %.2f", Config.MiscSize.Speed);
            }

            if (Config.MiscHook.SpeedPatchReady) {
                HandleSpeed();
            }
        }

        ImGui::PopItemWidth();
    }

    if (Config.Misc.Slide) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        ImVec2 textSize = ImGui::CalcTextSize(TEXT_SLIDE_DIST);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), TEXT_SLIDE_DIST);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        const char* strengthLabel;
        if (Config.MiscSize.Slide < 2.3f) {
            strengthLabel = OBF("LAMBAT");
        } else if (Config.MiscSize.Slide < 2.5f) {
            strengthLabel = OBF("NORMAL");
        } else {
            strengthLabel = OBF("CEPAT");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1fx)"), strengthLabel, Config.MiscSize.Slide);

        if (ImGui::SliderFloat(OBF("##slide_speed"), &Config.MiscSize.Slide, 2.2f, 2.7f, buffer)) {
            if (Config.MiscHook.SlidePatchReady) {
                HandleSlide();
            }
        }

        ImGui::PopItemWidth();
    }

    if (Config.Misc.ResourceOptimization) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        const char *optSizeText = OBF("OPTIMIZATION LEVEL");
        ImVec2 textSize = ImGui::CalcTextSize(optSizeText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), optSizeText);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        const char* levelLabel;
        if (Config.MiscSize.OptimizationLevel < 0.3f) {
            levelLabel = OBF("RENDAH");
        } else if (Config.MiscSize.OptimizationLevel < 0.7f) {
            levelLabel = OBF("SEDANG");
        } else {
            levelLabel = OBF("TINGGI");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1f)"), levelLabel, Config.MiscSize.OptimizationLevel);

        if (ImGui::SliderFloat(OBF("##optimization_level"), &Config.MiscSize.OptimizationLevel, 0.0f, 1.0f, buffer)) {
            // LOGIO("Optimization level changed to %.2f", Config.MiscSize.OptimizationLevel);
        }

        ImGui::PopItemWidth();
    }

    // DISABLED: ResourceOptimization submenu dinonaktifkan
    // if (ResourceOptimization::highQualityMode) {
    if (false) { // DISABLED: ResourceOptimization dinonaktifkan
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        const char *hdrQualityText = OBF("GRAPHICS QUALITY");
        ImVec2 textSize = ImGui::CalcTextSize(hdrQualityText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.2f, 1.0f), hdrQualityText);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        static float graphicsQuality = 1.0f;

        const char* qualityLabel;
        if (graphicsQuality < 0.5f) {
            qualityLabel = OBF("MEDIUM");
        } else if (graphicsQuality < 1.5f) {
            qualityLabel = OBF("HIGH");
        } else {
            qualityLabel = OBF("ULTRA");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1f)"), qualityLabel, graphicsQuality);

        if (ImGui::SliderFloat(OBF("##graphics_quality"), &graphicsQuality, 0.3f, 2.0f, buffer)) {
            // LOGIO("HDR Graphics: Quality level set to %.2f", graphicsQuality);
        }

        ImGui::PopItemWidth();

        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.0f, 0.8f));
        ImGui::TextWrapped(OBF("Catatan: Mode kualitas tinggi dapat menurunkan performa pada perangkat lama"));
        ImGui::PopStyleColor();
    }

    // ❌ DISABLED: SmartFPS completely disabled for testing
    /*
    if (Config.Misc.SmartFPS) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Separator();

        const char *smartFPSText = OBF("SMART FPS - UNLOCK ONLY MODE");
        ImVec2 textSize = ImGui::CalcTextSize(smartFPSText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), smartFPSText);
        ImGui::Spacing();

        if (Config.Misc.SmartFPS && !SmartFPS::enabled) {
            SmartFPS::Enable();
        } else if (!Config.Misc.SmartFPS && SmartFPS::enabled) {
            SmartFPS::Disable();
        }

        ImGui::TextColored(ImVec4(0.0f, 1.0f, 1.0f, 1.0f), OBF("Status: UNLOCK ONLY - NO FORCE LOCK"));
        ImGui::Spacing();

        ImGui::BulletText(OBF("Ultra Frame Rate options unlocked"));
        ImGui::BulletText(OBF("Very High + Ultra combination enabled"));
        ImGui::BulletText(OBF("No forced lock to 180 FPS"));
        ImGui::BulletText(OBF("User can choose any Ultra FPS"));
        ImGui::Spacing();

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), OBF("Test Instructions:"));
        ImGui::BulletText(OBF("Go to Settings > Graphics"));
        ImGui::BulletText(OBF("Try Very High + Ultra Frame Rate"));
        ImGui::BulletText(OBF("Should not lock to 180 FPS"));
        ImGui::BulletText(OBF("Test different Ultra FPS options"));
        ImGui::Spacing();
    }
    */
    // ❌ END DISABLED: SmartFPS completely disabled for testing

    ImGui::Spacing();
}

#endif // ARCAMOD_MISC_PANEL_H