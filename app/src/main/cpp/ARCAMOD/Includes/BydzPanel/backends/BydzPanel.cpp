#include "BydzPanel.h"

void BydzPanel::Init(const char *url) {
    std::string site_orig(url);
    PANEL_DATA.SITE_URL = site_orig;
    
    PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, oxorany("accept: application/json"));
    PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, oxorany("content-type: application/json"));
    
    PANEL_DATA.INIT = true;
}

bool BydzPanel::IsInitialized() {
    return PANEL_DATA.INIT;
}

std::string BydzPanel::GetUserID() {
    return PANEL_DATA.USER_ID;
}

std::string BydzPanel::GetUUID() {
    return PANEL_DATA.UUID;
}

std::string BydzPanel::GetDevice() {
    return PANEL_DATA.DEVICE;
}

std::string BydzPanel::GetGame() {
    return PANEL_DATA.GAME;
}

std::string BydzPanel::GetToken() {
    return PANEL_DATA.TOKEN;
}

time_t BydzPanel::EXPIRED::UTC() {
    return PANEL_DATA.UTC_BASE;
}

time_t BydzPanel::EXPIRED::Local() {
    return PANEL_DATA.LOCAL_BASE;
}

std::string BydzPanel::DATE::UTC() {
    const char* dayNames[] = { oxorany("Sunday"), oxorany("Monday"), oxorany("Tuesday"), oxorany("Wednesday"), oxorany("Thursday"), oxorany("Friday"), oxorany("Saturday") };
    const char* monthNames[] = { oxorany("January"), oxorany("February"), oxorany("March"), oxorany("April"), oxorany("May"), oxorany("June"), oxorany("July"), oxorany("August"), oxorany("September"), oxorany("October"), oxorany("November"), oxorany("December") };

    std::string _ret_date;

    time_t exp_time = EXPIRED::UTC();

    if (exp_time < 0) {
        return _ret_date;
    }

    struct tm* timeInfo = gmtime(&exp_time);

    if (timeInfo != nullptr) {
        char formattedTime[100];
        std::strftime(formattedTime, sizeof(formattedTime), "%H:%M %A, %d %B %Y", timeInfo);

        return formattedTime;
    }

    return _ret_date;
}

std::string BydzPanel::DATE::Local() {
    std::string _ret_date;

    time_t exp_time = EXPIRED::Local();

    if (exp_time < 0) {
        return _ret_date;
    }

    struct tm* timeInfo = localtime(&exp_time);

    if (timeInfo != nullptr) {
        char formattedTime[100];
        std::strftime(formattedTime, sizeof(formattedTime), "%H:%M %A, %d %B %Y", timeInfo);

        return formattedTime;
    }

    return _ret_date;
}

json BydzPanel::JSON::Create() {
    TEMP_JSON.clear();

    return TEMP_JSON;
}

void BydzPanel::JSON::Set(json new_json) {
    TEMP_JSON.clear();
    TEMP_JSON = new_json;
}

std::string BydzPanel::JSON::Dump() {
    return TEMP_JSON.dump();
}

long long BydzPanel::TIME::GetMilliseconds() {
    auto retTime = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();

    return retTime;
}

std::string BydzPanel::TIME::GetTimeZone() {
    std::time_t timenow = std::time(nullptr);
    std::tm* localTime = std::localtime(&timenow);
    return localTime->tm_zone;
}

std::string BydzPanel::TIME::GetUTCString() {
    std::time_t timenow = std::time(nullptr);
    std::string rettime;
    rettime += std::to_string(timenow);

    return rettime;
}

std::string BydzPanel::TIME::GetLocalString() {
    std::time_t timenow = std::time(nullptr);
    tm *local_tm = localtime(&timenow);
    time_t local_time = mktime(local_tm);
    std::string rettime;
    rettime += std::to_string(local_time);

    return rettime;
}

time_t BydzPanel::TIME::GetUTC() {
    std::time_t timenow = std::time(nullptr);
    return timenow;
}

time_t BydzPanel::TIME::GetLocal() {
    std::time_t timenow = std::time(nullptr);
    tm *local_tm = localtime(&timenow);
    time_t local_time = mktime(local_tm);
    return local_time;
}

std::string BydzPanel::STATUS::GetStatus() {
    return PANEL_DATA.STATUS;
}

int BydzPanel::STATUS::GetNumber() {
    return PANEL_DATA.IS_VIP;
}

bool BydzPanel::STATUS::IsVIP() {
    return ((PANEL_DATA.IS_VIP - 5) == 0);
}

bool BydzPanel::STATUS::IsFree() {
    return ((PANEL_DATA.IS_VIP - 3) == 0);
}

