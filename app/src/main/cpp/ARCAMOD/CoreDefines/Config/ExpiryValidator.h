#ifndef ARCAMOD_EXPIRY_VALIDATOR_H
#define ARCAMOD_EXPIRY_VALIDATOR_H

#include <ctime>
#include <iostream>
#include <signal.h>
#include <unistd.h>

static inline void set_expiration_date() {
    int tahun = 2085;
    int bulan = 8;
    int tanggal = 15;
    int jam = 12;
    int menit = 0;
    int detik = 0;

    struct tm exp_tm = {};
    exp_tm.tm_year = tahun - 1900;
    exp_tm.tm_mon = bulan - 1;
    exp_tm.tm_mday = tanggal;
    exp_tm.tm_hour = jam - 7;
    exp_tm.tm_min = menit;
    exp_tm.tm_sec = detik;

    time_t expired_time_gmt7 = mktime(&exp_tm);
    Config.UserData.ExpiredUTC = expired_time_gmt7;

    time_t current_time = time(nullptr);

    char expired_date_str[64];
    char current_date_str[64];

    struct tm *expired_tm = localtime(&expired_time_gmt7);
    strftime(expired_date_str, sizeof(expired_date_str), OBF("%d %B %Y %H:%M:%S"), expired_tm);

    struct tm *current_tm = localtime(&current_time);
    strftime(current_date_str, sizeof(current_date_str), OBF("%d %B %Y %H:%M:%S"), current_tm);

    // LOGI(OBF("Tanggal kedaluwarsa: %s"), expired_date_str);
    // LOGI(OBF("Tanggal saat ini: %s"), current_date_str);

    if (current_time > expired_time_gmt7) {
        Config.Display.Lable += OBF(" | EXPIRED");
        Config.UserData.IsLoggedIn = false;

        // LOGE(OBF("Lisensi telah kedaluwarsa pada %s! Aplikasi akan dihentikan..."), expired_date_str);

        abort();

        // kill(getpid(), SIGKILL);

        // int *ptr = nullptr;
        // *ptr = 1; // Segmentation fault

        pthread_exit(nullptr);
    }
}

#endif // ARCAMOD_EXPIRY_VALIDATOR_H
