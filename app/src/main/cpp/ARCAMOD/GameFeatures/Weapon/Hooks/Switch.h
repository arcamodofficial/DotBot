void HandleSwitch() {
    if (Config.Weapon.Switch) {
        if (!Config.WeaponHook.SwitchPatchReady) {
            PATCH("libunity.so", "0x857C45C", "200080D2C0035FD6");
            Config.WeaponHook.SwitchPatchReady = true;
        }
    } else {
        if (Config.WeaponHook.SwitchPatchReady) {
            PATCH("libunity.so", "0x857C45C", "E80F1DFCF44F01A9");
            Config.WeaponHook.SwitchPatchReady = false;
        }
    }
    Config.WeaponHook.SwitchReady = true;
}
