#ifndef ARCAMOD_WEAPONS_PANEL_H
#define ARCAMOD_WEAPONS_PANEL_H

#define TEXT_WEAPON_MENU OBF("WEAPON MENU")
#define TEXT_RELOAD OBF("Reload")
#define TEXT_SCOPE OBF("Scope")
#define TEXT_CROSSHAIR OBF("CrossHair")
#define TEXT_RECOIL OBF("Recoil")
#define TEXT_AIM OBF("Aim")
#define TEXT_SPREAD OBF("Spread")
#define TEXT_DAMAGE OBF("Damage")

static void displayWeaponsMenu() {
    static int weaponsMenuLogCounter = 0;
    if (++weaponsMenuLogCounter % 3600 == 0) {
        // LOGIO("Weapons Menu: displayWeaponsMenu() dipanggil - frame %d", weaponsMenuLogCounter);
        weaponsMenuLogCounter = 0;
    }

    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();
    ImVec2 textSizeWeapons = ImGui::CalcTextSize(TEXT_WEAPON_MENU);

    ImVec2 textPosWeapons = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeWeapons.x) * 0.5f,
                                   panelCenter.y + (panelSizeAvail.y - textSizeWeapons.y) * 0.15f);
    ImGui::SetCursorScreenPos(textPosWeapons);
    ImGui::Text(OBF("%s"), TEXT_WEAPON_MENU);

    ImGui::Dummy(ImVec2(0.0f, 40.0f));

    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    float totalWidth = panelSizeAvail.x;
    float checkboxWidth = 100.0f;
    float spaceBetweenHorizontal = 80.0f;
    float spaceBetweenVertical = 5.0f;
    float totalCheckBoxWidth = 3 * checkboxWidth + 2 * spaceBetweenHorizontal;

    float startX = (totalWidth - totalCheckBoxWidth) / 2.0f - 20.0f;

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y));
    if (ImGui::Checkbox(TEXT_RELOAD, &Config.Weapon.Reload)) {
    }

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y));
    if (ImGui::Checkbox(TEXT_SCOPE, &Config.Weapon.Scope)) {
    }

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y));
    if (ImGui::Checkbox(TEXT_CROSSHAIR, &Config.Weapon.Crosshair)) {
    }

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + checkboxWidth + spaceBetweenVertical));
    if (ImGui::Checkbox(TEXT_RECOIL, &Config.Weapon.Recoil)) {
    }

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + checkboxWidth + spaceBetweenVertical));
    if (ImGui::Checkbox(TEXT_AIM, &Config.Weapon.Aim)) {
    }

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y + checkboxWidth + spaceBetweenVertical));
    if (ImGui::Checkbox(TEXT_SPREAD, &Config.Weapon.Spread)) {
    }

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    if (ImGui::Checkbox(TEXT_DAMAGE, &Config.Weapon.HighDamage)) {
    }

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    if (ImGui::Checkbox(OBF("Ammo"), &Config.Weapon.InfiniteAmmo)) {
    }

    // Tambahkan kode yang dikomentari sesuai permintaan user
//    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
//    if (ImGui::Checkbox(OBF("Switch"), &Config.Weapon.Switch)) {
//        // Action for Switch
//    }

