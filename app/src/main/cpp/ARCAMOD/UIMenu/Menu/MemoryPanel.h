#ifndef ARCAMOD_MEMORY_PANEL_H
#define ARCAMOD_MEMORY_PANEL_H

#define TEXT_MEMORY_MENU OBF("MEMORY MENU")
#define TEXT_WALL_HACK OBF("Wall Hack")
#define TEXT_DISTANCE_BR OBF("Distance BR")
#define TEXT_HEALTH_BR OBF("Health BR")
#define TEXT_HEALTH_MP OBF("Health MP")
#define TEXT_ESP_SCALE OBF("ESP Scale")
#define TEXT_ESP_SCALE_SIZE OBF("ESP SCALE SIZE")

static void displayMemoryMenu() {
    static int memoryMenuLogCounter = 0;
    if (++memoryMenuLogCounter % 3600 == 0) {
        // LOGIO("Memory Menu: displayMemoryMenu() dipanggil - frame %d", memoryMenuLogCounter);
        memoryMenuLogCounter = 0;
    }

    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();
    ImVec2 textSizeMemory = ImGui::CalcTextSize(TEXT_MEMORY_MENU);

    ImVec2 textPosMemory = ImVec2(panelCenter.x + (panelSizeAvail.x - textSizeMemory.x) * 0.5f,
                                  panelCenter.y + (panelSizeAvail.y - textSizeMemory.y) * 0.15f);
    ImGui::SetCursorScreenPos(textPosMemory);
    ImGui::Text(OBF("%s"), TEXT_MEMORY_MENU);

    ImGui::Dummy(ImVec2(0.0f, 40.0f));

    ImVec2 cursorPos = ImGui::GetCursorScreenPos();
    float totalWidth = panelSizeAvail.x;
    float checkboxWidth = 100.0f;
    float spaceBetweenHorizontal = 80.0f;
    float spaceBetweenVertical = 5.0f;
    float totalCheckBoxWidth = 3 * checkboxWidth + 2 * spaceBetweenHorizontal;
    float startX = (totalWidth - totalCheckBoxWidth) / 2.0f - 20.0f;

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y));
    ImGui::Checkbox(TEXT_WALL_HACK, &Config.View.Wallhack.Normal);

//    ImGui::SameLine();
//    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y));
//    ImGui::Checkbox(OBF("Old BR"), &Config.View.Wallhack.EspNameOldBR);

//    ImGui::SameLine();
//    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y));
//    ImGui::Checkbox(OBF("Color MP"), &Config.View.Wallhack.EspNameColorMP);

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_DISTANCE_BR, &Config.View.Wallhack.EspNameColorBR);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_HEALTH_BR, &Config.View.Wallhack.EspNameHealthBR);

    ImGui::SameLine();
    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + checkboxWidth + spaceBetweenHorizontal, cursorPos.y));
//    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y + checkboxWidth + spaceBetweenVertical));
    ImGui::Checkbox(TEXT_HEALTH_MP, &Config.View.Wallhack.EspNameHealthMP);

    ImGui::NewLine();

    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX + 2 * (checkboxWidth + spaceBetweenHorizontal), cursorPos.y));
//    ImGui::SetCursorScreenPos(ImVec2(cursorPos.x + startX, cursorPos.y + 2 * (checkboxWidth + spaceBetweenVertical)));
    ImGui::Checkbox(TEXT_ESP_SCALE, &Config.View.Wallhack.EspScale);

    ImGui::Spacing();

    if (Config.View.Wallhack.EspScale) {
        ImGui::Dummy(ImVec2(0.0f, 80.0f));

        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::Separator();

        ImVec2 textSize = ImGui::CalcTextSize(TEXT_ESP_SCALE_SIZE);
        float windowWidth = ImGui::GetContentRegionAvail().x;
        float xPos = (windowWidth - textSize.x) * 0.5f;
        ImGui::SetCursorPosX(xPos);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), OBF("%s"), TEXT_ESP_SCALE_SIZE);
        ImGui::Spacing();

        ImGui::PushItemWidth(-1);

        const char* scaleLabel;
        if (Config.MiscSize.EspScale < 2.0f) {
            scaleLabel = OBF("NORMAL");
        } else if (Config.MiscSize.EspScale < 3.0f) {
            scaleLabel = OBF("MEDIUM");
        } else if (Config.MiscSize.EspScale < 4.0f) {
            scaleLabel = OBF("LARGE");
        } else {
            scaleLabel = OBF("X-LARGE");
        }

        char buffer[32];
        snprintf(buffer, sizeof(buffer), OBF("%s (%.1fx)"), scaleLabel, Config.MiscSize.EspScale);

        float oldEspScale = Config.MiscSize.EspScale;

        if (ImGui::SliderFloat(OBF("##esp_scale"), &Config.MiscSize.EspScale, 1.0f, 5.0f, buffer)) {
            if (oldEspScale != Config.MiscSize.EspScale) {
                // LOGIO("ESP Scale changed to %.2f", Config.MiscSize.EspScale);
                SetEspScale(Config.MiscSize.EspScale);
            }
        }

        ImGui::PopItemWidth();
    }
}

#endif // ARCAMOD_MEMORY_PANEL_H