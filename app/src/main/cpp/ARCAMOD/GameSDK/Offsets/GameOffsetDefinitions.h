#ifndef ARCAMOD_GAME_OFFSET_DEFINITIONS_H
#define ARCAMOD_GAME_OFFSET_DEFINITIONS_H

#pragma once
#include <stdint.h>

// ARCAMOD ESP OFFSET DEFINITIONS - Update guide untuk game version baru:
// 1. Analisis dengan IDA Pro/Ghidra untuk mendapatkan offset baru
// 2. Update offset ESP: Pawn, BaseGame, AttackableTarget, PlayerInfo, Vehicle
// 3. Update Functions: Transform, Camera, GamePlay, Screen, SystemInfo
// 4. Test ESP functionality setelah update
// Format: constexpr type name = value; // ClassName$$MethodName

namespace Offsets {
    // ESP SYSTEM OFFSETS - Semua offset untuk ESP dalam satu kelompok
    namespace Pawn {
        constexpr uintptr_t IsAlive = 1328; // GameBase_Pawn__get_IsAlive - Updated: a1 + 1328
        constexpr uintptr_t IsBot = 1433; // GameBase_Pawn__get_IsBot - Updated: a1 + 1433
        constexpr uintptr_t PlayerInfo = 1440; // GameBase_Pawn__get_PlayerName - Updated: a1 + 1440
        constexpr uintptr_t CurrentVehicle = 816; // GameBase_Pawn__get_CurrentVehicle - Updated: a1 + 816
        constexpr uintptr_t IsOnVehicle = 1272; // GameBase_Pawn__get_IsOnVehicle - Updated: uses a1 + 1272
        constexpr uintptr_t IsSkiing = 1272; // GameBase_Pawn__get_IsSkiing - Updated: a1 + 1272
        constexpr unsigned int Mesh = 6400; // GameBase_Pawn__get_MeshRenderers - Updated: a1 + 6400
        constexpr unsigned int HeadBone = 760; // GameBase_Pawn__get_HeadBone - Updated: a1 + 760
        constexpr unsigned int SpineBone = 6920; // GameBase_PlayerPawn__get_SpineBone - Updated: a1 + 6920
        constexpr unsigned int NeckBone = 7200; // GameBase_PlayerPawn__get_NeckBone - Updated: a1 + 7200
        constexpr unsigned int HipsBone = 7208; // GameBase_PlayerPawn__get_HipsBone - Updated: a1 + 7208
        constexpr unsigned int LeftAnkleBone = 7216; // GameBase_PlayerPawn__get_LeftAnkleBone - Updated: a1 + 7216
        constexpr unsigned int RightAnkleBone = 7224; // GameBase_PlayerPawn__get_RightAnkleBone - Updated: a1 + 7224
        [[maybe_unused]] constexpr unsigned int ModelRoot = 1536; // GameBase_Pawn__get_ModelRoot
        [[maybe_unused]] constexpr unsigned int LastRespawnTime = 1356; // GameBase_Pawn__get_LastRespawnTime
        [[maybe_unused]] constexpr unsigned int BRMeshShow = 129; // GameBase_Pawn__get_BRMeshShow
        [[maybe_unused]] constexpr unsigned int LastPlayBloodEffect = 1240; // GameBase_Pawn__get_LastPlayBloodEffectTime
    }
    namespace BaseGame {
        constexpr unsigned int EnemyPawns = 360; // GameBase_BaseGame__GetEnemyPawns
        constexpr unsigned int MatchInProgress = 148; // GameBase_BaseGame__get_MatchInProgress
        constexpr unsigned int AttackableTargetDictionary = 392; // GameBase_BaseGame__GetAttackableTarget
    }
    namespace AttackableTarget {
        constexpr unsigned int AttackableInfo = 120; // GameEngine_AttackableTarget__get_AttackableInfo
    }
    namespace AttackableTargetInfo {
        constexpr unsigned int Health = 52; // GameEngine.AttackableTargetInfo$$get_Health
        constexpr unsigned int MaxHealth = 56; // GameEngine.AttackableTargetInfo$$get_MaxHealth
        constexpr unsigned int ExtraHealth = 64; // GameEngine.AttackableTargetInfo$$get_ExtraHealth
        constexpr unsigned int MaxExtraHealth = 68; // GameEngine.AttackableTargetInfo$$get_MaxExtraHealth
        constexpr unsigned int Signal = 72; // GameEngine_AttackableTargetInfo__get_Signal - Updated: a1 + 72
        constexpr unsigned int MaxSignal = 76; // GameEngine.AttackableTargetInfo$$get_MaxSignal
        [[maybe_unused]] constexpr unsigned int ActorID = 48; // GameEngine.AttackableTargetInfo$$get_ActorID
        [[maybe_unused]] constexpr unsigned int MaxHealthpointDelta = 60; // GameEngine.AttackableTargetInfo$$get_MaxHealthpointDelta
    }
    namespace PlayerInfo {
        constexpr uintptr_t TeamID = 256; // GameEngine_PlayerInfo__get_TeamID
        constexpr uintptr_t NickName = 336; // GameEngine_PlayerInfo__get_NickName
        constexpr uintptr_t GamePlayerID = 248; // GameEngine_PlayerInfo__get_GamePlayerID
        constexpr uintptr_t GameLevel = 448; // GameEngine_PlayerInfo__get_GameLevel
        constexpr uintptr_t TeamKillCount = 852; // GameEngine_PlayerInfo__get_TeamKillEnemyCount - Updated: a1 + 852
        constexpr uintptr_t KillEnemyCount = 728; // GameEngine_PlayerInfo__get_KillEnemyCount - Updated: a1 + 728
        constexpr uintptr_t DeathCount = 752; // GameEngine_PlayerInfo__get_DeathCount - Updated: a1 + 752
        constexpr uintptr_t AssistCount = 768; // GameEngine_PlayerInfo__get_AssistCount - Updated: a1 + 768
        constexpr uintptr_t HeadShotCount = 684; // GameEngine_PlayerInfo__get_HeadShotCount - Updated: a1 + 684
        constexpr uintptr_t KillStreak = 740; // GameEngine_PlayerInfo__get_KillStreak - Updated: a1 + 740
        constexpr uintptr_t TotalDamage = 800; // GameEngine_PlayerInfo__get_TotalDamage - Updated: a1 + 800
        constexpr uintptr_t IsFiringForUIShow = 454; // GameEngine_PlayerInfo__get_IsFiringForUIShow
        constexpr uintptr_t GamePlayerID_AI = 352; // GameEngine_PlayerInfo__get_GamePlayerId_AI
        constexpr uintptr_t Health = AttackableTargetInfo::Health;
        constexpr uintptr_t MaxHealth = AttackableTargetInfo::MaxHealth;
        [[maybe_unused]] constexpr unsigned int PlayerID = 244; // GameEngine_PlayerInfo__get_PlayerID
        [[maybe_unused]] constexpr unsigned int TeamSeatID = 268; // GameEngine_PlayerInfo__get_TeamSeatID
        [[maybe_unused]] constexpr unsigned int TeamSeatID_GroupRoom = 276; // GameEngine_PlayerInfo__get_TeamSeatID_GroupRoom
        [[maybe_unused]] constexpr unsigned int ElectricCarID = 312; // GameEngine_PlayerInfo__get_ElectricCarID
    }

