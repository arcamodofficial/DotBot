#ifndef ARCAMOD_XENOKEYVALIDATION_H
#define ARCAMOD_XENOKEYVALIDATION_H

#include <string>
#include <fstream>

class Settings;

void HandleFakeStatus();

#define XENO_KEY_FILE OBF("/data/data/com.garena.game.codm/files/.xeno_key")

static bool SaveXenoKeyToFile(const std::string& key) {
    try {
        std::ofstream file(XENO_KEY_FILE);
        if (!file.is_open()) {
            // LOGE("[XENO-KEY] Gagal membuka file untuk menyimpan key");
            return false;
        }
        file << key;
        file.close();
        // LOGI("[XENO-KEY] Key berhasil disimpan ke file: %s", key.c_str());
        return true;
    } catch (...) {
        // LOGE("[XENO-KEY] Error saat menyimpan key ke file");
        return false;
    }
}

static std::string LoadXenoKeyFromFile() {
    std::string key;
    try {
        std::ifstream file(XENO_KEY_FILE);
        if (!file.is_open()) {
            // LOGE("[XENO-KEY] File key tidak ditemukan");
            return "";
        }
        std::getline(file, key);
        file.close();
        // LOGI("[XENO-KEY] Key berhasil dimuat dari file: %s", key.c_str());
        return key;
    } catch (...) {
        // LOGE("[XENO-KEY] Error saat memuat key dari file");
        return "";
    }
}

#define XENO_PANEL_URL OBF("https://xeno-store-official.xyz/connect")

static void init_xeno_key_validation();
static void trigger_xeno_key_validation();
static void activate_fake_status_for_xeno();
static bool ValidateXenoKey(const std::string& key);
static void DrawXenoKeyLoginMenu();

static inline void DrawCenteredText(const char* text) {
    ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, true);
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float xPos = (windowWidth - textSize.x) * 0.5f;
    ImGui::SetCursorPosX(xPos);
    ImGui::TextWrapped(text);
}

struct XenoKeyDataStruct {
    std::string userKey;
    std::string authToken;
    std::string expiredDate;
    std::string errorMessage;
    bool isLoggedIn = false;
    bool isLoginAttempted = false;
    bool loginSuccess = false;
    bool isValidated = false;
};

XenoKeyDataStruct XenoKeyData;

static bool xeno_key_validation_triggered = false;
static bool xeno_fake_status_activated = false;

static std::string GetXenoUserKey() {
    return XenoKeyData.userKey;
}

