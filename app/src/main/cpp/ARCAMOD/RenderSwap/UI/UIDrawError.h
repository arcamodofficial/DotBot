#ifndef ARCAMOD_DRAW_ERROR_H
#define ARCAMOD_DRAW_ERROR_H

extern int g_CurrentDisplayType;

static inline void DrawCenteredErrorText(const char* text) {
    ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, true);
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float xPos = (windowWidth - textSize.x) * 0.5f;
    ImGui::SetCursorPosX(xPos);
    ImGui::TextWrapped(text);
}

static inline void drawError() {
    g_CurrentDisplayType = 2;
    ImGui::SetNextWindowSize(ImVec2(glWidth * 0.38f, glHeight * 0.54f), ImGuiCond_Once);

    float padding = 10.0f;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(padding, padding));

    ImGui::Begin(TEXT_WINDOW_NAME, nullptr, ImGuiWindowFlags_None);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 8.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5.0f, 5.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 5.0f));
    ImGui::Dummy(ImVec2(0, 5.0f));

    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();

    ImGui::Dummy(ImVec2(0, panelSizeAvail.y * 0.3f));

    float windowWidth = ImGui::GetWindowWidth();
    ImVec2 titleSize = ImGui::CalcTextSize(OBF("ERROR"));
    float titleX = (windowWidth - titleSize.x) * 0.5f;

    ImGui::SetCursorPosX(titleX);
    ImGui::TextColored(ImVec4(1.0f, 0.1f, 0.1f, 1.0f), OBF("ERROR"));

    ImGui::Spacing();
    ImGui::Spacing();

    std::string error_code = OBF("Error Code: ") + std::to_string(Config.Message.Code);
    ImVec2 codeSize = ImGui::CalcTextSize(error_code.c_str());
    float codeX = (windowWidth - codeSize.x) * 0.5f;

    ImGui::SetCursorPosX(codeX);
    ImGui::TextWrapped(error_code.c_str());

    ImGui::Spacing();
    ImGui::Spacing();

    std::string error_msg = OBF("Message: ") + Config.Message.Error;

    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 0.2f));
    ImGui::BeginChild(OBF("ErrorMsg"), ImVec2(panelSizeAvail.x * 0.9f, 100), true);
    ImGui::TextWrapped(error_msg.c_str());
    ImGui::EndChild();
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::SetCursorPosX((windowWidth - ImGui::CalcTextSize(OBF("Silakan hubungi admin t.me/arcamod")).x) * 0.5f);
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 1.0f, 1.0f), OBF("Silakan hubungi admin t.me/arcamod"));

    ImGui::PopStyleVar(3);

    ImGui::End();
    ImGui::PopStyleVar();
}

#endif // ARCAMOD_DRAW_ERROR_H