    namespace Vehicle {
        constexpr uintptr_t AllVehicles = 400; // GameBase.BaseGame$$get_allVehicles
        constexpr uintptr_t Transform = 104; // GameBase.VehicleNotOnRigidbody$$get_Position
        constexpr uintptr_t TypeId = 96; // GameEngine.VehicleInfo$$get_VehicleTypeId
        constexpr uintptr_t VehicleType = 304; // GameEngine.PhysicsVehicle$$get_VehicleType
        constexpr uintptr_t VehicleMgr = 280; // GameBase.BaseGame$$get_VehicleMgr
        constexpr uintptr_t GetVehicleByID = 0x752B08C; // BaseGame::GetVehicle
        constexpr uintptr_t ChassisCenter = 388; // PhysicsVehicle chassis center
        constexpr uintptr_t ChassisCenterY = 392; // PhysicsVehicle chassis Y
        constexpr uintptr_t ChassisCenterZ = 396; // PhysicsVehicle chassis Z
        constexpr uintptr_t AttachRoot = 0x4E185C4; // PhysicsVehicle::GetAttchRoot
        constexpr uintptr_t VTableHealthOffset = 888; // Virtual table health offset
        constexpr uintptr_t VTableHealthParam = 896; // Virtual table health param
        constexpr uintptr_t AvailableVehicles = 64; // VehicleManager available vehicles
        constexpr uintptr_t FastVehicleCheck = 308; // GameBase_Pawn__IsVehicleFast
        constexpr uint32_t FastVehicleIdentifier = 31707127; // Fast vehicle identifier
        constexpr uintptr_t VehicleSkisData = 3656; // GameBase_Pawn__GetVehicleSkisData - Updated: a1 + 3656
        constexpr uintptr_t SkisExportInfo = 320; // GameBase_Pawn__get_m_PhysSkisVehicleExportInfo
        constexpr uintptr_t PhysVehicleSkisOffset = 128; // SkiingComponent__get_PhysVehicleSkis
        [[maybe_unused]] constexpr unsigned int WheeledVehicleNum = 0; // GameBase_BaseGame__get_WheeledVehicleNum
        namespace BRVehicleID {
            constexpr uint32_t BasicLandVehicle = 0x7459282;
            constexpr uint32_t SecondaryVehicle = 0x7459283;
            constexpr uint32_t Helicopter = 0x7459286;
            constexpr uint32_t AmphibiousVehicle = 0x7459287;
            constexpr uint32_t FastVehicle = 0x7459288;
            constexpr uint32_t SpecialVehicle = 0x745928D;
            constexpr uint32_t CustomVehicle = 122000060;
        }
        namespace BRVehicleEffectID {
            constexpr uint32_t StartEffect = 700000261;
            constexpr uint32_t LoopEffect = 700000262;
            constexpr uint32_t EndEffect = 700000263;
        }
        namespace BRVehicleAssetID {
            constexpr uint32_t BasicLandVehicle = 700000266;
            constexpr uint32_t SecondaryVehicle = 700000269;
            constexpr uint32_t Helicopter = 700000268;
            constexpr uint32_t AmphibiousVehicle = 700000267;
            constexpr uint32_t FastVehicle = 700000270;
            constexpr uint32_t SpecialVehicle = 700000265;
            constexpr uint32_t CustomVehicle = 700000279;
        }
    }