static void SetXenoUserKey(const std::string& key) {
    XenoKeyData.userKey = key;
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

static bool ValidateXenoKey(const std::string& key) {
    CURL *curl;
    CURLcode res;
    std::string responseData;
    bool validationSuccess = false;

    XenoKeyData.errorMessage.clear();
    XenoKeyData.userKey = key;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, OBF("POST"));
        curl_easy_setopt(curl, CURLOPT_URL, XENO_PANEL_URL);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, OBF("https"));

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, OBF("Accept: application/json"));
        headers = curl_slist_append(headers, OBF("Content-Type: application/x-www-form-urlencoded"));
        headers = curl_slist_append(headers, OBF("Charset: UTF-8"));
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char postData[4096];
        sprintf(postData, OBF("game=CODM&user_key=%s&serial=%s"),
                key.c_str(), Config.Init.uuid.c_str());

        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json response = json::parse(responseData);

                if (response.contains(OBF("status")) && response[OBF("status")] == true) {
                    if (response.contains(OBF("data")) && response[OBF("data")].is_object()) {
                        auto& data = response[OBF("data")];

                        if (data.contains(OBF("token")) && data[OBF("token")].is_string()) {
                            XenoKeyData.authToken = data[OBF("token")].get<std::string>();

                            if (data.contains(OBF("expired_date")) && data[OBF("expired_date")].is_string()) {
                                XenoKeyData.expiredDate = data[OBF("expired_date")].get<std::string>();
                            } else {
                                XenoKeyData.expiredDate = "";
                            }

                            if (data.contains(OBF("rng")) && data[OBF("rng")].is_number()) {
                                time_t rng = data[OBF("rng")].get<time_t>();

                                if (rng + 30 > time(0)) {
                                    std::string authString = OBF("CODM");
                                    authString += OBF("-");
                                    authString += key;
                                    authString += OBF("-");
                                    authString += Config.Init.uuid;
                                    authString += OBF("-");
                                    authString += OBF("Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E");

                                    std::string calculatedToken = Tools::CalcMD5(authString);

                                    validationSuccess = (XenoKeyData.authToken == calculatedToken);

                                    if (validationSuccess) {
                                        XenoKeyData.isLoggedIn = true;
                                        XenoKeyData.loginSuccess = true;
                                        XenoKeyData.isValidated = true;
                                        XenoKeyData.errorMessage = OBF("Login successful!");
                                        // LOGI("[XENO-KEY] Validasi key berhasil!");
                                        // LOGI("[XENO-KEY] Data tersimpan: isLoggedIn=%d, userKey=%s, expiredDate=%s",
                                        //      XenoKeyData.isLoggedIn,
                                        //      XenoKeyData.userKey.c_str(),
                                        //      XenoKeyData.expiredDate.c_str());

                                        if (Config.Init.IsReachedLobby) {
                                            activate_fake_status_for_xeno();
                                        }
                                    } else {
                                        XenoKeyData.errorMessage = OBF("Invalid token");
                                        // LOGE("[XENO-KEY] Token tidak valid - mismatch");
                                    }
                                } else {
                                    XenoKeyData.errorMessage = OBF("Token has expired");
                                    // LOGE("[XENO-KEY] Token telah kedaluwarsa");
                                }
                            } else {
                                XenoKeyData.errorMessage = OBF("Data 'rng' not found or invalid");
                                // LOGE("[XENO-KEY] Data 'rng' tidak ditemukan");
                            }
                        } else {
                            XenoKeyData.errorMessage = OBF("Token not found in response");
                            // LOGE("[XENO-KEY] Token tidak ditemukan dalam respons");
                        }
                    } else {
                        XenoKeyData.errorMessage = OBF("Data not found in response");
                        // LOGE("[XENO-KEY] Data tidak ditemukan dalam respons");
                    }
                } else if (response.contains(OBF("reason")) && response[OBF("reason")].is_string()) {
                    XenoKeyData.errorMessage = response[OBF("reason")].get<std::string>();
                    // LOGE("[XENO-KEY] Login gagal: %s", XenoKeyData.errorMessage.c_str());
                } else {
                    XenoKeyData.errorMessage = OBF("Login failed with unknown reason");
                    // LOGE("[XENO-KEY] Login gagal dengan alasan yang tidak diketahui");
                }
            } catch (json::exception& e) {
                XenoKeyData.errorMessage = OBF("Error processing response: ");
                XenoKeyData.errorMessage += e.what();
                // LOGE("[XENO-KEY] Error memproses respons: %s", e.what());
            }
        } else {
            XenoKeyData.errorMessage = curl_easy_strerror(res);
            // LOGE("[XENO-KEY] cURL error: %s", XenoKeyData.errorMessage.c_str());
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    XenoKeyData.isLoginAttempted = true;
    return validationSuccess;
}

