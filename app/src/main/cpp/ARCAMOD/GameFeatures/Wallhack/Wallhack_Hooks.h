#ifndef WALLHACK_HOOKS_H
#define WALLHACK_HOOKS_H

void WallhackHook();

#include "Hooks/WallhackNormal.h"
#include "Hooks/WallhackOutline.h"
#include "Hooks/WallhackEspNameOldBR.h"
#include "Hooks/WallhackEspNameHealthBR.h"
#include "Hooks/WallhackEspNameColorBR.h"
#include "Hooks/WallhackEspNameColorMP.h"
#include "Hooks/WallhackEspNameHealthMP.h"
#include "Hooks/WallhackBoostFPS.h"
#include "Hooks/WallhackEspScale.h"

static int wallhackFrameCounter = 0;
static const int HEAVY_FEATURE_INTERVAL = 3;

void WallhackHook() {
    wallhackFrameCounter++;
    if (wallhackFrameCounter > 999) wallhackFrameCounter = 0;

    HandleWallhackBoostFPS();
    HandleWallhackOutline();

    if (wallhackFrameCounter % HEAVY_FEATURE_INTERVAL == 0) {
        HandleWallhackEspNameOldBR();
        HandleWallhackEspNameHealthBR();
        HandleWallhackEspNameColorBR();
        HandleWallhackEspNameColorMP();
    }

    if (Config.View.Wallhack.Normal) {
        HandleWallhackNormal();
    }

    if (Config.View.Wallhack.EspScale) {
        HandleWallhackEspScale();
    }

    if (Config.View.Wallhack.EspNameHealthMP) {
        HandleWallhackEspNameHealthMP();
    }
}

#endif // WALLHACK_HOOKS_H