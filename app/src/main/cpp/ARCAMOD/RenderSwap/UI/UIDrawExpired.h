#ifndef ARCAMOD_DRAW_EXPIRED_H
#define ARCAMOD_DRAW_EXPIRED_H

extern int g_CurrentDisplayType;

static inline void drawExpired() {
    g_CurrentDisplayType = 3;

    if (!ImGui::GetCurrentContext()) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    static ImVec2 cachedTextSize(0, 0);
    static bool textSizeCalculated = false;
    static std::string cachedUserIdText = "";

    if (!textSizeCalculated || cachedUserIdText != Config.UserData.UserID) {
        ImFont* font = ImGui::GetFont();
        if (font && font->ContainerAtlas) {
            cachedUserIdText = Config.UserData.UserID;
            std::string fullText = OBF("USER ID EXPIRED !! Please contact admin to renew your license | User ID : ") + cachedUserIdText;
            cachedTextSize = ImGui::CalcTextSize(fullText.c_str());
            textSizeCalculated = true;
        } else {
            cachedTextSize = ImVec2(600, 20);
        }
    }

    if (glHeight <= 0 || glWidth <= 0) return;

    float margin = 15.0f;
    ImVec2 textPos(margin, glHeight - cachedTextSize.y - margin);

    float brushPadding = 18.0f;
    float brushHeight = cachedTextSize.y + (brushPadding * 0.8f);
    float brushWidth = cachedTextSize.x + (brushPadding * 1.4f);

    ImU32 brushMainColor = IM_COL32(160, 20, 20, 200);
    ImU32 brushDarkColor = IM_COL32(120, 15, 15, 180);
    ImU32 textColor = IM_COL32(255, 255, 255, 255);

    float backgroundOffset = 8.0f;
    ImVec2 brushPos(textPos.x - brushPadding, textPos.y - brushPadding + backgroundOffset);

    ImVec2 brushPoints1[] = {
            ImVec2(brushPos.x + 3, brushPos.y + brushHeight * 0.4f),
            ImVec2(brushPos.x + 8, brushPos.y + 1),
            ImVec2(brushPos.x + 20, brushPos.y),
            ImVec2(brushPos.x + brushWidth * 0.75f, brushPos.y + 2),
            ImVec2(brushPos.x + brushWidth - 4, brushPos.y + 6),
            ImVec2(brushPos.x + brushWidth - 2, brushPos.y + brushHeight * 0.6f),
            ImVec2(brushPos.x + brushWidth - 6, brushPos.y + brushHeight - 1),
            ImVec2(brushPos.x + brushWidth * 0.8f, brushPos.y + brushHeight),
            ImVec2(brushPos.x + brushWidth * 0.5f, brushPos.y + brushHeight),
            ImVec2(brushPos.x + 15, brushPos.y + brushHeight - 2),
            ImVec2(brushPos.x + 4, brushPos.y + brushHeight * 0.75f),
            ImVec2(brushPos.x + 1, brushPos.y + brushHeight * 0.55f)
    };
    drawList->AddConvexPolyFilled(brushPoints1, 12, brushMainColor);

    ImVec2 brushPoints2[] = {
            ImVec2(brushPos.x + 1, brushPos.y + brushHeight * 0.45f + 1),
            ImVec2(brushPos.x + 6, brushPos.y + 3),
            ImVec2(brushPos.x + 18, brushPos.y + 2),
            ImVec2(brushPos.x + brushWidth * 0.65f, brushPos.y + 4),
            ImVec2(brushPos.x + brushWidth - 8, brushPos.y + 8),
            ImVec2(brushPos.x + brushWidth - 4, brushPos.y + brushHeight * 0.7f),
            ImVec2(brushPos.x + brushWidth - 10, brushPos.y + brushHeight),
            ImVec2(brushPos.x + brushWidth * 0.75f, brushPos.y + brushHeight + 1),
            ImVec2(brushPos.x + brushWidth * 0.4f, brushPos.y + brushHeight),
            ImVec2(brushPos.x + 12, brushPos.y + brushHeight - 3),
            ImVec2(brushPos.x + 2, brushPos.y + brushHeight * 0.8f),
            ImVec2(brushPos.x, brushPos.y + brushHeight * 0.65f)
    };
    drawList->AddConvexPolyFilled(brushPoints2, 12, brushDarkColor);

    ImVec2 texturePoints1[] = {
            ImVec2(brushPos.x + 2, brushPos.y + 4),
            ImVec2(brushPos.x + 10, brushPos.y + 2),
            ImVec2(brushPos.x + 16, brushPos.y + 7),
            ImVec2(brushPos.x + 8, brushPos.y + 10),
            ImVec2(brushPos.x + 3, brushPos.y + 8)
    };
    drawList->AddConvexPolyFilled(texturePoints1, 5, brushDarkColor);

    ImVec2 texturePoints2[] = {
            ImVec2(brushPos.x + brushWidth - 15, brushPos.y + brushHeight - 8),
            ImVec2(brushPos.x + brushWidth - 4, brushPos.y + brushHeight - 6),
            ImVec2(brushPos.x + brushWidth - 2, brushPos.y + brushHeight - 1),
            ImVec2(brushPos.x + brushWidth - 12, brushPos.y + brushHeight),
            ImVec2(brushPos.x + brushWidth - 18, brushPos.y + brushHeight - 4)
    };
    drawList->AddConvexPolyFilled(texturePoints2, 5, brushDarkColor);

    std::string fullText = OBF("USER ID EXPIRED !! Please contact admin to renew your license | User ID : ") + Config.UserData.UserID;
    drawList->AddText(textPos, textColor, fullText.c_str());
}

#endif // ARCAMOD_DRAW_EXPIRED_H