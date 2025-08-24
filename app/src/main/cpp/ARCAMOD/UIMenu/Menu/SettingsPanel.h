#ifndef ARCAMOD_SETTINGS_PANEL_H
#define ARCAMOD_SETTINGS_PANEL_H

#define TEXT_SETTINGS_MENU OBF("SETTINGS MENU")
#define TEXT_FPS_DISPLAY OBF("FPS DISPLAY")
#define TEXT_FPS_IN_NAME OBF("Show FPS in Name")
#define TEXT_FPS_ON_SCREEN OBF("Show FPS on Screen")
#define TEXT_MENU_VISIBILITY OBF("MENU VISIBILITY")
#define TEXT_HIDE_MENU OBF("Hide Menu")
#define TEXT_HIDE_MENU_TIP OBF("Hide Menu Tip")
#define TEXT_ESP_MODE OBF("ESP MODE")
#define TEXT_SMOOTH_FPS OBF("Smooth FPS")
#define TEXT_ESP_OLD_BR OBF("ESP OLD BR")
#define TEXT_WALLHACK OBF("WALLHACK")
#define TEXT_NORMAL OBF("NORMAL")
#define TEXT_OUTLINE OBF("OUTLINE")
#define TEXT_BOOST_FPS OBF("BOOST FPS")

