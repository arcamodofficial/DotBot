#ifndef ARCAMOD_ESP_PANEL_H
#define ARCAMOD_ESP_PANEL_H

#define TEXT_ESP_MENU OBF("ESP MENU")
#define TEXT_LINE OBF("Line")
#define TEXT_BOX OBF("Box")
#define TEXT_HEALTH OBF("Health")
#define TEXT_NAME OBF("Name")
#define TEXT_DISTANCE OBF("Distance")
#define TEXT_BOX_FILL OBF("BOX FILL SETTINGS")
#define TEXT_ENABLE OBF("Enable")
#define TEXT_DISABLE OBF("Disable")
#define TEXT_SKELETON OBF("Skeleton")

static void displayESPMenu() {
    static int espMenuLogCounter = 0;
    if (++espMenuLogCounter % 3600 == 0) {
        // LOGIO("ESP Menu: displayESPMenu() dipanggil - frame %d", espMenuLogCounter);
        espMenuLogCounter = 0;
    }

    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();
    ImVec2 textSizeESP = ImGui::CalcTextSize(TEXT_ESP_MENU);

    ImVec2 textPosESP = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeESP.x) * 0.5f,
                               panelCenter.y + (panelSizeAvail.y - textSizeESP.y) * 0.15f);
    ImGui::SetCursorScreenPos(textPosESP);
    ImGui::Text(OBF("%s"), TEXT_ESP_MENU);

    ImGui::Dummy(ImVec2(0.0f, 40.0f));

    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    float totalWidth = panelSizeAvail.x;
    float checkboxWidth = 100.0f;
    float spaceBetweenHorizontal = 80.0f;
    float spaceBetweenVertical = 5.0f;
    float totalCheckBoxWidth = 3 * checkboxWidth + 2 * spaceBetweenHorizontal;
    float startX = (totalWidth - totalCheckBoxWidth) / 2.0f - 20.0f;

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y));
    ImGui::Checkbox(TEXT_LINE, &Config.View.Line);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y));
    ImGui::Checkbox(TEXT_BOX, &Config.View.Box);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y));
    ImGui::Checkbox(TEXT_HEALTH, &Config.View.Health);

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + checkboxWidth + spaceBetweenVertical));

    ImGui::Checkbox(TEXT_NAME, &Config.View.Name);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + checkboxWidth + spaceBetweenVertical));

    ImGui::Checkbox(TEXT_DISTANCE, &Config.View.Distance);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_SKELETON, &Config.View.Skeleton);

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    ImGui::Checkbox(OBF("Team Info"), &Config.View.DetailedTeamInfo);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    ImGui::Checkbox(OBF("Vehicle"), &Config.View.Vehicle.Enable);

    ImGui::NewLine();

    if (Config.View.Vehicle.Enable) {
        float vehicleESPSectionY = cursorPos.y + 3 * (checkboxWidth + spaceBetweenVertical) + 10.0f;

        ImVec2 textSizeVehicleESP = ImGui::CalcTextSize(OBF("VEHICLE ESP SETTINGS"));
        ImVec2 textPosVehicleESP = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeVehicleESP.x) * 0.5f, vehicleESPSectionY);
        ImGui::SetCursorScreenPos(textPosVehicleESP);
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "%s", OBF("VEHICLE ESP SETTINGS"));

        float vehicleESPCheckY = vehicleESPSectionY + 35.0f;

        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, vehicleESPCheckY));
        ImGui::Checkbox(OBF("V-Line"), &Config.View.Vehicle.Line);

        ImGui::SameLine();
        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, vehicleESPCheckY));
        ImGui::Checkbox(OBF("V-Box"), &Config.View.Vehicle.Box);

        ImGui::SameLine();
        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), vehicleESPCheckY));
        ImGui::Checkbox(OBF("V-Distance"), &Config.View.Vehicle.Distance);

        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, vehicleESPCheckY + checkboxWidth + spaceBetweenVertical));
        ImGui::Checkbox(OBF("V-Health"), &Config.View.Vehicle.Health);

        ImGui::NewLine();
        ImGui::Dummy(ImVec2(0.0f, 10.0f));
    }

    if (Config.View.Box) {
        float boxFillSectionY;
        if (Config.View.Vehicle.Enable) {
            float vehicleESPHeight = 35.0f + (checkboxWidth + spaceBetweenVertical) * 2;
            boxFillSectionY = cursorPos.y + 3 * (checkboxWidth + spaceBetweenVertical) + 10.0f + vehicleESPHeight + 15.0f;
        } else {
            boxFillSectionY = cursorPos.y + 3 * (checkboxWidth + spaceBetweenVertical) + 10.0f;
        }

        ImVec2 textSizeBoxFill = ImGui::CalcTextSize(TEXT_BOX_FILL);
        ImVec2 textPosBoxFill = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeBoxFill.x) * 0.5f, boxFillSectionY);
        ImGui::SetCursorScreenPos(textPosBoxFill);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%s", TEXT_BOX_FILL);

        float boxFillCheckY = boxFillSectionY + 35.0f;

        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, boxFillCheckY));
        if (ImGui::Checkbox(TEXT_ENABLE, &Config.View.EnableBoxFill)) {
            Config.View.EnableBoxFill = true;
            Config.View.DisableBoxFill = false;
        }

        ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), boxFillCheckY));
        if (ImGui::Checkbox(TEXT_DISABLE, &Config.View.DisableBoxFill)) {
            Config.View.EnableBoxFill = false;
            Config.View.DisableBoxFill = true;
        }
    }

    ImGui::Spacing();
}

#endif // ARCAMOD_ESP_PANEL_H