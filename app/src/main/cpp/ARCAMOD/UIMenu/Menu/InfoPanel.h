#ifndef ARCAMOD_INFO_PANEL_H
#define ARCAMOD_INFO_PANEL_H

#include "UpdateStatusPanel.h"

#define TEXT_INFO_MENU OBF("INFO MENU")
#define TEXT_DISCLAIMER OBF("DISCLAIMER")
#define TEXT_INFORMATION OBF("INFORMATION")
#define TEXT_INDONESIA OBF("INDONESIA")
#define TEXT_ENGLISH OBF("ENGLISH")

static void displayInfoMenu() {
    static int infoMenuLogCounter = 0;
    if (++infoMenuLogCounter % 3600 == 0) {
        // LOGIO("Info Menu: displayInfoMenu() dipanggil - frame %d", infoMenuLogCounter);
        infoMenuLogCounter = 0;
    }

    ImVec2 panelCenter = ImGui::GetCursorScreenPos();
    ImVec2 panelSizeAvail = ImGui::GetContentRegionAvail();

    ImGui::Dummy(ImVec2(0, 80.0f));

    ImVec2 textSizeDisclaimer = ImGui::CalcTextSize(TEXT_DISCLAIMER);
    float titlePosY = ImGui::GetCursorPosY();
    float titleCenterX = (panelSizeAvail.x - textSizeDisclaimer.x) * 0.5f;

    ImGui::SetCursorPosX(titleCenterX);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
    ImGui::Text(OBF("%s"), TEXT_DISCLAIMER);
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Spacing();

    float disclaimerWidth = panelSizeAvail.x * 0.85f;
    float leftPadding = (panelSizeAvail.x - disclaimerWidth) * 0.5f;

    ImGuiIO& io = ImGui::GetIO();
    ImFont* smallerFont = io.Fonts->Fonts[1];

    if (smallerFont) {
        ImGui::PushFont(smallerFont);
    }

    ImGui::SetCursorPosX(leftPadding);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.7f, 0.7f, 1.0f));

    ImGui::PushTextWrapPos(leftPadding + disclaimerWidth);
    ImGui::TextWrapped(OBF("This mod is for educational purposes only. Use at your own risk. The developers are not responsible for any bans, penalties, or other consequences resulting from its use. By using this software, you acknowledge that cheating in online games violates the terms of service and can result in account termination."));
    ImGui::PopTextWrapPos();

    ImGui::PopStyleColor();

    if (smallerFont) {
        ImGui::PopFont();
    }

    ImGui::Dummy(ImVec2(0, 50.0f));

    ImVec2 textSizeInfo = ImGui::CalcTextSize(TEXT_INFORMATION);
    float infoCenterX = (panelSizeAvail.x - textSizeInfo.x) * 0.5f;

    ImGui::SetCursorPosX(infoCenterX);
    ImGui::Text(OBF("%s"), TEXT_INFORMATION);

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    float contentStartX = ImGui::GetCursorPosX() + 20.0f;
    ImGui::SetCursorPosX(contentStartX);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 30);

    ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + panelSizeAvail.x - 40);

    if (smallerFont) {
        ImGui::PushFont(smallerFont);
    }

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::Text(OBF("%s"), TEXT_INDONESIA);
    ImGui::PopStyleColor();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.7f, 0.0f, 1.0f));

    float bulletX = contentStartX;
    float textX = bulletX + 15.0f;

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Sebelum membuka MOD pastikan Clear Cache Apps CODM"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Jika sudah dalam game jangan spam keluar balik ke Lobby selesaikan pertandingan"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Rekomendasi Fitur aman yang di gunakan untuk MP : Wallhack/ESP Untuk BR : Wallhack/ESP, No Recoil, AIM Adjust"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Hindari masuk ruangan latihan berulang kali"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Anda bisa gunakan semua fitur jika hanya untuk bersenang-senang"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Gunakan Cheat dengan bijak"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Ingat tidak ada Bypass Anti Report berfikirlah Logis"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Tidak ada Cheat tanpa Banned"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Usahakan Uji 1x Match Battle Royale gunakan akun dummy untuk memastikan Bypass masih aman"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Jika mendapatkan Crash / game mengulang kembali saat ganti akun / di dalam game, segera tutup buang Recent Apps CODM nya lalu buka kembali"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Terimakasih"));
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    ImGui::SetCursorPosX(contentStartX);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    ImGui::Text(OBF("%s"), TEXT_ENGLISH);
    ImGui::PopStyleColor();
    ImGui::Separator();
    ImGui::Spacing();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 0.85f, 1.0f, 1.0f));

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Before opening MOD, make sure to Clear Cache of CODM Apps"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Once in game, don't spam exit back to Lobby, finish the match"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Recommended safe features to use for MP: Wallhack/ESP, For BR: Wallhack/ESP, No Recoil, AIM Adjust"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Avoid entering training rooms repeatedly"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("You can use all features if it's just for fun"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Use Cheat wisely"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Remember there is no Bypass Anti Report, think logically"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("There is no Cheat without risk of being Banned"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Recommend testing 1x Battle Royale match using dummy account to ensure Bypass safety"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("If you experience Crash / game restart when switching accounts / in-game, immediately close and remove CODM from Recent Apps then reopen"));
    ImGui::Spacing();

    ImGui::SetCursorPosX(bulletX);
    ImGui::Text(OBF("-"));
    ImGui::SameLine();
    ImGui::SetCursorPosX(textX);
    ImGui::TextWrapped(OBF("Thank you"));
    ImGui::PopStyleColor();

    ImGui::Dummy(ImVec2(0, 50.0f));

    std::vector<UpdateInfo> updates = getUpdates();

    for (size_t i = 0; i < updates.size(); i++) {
        displayCollapsibleChangelog(updates[i], i == 0);

        if (i < updates.size() - 1) {
            ImGui::Spacing();
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    if (smallerFont) {
        ImGui::PopFont();
    }

    ImGui::PopTextWrapPos();
}

#endif // ARCAMOD_INFO_PANEL_H