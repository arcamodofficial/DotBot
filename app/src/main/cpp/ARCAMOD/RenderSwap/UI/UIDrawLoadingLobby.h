#ifndef ARCAMOD_DRAW_ONLOADINGLOBBY_H
#define ARCAMOD_DRAW_ONLOADINGLOBBY_H

static inline void drawOnLoadingLobby(time_t currentTime) {
    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    static ImVec2 cachedTextSize(0, 0);
    static bool textSizeCalculated = false;

    if (!textSizeCalculated) {
        ImFont* font = ImGui::GetFont();
        if (font && font->ContainerAtlas) {
            cachedTextSize = ImGui::CalcTextSize(OBF("Detecting game Lobby to activate Features"));
            textSizeCalculated = true;
        } else {
            cachedTextSize = ImVec2(350, 20);
        }
    }

    if (glHeight <= 0 || glWidth <= 0) return;

    float margin = 15.0f;
    ImVec2 textPos(margin, glHeight - cachedTextSize.y - margin);

    ImU32 textColor = IM_COL32(255, 255, 255, 255);

    drawList->AddText(textPos, textColor, OBF("Detecting game Lobby to activate Features"));

}

#endif // ARCAMOD_DRAW_ONLOADINGLOBBY_H