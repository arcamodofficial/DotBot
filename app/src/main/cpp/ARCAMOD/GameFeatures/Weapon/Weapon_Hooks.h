#define ARCAMOD_WEAPON_HOOKS_H
#ifndef WEAPON_HOOKS_H
#define WEAPON_HOOKS_H

void WeaponHook();

#include "Hooks/Aim.h"
//#include "Hooks/Bullet.h"
#include "Hooks/Reload.h"
#include "Hooks/Scope.h"
#include "Hooks/Crosshair.h"
#include "Hooks/Recoil.h"
#include "Hooks/HighDamage.h"
//#include "Hooks/Switch.h"
//#include "Hooks/Overheat.h"
#include "Hooks/Spread.h"
#include "Hooks/InfiniteAmmo.h"

void WeaponHook() {
    HandleCrosshair();
    HandleHighDamage();

    if (Config.Weapon.Aim) {
        HandleAim();
    }
    if (Config.Weapon.Reload) {
        HandleReload();
    }
    if (Config.Weapon.Scope) {
        HandleScope();
    }
    if (Config.Weapon.Recoil) {
        HandleRecoil();
    }
    if (Config.Weapon.Spread) {
        HandleSpread();
    }
    if (Config.Weapon.InfiniteAmmo) {
        HandleInfiniteAmmo();
    }
}

#endif // WEAPON_HOOKS_H