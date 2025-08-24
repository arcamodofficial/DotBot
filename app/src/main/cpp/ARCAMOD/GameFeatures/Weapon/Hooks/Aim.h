#ifndef ARCAMOD_AIM_H
#define ARCAMOD_AIM_H

#ifdef RELEASE
#pragma clang optimize off
#pragma GCC optimize ("O0")
#pragma GCC push_options
#endif

#define ADDR_GETASSITAIMSPEED OBF(WEAPON_GetAssitAimSpeed)

typedef float (*tGetAssitAimSpeed)(void *thiz, char isPVE, char isGamepad, double unk1, double unk2,
                                   double unk3,
                                   long double angle, long double distance, long double unk4);

tGetAssitAimSpeed original_GetAssitAimSpeed;

static float
hook_GetAssitAimSpeed(void *thiz, char isPVE, char isGamepad, double unk1, double unk2, double unk3,
                      long double angle, long double distance, long double unk4) {

    if (!Config.Weapon.Aim) {
        return 0.2f;
    }

    float aimFactor = Config.WeaponSize.Aim;
    bool isExtremeLevel = (aimFactor >= 6.0f);
    bool isUltraLevel = (aimFactor >= 4.0f && aimFactor < 6.0f);
    bool isHighLevel = (aimFactor >= 3.0f && aimFactor < 4.0f);
    bool isMediumLevel = (aimFactor >= 2.0f && aimFactor < 3.0f);
    bool isLowLevel = (aimFactor < 2.0f);
    bool isVeryLowLevel = (aimFactor < 1.0f);

    bool hasTarget = ((float) angle > 0.1f || (float) distance > 0.1f);

    if (isExtremeLevel && hasTarget) {
        float lockStrength = 80.0f;

        if ((float) distance < 25.0f) {
            lockStrength = 100.0f;
        }

        if ((float) angle < 8.0f) {
            lockStrength = 150.0f;
        }

        if ((float) distance < 20.0f && (float) angle < 5.0f) {
            lockStrength = 200.0f;
        }

        return lockStrength;
    }

    if (isUltraLevel && hasTarget) {
        float lockStrength = 40.0f;

        if ((float) distance < 20.0f) {
            lockStrength = 60.0f;
        }

        if ((float) angle < 5.0f) {
            lockStrength = 80.0f;
        }

        return lockStrength;
    }

    if (isHighLevel && hasTarget) {
        float lockStrength = 18.0f;

        if ((float) distance < 30.0f || (float) angle < 10.0f) {
            lockStrength = 25.0f;
        }

        if ((float) distance < 15.0f) {
            lockStrength = 35.0f;
        }

        return lockStrength;
    }

    if (isMediumLevel && hasTarget) {
        float semiLockStrength = 10.0f;

        if ((float) distance < 35.0f || (float) angle < 12.0f) {
            semiLockStrength = 14.0f;

            if ((float) distance < 30.0f && (float) angle < 10.0f) {
                semiLockStrength = 17.0f;
            }

            if ((float) distance < 15.0f || (float) angle < 5.0f) {
                semiLockStrength = 20.0f;
            }
        }

        return semiLockStrength;
    }

    if (isLowLevel && !isVeryLowLevel && hasTarget) {
        float lightLockStrength = 6.0f;

        if ((float) distance < 25.0f || (float) angle < 10.0f) {
            lightLockStrength = 8.0f;

            if ((float) distance < 20.0f && (float) angle < 8.0f) {
                lightLockStrength = 10.0f;
            }

            if ((float) distance < 12.0f || (float) angle < 4.0f) {
                lightLockStrength = 12.0f;
            }
        }

        return lightLockStrength;
    }

    float baseAimSpeed;
    if (isExtremeLevel) {
        baseAimSpeed = 1.8f;
    } else if (isUltraLevel) {
        baseAimSpeed = 1.5f;
    } else if (isHighLevel) {
        baseAimSpeed = 1.2f;
    } else if (isMediumLevel) {
        baseAimSpeed = 0.9f;
    } else if (isLowLevel && !isVeryLowLevel) {
        baseAimSpeed = 0.7f;
    } else {
        baseAimSpeed = 0.6f;
    }

    float aimMultiplier;
    if (isExtremeLevel) {
        aimMultiplier = 4.0f;
    } else if (isUltraLevel) {
        aimMultiplier = 3.5f;
    } else if (isVeryLowLevel) {
        aimMultiplier = 3.0f;
    } else if (isLowLevel) {
        aimMultiplier = 2.5f;
    } else if (isMediumLevel) {
        aimMultiplier = 2.0f;
    } else {
        aimMultiplier = 1.5f;
    }
    float targetSpeed = baseAimSpeed * (aimFactor * aimMultiplier);

    float dist = (float) distance;
    if (dist > 0.1f) {
        if (Config.Weapon.AimCloseBoost) {
            if (dist < 20.0f) {
                if (isExtremeLevel) {
                    targetSpeed *= 5.0f;
                } else if (isUltraLevel) {
                    targetSpeed *= 4.5f;
                } else if (isVeryLowLevel) {
                    targetSpeed *= 4.0f;
                } else if (isLowLevel) {
                    targetSpeed *= 3.5f;
                } else if (isMediumLevel) {
                    targetSpeed *= 3.0f;
                } else {
                    targetSpeed *= 2.5f;
                }
            } else if (dist < 40.0f) {
                if (isExtremeLevel) {
                    targetSpeed *= 4.0f;
                } else if (isUltraLevel) {
                    targetSpeed *= 3.5f;
                } else if (isVeryLowLevel) {
                    targetSpeed *= 3.0f;
                } else if (isLowLevel) {
                    targetSpeed *= 2.5f;
                } else if (isMediumLevel) {
                    targetSpeed *= 2.2f;
                } else {
                    targetSpeed *= 1.8f;
                }
            }
            else if (dist > 80.0f) {
                if (isExtremeLevel || isUltraLevel) {
                    targetSpeed *= 1.0f;
                } else if (isLowLevel || isMediumLevel) {
                    targetSpeed *= 0.9f;
                } else {
                    targetSpeed *= 0.7f;
                }
            }
        }
    }

    float ang = (float) angle;
    if (ang > 0.1f) {
        if (Config.Weapon.AimPrecision) {
            if (ang < 5.0f) {
                if (isExtremeLevel) {
                    targetSpeed *= 5.0f;
                } else if (isUltraLevel) {
                    targetSpeed *= 4.0f;
                } else if (isVeryLowLevel) {
                    targetSpeed *= 3.5f;
                } else if (isLowLevel) {
                    targetSpeed *= 3.0f;
                } else if (isMediumLevel) {
                    targetSpeed *= 2.5f;
                } else {
                    targetSpeed *= 2.0f;
                }
            } else if (ang < 15.0f) {
                if (isExtremeLevel) {
                    targetSpeed *= 4.0f;
                } else if (isUltraLevel) {
                    targetSpeed *= 3.5f;
                } else if (isVeryLowLevel) {
                    targetSpeed *= 2.8f;
                } else if (isLowLevel) {
                    targetSpeed *= 2.5f;
                } else if (isMediumLevel) {
                    targetSpeed *= 2.0f;
                } else {
                    targetSpeed *= 1.5f;
                }
            }
            else if (ang > 30.0f) {
                if (isExtremeLevel || isUltraLevel) {
                    targetSpeed *= 0.9f;
                } else if (isLowLevel || isVeryLowLevel) {
                    targetSpeed *= 0.7f;
                } else {
                    targetSpeed *= 0.5f;
                }
            }
        }
    }

    if (isExtremeLevel) {
        if (targetSpeed < 2.0f) targetSpeed = 2.0f;
    } else if (isUltraLevel) {
        if (targetSpeed < 1.5f) targetSpeed = 1.5f;
    } else if (isVeryLowLevel) {
        if (targetSpeed < 1.2f) targetSpeed = 1.2f;
    } else if (isLowLevel) {
        if (targetSpeed < 1.0f)
            targetSpeed = 1.0f;
    } else if (isMediumLevel) {
        if (targetSpeed < 0.8f) targetSpeed = 0.8f;
    } else {
        if (targetSpeed < 0.5f) targetSpeed = 0.5f;
    }

    if (targetSpeed > 250.0f) targetSpeed = 250.0f;

    return targetSpeed;
}