//    ImGui::SameLine();
//    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
//    if (ImGui::Checkbox(OBF("Overheat"), &Config.Weapon.Overheat)) {
//        // Action for Overheat
//    }

    if (Config.Weapon.Spread) {
        ImGui::Separator();

        const char *spreadSettingsText = OBF("Bullet Spread");
        ImVec2 textSize = ImGui::CalcTextSize(spreadSettingsText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), spreadSettingsText);

        ImGui::PushItemWidth(-1);
        float spreadFactor = Config.WeaponSize.SpreadFactor;

        const char* spreadLabel;
        if (spreadFactor < 0.2f) {
            spreadLabel = OBF("ZERO SPREAD");
        } else if (spreadFactor < 0.5f) {
            spreadLabel = OBF("HIGH ACCURACY");
        } else if (spreadFactor < 0.8f) {
            spreadLabel = OBF("MEDIUM ACCURACY");
        } else {
            spreadLabel = OBF("LOW ACCURACY");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.2f)"), spreadLabel, spreadFactor);

        if (ImGui::SliderFloat(OBF("##spread_factor"), &spreadFactor, 0.05f, 1.0f, buffer)) {
            Config.WeaponSize.SpreadFactor = spreadFactor;
        }

        ImGui::PopItemWidth();
    }

    if (Config.Weapon.Scope) {
        ImGui::Separator();

        const char *scopeSettingsText = OBF("Scope Speed");
        ImVec2 textSize = ImGui::CalcTextSize(scopeSettingsText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), scopeSettingsText);

        ImGui::PushItemWidth(-1);
        float scopeFactor = Config.WeaponSize.ScopeFactor;

        const char* scopeLabel;
        if (scopeFactor < 0.3f) {
            scopeLabel = OBF("SLOW SCOPE");
        } else if (scopeFactor < 0.7f) {
            scopeLabel = OBF("MEDIUM SCOPE");
        } else {
            scopeLabel = OBF("FAST SCOPE");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.2f)"), scopeLabel, scopeFactor);

        if (ImGui::SliderFloat(OBF("##scope_factor"), &scopeFactor, 0.1f, 1.0f, buffer)) {
            Config.WeaponSize.ScopeFactor = scopeFactor;
        }

        ImGui::PopItemWidth();
    }

    if (Config.Weapon.Reload) {
        ImGui::Separator();

        const char *reloadSettingsText = OBF("Reload Speed");
        ImVec2 textSize = ImGui::CalcTextSize(reloadSettingsText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), reloadSettingsText);

        ImGui::PushItemWidth(-1);
        float reloadFactor = Config.WeaponSize.ReloadFactor;

        const char* reloadLabel;
        if (reloadFactor < 0.3f) {
            reloadLabel = OBF("FAST RELOAD");
        } else if (reloadFactor < 0.7f) {
            reloadLabel = OBF("MEDIUM RELOAD");
        } else {
            reloadLabel = OBF("SLOW RELOAD");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.2f)"), reloadLabel, reloadFactor);

        if (ImGui::SliderFloat(OBF("##reload_factor"), &reloadFactor, 0.1f, 1.0f, buffer)) {
            Config.WeaponSize.ReloadFactor = reloadFactor;
        }

        ImGui::PopItemWidth();
    }

    if (Config.Weapon.Recoil) {
        ImGui::Separator();

        const char *recoilSettingsText = OBF("Recoil Control");
        ImVec2 textSize = ImGui::CalcTextSize(recoilSettingsText);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), recoilSettingsText);

        ImGui::PushItemWidth(-1);
        float recoilFactor = Config.WeaponSize.RecoilFactor;

        const char* recoilLabel;
        if (recoilFactor < 0.3f) {
            recoilLabel = OBF("HIGH RECOIL");
        } else if (recoilFactor < 0.7f) {
            recoilLabel = OBF("MEDIUM RECOIL");
        } else {
            recoilLabel = OBF("LOW RECOIL");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1f)"), recoilLabel, recoilFactor);

        if (ImGui::SliderFloat(OBF("##recoil_factor"), &recoilFactor, 0.0f, 1.0f, buffer)) {
            Config.WeaponSize.RecoilFactor = recoilFactor;
        }

        ImGui::PopItemWidth();
    }

    if (Config.Weapon.Aim) {
        ImGui::Separator();

        const char *aimSettingsText = OBF("Aim Assist Strength");
        ImVec2 textSize = ImGui::CalcTextSize(aimSettingsText, nullptr, true);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), aimSettingsText);

        ImGui::PushItemWidth(-1);
        float aimSpeed = Config.WeaponSize.Aim;

        const char* strengthLabel;
        if (aimSpeed >= 6.0f) {
            strengthLabel = OBF("EXTREME");
        } else if (aimSpeed >= 4.0f) {
            strengthLabel = OBF("ULTRA");
        } else if (aimSpeed >= 3.0f) {
            strengthLabel = OBF("HIGH");
        } else if (aimSpeed >= 2.0f) {
            strengthLabel = OBF("MEDIUM");
        } else {
            strengthLabel = OBF("LOW");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1f)"), strengthLabel, aimSpeed);

        if (ImGui::SliderFloat(OBF("##aim_strength"), &aimSpeed, 0.1f, 8.0f, buffer)) {
            Config.WeaponSize.Aim = aimSpeed;
        }

        ImGui::PopItemWidth();
    }
}

#endif // ARCAMOD_WEAPONS_PANEL_H