    // WEAPON SYSTEM OFFSETS - CENTRALIZED untuk mudah update di masa depan
    // Format: #define global untuk kompatibilitas penuh dengan OBF() tanpa modifikasi
    // UPDATE GUIDE: Saat game update, ubah nilai offset di bawah ini
    #define WEAPON_GetAssitAimSpeed "0x875B248"        // GameEngine_WeaponFireComponent__GetAssitAimSpeed - Aim.h
    #define WEAPON_Crosshair_Patch "0xA2EF800"        // Crosshair modification patch - Crosshair.h
    #define WEAPON_HighDamage_Patch "0x89164A0"       // High damage patch - HighDamage.h
    #define WEAPON_GetScaleRecoil "0x9FE9618"         // GameEngine_WeaponFireComponent__GetScaleRecoil - Recoil.h
    #define WEAPON_GetChangeClipTime "0x890F0D4"      // GameEngine_WeaponFireComponent__GetChangeClipTime - Reload.h
    #define WEAPON_GetAimingTime "0xA28A604"          // GameEngine_WeaponFireComponent__GetAimingTime - Scope.h
    #define WEAPON_GetRealSpreadModifier "0x9FE7D88"  // GameEngine_WeaponFireComponent__GetRealSpreadModifier - Spread.h
    #define WEAPON_CalcShotSpreadSize "0x9FE8030"     // GameEngine_WeaponFireComponent__CalcShotSpreadSize - Spread.h
    #define WEAPON_RandomShotSpread "0x9FE7C44"       // GameEngine_WeaponFireComponent__RandomShotSpread - Spread.h
    #define WEAPON_AmmoCanFire "0x8913420"            // GameEngine_WeaponFireComponent__AmmoCanFire - InfiniteAmmo.h
    #define WEAPON_ConsumeAmmo "0xA2AA750"            // GameEngine_WeaponFireComponent__ConsumeAmmo - InfiniteAmmo.h
    #define WEAPON_GetInfiniteCarriedAmmo "0x8913914" // GameEngine_WeaponFireComponent__GetInfiniteCarriedAmmo - InfiniteAmmo.h

    // MISC SYSTEM OFFSETS - CENTRALIZED untuk mudah update di masa depan
    // Format: #define global untuk kompatibilitas penuh dengan OBF() tanpa modifikasi
    // UPDATE GUIDE: Saat game update, ubah nilai offset di bawah ini

