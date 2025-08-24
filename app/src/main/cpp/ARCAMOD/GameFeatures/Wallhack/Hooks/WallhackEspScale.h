#ifndef ARCAMOD_WALLHACKESPSCALE_H
#define ARCAMOD_WALLHACKESPSCALE_H

typedef int64_t (*original_set_name_blood_scale_func)(int64_t a1, float a2);

original_set_name_blood_scale_func originalSetNameBloodScaleFunction = nullptr;

static bool espScaleHooksInstalled = false;
static bool espScaleActive = false;
static bool espScaleInitialized = false;
static bool espScaleLogged = false;

#define SET_NAME_BLOOD_SCALE_OFFSET OBF(WALLHACK_EspScale_SetNameBloodScale)

static float espScaleFactor = 2.0f;
static bool debugModeEspScale = false;

static int64_t SetNameBloodScaleHook(int64_t a1, float a2) {
    if (!espScaleActive || !a1) {
        return originalSetNameBloodScaleFunction(a1, a2);
    }

    static int logCount = 0;
    if (debugModeEspScale && logCount < 3) {
        logCount++;
    }

    float modifiedScale = a2;
    if (a2 > 0.0f) {
        modifiedScale = a2 * espScaleFactor;

        if (debugModeEspScale && logCount < 4) {
            // LOGIO("EspScale: Memodifikasi skala dari %f menjadi %f (faktor: %.1fx)",
                  // a2, modifiedScale, espScaleFactor);
        }
    }

    return originalSetNameBloodScaleFunction(a1, modifiedScale);
}

static bool SetupEspScaleHooks() {
    if (espScaleHooksInstalled) {
        return true;
    }

    bool hookSuccessful = false;

    uintptr_t setNameBloodAddr = Tools::GetRealOffsets(OBF("libunity.so"), SET_NAME_BLOOD_SCALE_OFFSET);

    if (setNameBloodAddr != 0) {
        originalSetNameBloodScaleFunction = (original_set_name_blood_scale_func) setNameBloodAddr;

        bool scaleHookResult = Tools::Hook(
                (void *) setNameBloodAddr,
                (void *) SetNameBloodScaleHook,
                (void **) &originalSetNameBloodScaleFunction
        );

        if (scaleHookResult) {
            hookSuccessful = true;
        } else {
            // LOGEO("EspScale: Hook gagal (SetNameBloodScale)");
        }
    }

    espScaleHooksInstalled = hookSuccessful;

    return hookSuccessful;
}

static int espScaleFrameCounter = 0;

static void SetEspScale(float scale) {
    if (scale >= 1.0f && scale <= 5.0f) {
        espScaleFactor = scale;
    }
}

static void SetEspScaleActive(bool active) {
    espScaleActive = active;

    if (active && !espScaleLogged) {
        espScaleLogged = true;
    } else if (!active && espScaleLogged) {
        espScaleLogged = false;
    }
}

static void HandleWallhackEspScale() {
    espScaleFrameCounter++;
    if (espScaleFrameCounter < 300 && espScaleInitialized) {
        return;
    }
    espScaleFrameCounter = 0;

    if (Config.View.Wallhack.EspScale) {
        if (!espScaleInitialized) {
            if (SetupEspScaleHooks()) {
                espScaleInitialized = true;
            } else {
                // LOGEO("EspScale: Gagal menginisialisasi hook");
            }
        }

        SetEspScaleActive(true);
        Config.View.WallhackHook.EspScaleReady = true;
    } else {
        SetEspScaleActive(false);
        Config.View.WallhackHook.EspScaleReady = false;
    }
}

#endif //ARCAMOD_WALLHACKESPSCALE_H