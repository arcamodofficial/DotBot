#include <ctime>
#include <chrono>
#include <string>
#include <curl/curl.h>
#include <android/log.h>
/*
 * Bydz ImGui Panel Helper
 * Private Usages only
 */

struct BYDZ_CONFIG_STRUCT {
    bool INIT = false;
    std::string SITE_URL;
    curl_slist *HEADERS = NULL;
    std::string UUID;
    std::string DEVICE;
    std::string GAME;
    std::string USER_ID;
    std::string TOKEN;
    time_t UTC_BASE;
    time_t LOCAL_BASE;
    std::string STATUS;
    int IS_VIP;
    bool VALIDATION_COMPLETED = false;
};

static BYDZ_CONFIG_STRUCT PANEL_DATA;

namespace BydzPanel {
    /*
     * Initiate Helper, Set Server SITE_URL
     */
    static void Init(const char *url) {
        std::string site_orig(url);
        PANEL_DATA.SITE_URL = site_orig;

        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("accept: application/json"));
        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("content-type: application/json"));

        PANEL_DATA.INIT = true;
    }

    /*
     * Used for check if it's has been inited correctly.
     */
    static bool IsInitialized() {
        return PANEL_DATA.INIT;
    }

    /*
     * Get User ID
     */
    static std::string GetUserID() {
        return PANEL_DATA.USER_ID;
    }

    /*
     * Get UUID
     */
    static std::string GetUUID() {
        return PANEL_DATA.UUID;
    }

    /*
     * Get DEVICE
     */
    static std::string GetDevice() {
        return PANEL_DATA.DEVICE;
    }

    /*
     * Get UUID
     */
    static std::string GetGame() {
        return PANEL_DATA.GAME;
    }

    /*
     * Get TOKEN
     */
    static std::string GetToken() {
        return PANEL_DATA.TOKEN;
    }

    namespace EXPIRED {
        /*
         * Get UTC EXPIRED Timestamp
         */
        static time_t UTC() {
            return PANEL_DATA.UTC_BASE;
        }

        /*
         * Get LOCAL EXPIRED Timestamp
         */
        static time_t Local() {
            return PANEL_DATA.LOCAL_BASE;
        }
    };

    namespace DATE {
        /*
         * Get String Date UTC
         */
        static std::string UTC() {
            const char* dayNames[] = { OBF("Sunday"), OBF("Monday"), OBF("Tuesday"), OBF("Wednesday"), OBF("Thursday"), OBF("Friday"), OBF("Saturday") };
            const char* monthNames[] = { OBF("January"), OBF("February"), OBF("March"), OBF("April"), OBF("May"), OBF("June"), OBF("July"), OBF("August"), OBF("September"), OBF("October"), OBF("November"), OBF("December") };

            std::string _ret_date;

            time_t exp_time = EXPIRED::UTC();

            if (exp_time < 0) {
                return _ret_date;
            }

            struct tm* timeInfo = gmtime(&exp_time);

            if (timeInfo != nullptr) {
                char formattedTime[100];
                std::strftime(formattedTime, sizeof(formattedTime), OBF("%H:%M %A, %d %B %Y"), timeInfo);

                return formattedTime;
            }

            return _ret_date;
        }

        /*
         * Get String Date LOCAL
         */
        static std::string Local() {
            std::string _ret_date;

            time_t exp_time = EXPIRED::Local();

            if (exp_time < 0) {
                return _ret_date;
            }

            struct tm* timeInfo = localtime(&exp_time);

            if (timeInfo != nullptr) {
                char formattedTime[100];
                std::strftime(formattedTime, sizeof(formattedTime), OBF("%H:%M %A, %d %B %Y"), timeInfo);

                return formattedTime;
            }

            return _ret_date;
        }
    };

    /*
     * Internal JSON Helper
     */
    namespace JSON {
        json TEMP_JSON;

        static json Create() {
            TEMP_JSON.clear();

            return TEMP_JSON;
        }

        static void Set(json new_json) {
            TEMP_JSON.clear();
            TEMP_JSON = new_json;
        }

        static std::string Dump() {
            return TEMP_JSON.dump();
        }
    };

    /*
     * Internal Time Handler
     */
    namespace TIME {
        static time_t StringToTime(std::string timestring) {
            std::istringstream iss(timestring);
            time_t timestamp;
            if (!(iss >> timestamp)) {
                throw std::runtime_error(OBF("Failed to convert timestamp string to time_t"));
            }

            return timestamp;
        }

        static long long GetMilliseconds() {
            auto retTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
            ).count();

            return retTime;
        }

        static std::string GetTimeZone() {
            std::time_t timenow = std::time(nullptr);
            std::tm* localTime = std::localtime(&timenow);
            return localTime->tm_zone;
        }

        static std::string GetUTCString() {
            std::time_t timenow = std::time(nullptr);
            std::string rettime;
            rettime += std::to_string(timenow);

            return rettime;
        }

        static std::string GetLocalString() {
            std::time_t timenow = std::time(nullptr);
            tm *local_tm = localtime(&timenow);
            time_t local_time = mktime(local_tm);
            std::string rettime;
            rettime += std::to_string(local_time);

            return rettime;
        }

        static time_t GetUTC() {
            // Jika validasi sudah dilakukan, gunakan waktu dari validasi pertama
            if (PANEL_DATA.VALIDATION_COMPLETED) {
                return PANEL_DATA.UTC_BASE - 86400; // Kurangi 1 hari untuk memastikan masih valid
            }
            
            // Jika belum, gunakan waktu saat ini
            std::time_t timenow = std::time(nullptr);
            return timenow;
        }

        static time_t GetLocal() {
            // Jika validasi sudah dilakukan, gunakan waktu dari validasi pertama
            if (PANEL_DATA.VALIDATION_COMPLETED) {
                return PANEL_DATA.LOCAL_BASE - 86400; // Kurangi 1 hari untuk memastikan masih valid
            }
            
            // Jika belum, gunakan waktu saat ini
            std::time_t timenow = std::time(nullptr);
            tm *local_tm = localtime(&timenow);
            time_t local_time = mktime(local_tm);
            return local_time;
        }
    };

    namespace STATUS {
        static std::string GetStatus() {
            return PANEL_DATA.STATUS;
        }

        static int GetNumber() {
            return PANEL_DATA.IS_VIP;
        }

        static bool IsVIP() {
            return ((PANEL_DATA.IS_VIP - 5) == 0);
        }

        static bool IsFree() {
            return ((PANEL_DATA.IS_VIP - 3) == 0);
        }
    };

    /*
     * Get SITE_URL as HTTP
     */
    static std::string GetHTTP() {
        if (!IsInitialized()) exit(-1);

        std::string tmp;
        tmp += OBF("http://");
        tmp += PANEL_DATA.SITE_URL;
        return tmp;
    }

    /*
     * Get SITE_URL as HTTPS
     */
    static std::string GetHTTPS() {
        if (!IsInitialized()) exit(-1);

        std::string tmp;
        tmp += OBF("https://");
        tmp += PANEL_DATA.SITE_URL;
        return tmp;
    }

    /*
     * Rewriting cookie
     */
    static void RewriteCookie(std::string new_cookie, bool clear = true) {
        if (clear) {
            PANEL_DATA.HEADERS = NULL;
            PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("Accept: application/json"));
            PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("Content-type: application/json"));

            std::string set_referer;
            set_referer += OBF("Referer: ");
            set_referer += GetHTTPS();

            PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, set_referer.data());

            if (!PANEL_DATA.TOKEN.empty()) {
                std::string set_auth;
                set_auth += OBF("Authorization: Bearer ");
                set_auth += PANEL_DATA.TOKEN;
                PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, set_auth.data());
            }
        }


        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, new_cookie.data());
    }

    /*
     * Used to catching Response Content
     */
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t totalSize = size * nmemb;
        output->append(static_cast<char*>(contents), totalSize);
        return totalSize;
    }

    /*
     * Used to catching headers data
     * It's used to handle cookies
     */
    size_t HandleHeaders(void* contents, size_t size, size_t nmemb, std::string* output) {
        size_t total_size = size * nmemb;
        output->append(static_cast<char*>(contents), total_size);
        return total_size;
    }

    /*
     * Main GET Function.
     */
    static json Get(const char *main_url, const char *path_url) {
        //if (!IsInitialized()) exit(-1);

        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("accept: application/json"));
        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("content-type: application/json"));

        if (!PANEL_DATA.TOKEN.empty()) {
            std::string set_auth;
            set_auth += OBF("Authorization: Bearer ");
            set_auth += PANEL_DATA.TOKEN;
            PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, set_auth.data());
        }

        CURL* curl;
        CURLcode res;
        std::string responseData;
        std::string tmp_headers;
        curl_global_init(CURL_GLOBAL_SSL);

        curl = curl_easy_init();

        if (curl) {
            std::string url_serv;
            url_serv += main_url;
            url_serv += path_url;

            //curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, OBF("1.1.1.1,1.0.0.1,8.8.8.8,8.8.4.4"));
            curl_easy_setopt(curl, CURLOPT_URL, url_serv.data());
            curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, HandleHeaders);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &tmp_headers);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, PANEL_DATA.HEADERS);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

            res = curl_easy_perform(curl);

            //curl_slist_free_all(PANEL_DATA.HEADERS);

            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        PANEL_DATA.HEADERS = NULL;

        if (res != CURLE_OK) {
            json returnJSON;
            returnJSON[(OBF("code"))]  = res;
            returnJSON[(OBF("error"))] = curl_easy_strerror(res);

            return returnJSON;
        } else {
            std::string convertedCookies;
            size_t cookieStart, cookieEnd;
            cookieStart = tmp_headers.find(OBF("set-cookie: "));
            while (cookieStart != std::string::npos) {
                cookieEnd = tmp_headers.find("\r\n", cookieStart);
                if (cookieEnd != std::string::npos) {
                    std::string cookie = tmp_headers.substr(cookieStart + 12, cookieEnd - (cookieStart + 12));
                    convertedCookies += cookie;
                    convertedCookies += OBF(";");
                }
                cookieStart = tmp_headers.find(OBF("set-cookie: "), cookieEnd);
            }

            cookieStart = tmp_headers.find(OBF("Set-Cookie: "));
            while (cookieStart != std::string::npos) {
                cookieEnd = tmp_headers.find("\r\n", cookieStart);
                if (cookieEnd != std::string::npos) {
                    std::string cookie = tmp_headers.substr(cookieStart + 12, cookieEnd - (cookieStart + 12));
                    convertedCookies += cookie;
                    convertedCookies =+ OBF(";");
                }
                cookieStart = tmp_headers.find(OBF("Set-cookie: "), cookieEnd);
            }

            if (!convertedCookies.empty()) {
                std::string new_cookie;
                new_cookie += OBF("cookie: ");
                new_cookie += convertedCookies;
                RewriteCookie(new_cookie);
            }

            json returnJSON;

            try {
                returnJSON[(OBF("response"))]  = json::parse(responseData);
            } catch (json::exception &e) {
                json falseJson;
                return falseJson;
            }

            return returnJSON;
        }

        return NULL;
    }

    /*
     * Main POST Function.
     */
    static json Post(json POST_DATA, const char *main_url, const char *path_url) {
        //if (!IsInitialized()) exit(-1);

        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("accept: application/json"));
        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("content-type: application/json"));

        if (!PANEL_DATA.TOKEN.empty()) {
            std::string set_auth;
            set_auth += OBF("Authorization: Bearer ");
            set_auth += PANEL_DATA.TOKEN;
            PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, set_auth.data());
        }

        CURL* curl;
        CURLcode res;
        std::string responseData;
        std::string tmp_headers;
        curl_global_init(CURL_GLOBAL_SSL);

        curl = curl_easy_init();

        if (curl) {
            std::string url_serv;
            url_serv += OBF("https://");
            url_serv += main_url;

            url_serv += path_url;

            //curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, OBF("8.8.8.8,8.8.4.4"));
            curl_easy_setopt(curl, CURLOPT_URL, url_serv.data());
            curl_easy_setopt(curl, CURLOPT_POST, 1);

            std::string post_str = POST_DATA.dump();

            const char *jsonPayload = post_str.c_str();
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, PANEL_DATA.HEADERS);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

            res = curl_easy_perform(curl);

            //curl_slist_free_all(PANEL_DATA.HEADERS);

            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        PANEL_DATA.HEADERS = NULL;

        if (res != CURLE_OK) {
            json returnJSON;
            returnJSON[(OBF("code"))]  = res;
            returnJSON[(OBF("error"))] = curl_easy_strerror(res);

            return returnJSON;
        } else {
            json returnJSON;

            try {
                returnJSON[(OBF("response"))]  = json::parse(responseData);
            } catch (json::exception &e) {
                json falseJson;
                return falseJson;
            }

            return returnJSON;
        }
    }

    /*
     * Main POST Function.
     */
    static json PostLoginEnjoyers(json POST_DATA) {
        //if (!IsInitialized()) exit(-1);

        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("accept: application/json"));
        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, OBF("content-type: application/json"));

        CURL* curl;
        CURLcode res;
        std::string responseData;
        std::string tmp_headers;
        curl_global_init(CURL_GLOBAL_SSL);

        curl = curl_easy_init();

        if (curl) {
            std::string url_serv;
            url_serv += OBF("https://apimuslim-vvip-mods.xyz/api/v5/codm");
            //curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, OBF("8.8.8.8,8.8.4.4"));
            curl_easy_setopt(curl, CURLOPT_URL, url_serv.data());
            curl_easy_setopt(curl, CURLOPT_POST, 1);

            std::string post_str = POST_DATA.dump();

            const char *jsonPayload = post_str.c_str();
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, PANEL_DATA.HEADERS);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &responseData);

            res = curl_easy_perform(curl);

            //curl_slist_free_all(PANEL_DATA.HEADERS);

            curl_easy_cleanup(curl);
        }

        curl_global_cleanup();

        PANEL_DATA.HEADERS = NULL;

        if (res != CURLE_OK) {
            json returnJSON;
            returnJSON[(OBF("code"))]  = res;
            returnJSON[(OBF("error"))] = curl_easy_strerror(res);

            return returnJSON;
        } else {
            json returnJSON;

            try {
                returnJSON[(OBF("response"))]  = json::parse(responseData);
            } catch (json::exception &e) {
                json falseJson;
                return falseJson;
            }

            return returnJSON;
        }
    }

    static void RenewCookies(const char *main_url) {
        json _get_sanctum_cookies = Get(main_url, OBF("/api/sanctum/csrf-cookie"));
    }

    static bool CheckConnection(const char *main_url) {
        //RenewCookies();

        json _datapost;

        _datapost[(OBF("time"))] = TIME::GetMilliseconds();

        json _response = Post(_datapost, main_url, OBF("/api/native/check/connection"));

        if (_response.contains(OBF("response"))) {
            json _web_resp = _response[(OBF("response"))].get<json>();

            if (_web_resp.contains(OBF("code"))) {
                int _code = _web_resp[(OBF("code"))].get<int>();

                if (_code == 0) {
                    return true;
                }
            }
        }

        return false;
    }


    /*
     * Fetch Data Login
     */
    static json GetUserInfo(const char* main_url, json device_data) {
        // Cek apakah validasi sudah dilakukan sebelumnya
        if (PANEL_DATA.VALIDATION_COMPLETED) {
            // Log menggunakan __android_log_print
            __android_log_print(ANDROID_LOG_INFO, "BydzPanel", "Menggunakan cache data validasi sebelumnya");
            json cached_result;
            cached_result[(OBF("code"))] = 0;
            cached_result[(OBF("id"))] = PANEL_DATA.USER_ID;
            cached_result[(OBF("exp"))] = std::to_string(PANEL_DATA.UTC_BASE);
            cached_result[(OBF("token"))] = PANEL_DATA.TOKEN;
            cached_result[(OBF("status"))] = PANEL_DATA.STATUS;
            return cached_result;
        }
        
        //RenewCookies();

        json _return_info;
        _return_info[(OBF("code"))] = -1;
        _return_info[(OBF("message"))] = OBF("Cannot reach server, please check your connection");

        if (
                !device_data.contains(OBF("uuid")) ||
                !device_data.contains(OBF("device")) ||
                !device_data.contains(OBF("game"))
                ) {
            _return_info[(OBF("message"))] = OBF("NULL object reference");

            return _return_info;
        }
        std::string _d_uuid, _d_device, _d_game;

        try {
            _d_uuid       = device_data[(OBF("uuid"))].get<std::string>();
            _d_device     = device_data[(OBF("device"))].get<std::string>();
            _d_game       = device_data[(OBF("game"))].get<std::string>();
        } catch (json::exception e) {
            _return_info[(OBF("message"))] = OBF("Error when gathering data");

            return _return_info;
        }

        PANEL_DATA.GAME = _d_game;

        json _post_user_info;
        _post_user_info[(OBF("uuid"))]     = AES::Encrypt(_d_uuid, AES::Mode.MAIN);
        _post_user_info[(OBF("device"))]   = AES::Encrypt(_d_device, AES::Mode.MAIN);
        _post_user_info[(OBF("game"))]     = AES::Encrypt(_d_game, AES::Mode.MAIN);
        //_post_user_info[(OBF("timezone"))] = AES::Encrypt(TIME::GetTimeZone(), AES::Mode.MAIN);
        //_post_user_info[(OBF("time_utc"))] = AES::Encrypt(TIME::GetUTCString(), AES::Mode.MAIN);
        //_post_user_info[(OBF("time_loc"))] = AES::Encrypt(TIME::GetLocalString(), AES::Mode.MAIN);

        std::string _user_info_enc_1 = _post_user_info.dump();
        //printf("ssss : %s\n", time_string.data());
        json _user_info_data_1;
        _user_info_data_1[(OBF("data"))] = AES::Encrypt(_user_info_enc_1, AES::Mode.SECOND);

        std::string _user_info_enc_final = _user_info_data_1.dump();
        //printf("shit : %s\n", _user_info_enc_final.data());
        json _user_info_data_final;
        _user_info_data_final[(OBF("data"))] = AES::Encrypt(_user_info_enc_final, AES::Mode.MAIN);

        json _response = Post(_user_info_data_final, main_url, OBF("/api/v2/public/user/login"));

        if (_response.contains(OBF("response"))) {
            json _web_resp = _response[(OBF("response"))];
            std::string err_catch;
            err_catch += OBF("Message : ");
            err_catch += _web_resp.dump().data();
            //printf("shit : %s", _web_resp.dump().data());
            //__android_log_print(4,  "bydzc", "response : %s", err_catch.data());

            if (_web_resp.contains(OBF("code"))) {
                int _resp_code = _web_resp[(OBF("code"))].get<int>();

                if (_resp_code == 0) {
                    std::string _resp_data = _web_resp[(OBF("data"))].get<std::string>();

                    std::string _resp_data_dec_1 = AES::Decrypt(_resp_data, AES::Mode.MAIN);
                    std::string _resp_data_dec_2 = AES::Decrypt(_resp_data_dec_1, AES::Mode.SECOND);
                    json _user_data;

                    try {
                        _user_data = json::parse(_resp_data_dec_2);

                    } catch(json::exception &e) {
                        _return_info[(OBF("message"))] = OBF("Error when accessing website response");

                        return _return_info;
                    }
/*
                    if (_user_data.contains("id")) {
                        try {
                            std::string _decode_id = _user_data[(OBF("id"))].get<std::string>();

                            std::string _decoded_id = AES::Decrypt(_decode_id, AES::Mode.MAIN);

                            _user_data[(OBF("id"))] = _decoded_id;
                        } catch (json::exception &e) {
                            _return_info[(OBF("message"))] = OBF("Error when decoding ID from panel");

                            return _return_info;
                        }
                    } else {
                        _return_info[(OBF("message"))] = OBF("User ID from Website is invalid");

                        return _return_info;
                    }

                    if (_user_data.contains("exp")) {
                        try {
                            std::string _decode_exp = _user_data[(OBF("exp"))].get<std::string>();

                            std::string _decoded_exp = AES::Decrypt(_decode_exp, AES::Mode.MAIN);

                            _user_data[(OBF("exp"))] = _decoded_exp;
                        } catch (json::exception &e) {
                            _return_info[(OBF("message"))] = OBF("Error when decoding second data from panel");

                            return _return_info;
                        }
                    } else {
                        _return_info[(OBF("message"))] = OBF("User EXP from Website is invalid");

                        return _return_info;
                    }

                    if (_user_data.contains("token")) {
                        try {
                            std::string _decode_token = _user_data[(OBF("token"))].get<std::string>();

                            std::string _decoded_token = AES::Decrypt(_decode_token, AES::Mode.MAIN);

                            _user_data[(OBF("token"))] = _decoded_token;
                        } catch (json::exception &e) {
                            _return_info[(OBF("message"))] = OBF("Error when decoding third data from panel");

                            return _return_info;
                        }
                    } else {
                        _return_info[(OBF("message"))] = OBF("User Token from Website is invalid");

                        return _return_info;
                    }

                    if (_user_data.contains("status")) {
                        try {
                            std::string _decode_status = _user_data[(OBF("status"))].get<std::string>();

                            std::string _decoded_status = AES::Decrypt(_decode_status, AES::Mode.MAIN);

                            _user_data[(OBF("status"))] = _decoded_status;
                        } catch (json::exception &e) {
                            _return_info[(OBF("message"))] = OBF("Error when decoding third data from panel");

                            return _return_info;
                        }
                    } else {
                        _return_info[(OBF("message"))] = OBF("User Token from Website is invalid");

                        return _return_info;
                    }

                    if (_user_data.contains("time_utc")) {
                        try {
                            std::string _decode_time_utc = _user_data[(OBF("time_utc"))].get<std::string>();

                            std::string _decoded_time_utc = AES::Decrypt(_decode_time_utc, AES::Mode.MAIN);

                            _user_data[(OBF("time_utc"))] = _decoded_time_utc;
                        } catch (json::exception &e) {
                            _return_info[(OBF("message"))] = OBF("Error when decoding third data from panel");

                            return _return_info;
                        }
                    } else {
                        _return_info[(OBF("message"))] = OBF("User Token from Website is invalid");

                        return _return_info;
                    }
                    */
/*
                    if (_user_data.contains("time_loc")) {
                        try {
                            std::string _decode_time_loc = _user_data[(OBF("time_loc"))].get<std::string>();

                            std::string _decoded_time_loc = AES::Decrypt(_decode_time_loc, AES::Mode.MAIN);

                            _user_data[(OBF("time_loc"))] = _decoded_time_loc;
                        } catch (json::exception &e) {
                            _return_info[(OBF("message"))] = OBF("Error when decoding third data from panel");

                            return _return_info;
                        }
                    } else {
                        _return_info[(OBF("message"))] = OBF("User Token from Website is invalid");

                        return _return_info;
                    }
*/
                    time_t resp_utc = std::stoll(_user_data[(OBF("time_utc"))].get<std::string>());
                    //__android_log_print(4,  "BydzGUI", "time_utc : %s", _user_data.dump().data());
                    //time_t resp_utc = _user_data[(OBF("time_utc"))].get<time_t>();
                    //time_t resp_loc = std::stoll(_user_data[(OBF("time_loc"))].get<std::string>());
/*
                    if (resp_utc > max_utc //|| resp_loc > max_loc
                    ) {
                        _return_info[(OBF("message"))] = OBF("Unable to retrieve server data");

                        return _return_info;
                    }

                    //__android_log_print(4,  "bydzc", "userdata : %s", _user_data.dump().data());
*/
                    PANEL_DATA.USER_ID  = _user_data[(OBF("id"))].get<std::string>();
                    PANEL_DATA.TOKEN    = _user_data[(OBF("token"))].get<std::string>();
                    //__android_log_print(4,  "BydzGUI", "shittimee");
                    //__android_log_print(4,  "bydzc", "integritystart");
                    PANEL_DATA.UTC_BASE = std::stoll(_user_data[(OBF("exp"))].get<std::string>());
                    //PANEL_DATA.UTC_BASE = _user_data[(OBF("exp"))].get<time_t>();
                    //__android_log_print(4,  "BydzGUI", "shittime");
                    //__android_log_print(4,  "bydzc", "integritydone");
                    PANEL_DATA.STATUS = _user_data[(OBF("status"))].get<std::string>();

                    if (strstr(PANEL_DATA.STATUS.data(), OBF("VIP"))) {
                        PANEL_DATA.IS_VIP = 5;
                    } else {
                        PANEL_DATA.IS_VIP = 3;
                    }

                    struct tm* utc_to_local = std::localtime(&PANEL_DATA.UTC_BASE);

                    if (utc_to_local != nullptr) {
                        PANEL_DATA.LOCAL_BASE = std::mktime(utc_to_local);
                        //free(&utc_to_local);
                        //__android_log_print(4,  "bydzc", "mktime");
                    } else {
                        _return_info[(OBF("message"))] = OBF("Time Library Conversion error");

                        return _return_info;
                    }

//PANEL_DATA.LOCAL_BASE = 200000000;
                    _user_data[(OBF("code"))] = 0;
                    //__android_log_print(4,  "bydzc", "return");

                    // Tandai bahwa validasi sudah selesai
                    PANEL_DATA.VALIDATION_COMPLETED = true;
                    __android_log_print(ANDROID_LOG_INFO, "BydzPanel", "Validasi panel selesai - tidak akan melakukan validasi lagi");

                    return _user_data;
                } else {
                    _return_info[(OBF("code"))] = _resp_code;

                    std::string _err_msg;

                    try {
                        _err_msg = _web_resp[(OBF("message"))].get<std::string>();
                    } catch (json::exception e) {
                        _return_info[(OBF("message"))] = OBF("Cannot retrieving message from server.");

                        return _return_info;
                    }

                    _return_info[(OBF("message"))] = _err_msg;
                }
            } else {
                if (_web_resp.contains(OBF("message"))) {
                    std::string _err_msg;

                    try {
                        _err_msg = _web_resp[(OBF("message"))].get<std::string>();
                    } catch (json::exception e) {
                        _return_info[(OBF("message"))] = OBF("Cannot retrieving message from server.");

                        return _return_info;
                    }

                    _return_info[(OBF("message"))] = _err_msg;
                } else {
                    _return_info[(OBF("message"))] = err_catch;
                }
            }
        }

        return _return_info;
    }

    /*
     * Validate Current User Info
     */
    static json ValidateUser(const char *main_url) {
        // Jika validasi sudah dilakukan, kembalikan data yang disimpan sebelumnya
        if (PANEL_DATA.VALIDATION_COMPLETED) {
            __android_log_print(ANDROID_LOG_INFO, "BydzPanel", "Menggunakan cache data validasi sebelumnya");
            json cached_result;
            cached_result[(OBF("code"))] = 0;
            cached_result[(OBF("id"))] = PANEL_DATA.USER_ID;
            cached_result[(OBF("exp_utc"))] = std::to_string(PANEL_DATA.UTC_BASE);
            cached_result[(OBF("token"))] = PANEL_DATA.TOKEN;
            return cached_result;
        }
        
        //RenewCookies();

        json _ret_data;
        _ret_data[(OBF("code"))] = -1;
        _ret_data[(OBF("message"))] = OBF("NULL error reference - REVALIDATE");

        if (PANEL_DATA.USER_ID.empty()) {
            _ret_data[(OBF("message"))] = OBF("User is unauthenticated");

            return _ret_data;
        }

        json _current_data;
        _current_data[(OBF("token"))]     = GetToken();
        _current_data[(OBF("exp_local"))] = EXPIRED::Local();
        _current_data[(OBF("exp_utc"))]   = EXPIRED::UTC();
        //_current_data[(OBF("timezone"))]  = TIME::GetTimeZone();
        _current_data[(OBF("time_utc"))] = AES::Encrypt(TIME::GetUTCString(), AES::Mode.MAIN);
        _current_data[(OBF("time_loc"))] = AES::Encrypt(TIME::GetLocalString(), AES::Mode.MAIN);

        std::string _c_token, _c_local, _c_utc, _c_timezone;

        try {
            _c_token    = AES::Encrypt(_current_data[(OBF("token"))].get<std::string>(), AES::Mode.MAIN);
            _c_local    = AES::Encrypt(std::to_string(_current_data[(OBF("exp_local"))].get<time_t>()), AES::Mode.MAIN);
            _c_utc      = AES::Encrypt(std::to_string(_current_data[(OBF("exp_utc"))].get<time_t>()), AES::Mode.MAIN);
            // _c_timezone = AES::Encrypt(_current_data[(OBF("timezone"))].get<std::string>(), AES::Mode.MAIN);
        } catch (json::exception e) {
            _ret_data[(OBF("message"))] = OBF("Error when gathering data");

            return _ret_data;
        }

        json _enc_current_data;
        _enc_current_data[(OBF("token"))]     = _c_token;
        _enc_current_data[(OBF("exp_local"))] = _c_local;
        _enc_current_data[(OBF("exp_utc"))]   = _c_utc;
        //_enc_current_data[(OBF("timezone"))]  = _c_timezone;

        std::string _curr_data_encode = AES::Encrypt(_enc_current_data.dump(), AES::Mode.SECOND);
        std::string _curr_data_encode_final = AES::Encrypt(_curr_data_encode, AES::Mode.MAIN);

        json _current_final_data;
        _current_final_data[(OBF("data"))] = _curr_data_encode_final;

        json _do_get_info = Post(_current_final_data, main_url, OBF("/api/v2/auth/user/info"));

        if (_do_get_info.contains(OBF("response"))) {
            json _responsed = _do_get_info[(OBF("response"))];
            std::string err_catch;
            err_catch += OBF("Web Response : ");
            err_catch += _responsed.dump().data();

            if (_responsed.contains(OBF("code"))) {
                int _resp_code = _responsed[(OBF("code"))].get<int>();

                if (_resp_code == 0) {
                    std::string _encoded_resp = _responsed[(OBF("data"))].get<std::string>();

                    std::string _encoded_resp_1 = AES::Decrypt(_encoded_resp, AES::Mode.MAIN);
                    std::string _encoded_resp_2 = AES::Decrypt(_encoded_resp_1, AES::Mode.SECOND);

                    json _resp_data;

                    try {
                        _resp_data = json::parse(_encoded_resp_2);
                    } catch (json::exception &e) {
                        _ret_data[(OBF("message"))] = OBF("Unable to decrypt data - REVALIDATE");

                        return _ret_data;
                    }

                    if (_resp_data.contains("id")) {
                        std::string _decode_id = _resp_data[(OBF("id"))].get<std::string>();

                        std::string _decoded_id = AES::Decrypt(_decode_id, AES::Mode.MAIN);

                        _resp_data[(OBF("id"))] = _decoded_id;
                    } else {
                        _ret_data[(OBF("message"))] = OBF("User ID from Website is invalid - REVALIDATE");

                        return _ret_data;
                    }

                    if (_resp_data.contains("exp_local")) {
                        std::string _decode_exp_local = _resp_data[(OBF("exp_local"))].get<std::string>();

                        std::string _decoded_exp_local = AES::Decrypt(_decode_exp_local, AES::Mode.MAIN);

                        _resp_data[(OBF("exp_local"))] = _decoded_exp_local;
                    } else {
                        _ret_data[(OBF("message"))] = OBF("User Date from Website is invalid - REVALIDATE");

                        return _ret_data;
                    }

                    if (_resp_data.contains("exp_utc")) {
                        std::string _decode_exp_utc = _resp_data[(OBF("exp_utc"))].get<std::string>();

                        std::string _decoded_exp_utc = AES::Decrypt(_decode_exp_utc, AES::Mode.MAIN);

                        _resp_data[(OBF("exp_utc"))] = _decoded_exp_utc;
                    } else {
                        _ret_data[(OBF("message"))] = OBF("User Date from Website is invalid - REVALIDATE");

                        return _ret_data;
                    }

                    if (_resp_data.contains("token")) {
                        std::string _decode_token = _resp_data[(OBF("token"))].get<std::string>();

                        std::string _decoded_token = AES::Decrypt(_decode_token, AES::Mode.MAIN);

                        _resp_data[(OBF("token"))] = _decoded_token;
                    } else {
                        _ret_data[(OBF("message"))] = OBF("User Date from Website is invalid - REVALIDATE");

                        return _ret_data;
                    }

                    // Tandai bahwa validasi sudah selesai
                    PANEL_DATA.VALIDATION_COMPLETED = true;
                    __android_log_print(ANDROID_LOG_INFO, "BydzPanel", "Validasi panel selesai - tidak akan melakukan validasi lagi");

                    return _resp_data;
                } else {
                    _ret_data[(OBF("code"))] = _resp_code;

                    if (_responsed.contains(OBF("message"))) {
                        _ret_data[(OBF("message"))] = _responsed[(OBF("message"))].get<std::string>();
                    }
                }
            } else {
                if (_responsed.contains(OBF("message"))) {
                    std::string _err_msg;

                    try {
                        _err_msg = _responsed[(OBF("message"))].get<std::string>();
                    } catch (json::exception e) {
                        _ret_data[(OBF("message"))] = OBF("Cannot retrieving message from server.");

                        return _ret_data;
                    }

                    _ret_data[(OBF("message"))] = _err_msg;
                } else {
                    _ret_data[(OBF("message"))] = err_catch;
                }
            }
        }

        return _ret_data;
    }
};