    // PATCH-BASED MISC FEATURES
    #define MISC_Jump_Patch1 "0x90D6F78"              // Jump patch point 1 - Jump.h
    #define MISC_Jump_Patch2 "0x90D6F68"              // Jump patch point 2 - Jump.h
    #define MISC_Jump_Patch3 "0x90D71E8"              // Jump patch point 3 - Jump.h
    #define MISC_Jump_Patch4 "0x9084E78"              // Jump patch point 4 - Jump.h
    #define MISC_Jump_Patch5 "0x90D7274"              // Jump patch point 5 - Jump.h
    #define MISC_Jump_Patch6 "0x907CC98"              // Jump patch point 6 - Jump.h
    #define MISC_Swim_Patch "0x91ED068"               // Swim speed modification - Swim.h
    #define MISC_Tutorial_Patch "0x8ABF5DC"           // Tutorial bypass - Tutorial.h
    // SPECTATOR NO DELAY HOOKS - Berdasarkan SpectatedAssembly+XREF.cpp (20 Offset)
    #define MISC_Spectate_ObserverCtor "0x904D040"         // GameBase_ObserverDelayManager___ctor - Spectate.h
    #define MISC_Spectate_ObserverInit "0x904D1E4"         // GameBase_ObserverDelayManager__Init - Spectate.h
    #define MISC_Spectate_LogicalInit "0x4BDF590"          // GameEngine_LogicalComponent__Init - Spectate.h
    #define MISC_Spectate_OnStartMatch "0x904D240"         // GameBase_ObserverDelayManager__OnStartMatch - Spectate.h
    #define MISC_Spectate_ObserverTick "0x904D450"         // GameBase_ObserverDelayManager__Tick - Spectate.h
    #define MISC_Spectate_LogicalTick "0x4BDF5E0"          // GameEngine_LogicalComponent__Tick - Spectate.h
    #define MISC_Spectate_GetDelayCountDown "0x904D698"    // GameBase_ObserverDelayManager__GetDelayCountDown - Spectate.h
    #define MISC_Spectate_RecycleData "0x904DC04"          // GameBase_ObserverDelayManager__RecycleData - Spectate.h
    #define MISC_Spectate_RealtimeStartup "0x4095310"      // TimeUtils__get_realtimeSinceStartup - Spectate.h
    #define MISC_Spectate_LogicalShutdown "0x4C5FD3C"      // GameEngine_LogicalComponent__Shutdown - Spectate.h
    #define MISC_Spectate_NeedDelayProcess "0x904DD18"     // GameBase_ObserverDelayManager__NeedDelayProcess - Spectate.h
    #define MISC_Spectate_NetworkProcessPacket "0x7A7CD64" // Network_GameServerHandler__ProcessPacket - Spectate.h
    #define MISC_Spectate_PingTick "0x86B8FB8"             // MatchPingEntity__TickPing - Spectate.h
    #define MISC_Spectate_ProcessForDelay "0x904DD88"      // GameBase_ObserverDelayManager__ProcessForDelay - Spectate.h
    #define MISC_Spectate_GetData "0x904E1B8"              // GameBase_ObserverDelayManager__GetData - Spectate.h
    #define MISC_Spectate_GetByteByLength "0x904E324"      // GameBase_ObserverDelayManager__GetByteByLength - Spectate.h
    #define MISC_Spectate_GetDataFromPool "0x904E478"      // GameBase_ObserverDelayManager__GetDataFromPoolByCount - Spectate.h
    #define MISC_Spectate_SetDelayAvailable "0x904E644"    // GameBase_ObserverDelayManager__SetDelayAvaliable - Spectate.h
    #define MISC_Spectate_SetNeedPoolSort "0x904E6A8"      // GameBase_ObserverDelayManager__SetIsNeedPoolSort - Spectate.h
    #define MISC_Spectate_ComponentStartMatch "0x532650C"  // GameComponent__OnStartMatch - Spectate.h

    // Legacy compatibility untuk patch-based approach (deprecated)
    #define MISC_Spectate_Patch1 MISC_Spectate_ObserverInit          // Spectate patch point 1 - Spectate.h
    #define MISC_Spectate_Patch2 MISC_Spectate_NeedDelayProcess      // Spectate patch point 2 - Spectate.h
    #define MISC_Spectate_Patch3 MISC_Spectate_ProcessForDelay       // Spectate patch point 3 - Spectate.h
    #define MISC_Spectate_Patch4 "0x4BF8260"                         // Spectate patch point 4 - Spectate.h (legacy)
    #define MISC_Spectate_Patch5 "0x4BF9C78"                         // Spectate patch point 5 - Spectate.h (legacy)
    #define MISC_Spectate_Patch6 MISC_Spectate_RealtimeStartup       // Spectate patch point 6 - Spectate.h

    // HOOK-BASED MISC FEATURES
    #define MISC_Speed_MaxMoveSpeed "0x9069B20"       // GameBase_Pawn__get_MaxMoveSpeed - Speed.h
    #define MISC_Speed_CalcFinalMoveScale "0x908A95C" // GameBase_Pawn__CalcFinalMoveScale - Speed.h
    #define MISC_LobbyDetection_ReportLoginService "0x75D33B4" // GameBase_BeaconReporter__ReportLoginServiceInLobby - LobbyDetection.h