static void DrawXenoKeyLoginMenu() {
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoResize |
                                    ImGuiWindowFlags_NoCollapse |
                                    ImGuiWindowFlags_NoScrollbar;

    ImVec2 display_size = ImGui::GetIO().DisplaySize;

    float window_width = display_size.x * 0.7f;
    float window_height = 250.0f;

    ImGui::SetNextWindowPos(ImVec2((display_size.x - window_width) * 0.5f, (display_size.y - window_height) * 0.5f), ImGuiCond_Once);
    ImGui::SetNextWindowSize(ImVec2(window_width, window_height), ImGuiCond_Once);

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.85f));
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));
    ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.0f, 0.0f, 0.9f));
    ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.3f, 0.0f, 0.3f, 1.0f));

    ImGui::Begin(Config.Display.Lable.c_str(), nullptr, window_flags);

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.3f, 0.8f, 1.0f));
    float original_font_size = ImGui::GetFontSize();
    ImGui::SetWindowFontScale(1.2f);
    DrawCenteredText(OBF("Input Your Key"));
    ImGui::SetWindowFontScale(1.0f);
    ImGui::PopStyleColor();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    static char keyInput[64] = {0};

    if (keyInput[0] == '\0' && !XenoKeyData.userKey.empty()) {
        strncpy(keyInput, XenoKeyData.userKey.c_str(), sizeof(keyInput) - 1);
        keyInput[sizeof(keyInput) - 1] = '\0';
        // LOGI("[XENO-KEY] Loaded saved key to input field: %s", keyInput);
    }

    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.05f, 0.05f, 0.05f, 0.9f));  // Background field gelap
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));        // Teks putih
    ImGui::PushItemWidth(-1);
    ImGui::InputText(OBF("##keyInput"), keyInput, sizeof(keyInput));
    ImGui::PopItemWidth();
    ImGui::PopStyleColor(2);

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    // Tombol Paste dan Save dengan layout horizontal
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.0f, 0.3f, 0.8f));        // Button ungu gelap
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.0f, 0.4f, 0.9f)); // Hover ungu
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.5f, 0.0f, 0.5f, 1.0f));  // Active ungu cerah
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));          // Teks putih

    // Buat tiga tombol berdampingan
    float buttonWidth = (ImGui::GetContentRegionAvail().x - ImGui::GetStyle().ItemSpacing.x * 2) / 3;

    // Tombol Paste Key
    if (ImGui::Button(OBF("Paste Key"), ImVec2(buttonWidth, 30.0f))) {
        try {
            // Gunakan fungsi getClipboard() dari imgui_stuff.h
            std::string clipboard = getClipboard();
            if (!clipboard.empty()) {
                // Batasi panjang clipboard yang disalin ke keyInput
                strncpy(keyInput, clipboard.c_str(), sizeof(keyInput) - 1);
                keyInput[sizeof(keyInput) - 1] = '\0';
            }
        } catch (std::exception& e) {
            // LOGE("[XENO-KEY] Error saat mengambil clipboard: %s", e.what());
        }
    }

    ImGui::SameLine();

    // Tombol Save Key
    if (ImGui::Button(OBF("Save Key"), ImVec2(buttonWidth * 0.65f, 30.0f))) {
        if (strlen(keyInput) > 0) {
            // Simpan key ke XenoKeyData dan file terpisah
            XenoKeyData.userKey = keyInput;

            // Simpan ke file terpisah
            if (SaveXenoKeyToFile(XenoKeyData.userKey)) {
                XenoKeyData.errorMessage = OBF("Key saved successfully!");
            } else {
                XenoKeyData.errorMessage = OBF("Failed to save key to file!");
            }

            XenoKeyData.isLoginAttempted = true;
            XenoKeyData.loginSuccess = true;
            // LOGI("[XENO-KEY] Key disimpan: %s", XenoKeyData.userKey.c_str());
        } else {
            XenoKeyData.errorMessage = OBF("Please enter a key to save");
            XenoKeyData.isLoginAttempted = true;
            XenoKeyData.loginSuccess = false;
        }
    }

    ImGui::SameLine();

    // Tombol Load Key (baru)
    if (ImGui::Button(OBF("Load Key"), ImVec2(buttonWidth * 0.65f, 30.0f))) {
        // Muat key dari file terpisah
        std::string loadedKey = LoadXenoKeyFromFile();

        if (!loadedKey.empty()) {
            // Salin key yang dimuat ke buffer input
            strncpy(keyInput, loadedKey.c_str(), sizeof(keyInput) - 1);
            keyInput[sizeof(keyInput) - 1] = '\0';

            // Update XenoKeyData
            XenoKeyData.userKey = loadedKey;

            XenoKeyData.errorMessage = OBF("Key loaded successfully!");
            XenoKeyData.isLoginAttempted = true;
            XenoKeyData.loginSuccess = true;
            // LOGI("[XENO-KEY] Key dimuat: %s", loadedKey.c_str());
        } else {
            XenoKeyData.errorMessage = OBF("No saved key found!");
            XenoKeyData.isLoginAttempted = true;
            XenoKeyData.loginSuccess = false;
        }
    }

    ImGui::SameLine();

    // Tombol Clear Key
    if (ImGui::Button(OBF("Clear Key"), ImVec2(buttonWidth * 0.65f, 30.0f))) {
        // Hapus key dari input
        memset(keyInput, 0, sizeof(keyInput));

        // Hapus key dari XenoKeyData
        XenoKeyData.userKey.clear();

        // Coba hapus file key
        try {
            std::remove(XENO_KEY_FILE);
            XenoKeyData.errorMessage = OBF("Key cleared successfully!");
            // LOGI("[XENO-KEY] File key berhasil dihapus");
        } catch (...) {
            XenoKeyData.errorMessage = OBF("Key cleared from memory!");
            // LOGI("[XENO-KEY] Gagal menghapus file key tetapi key dihapus dari memori");
        }

        XenoKeyData.isLoginAttempted = true;
        XenoKeyData.loginSuccess = true;
        XenoKeyData.isLoggedIn = false;
        // LOGI("[XENO-KEY] Key dihapus");
    }

    ImGui::Spacing();

    // Tombol login dengan style yang sama
    if (ImGui::Button(OBF("Login"), ImVec2(ImGui::GetContentRegionAvail().x, 30.0f))) {
        if (strlen(keyInput) > 0) {
            std::string key(keyInput);
            bool success = ValidateXenoKey(key);

            // Jika login berhasil, simpan key ke XenoKeyData tanpa SaveSettings
            if (success) {
                XenoKeyData.userKey = key;
                // LOGI("[XENO-KEY] Login berhasil, key disimpan ke memori");
            }
        } else {
            XenoKeyData.errorMessage = OBF("Please enter a valid key");
            XenoKeyData.isLoginAttempted = true;
        }
    }

    ImGui::PopStyleColor(4);

    ImGui::Spacing();
    ImGui::Spacing();

    // Tampilkan pesan error jika ada
    if (XenoKeyData.isLoginAttempted) {
        ImGui::PushStyleColor(ImGuiCol_Text, XenoKeyData.loginSuccess ?
                                             ImVec4(0.0f, 1.0f, 0.0f, 1.0f) :  // Hijau untuk sukses
                                             ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Merah untuk error

        ImGui::Spacing();
        DrawCenteredText(XenoKeyData.errorMessage.c_str());
        ImGui::PopStyleColor();
    }

    ImGui::End();
    ImGui::PopStyleColor(4);  // Pop warna untuk window
}

