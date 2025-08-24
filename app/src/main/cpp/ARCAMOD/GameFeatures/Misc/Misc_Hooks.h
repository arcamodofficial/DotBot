#ifndef ARCAMOD_MISC_HOOKS_H
#define ARCAMOD_MISC_HOOKS_H

void MiscHook();

#include "Hooks/Jump.h"
#include "Hooks/Speed.h"
#include "Hooks/Spectate.h"
#include "Hooks/Parachute.h"
#include "Hooks/SkyDiving.h"
#include "Hooks/Slide.h"
#include "Hooks/Swim.h"
#include "Hooks/Tutorial.h"
#include "Hooks/FakeStatus.h"
// DISABLED: ResourceOptimization dinonaktifkan
// #include "Hooks/ResourceOptimization.h"
#include "Hooks/SmartFPS.h"
#include "Hooks/UltraFPSGraphicUnlock.h"
#include "Hooks/SkiingBoost.h"

// DISABLED: Handler ResourceOptimization dinonaktifkan
// void HandleResourceOptimization() {
//     if (Config.Misc.ResourceOptimization) {
//         ResourceOptimization::Update();
//     }
// }

// ❌ DISABLED: SmartFPS completely disabled for testing - NO RENDER CODE
/*
void HandleSmartFPS() {
    static int callCount = 0;
    callCount++;
    if (callCount <= 3) {
        LOGIO("HandleSmartFPS: Called #%d - Config.Misc.SmartFPS=%s",
              callCount, Config.Misc.SmartFPS ? "true" : "false");
    }

    if (Config.Misc.SmartFPS) {
        SmartFPS::Update();
    }
}
*/

static void HandleUltraFPSGraphicUnlock() {
    if (!UltraFPSGraphicUnlock::IsEnabled()) {
        UltraFPSGraphicUnlock::Enable();
    }
}

void MiscHook() {
    static bool initialized = false;
    if (!initialized) {
        initialized = true;

        // DISABLED: ResourceOptimization dinonaktifkan
        // ❌ DISABLED: SmartFPS completely disabled for testing
        // SmartFPS::Init();
        // ResourceOptimization::Init();

        UltraFPSGraphicUnlock::InitializeHooks();
    }

    HandleJump();
    HandleSwim();
    HandleTutorial();

    if (Config.Misc.Speed) {
        HandleSpeed();
    }
    if (Config.Misc.Spectate) {
        HandleSpectate();
    }
    if (Config.Misc.Parachute) {
        HandleParachute();
    }
    if (Config.Misc.SkyDiving) {
        HandleSkyDiving();
    }
    if (Config.Misc.Slide) {
        HandleSlide();
    }
    if (Config.Misc.SkiingBoost) {
        HandleSkiingBoost();
    }
    if (Config.Misc.UltraFPSGraphicUnlock) {
        HandleUltraFPSGraphicUnlock();
    }

    HandleFakeStatus();

    // DISABLED: Handler ResourceOptimization dinonaktifkan
    // HandleResourceOptimization();
    // ❌ DISABLED: SmartFPS completely disabled for testing
    // HandleSmartFPS();
}

#endif //ARCAMOD_MISC_HOOKS_H