    // NETWORK HOOKS OFFSETS - CENTRALIZED untuk mudah update di masa depan
    #define NETWORK_GameNetClient_Send "0x7A69978"            // Network_GameNetClient__Send - Integrated to FakeStatus.h
    #define NETWORK_GameNetClient_PushToSendDeliveryBuffer "0x7A7C9AC" // Network_GameNetClient__PushToSendDeliveryBuffer - Integrated to FakeStatus.h
    // REMOVED: BeginReportPlayerPull and EndReportPlayerPull hooks - No longer needed

    // TERSAFE HOOKS OFFSETS - CENTRALIZED untuk mudah update di masa depan
    #define TERSAFE_ProcCheck "0x3128FC8"                     // TerSafe proc check function - TerSafeHook.h
    #define TERSAFE_StatusVar "0xE482FE8"                     // TerSafe status variable - TerSafeHook.h

    // UNITY SYSTEM OFFSETS - CENTRALIZED untuk mudah update di masa depan
    #define UNITY_VulkanSetter "0x884098C"                    // GameEngine_SystemSetting__set_EnableVulkan - unity_offsets.h
    #define MISC_Parachute_OpenParachute "0x9BBA1B4"  // GameBase.SkydivingPhysics$$OpenParachute - Parachute.h
    #define MISC_SkyDiving_MaxVelocityForward "0x9BC6DC4"     // GameBase.SkydivingPhysics$$get_MaxVelocityForward - SkyDiving.h
    #define MISC_SkyDiving_AccelerationForward "0x9BC6D64"    // GameBase.SkydivingPhysics$$get_AccelerationForward - SkyDiving.h
    #define MISC_SkyDiving_MaxVelocitySpeedUp "0x9BC6E84"     // GameBase.SkydivingPhysics$$get_MaxVelocityForwardSpeedUp - SkyDiving.h
    #define MISC_SkyDiving_MaxVelocitySpeedDown "0x9BC6EE4"   // GameBase.SkydivingPhysics$$get_MaxVelocityForwardSpeedDown - SkyDiving.h
    #define MISC_SkyDiving_InitVelocity "0x9BC72C4"           // GameBase.SkydivingPhysics$$get_InitVelocity - SkyDiving.h
    #define MISC_SkyDiving_Tick "0x9BC29A0"                   // GameBase.SkydivingPhysics$$Tick - SkyDiving.h
    #define MISC_SkyDiving_GetForward "0x9BCB150"             // GameBase.SkydivingPhysics$$GetForward - SkyDiving.h
    #define MISC_SkyDiving_UpdateVelocityGravity "0x9BC9400"  // GameBase.SkydivingPhysics$$UpdateVelocityGravity - SkyDiving.h
    #define MISC_SkyDiving_UpdateSkydivingStage "0x9BC9538"   // GameBase.SkydivingPhysics$$UpdateSkydivingStage - SkyDiving.h
    #define MISC_SkyDiving_UpdatePawnRotation "0x9BC8960"     // GameBase.SkydivingPhysics$$UpdatePawnRotation - SkyDiving.h
    #define MISC_Slide_SlideAccel "0x9BDBBA8"                 // GameBase_SlideTackleComponent__get_SlideTackleAcclerationSpeed - Slide.h
    #define MISC_Slide_SlideSpeed "0x9BDBB8C"                 // GameBase_SlideTackleComponent__get_SlideTackleSpeed - Slide.h
    #define MISC_Slide_MaxSpeed "0x914AD9C"                   // GameBase_SlideTackleComponent__GetMaxSpeed - Slide.h
    #define MISC_Slide_SuperSlideRate "0x9BDB974"             // GameBase_SlideTackleComponent__GetSuperSlideRate - Slide.h
    #define MISC_Slide_TickLocalPlayer "0x9BDC968"            // GameBase_SlideTackleComponent__TickLocalPlayer - Slide.h
    #define MISC_SkiingBoost_MaxSpeed "0x90DE3A0"             // GameBase_Pawn__get_m_PhysSkisMaxSpeed - SkiingBoost.h
    #define MISC_SkiingBoost_SlopMaxSpeed "0x90DE448"         // GameBase_Pawn__get_m_PhysSkisSlopMaxSpeed - SkiingBoost.h
    #define MISC_SkiingBoost_SpeedUp "0x90E4040"              // GameBase_Pawn__GetPhysSkiingSpeedUp - SkiingBoost.h
    #define MISC_SkiingBoost_MoveMaxSpeed "0x90E3CD8"         // GameBase_Pawn__GetPhysSkiingMoveMaxSpeed - SkiingBoost.h
    #define MISC_SkiingBoost_SpeedKph "0x90E3B18"             // GameBase_Pawn__GetPhysSkisSpeedKPH - SkiingBoost.h

