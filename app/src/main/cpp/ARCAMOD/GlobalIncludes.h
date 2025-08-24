#ifndef ARCAMOD_GLOBAL_INCLUDES_H
#define ARCAMOD_GLOBAL_INCLUDES_H
#pragma once

#ifdef __arm__
#define ARM32 1
#endif

#include "Includes/Includes.h"
#include "CoreDefines/CoreIncludes.h"
#include "GameSDK/GameSDKIncludes.h"
#include "EngineHooks/HookIncludes.h"
#include "UnityIntegration/UnityAPIInit.h"
#include "Modules/ModulesIncludes.h"
#include "GameFeatures/Includes.h"
// DISABLED: Auto Feedback dinonaktifkan secara total - include di-comment
// #include "ScreenshotFeedback/ScreenshotFeedback.h"
#include "UIMenu/UIIncludes.h"
#include "RenderSwap/RendererIncludes.h"
#include "RemapTools/RemapTools.hpp"

#endif //ARCAMOD_GLOBAL_INCLUDES_H
