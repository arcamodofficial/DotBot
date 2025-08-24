#ifndef ARCAMOD_DRAW_ONLOGIN_H
#define ARCAMOD_DRAW_ONLOGIN_H

extern int g_CurrentDisplayType;

static inline void drawOnLogin() {
    g_CurrentDisplayType = 1;

    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    static ImVec2 cachedTextSize(0, 0);
    static bool textSizeCalculated = false;

    if (!textSizeCalculated) {
        ImFont* font = ImGui::GetFont();
        if (font && font->ContainerAtlas) {
            cachedTextSize = ImGui::CalcTextSize(OBF("Waiting On Lobby To Show User ID MOD"));
            textSizeCalculated = true;
        } else {
            cachedTextSize = ImVec2(300, 20);
        }
    }

    if (glHeight <= 0 || glWidth <= 0) return;

    float margin = 15.0f;
    ImVec2 textPos(margin, glHeight - cachedTextSize.y - margin);

    ImU32 textColor = IM_COL32(255, 255, 255, 255);

    drawList->AddText(textPos, textColor, OBF("Waiting On Lobby To Show User ID MOD"));
}

#endif // ARCAMOD_DRAW_ONLOGIN_H