    // WALLHACK SYSTEM OFFSETS - CENTRALIZED untuk mudah update di masa depan
    // Format: #define global untuk kompatibilitas penuh dengan OBF() tanpa modifikasi
    // UPDATE GUIDE: Saat game update, ubah nilai offset di bawah ini

    // PATCH-BASED WALLHACK FEATURES
    #define WALLHACK_BoostFPS_Patch1 "0x884703C"          // BoostFPS patch point 1 - WallhackBoostFPS.h
    #define WALLHACK_BoostFPS_Patch2 "0x883480C"          // BoostFPS patch point 2 - WallhackBoostFPS.h
    #define WALLHACK_BoostFPS_Patch3 "0x8830880"          // BoostFPS patch point 3 - WallhackBoostFPS.h
    #define WALLHACK_BoostFPS_Patch4 "0x8830D08"          // BoostFPS patch point 4 - WallhackBoostFPS.h
    #define WALLHACK_Outline_Patch "0x6C95C8C"            // Outline wallhack patch - WallhackOutline.h
    // #define WALLHACK_EspNameOldBR_Patch1 "0x5719920"      // ESP Name Old BR patch 1 - WallhackEspNameOldBR.h
    // #define WALLHACK_EspNameOldBR_Patch2 "0x65C31E4"      // ESP Name Old BR patch 2 - WallhackEspNameOldBR.h
    #define WALLHACK_EspNameOldBR_DefaultBrazur "0x5CF9924"   // Default Brazur offset - WallhackEspNameOldBR.h
    #define WALLHACK_EspNameOldBR_DefaultPawn "0x57B8234"     // Default Pawn offset - WallhackEspNameOldBR.h
    #define WALLHACK_EspNameHealthBR_Patch1 "0x5CF9924"   // ESP Name Health BR patch 1 - WallhackEspNameHealthBR.h
    #define WALLHACK_EspNameHealthBR_Patch2 "0x91518A8"   // ESP Name Health BR patch 2 - WallhackEspNameHealthBR.h
    #define WALLHACK_EspNameColorBR_Patch1 "0x5CF9924"    // ESP Name Color BR patch 1 - WallhackEspNameColorBR.h
    // #define WALLHACK_EspNameColorBR_Patch2 "0x65C31E4"    // ESP Name Color BR patch 2 - WallhackEspNameColorBR.h
    // #define WALLHACK_EspNameColorMP_Patch1 "0x5719920"    // ESP Name Color MP patch 1 - WallhackEspNameColorMP.h
    // #define WALLHACK_EspNameColorMP_Patch2 "0x65C31E4"    // ESP Name Color MP patch 2 - WallhackEspNameColorMP.h

    // HOOK-BASED WALLHACK FEATURES
    #define WALLHACK_Normal_OnRespawnPlayer "0x91C2F4C"   // GameBase_PlayerPawn__OnRespawnPlayer - WallhackNormal.h
    #define WALLHACK_Normal_ShowOcclusionEffect "0x8FF5580"  // GameBase_PlayerPawn__ShowFreeViewOcclustionEffect - WallhackNormal.h
    #define WALLHACK_EspScale_SetNameBloodScale "0x9150658"  // SetNameBloodScale function - WallhackEspScale.h
    #define WALLHACK_EspNameHealthMP_Hook "0x5285F68"     // ESP Name Health MP hook - WallhackEspNameHealthMP.h

    // RENDERING FUNCTIONS - Unity engine functions untuk ESP
    namespace Functions {
        constexpr unsigned int Transform_get_position = 0xAF305B0; // UnityEngine.Transform$$get_position
        constexpr unsigned int Camera_get_main = 0xAEDC90C; // UnityEngine.Camera$$get_main
        constexpr unsigned int Camera_WorldToScreenPoint = 0xAEDC4D0; // UnityEngine.Camera$$WorldToScreenPoint
        constexpr unsigned int GamePlay_get_MatchGame = 0x4BDE6A0; // GameEngine.GamePlay$$get_MatchGame
        constexpr unsigned int BaseGame_get_MatchInProgress = 0x759B1A4; // GameBase.BaseGame$$get_MatchInProgress
        constexpr unsigned int Pawn_GetRootTransform = 0x906E954; // GameBase.Pawn$$GetRootTransform
        constexpr unsigned int Pawn_GetHeadTransform = 0x906EC00; // GameBase.Pawn$$GetHeadTransform
        constexpr unsigned int Component_get_transform = 0xAEE1EE8; // UnityEngine.Component$$get_transform
        constexpr unsigned int Screen_get_height = 0xAF0B548; // UnityEngine.Screen$$get_height
        constexpr unsigned int Screen_get_width = 0xAF0B4D4; // UnityEngine.Screen$$get_width
        constexpr unsigned int Screen_get_dpi = 0xAF3CF70; // UnityEngine.Screen$$get_dpi
        constexpr unsigned int Input_get_touchCount = 0xAF12FDC; // UnityEngine.Input$$get_touchCount
        constexpr unsigned int Input_get_touchSupported = 0xAF130F0; // UnityEngine.Input$$get_touchSupported
        constexpr unsigned int Input_GetTouch = 0xAF12FF0; // UnityEngine.Input$$GetTouch
        constexpr unsigned int Input_GetKeyDownInt = 0xAF124C8; // UnityEngine.Input$$GetKeyDownInt
        constexpr unsigned int SystemInfo_get_deviceUniqueIdentifier = 0xAF452B4; // UnityEngine.SystemInfo$$get_deviceUniqueIdentifier
        constexpr unsigned int SystemInfo_get_deviceName = 0xAF452C8; // UnityEngine.SystemInfo$$get_deviceName
        constexpr unsigned int SystemInfo_get_deviceModel = 0xAF452DC; // UnityEngine.SystemInfo$$get_deviceModel