std::string BydzPanel::GetHTTP() {
    if (!IsInitialized()) exit(-1);

    std::string tmp;
    tmp += oxorany("http://");
    tmp += PANEL_DATA.SITE_URL;
    return tmp;
}

std::string BydzPanel::GetHTTPS() {
    if (!IsInitialized()) exit(-1);

    std::string tmp;
    tmp += oxorany("https://");
    tmp += PANEL_DATA.SITE_URL;
    return tmp;
}

void BydzPanel::RewriteCookie(std::string new_cookie, bool clear) {
    if (clear) {
        PANEL_DATA.HEADERS = NULL;
        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, oxorany("Accept: application/json"));
        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, oxorany("Content-type: application/json"));

        std::string set_referer;
        set_referer += oxorany("Referer: ");
        set_referer += GetHTTPS();

        PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, set_referer.data());

        if (!PANEL_DATA.TOKEN.empty()) {
            std::string set_auth;
            set_auth += oxorany("Authorization: Bearer ");
            set_auth += PANEL_DATA.TOKEN;
            PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, set_auth.data());
        }
    }


    PANEL_DATA.HEADERS = curl_slist_append(PANEL_DATA.HEADERS, new_cookie.data());
}

size_t BydzPanel::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

size_t BydzPanel::HandleHeaders(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t total_size = size * nmemb;
    output->append(static_cast<char*>(contents), total_size);
    return total_size;
}

json BydzPanel::Get(const char *path_url) {
    if (!IsInitialized()) exit(-1);

    CURL* curl;
    CURLcode res;
    std::string responseData;
    std::string tmp_headers;
    curl_global_init(CURL_GLOBAL_SSL);

    curl = curl_easy_init();

    if (curl) {
        std::string url_serv(GetHTTPS());
        url_serv += path_url;

        curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, oxxo("8.8.8.8,8.8.4.4"));
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

    if (res != CURLE_OK) {
        json returnJSON;
        returnJSON[(oxorany("code"))]  = res;
        returnJSON[(oxorany("error"))] = curl_easy_strerror(res);

        return returnJSON;
    } else {
        std::string convertedCookies;
        size_t cookieStart, cookieEnd;
        cookieStart = tmp_headers.find(oxorany("set-cookie: "));
        while (cookieStart != std::string::npos) {
            cookieEnd = tmp_headers.find("\r\n", cookieStart);
            if (cookieEnd != std::string::npos) {
                std::string cookie = tmp_headers.substr(cookieStart + 12, cookieEnd - (cookieStart + 12));
                convertedCookies += cookie + oxorany(";");
            }
            cookieStart = tmp_headers.find(oxorany("set-cookie: "), cookieEnd);
        }

        cookieStart = tmp_headers.find(oxorany("Set-Cookie: "));
        while (cookieStart != std::string::npos) {
            cookieEnd = tmp_headers.find("\r\n", cookieStart);
            if (cookieEnd != std::string::npos) {
                std::string cookie = tmp_headers.substr(cookieStart + 12, cookieEnd - (cookieStart + 12));
                convertedCookies += cookie + oxorany(";");
            }
            cookieStart = tmp_headers.find(oxorany("Set-cookie: "), cookieEnd);
        }

        if (!convertedCookies.empty()) {
            std::string new_cookie;
            new_cookie += oxorany("cookie: ");
            new_cookie += convertedCookies;
            RewriteCookie(new_cookie);
        }

        json returnJSON;

        try {
            returnJSON[(oxorany("response"))]  = json::parse(responseData);
        } catch (json::exception &e) {
            json falseJson;
            return falseJson;
        }

        return returnJSON;
    }

    return NULL;
}

json BydzPanel::Post(json POST_DATA, const char *path_url) {
    if (!IsInitialized()) exit(-1);

    CURL* curl;
    CURLcode res;
    std::string responseData;
    std::string tmp_headers;
    curl_global_init(CURL_GLOBAL_SSL);

    curl = curl_easy_init();

    if (curl) {
        std::string url_serv(GetHTTPS());
        url_serv += path_url;

        curl_easy_setopt(curl, CURLOPT_DNS_SERVERS, oxxo("8.8.8.8,8.8.4.4"));
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

    if (res != CURLE_OK) {
        json returnJSON;
        returnJSON[(oxorany("code"))]  = res;
        returnJSON[(oxorany("error"))] = curl_easy_strerror(res);

        return returnJSON;
    } else {
        json returnJSON;

        try {
            returnJSON[(oxorany("response"))]  = json::parse(responseData);
        } catch (json::exception &e) {
            json falseJson;
            return falseJson;
        }

        return returnJSON;
    }
}