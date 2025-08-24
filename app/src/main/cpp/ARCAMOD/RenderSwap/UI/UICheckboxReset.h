#ifndef RESET_CHECKBOXES_H
#define RESET_CHECKBOXES_H

static void resetAllCheckboxes() PASS_OBF PASS_OBF_STRING {
    Config.View.Line = false;
    Config.View.Box = false;
    Config.View.Health = false;
    Config.View.Name = false;
    Config.View.Distance = false;
    // Config.View.Signal = false;
    Config.View.Skeleton = false;
    // Config.View.Vehicle = false;
    Config.View.EnableBoxFill = false;
    Config.View.DisableBoxFill = false;

    Config.Weapon.Reload = false;
    Config.Weapon.Scope = false;
    Config.Weapon.Crosshair = false;
    Config.Weapon.Recoil = false;
    Config.Weapon.Aim = false;
    Config.Weapon.Spread = false;
    Config.Weapon.HighDamage = false;
    Config.Weapon.Bullet = false;
    Config.Weapon.InfiniteAmmo = false;

    Config.Misc.Jump = false;
    Config.Misc.Speed = false;
    Config.Misc.Spectate = false;
    Config.Misc.Slide = false;
    Config.Misc.Parachute = false;
    Config.Misc.Swim = false;
    Config.Misc.SkyDiving = false;
    Config.Misc.ResourceOptimization = false;
    // ❌ DISABLED: SmartFPS completely disabled for testing
    // Config.Misc.SmartFPS = false;
    Config.Misc.FakeStatus = false;
    Config.Misc.BlockAnalytics = false;

    Config.View.Wallhack.Normal = false;
    Config.View.Wallhack.EspNameColorBR = false;
    Config.View.Wallhack.EspNameHealthBR = false;
    Config.View.Wallhack.EspNameHealthMP = false;
    Config.View.Wallhack.EspScale = false;

    Config.Settings.ShowFpsInScreen = false;
    Config.View.Wallhack.BoostFPS = false;
    Config.Misc.Tutorial = false;
    Config.Misc.UltraFPSGraphicUnlock = false;

    // LOGI("Reset semua checkbox: Fitur dinonaktifkan karena lisensi berakhir atau validasi gagal");
}

static bool isLicenseAboutToExpire() PASS_OBF PASS_OBF_STRING {
    time_t utc_time = time(nullptr);
    time_t remainingTime = Config.UserData.ExpiredUTC - utc_time;

    return (remainingTime <= 900 && remainingTime > 0);
}

static time_t getRemainingLicenseTime() PASS_OBF PASS_OBF_STRING {
    time_t utc_time = time(nullptr);
    time_t remainingTime = Config.UserData.ExpiredUTC - utc_time;

    return (remainingTime > 0) ? remainingTime : 0;
}

#endif // RESET_CHECKBOXES_H