static void init_xeno_key_validation() {
    // LOGI("[XENO-KEY] Inisialisasi sistem validasi key...");
    XenoKeyData.isLoggedIn = false;
    XenoKeyData.isLoginAttempted = false;
    XenoKeyData.loginSuccess = false;
    XenoKeyData.errorMessage.clear();
    XenoKeyData.userKey.clear();
    xeno_key_validation_triggered = false;
    xeno_fake_status_activated = false;

    std::string savedKey = LoadXenoKeyFromFile();
    if (!savedKey.empty()) {
        XenoKeyData.userKey = savedKey;
        // LOGI("[XENO-KEY] Key berhasil dimuat dari file saat inisialisasi: %s", savedKey.c_str());
    } else {
        // LOGI("[XENO-KEY] Tidak ada key tersimpan ditemukan saat inisialisasi");
    }
}

static void trigger_xeno_key_validation() {
    if (!xeno_key_validation_triggered) {
        // LOGI("[XENO-KEY] Memicu validasi key XENO setelah deteksi lobby...");
        xeno_key_validation_triggered = true;
    }

    if (XenoKeyData.isLoggedIn && !xeno_fake_status_activated) {
        activate_fake_status_for_xeno();
    }
}

static void activate_fake_status_for_xeno() {
    if (!xeno_fake_status_activated && XenoKeyData.isLoggedIn) {
        // LOGI("[XENO-KEY] Validasi key berhasil - Mengaktifkan FakeStatus...");

        Config.Misc.FakeStatus = true;
        Config.Misc.FakeOfflineMode = true;
        Config.Misc.DisableReporting = true;
        Config.Misc.FakeReportID = true;
        Config.Misc.BlockAnalytics = true;

        srand(time(NULL));

        Config.MiscSize.FakeRecordID = rand() % 1000000 + 10000;

        // LOGI("[XENO-KEY] Fake Status diaktifkan dengan ID palsu: %u", Config.MiscSize.FakeRecordID);

        Config.Init.IsValidated = true;
        Config.Init.IsUserIDMode = false;
        Config.Init.IsXenoKeyMode = true;
        // LOGI("[XENO-KEY] Validation flags set: IsValidated=true, IsXenoKeyMode=true");

        HandleFakeStatus();

        xeno_fake_status_activated = true;
    }
}

#endif // ARCAMOD_XENOKEYVALIDATION_H