        // RESOURCE & FPS OPTIMIZATION - Quality settings dan frame rate control
        constexpr unsigned int SetQualityLevel = 0xAF2C2A8; // UnityEngine.QualitySettings$$SetQualityLevel
        constexpr unsigned int set_shadowDistance = 0xAF2C490; // UnityEngine.QualitySettings$$set_shadowDistance
        constexpr unsigned int set_shadows = 0xAF2C3B8; // UnityEngine.QualitySettings$$set_shadows
        constexpr unsigned int set_pixelLightCount = 0xAF2C340; // UnityEngine.QualitySettings$$set_pixelLightCount
        constexpr unsigned int set_enableLowQualitySettings = 0xAF11FA4; // UnityEngine.HierarchicalInstancedMeshRenderer$$set_enableLowQualitySettings
        constexpr uintptr_t set_trilinearFiltering = 0xAF2C6B4; // UnityEngine.QualitySettings$$set_trilinearFiltering
        constexpr unsigned int set_anisotropicFiltering = 0xAF2C68C; // UnityEngine.QualitySettings$$set_anisotropicFiltering
        constexpr unsigned int set_vSyncCount = 0xAF2C708; // UnityEngine.QualitySettings$$get_antiAliasing
        constexpr unsigned int GetMaxSupportedFrameRateLevel = 0x882FAC0; // GameEngine.SystemSetting$$GetMaxSupportedFrameRateLevel
        constexpr unsigned int GetMaxGraphicLevelByFrameRateLevel = 0x883203C; // GameEngine.SystemSetting$$GetMaxGraphicLevelByFrameRateLevel
        constexpr unsigned int GetMaxFrameRateLevel = 0x88307D4; // GameEngine.SystemSetting$$GetMaxFrameRateLevel
        constexpr unsigned int GetMaxSupportedFrameRateLevelForDevice = 0x8830880; // GameEngine.SystemSetting$$GetMaxSupportedFrameRateLevelForDevice
        // constexpr unsigned int get_Enable180FrameRate = 0x6BAD1B4; // GameEngine.SystemSetting$$get_Enable180FrameRate
        // constexpr unsigned int ClearGraphicsStyles = 0x84BB7D0; // GameEngine_SystemSetting__ClearGraphicsStyles
        // constexpr unsigned int SetOverrideBCGS = 0x7A8ED60; // CODPostEffectChain__SetOverrideBCGS
        constexpr unsigned int GetAppliedUltraFrameRateValues = 0x883090C; // GameEngine.SystemSetting$$GetAppliedUltraFrameRateValues
        constexpr unsigned int SetCurFrameRateLevel = 0x882F978; // GameEngine.SystemSetting$$set_CurFrameRateLevel
        constexpr unsigned int IsUltraFrameRateCustomized = 0x882FAB8; // GameEngine.SystemSetting$$get_IsUltraFrameRateCustomized
        constexpr unsigned int GetFrameRateValueFromFrameRateLevel = 0x8830D08; // GameEngine.SystemSetting$$GetFrameRateValue
        constexpr unsigned int Application_SetTargetFrameRate = 0xAED5394; // UnityEngine.Application$$set_targetFrameRate
        constexpr unsigned int SetFramerateCustomizeValue = 0x8841604; // GameEngine.SystemSetting$$set_FramerateCustomizeValue
        // constexpr unsigned int Enable180FrameRate = 0x6BAD1B4; // GameEngine.SystemSetting$$get_Enable180FrameRate
        constexpr unsigned int QualitySettings_SetFrameTiming = 0xAF2C76C; // UnityEngine.QualitySettings$$set_streamingMipmapsEnableAsyncUpload
        constexpr unsigned int AutoAdjustFrameRate = 0x882FD14; // GameEngine.SystemSetting$$AutoAdjustFrameRate
        constexpr unsigned int SetEnableVSync = 0x883195C; // GameEngine.SystemSetting$$SetEnableVSync
        constexpr unsigned int CheckFrameRateBlacklist = 0x88311C4; // GameEngine.SystemSetting$$CheckFrameRateBlacklist
        // constexpr unsigned int GetUltraFrameRateFinalFPS = 0x6BAD0D8; // GameEngine.SystemSetting$$GetUltraFrameRateFinalFPS
        constexpr unsigned int GetFrameRateValue = 0x8830D08; // GameEngine.SystemSetting$$GetFrameRateValue
        constexpr unsigned int UltraFrameRateBR = 0x8830904; // GameEngine.SystemSetting$$get_UltraFrameRateBR
        constexpr unsigned int SetFrameRate = 0x88315D8; // GameEngine.SystemSetting$$SetFrameRate
        constexpr unsigned int UpdateRotFrameRate = 0x8831E1C; // GameEngine.SystemSetting$$UpdateRotFrameRate
        constexpr unsigned int GetExtremeFrameRateNumInDifferentGameMode = 0xA179AB0; // GameSettings_FrameLevelContainer__GetExtremeFrameRateNumInDifferentGameMode
        // constexpr unsigned int ShouldSupport180FrameRate = 0x6BAD870; // GameEngine_SystemSetting__ShouldSupport180FrameRate
        // constexpr unsigned int set_Enable180FrameRate = 0x6BAD8C8; // GameEngine_SystemSetting__set_Enable180FrameRate
        constexpr unsigned int ApplyFrameRateWhenCurQTooHigh = 0xA179F40; // GameSettings_FrameLevelContainer__ApplyFrameRateWhenCurQTooHigh
        constexpr unsigned int SetUltraFrameRateDeviceInfo = 0x882FEBC; // GameEngine_SystemSetting__SetUltraFrameRateDeviceInfo
        // constexpr unsigned int GetMaxUltraFrameRateValue = 0x6BADEE0; // GameEngine_SystemSetting__GetMaxUltraFrameRateValue
        constexpr unsigned int AndroidModifyPreferredDisplayMode = 0x8831C80; // GameEngine_SystemSetting__AndroidModifyPreferredDisplayMode
        constexpr unsigned int OpenHarmonySetFrameRate = 0x8831DC0; // GameEngine_SystemSetting__OpenHarmonySetFrameRate
        constexpr unsigned int ResetEnableLobbyDynamicFrameRate = 0x8830760; // GameEngine_SystemSetting__ResetEnableLobbyDynamicFrameRate
        constexpr unsigned int get_EnableLobbyDyanmicFrameRate = 0x8830458; // GameEngine_SystemSetting__get_EnableLobbyDyanmicFrameRate
        constexpr unsigned int ShouldSupportLobbyDynamicFrameRate = 0x8830568; // GameEngine_SystemSetting__ShouldSupportLobbyDynamicFrameRate
        constexpr unsigned int SetupProperGraphicSettingForFrameRateLevel_FrameLevel = 0xA179CA8; // GameSettings_FrameLevelContainer__SetupProperGraphicSettingForFrameRateLevel
        constexpr unsigned int SetupProperGraphicSettingForFrameRateLevel_Settings = 0xA64ABEC; // GameSettings_SettingsNewSystem2Controller_Base__SetupProperGraphicSettingForFrameRateLevel
        constexpr unsigned int ApplyFrameRateWhenCurQTooHigh_FrameLevel = 0xA179F40; // GameSettings_FrameLevelContainer__ApplyFrameRateWhenCurQTooHigh
        constexpr unsigned int ApplyFrameRateWhenCurQTooHigh_Settings = 0xA64AE9C; // GameSettings_SettingsNewSystem2Controller_Base__ApplyFrameRateWhenCurQTooHigh
        constexpr unsigned int set_CurFrameRateLevel = 0x882F978; // GameEngine_SystemSetting__set_CurFrameRateLevel
        constexpr unsigned int OnFrameRateToggleChange = 0xA64A808; // GameSettings_SettingsNewSystem2Controller_Base__OnFrameRateToggleChange
    }
}

// Legacy compatibility

#endif // ARCAMOD_GAME_OFFSET_DEFINITIONS_H
#define OFFSET_ENEMYPAWNS Offsets::BaseGame::EnemyPawns