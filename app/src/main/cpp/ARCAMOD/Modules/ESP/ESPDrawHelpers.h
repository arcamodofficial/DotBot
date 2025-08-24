//
// Created by @arcamod on 22/12/2024.
//

#ifndef ARCAMOD_ESP_DRAW_HELPERS_H
#define ARCAMOD_ESP_DRAW_HELPERS_H

#include <cmath>
#include <random>

// Essential macros for fresh ESP implementation
// FORCE_CHECK macro removed - no longer using pointer validation restrictions

// Macro untuk validasi tambahan terhadap nilai yang diakses
#define VALIDATE_VALUE(value) (std::isfinite(value) && value >= -100000.0f && value <= 100000.0f)

// Legacy functions removed - not used in fresh ESP implementation
// All ESP rendering now done directly in ESPDraw.h using UnityAPIInit.h, OffsetDefinitions.h, Registry.h

#endif // ARCAMOD_ESP_DRAW_HELPERS_H