static void displaySettingsMenu() {
    static int settingsMenuLogCounter = 0;
    if (++settingsMenuLogCounter % 3600 == 0) {
        // LOGIO("Settings Menu: displaySettingsMenu() dipanggil - frame %d", settingsMenuLogCounter);
        settingsMenuLogCounter = 0;
    }

    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();
    ImVec2 textSizeSettings = ImGui::CalcTextSize(TEXT_SETTINGS_MENU);

    ImVec2 textPosSettings = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeSettings.x) * 0.5f, panelCenter.y + (panelSizeAvail.y - textSizeSettings.y) * 0.1f);
    ImGui::SetCursorScreenPos(textPosSettings);
    ImGui::Text(OBF("%s"), TEXT_SETTINGS_MENU);

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    const char *settingsText = ICON_FA_USER;
    ImVec2 textSize = ImGui::CalcTextSize(settingsText, nullptr, true);
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float xPos = (windowWidth - textSize.x) * 0.5f;
    ImGui::SetCursorPosX(xPos);
    ImGui::TextWrapped(settingsText);

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::BeginGroup();

    bool fpsOnScreen = Config.Settings.ShowFpsInScreen;
    if (ImGui::Checkbox(TEXT_FPS_ON_SCREEN, &fpsOnScreen)) {
        Config.Settings.ShowFpsInScreen = fpsOnScreen;
    }

    ImGui::EndGroup();

    ImGui::Spacing();

    if (ImGui::Button(TEXT_HIDE_MENU, ImVec2(ImGui::GetContentRegionAvailWidth(), 0))) {
        Config.Settings.HideMenu = true;
    }

    ImGui::Spacing();

    const char *fpsText = OBF("APPLY BEFORE LOGIN :");
    textSize = ImGui::CalcTextSize(fpsText, nullptr, true);
    windowWidth = ImGui::GetContentRegionAvail().x;
    xPos = (windowWidth - textSize.x) * 0.5f;
    ImGui::SetCursorPosX(xPos);
    ImGui::TextWrapped(fpsText);

    // ImGui::Checkbox(TEXT_BOOST_FPS, &Config.View.Wallhack.BoostFPS); // DISABLED: BOOST FPS checkbox dinonaktifkan
    ImGui::Checkbox(OBF("ULTRA FPS GRAPHIC UNLOCK"), &Config.Misc.UltraFPSGraphicUnlock);
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(OBF("Unlock High/Very High Graphic pada Ultra Frame Rate setting\n\n"
                              "PERINGATAN HIGH DEVICE ONLY!\n"
                              "WAJIB gunakan COOLER/PENDINGIN untuk mencegah overheat!\n"
                              "Hanya untuk device flagship dengan RAM 8GB+ dan processor tinggi\n"
                              "Fitur ini dapat menyebabkan panas berlebih pada device rendah"));
    }
    ImGui::Checkbox(OBF("SKIP TUTORIAL"), &Config.Misc.Tutorial);

    ImGui::Spacing();
    ImGui::Spacing();

    float buttonWidth = ImGui::GetContentRegionAvail().x * 0.45f;

    float totalButtonsWidth = buttonWidth * 2 + ImGui::GetStyle().ItemSpacing.x;
    float startPosX = (ImGui::GetContentRegionAvail().x - totalButtonsWidth) * 0.5f;

    ImGui::SetCursorPosX(startPosX);

    if (ImGui::Button(OBF("SAVE SETTINGS"), ImVec2(buttonWidth, 0))) {
        if (Settings::SaveSettings()) {
            ImGui::OpenPopup(OBF("Sukses"));
        } else {
            ImGui::OpenPopup(OBF("Error"));
        }
    }

    ImGui::SameLine();

    if (ImGui::Button(OBF("LOAD SETTINGS"), ImVec2(buttonWidth, 0))) {
        if (Settings::LoadSettings()) {
            Settings::ApplyGraphicsSettings();
            ImGui::OpenPopup(OBF("Sukses"));
        } else {
            ImGui::OpenPopup(OBF("Error"));
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.2f, 0.2f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.3f, 0.3f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 0.4f, 0.4f, 0.7f));

    if (ImGui::Button(OBF("DELETE SETTINGS"), ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
        ImGui::OpenPopup(OBF("Confirm Delete"));
    }

    ImGui::PopStyleColor(3);

    if (ImGui::BeginPopupModal(OBF("Confirm Delete"), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(OBF("Are you sure you want to delete all settings?"));
        ImGui::Text(OBF("This action cannot be undone."));
        ImGui::Separator();

        if (ImGui::Button(OBF("Yes, Delete"), ImVec2(120, 0))) {
            if (Settings::DeleteSettings()) {
                ImGui::CloseCurrentPopup();
                ImGui::OpenPopup(OBF("Success"));
            } else {
                ImGui::CloseCurrentPopup();
                ImGui::OpenPopup(OBF("Error"));
            }
        }

        ImGui::SameLine();

        if (ImGui::Button(OBF("Cancelled"), ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal(OBF("Success"), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(OBF("The operation was successful!"));
        ImGui::Separator();
        if (ImGui::Button(OBF("OK"), ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    if (ImGui::BeginPopupModal(OBF("Error"), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text(OBF("An error occurred while processing the settings."));
        ImGui::Separator();
        if (ImGui::Button(OBF("OK"), ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGuiIO &io = ImGui::GetIO();
    ImFont *smallerFont = io.Fonts->Fonts[1];
    if (smallerFont) {
        ImGui::PushFont(smallerFont);
    }

    ImVec2 panelRightPos = ImGui::GetCursorScreenPos();
    ImVec2 panelRightSize = ImGui::GetContentRegionAvail();
    float infoPosX = panelRightPos.x + 10.0f;
    float infoPosY = panelRightPos.y + panelRightSize.y - 60.0f;

    ImGui::SetCursorScreenPos(ImVec2(infoPosX, infoPosY));

#if IS_ONLINE_XENO == 1
    if (XenoKeyData.isLoggedIn && !XenoKeyData.userKey.empty()) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("Xeno Key: %s"), XenoKeyData.userKey.c_str());

        ImGui::SetCursorScreenPos(ImVec2(infoPosX, infoPosY + 20.0f));

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("Status:"));
        ImGui::SameLine();

        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), OBF("AKTIF"));
    } else {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("Status:"));
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), OBF("Not Active"));
    }
#else
    if (Config.UserData.IsLoggedIn && !Config.UserData.UserID.empty() && Config.UserData.ExpiredUTC > 0) {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("User ID: %s"), Config.UserData.UserID.c_str());

        ImGui::SetCursorScreenPos(ImVec2(infoPosX, infoPosY + 20.0f));

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("Status:"));
        ImGui::SameLine();

        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), OBF("AKTIF"));

        ImGui::SetCursorScreenPos(ImVec2(infoPosX, infoPosY + 40.0f));

        char expiredDateStr[64];
        struct tm *expiredTime = localtime(&Config.UserData.ExpiredLocal);
        strftime(expiredDateStr, sizeof(expiredDateStr), OBF("%d-%m-%Y"), expiredTime);

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("Expires: %s"), expiredDateStr);
    } else {
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), OBF("Status:"));
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f), OBF("Not Active"));
    }
#endif

    if (smallerFont) {
        ImGui::PopFont();
    }

    std::string versionText = OBF("App v1.6.52.9");

    ImVec2 textSizeVersion = ImGui::CalcTextSize(versionText.c_str(), nullptr, true);
    ImVec2 windowSize = ImGui::GetWindowSize();

    float versionTextPosX = windowSize.x - textSizeVersion.x + 20.0f;
    float versionTextPosY = windowSize.y - textSizeVersion.y + 1.0f;

    if (smallerFont) {
        ImGui::PushFont(smallerFont);
    }

    ImVec4 versionTextColor = ImVec4(1.0f, 1.0f, 0.8f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, versionTextColor);

    ImGui::SetCursorPos(ImVec2(versionTextPosX, versionTextPosY));
    ImGui::Text(versionText.c_str());

    if (smallerFont) {
        ImGui::PopFont();
    }

    ImGui::PopStyleColor();
}

#endif // ARCAMOD_SETTINGS_PANEL_H