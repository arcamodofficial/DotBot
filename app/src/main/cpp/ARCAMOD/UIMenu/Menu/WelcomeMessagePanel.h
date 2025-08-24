#ifndef ARCAMOD_WELCOME_MESSAGE_PANEL_H
#define ARCAMOD_WELCOME_MESSAGE_PANEL_H

#define TEXT_WELCOME OBF("Welcome!")
#define TEXT_EXPLORE OBF("Explore various features.")
#define TEXT_ADJUST OBF("Adjust your settings.")
#define TEXT_INFO_REMINDER OBF("Don't Forget to Always Check INFO Menu Before Using MOD")

static void displayWelcomeText() {
    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();

    ImVec2 textSizeWelcome = ImGui::CalcTextSize(TEXT_WELCOME);
    ImVec2 textPosWelcome = ImVec2(
            panelCenter.x + (panelSizeAvail.x - textSizeWelcome.x) * 0.5f,
            panelCenter.y + (panelSizeAvail.y - textSizeWelcome.y) * 0.3f
    );
    ImGui::SetCursorScreenPos(textPosWelcome);
    ImGui::Text(OBF("%s"), TEXT_WELCOME);

    ImVec2 textSizeExplore = ImGui::CalcTextSize(TEXT_EXPLORE);
    ImVec2 textPosExplore = ImVec2(
            panelCenter.x + (panelSizeAvail.x - textSizeExplore.x) * 0.5f,
            textPosWelcome.y + textSizeWelcome.y + 10.0f
    );
    ImGui::SetCursorScreenPos(textPosExplore);
    ImGui::Text(OBF("%s"), TEXT_EXPLORE);

    ImVec2 textSizeAdjust = ImGui::CalcTextSize(TEXT_ADJUST);
    ImVec2 textPosAdjust = ImVec2(
            panelCenter.x + (panelSizeAvail.x - textSizeAdjust.x) * 0.5f,
            textPosExplore.y + textSizeExplore.y + 10.0f
    );
    ImGui::SetCursorScreenPos(textPosAdjust);
    ImGui::Text(OBF("%s"), TEXT_ADJUST);

    ImVec2 textSizeReminder = ImGui::CalcTextSize(TEXT_INFO_REMINDER);
    ImVec2 textPosReminder = ImVec2(
            panelCenter.x + (panelSizeAvail.x - textSizeReminder.x) * 0.5f,
            textPosAdjust.y + textSizeAdjust.y + 20.0f
    );
    ImGui::SetCursorScreenPos(textPosReminder);
    ImGui::Text(OBF("%s"), TEXT_INFO_REMINDER);
}

#endif // ARCAMOD_WELCOME_MESSAGE_PANEL_H