static void HandleAim() {
    static bool initialized = false;

    if (Config.Weapon.Aim && !initialized) {
        uintptr_t addrGetAssitAimSpeed = Tools::GetRealOffsets(OBF("libunity.so"),
                                                               ADDR_GETASSITAIMSPEED);

        if (addrGetAssitAimSpeed != 0) {
            original_GetAssitAimSpeed = (tGetAssitAimSpeed) addrGetAssitAimSpeed;

            bool hookResult = Tools::Hook(
                    (void *) addrGetAssitAimSpeed,
                    (void *) hook_GetAssitAimSpeed,
                    (void **) &original_GetAssitAimSpeed
            );

            if (hookResult) {
                initialized = true;
                Config.WeaponHook.AimReady = true;
                Config.WeaponHook.AimPatchReady = true;
            }
        }
    } else if (!Config.Weapon.Aim && Config.WeaponHook.AimReady) {
    }

    static float lastAimValue = 0.0f;
    float currentAimValue = Config.WeaponSize.Aim;

    if (Config.Weapon.Aim && abs(lastAimValue - currentAimValue) > 0.01f) {
        lastAimValue = currentAimValue;
        Config.WeaponHook.LastAimValue = currentAimValue;
    }
}

#ifdef RELEASE
#pragma clang optimize on
#pragma GCC pop_options
#endif

#endif //ARCAMOD_AIM_H