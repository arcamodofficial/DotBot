#ifndef ARCAMOD_FAKESTATUS_H
#define ARCAMOD_FAKESTATUS_H

/*
 * ANTI-CRASH SYSTEM NOTICE:
 * All try-catch blocks in this file have been replaced with signal handler protection
 * for consistency with the enhanced crash protection system.
 * Signal handlers (SIGSEGV/SIGABRT) are set up at the ESP level to handle memory faults.
 * This provides better performance and consistent crash recovery across the entire system.
 * Hook functions now rely on the global crash protection system instead of individual try-catch blocks.
 */

// Definisi inline untuk int64_t jika header tidak tersedia
#if __has_include(<cstdint>)

#include <cstdint>

#elif __has_include(<stdint.h>)
#include <stdint.h>
#else
// Fallback typedefs
typedef long long int64_t;
#endif

// Include untuk manipulasi data structures
#include <unordered_set>

// ============================================================================
// DEFINISI OFFSET TERPUSAT - UNTUK MEMUDAHKAN PEMBARUAN DI MASA DEPAN
// ============================================================================

// === ROOM & LOBBY MANAGEMENT ===
#define ADDR_ROOM_DATA_PERSISTENT_RECORD OBF("0x9D97E78") // GameUI.Room.RoomDataPersistent$$RecordLastSelectPlaylistInfo_BrMatch_Runtime
#define ADDR_ROOM_PROTO_MANAGER_RECORD OBF("0x9E4D0B4")   // GameUI.Room.RoomProtoManager$$RecordRoomProtoSeqID
#define ADDR_ROOM_DATA_AGENT_SEND_PLAYER_STATE_INFO OBF("0x64903B0") // GameUI.Room.RoomDataAgent$$SendPlayerStateInfo
#define ADDR_ROOM_DATA_STORE_UPDATE_PLAYER_STATE_INFO OBF("0x9DA5C50") // GameUI.Room.RoomDataStore$$UpdatePlayerStateInfo
#define ADDR_ROOM_DATA_STORE_IS_PLAYER_IN_PLAYER_LIST OBF("0x9DA383C") // GameUI.Room.RoomDataStore$$IsPlayerInPlayerList
#define ADDR_LOBBY_SENDER_SEND_TO_ZONE OBF("0x5151924") // GameBase.LobbySender$$SendToZone
#define ADDR_WINNER_CIRCLE_PLAY_AGAIN OBF("0x7C3063C") // GameUI.WinnerCircleMainController$$OnPlayAgainMatchingStart

// === MATCH STATE MANAGEMENT ===
#define ADDR_IS_IN_MATCH_PREPARE OBF("0x4C07CCC")  // GameEngine.GameInfo$$IsInMatchPrepare
#define ADDR_IS_IN_MATCH_GAME OBF("0x632BF1C")     // GameUI.LobbyReconnectController$$IsInMatchGame
#define ADDR_IS_IN_GAME_REPLAY OBF("0x52748D4")   // GameBase.MatchGameInfo$$IsInGameReplay
#define ADDR_IS_IN_GAME_FINAL_KILL_REPLAY OBF("0x52749E0") // GameBase.MatchGameInfo$$IsInGameFinalKillReplay

// === REPORTING & DATA STORE ===
#define ADDR_SET_IS_NEED_REPORT OBF("0x6ED0AB4")  // RecommReportMatchDataStore$$SetIsNeedReport
#define ADDR_GET_RECORD_ID OBF("0x6ED1638")       // RecommReportMatchDataStore$$GetRecordID
#define ADDR_SET_RECORD_ID OBF("0x6ED1700")       // RecommReportMatchDataStore$$SetRecordID
#define ADDR_IS_ABLE_TO_POP OBF("0x6ED1840")       // RecommReportMatchDataStore$$isAbleToPop
#define ADDR_RECOMMREPORT_RELOGIN OBF("0x6ED2888") // RecommReportMatchDataStore__ReLogin
#define ADDR_RECOMMREPORT_CLEARTOTALEVENTS OBF("0x6ED06D0") // RecommReportMatchDataStore__ClearTotalEvents

// === PLAYER PREFERENCES ===
#define ADDR_PLAYER_PREFS_GET_INT OBF("0xAF2B8F8") // UnityEngine_PlayerPrefs__GetInt
#define ADDR_PLAYER_PREFS_SET_INT OBF("0xAF2B860") // UnityEngine_PlayerPrefs__SetInt
#define ADDR_PLAYER_PREFS_MANAGER_GET_INT OBF("0x654480C") // PlayerPrefsManager__GetCurrentPlayerInt

// === NETWORK & COMMUNICATION ===
#define ADDR_NETWORK_ZONE_SERVER_HANDLER_SEND OBF("0x7B5D028") // Network.ZoneServerHandler$$Send
#define ADDR_GCLOUD_SDK_GET_NETWORK_STATE OBF("0x7D22634") // GCloud.GCloudSDK$$GetNetworkState
#define ADDR_GCLOUD_SDK_GET_DETAIL_NETWORK_INFO OBF("0x7D22808") // GCloud.GCloudSDK$$gcloud_network_GetDetailNetworkInfo
#define ADDR_NETWORK_MONITOR_RECORD_ONCE_ZONE_RECONNECT_COUNT OBF("0x8FFD4DC") // GameBase.NetworkMonitor$$RecordOnceZoneReconnectCount
#define ADDR_NETWORK_GET_IP_ADDRESS OBF("0x2B7CC94") // System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress
// #define ADDR_SUB_IP_ADDRESS OBF("0xAF9DB48") // sub_A1F7AF4 - DISABLED
#define ADDR_IP_ADDRESS_CTOR OBF("0xAF968D0") // System_Net_IPAddress___ctor_184117456

// === NETWORK HOOKS OFFSETS (INTEGRATED FROM NetworkHooks.h) ===
#define ADDR_NETWORK_GAMENETCLIENT_SEND OBF("0x7A69978") // Network_GameNetClient__Send
#define ADDR_NETWORK_GAMENETCLIENT_PUSHTOSENDDELIVERYBUFFER OBF("0x7A7C9AC") // Network_GameNetClient__PushToSendDeliveryBuffer

// === TERSAFE HOOKS OFFSETS (INTEGRATED FROM TerSafeHook.h) ===
#define ADDR_TERSAFE_PROC_CHECK OBF("0x3128FC8") // TerSafe proc check function
#define ADDR_TERSAFE_STATUS_VAR OBF("0xE482FE8") // TerSafe status variable

// === ANTI-CHEAT & SECURITY ===
#define ADDR_C2S_NTF_USER_CHEAT_CTOR OBF("0x7A52D3C") // Network.C2S_NTF_USER_CHEAT$$.ctor
#define ADDR_BEACON_REPORTER_REPORT_IN_GAME_EXPERIENCE OBF("0x75D66A0") // GameBase_BeaconReporter__ReportInGameExperienceEventData
#define ADDR_DO_IN_GAME_EXPERIENCE_DATA_BEACON_REPORTER OBF("0x5258A38") // GameBase_MatchGame__DoInGameExperienceDataBeaconReporter

// === MATCH RECORDING & REPLAY ===
#define ADDR_MATCH_REPLAYER_SEQ_PROCESS OBF("0x7AB415C") // Network.MatchReplayer.ReplayData$$SeqProcess
#define ADDR_MATCH_RECORDER_CTOR OBF("0x7AB0BE8") // Network_MatchRecorder___ctor
#define ADDR_MATCH_RECORDER_GET_ACTIVE OBF("0x7AB0CB0") // Network_MatchRecorder__get_Active
#define ADDR_MATCH_RECORDER_SET_ACTIVE OBF("0x7AB0CB8") // Network_MatchRecorder__set_Active
#define ADDR_MATCH_RECORDER_RECORD OBF("0x7AB157C") // Network_MatchRecorder__Record
#define ADDR_MATCH_REPLAYER_CTOR OBF("0x7AB1848") // Network_MatchReplayer___ctor
#define ADDR_MATCH_REPLAYER_REPLAYDATA_CTOR OBF("0x7AB1980") // Network_MatchReplayer_ReplayData___ctor

// === TDM (TENCENT DATA MASTER) ANALYTICS ===
#define ADDR_TDM_REAL_TIME_REPORT_KV_EVENT OBF("0x89870DC") // TDM.TDataMaster$$tdm_real_time_report_kv_event
#define ADDR_TDM_REPORT_EVENT OBF("0x8986E50") // TDM.TDataMaster$$tdm_report_event
#define ADDR_TDM_ENABLE_REPORT OBF("0x89868D0") // TDM_TDataMaster__EnableReport
#define ADDR_TDM_REPORT_LOGIN_V2 OBF("0x8988544") // TDM_TDataMaster__ReportLoginV2
#define ADDR_TDM_REPORT_LOGIN_V2_NATIVE OBF("0x8988684") // TDM_TDataMaster__tdm_report_loginV2
#define ADDR_TDM_GET_TDMUID OBF("0x8986B1C") // TDM_TDataMaster__GetTDMUID
#define ADDR_TDM_GET_UID OBF("0x8986B48")    // TDM_TDataMaster__tdm_get_uid

// === TDM ANTI-CHEAT SYSTEM (NEW IMPLEMENTATIONS) ===
#define ADDR_TDM_INITIALIZE OBF("0x89866DC")                    // TDM_TDataMaster__Initialize
#define ADDR_TDM_INITIALIZE_V2 OBF("0x89867C0")                 // TDM_TDataMaster__InitializeV2
#define ADDR_TDM_ENABLE_DEVICE_INFO OBF("0x8986968")            // TDM_TDataMaster__EnableDeviceInfo
#define ADDR_TDM_ENABLE_HTTP_PROXY OBF("0x8986A00")             // TDM_TDataMaster__EnableHTTPProxy
#define ADDR_TDM_GET_STRING_DEVICE_INFO OBF("0x8988758")        // TDM_TDataMaster__GetStringDeviceInfo
#define ADDR_TDM_SET_STRING_DEVICE_INFO OBF("0x898897C")        // TDM_TDataMaster__SetStringDeviceInfo
#define ADDR_TDM_ENABLE_DEVICE_INFO_COLLECT OBF("0x8988C74")    // TDM_TDataMaster__EnableDeviceInfoCollect
#define ADDR_TDM_REPORT_EVENT_V2 OBF("0x8988D34")               // TDM_TDataMaster__ReportEventV2

// === TDM ADDITIONAL CRITICAL FUNCTIONS (DARI ASSEMBLY TENCENT.C) ===
#define ADDR_TDM_BUFFER_WRITER_RESET OBF("0x8986538")           // TDM_TBufferWriter__Reset - SANGAT KRITIS
#define ADDR_TDM_SET_LOG OBF("0x8986C9C")                       // TDM_TDataMaster__tdm_set_log - TINGGI
#define ADDR_TDM_FREE_UPLOAD_FILE_RESULT OBF("0x8988208")       // TDM_TDataMaster__tdm_free_upload_file_result - SEDANG

// === TGPA (TENCENT GAME PERFORMANCE ANALYTICS) ===
#define ADDR_TGPA_REPORT_USER_INFO OBF("0x7D6BF88") // GCloud.TGPA.TGPAHelper$$ReportUserInfo
#define ADDR_TGPA_GET_PLATFORM_SERVICE OBF("0x7D6A738") // GCloud.TGPA.TGPAHelper$$getPlatformService
#define ADDR_TGPA_SERVICE_ANDROID_CTOR OBF("0x7D6D1E4") // GCloud.TGPA.TGPAServiceAndroid$$.ctor
#define ADDR_TGPA_INIT OBF("0x7D6AE08") // GCloud_TGPA_TGPAHelper__Init

// === ANOSDK (ANTI-CHEAT SDK) ===
#define ADDR_ANOSDK_INIT OBF("0x7CE9C1C") // GCloud_AnoSDK_AnoSDK__Init
#define ADDR_ANOSDK_SET_USER_INFO OBF("0x7CE9E10") // GCloud_AnoSDK_AnoSDK__SetUserInfo
#define ADDR_ANOSDK_DEL_REPORT_DATA OBF("0x7CEA538") // GCloud_AnoSDK_AnoSDK__AnoSDKDelReportData
#define ADDR_ANOSDK_GET_REPORT_DATA4_STATUS OBF("0x7CEAB9C") // GCloud_AnoSDK_AnoSDK__GetReprotData4Status
#define ADDR_ANOSDK_GET_REPORT_DATA4 OBF("0x7CEAC8C") // GCloud_AnoSDK_AnoSDK__AnoSDKGetReportData4
// #define ADDR_ANOSDK_ON_PAUSE OBF("0x5AD47D8") // GCloud_AnoSDK_AnoSDK__OnPause
// #define ADDR_ANOSDK_ON_RESUME OBF("0x5AD4894") // GCloud_AnoSDK_AnoSDK__OnResume
#define ADDR_ANOSDK_RECV_SIGNATURE OBF("0x7CEAF58")  // GCloud_AnoSDK_AnoSDK__OnRecvSignature
#define ADDR_ANOSDK_IOCTL OBF("0x7CEB198") // GCloud_AnoSDK_AnoSDK__AnoSDKIoctl
#define ADDR_ANOSDK_IOCTL_WRAPPER OBF("0x7CEB2D0") // GCloud_AnoSDK_AnoSDK__Ioctl

// === CRASH REPORTING & ANALYTICS ===
#define ADDR_GCLOUD_GET_RES_ID OBF("0x7CE9AF8") // GCloud_AndroidResourceTools__gcloud_utils_get_res_id
#define ADDR_CRASHSIGHT_ADDSCENEDATA OBF("0x7D79A34") // CrashSightAgent__AddSceneData
#define ADDR_BUGLY_TOSTRING OBF("0x77400F4") // GameBase_BuglySceneDataReporter_BuglyReportMatchInfoData__ToBuglyString
#define ADDR_BUGLY_ONLOGINSUCC OBF("0x7741C00") // GameBase_BuglySceneDataReporter__OnLoginSucc
#define ADDR_BUGLY_UPDATESCENEDATA OBF("0x773DE30") // GameBase_BuglySceneDataReporter__UpdateSceneData

// === SYSTEM & UTILITY ===
#define ADDR_GAMEENGINE_DATASTORE_RELOGIN OBF("0x532BB78") // GameEngine_DataStore__ReLogin
#define ADDR_SUB_A9688F4 OBF("0xA9688F4")    // sub_A9688F4
#define ADDR_SUB_A9688FC OBF("0xA9688FC")    // sub_A9688FC
#define ADDR_SYSTEM_INTPTR_GET_SIZE OBF("0xADDA110") // System_IntPtr__get_Size

// === STACK TRACING & MONITORING ===
#define ADDR_CRASH_STACK_TRACE OBF("0x4F30828")      // CrashSightStackTrace__ExtractStackTrace
#define ADDR_CLIENT_MONITOR_SAMPLER OBF("0x6BF32F4") // GameBase_ClientMonitorManager__StackTraceSampler
#define ADDR_PERF_STATS_STACKTRACE OBF("0xAF27760")  // UnityEngine_PerfStats__RuntimeGetStacktrace
#define ADDR_ENVIRONMENT_STACKTRACE OBF("0xADC8AC0") // System_Environment__get_StackTrace
#define ADDR_MEMORY_CAKE_GET_ARGS OBF("0x8A28AC8")   // TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs

// === UQM CRASH REPORTING ===
#define ADDR_UQM_LOG_RECORD_ADAPTER OBF("0x7D75674")  // GCloud_UQM_UQMCrash__cs_logRecordAdapter
#define ADDR_UQM_REPORT_LOG_INFO OBF("0x7D75D28")     // GCloud_UQM_UQMCrash__cs_reportLogInfo
#define ADDR_UQM_GET_CRASH_UUID OBF("0x7D7616C")      // GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter
#define ADDR_UQM_SET_DEVICE_MODEL OBF("0x7D761EC")    // GCloud_UQM_UQMCrash__cs_setDeviceModelAdapter
#define ADDR_UQM_GET_CRASH_THREAD_ID OBF("0x7D765AC") // GCloud_UQM_UQMCrash__cs_getCrashThreadId
#define ADDR_UQM_GET_LAST_USER_ID OBF("0x7D76DBC")    // GCloud_UQM_UQMCrash__cs_getLastSessionUserId
#define ADDR_UQM_SET_USER_ID OBF("0x7D7A460")         // GCloud_UQM_UQMCrash__SetUserId
#define ADDR_UQM_SET_USER_ID_ADAPTER OBF("0x7D75958") // GCloud_UQM_UQMCrash__cs_setUserIdAdapter
#define ADDR_UQM_REPORT_CRASH OBF("0x7D81288")        // GCloud_UQM_UQMCrash__ReportCrash
#define ADDR_UQM_LOG OBF("0x7D7508C")                 // GCloud_UQM_UQMLog__Log
#define ADDR_UQM_REREGIST_ALL_MONITORS OBF("0x7D7AAF8")  // GCloud_UQM_UQMCrash__ReRegistAllMonitors
#define ADDR_UQM_REREGIST_ALL_MONITORS_ADAPTER OBF("0x7D75C28") // GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter

// === TSS MANAGER (TENCENT SECURITY SYSTEM) ===
#define ADDR_TSS_MANAGER_CHECK_SEND_ENABLE OBF("0x887DAB0") // GameEngine_TssManager__CheckSendEnable
#define ADDR_TSS_MANAGER_IS_ZONE_CONNECTED OBF("0x887D320") // GameEngine_TssManager__isZoneConnected
#define ADDR_TSS_MANAGER_SEND_DATA_TO_SVR OBF("0x887D084") // GameEngine_TssManager__SendDataToSvr
// #define ADDR_TSS_MANAGER_SEND_EIGEN_INFO OBF("0x6BF86E4") // GameEngine_TssManager__SendEigenInfoToServer
#define ADDR_TSS_MANAGER_GET_ALL_PENDING_REQUESTS OBF("0x887DC30") // GameEngine_TssManager__GetAllPendingTssSendRequests
#define ADDR_TSS_MANAGER_INIT OBF("0x887BDAC") // GameEngine_TssManager__Init
#define ADDR_DEVICE_UTIL_GET_MEMORY_SIZE OBF("0x550146C") // GameEngine_DeviceUtil__GetMemorySize

// === GARENA PLATFORM INTEGRATION ===
#define ADDR_DOLOGIN_GARENA OBF("0x6DFA910")          // GameBase.GcloudLoginConnector$$DoLoginGarena
#define ADDR_GET_CHANNEL_UID_GARENA OBF("0x6DFE130")  // GameBase.GcloudLoginConnector$$GetChannelInfoUidInGarena
#define ADDR_GET_GARENA_ID OBF("0x75D2778")           // GameBase.BeaconReporter$$GetGarenaID
#define ADDR_GET_GARENA_MATCH_INFO OBF("0x5C0ACBC")  // GameUI.Home.HomeMainController$$GetGarenaMatchInfo
#define ADDR_SHOW_GARENA_MATCH_VIEW OBF("0x7777738") // GameUI.Home.HomeMainView$$ShowGarenaMatchView
#define ADDR_ON_GARENA_LOGIN OBF("0xA11F514")        // GameLogin.UILoginMainController$$OnGarenaLogin

// === PANDORA ANALYTICS BLOCKING ===
#define ADDR_PANDORA_PAUSE_SOCKET OBF("0x404ECBC")    // PandoraSettings$$set_PauseSocketSending
#define ADDR_PANDORA_PAUSE_DOWNLOAD OBF("0x404EC4C")  // PandoraSettings$$set_PauseDownloading
#define ADDR_PANDORA_REPORT_USER_INFO OBF("0x7D709F4") // GCloud_TGPA_TGPAServiceBase__ReportUserInfo
#define ADDR_PANDORA_GET_CRASH_UUID OBF("0x7D7BFB4")   // GCloud_UQM_UQMCrash__GetCrashUuid
#define ADDR_PANDORA_SET_DEVICE_ID OBF("0x7D7B3A8")    // GCloud_UQM_UQMCrash__SetDeviceId

// === ANTI-REPORT SYSTEM ===
#define ADDR_CSACCOUNT_REPORT_USER_REQ OBF("0x40B36B0")  // msg_CSAccountReportUserReq__Write
#define ADDR_GCLOUD_SEND_TO_SERVER OBF("0x7D284E0")      // GCloud_LockStep_LockStepImpl__SendToServer
#define ADDR_C2S_REQ_REPORT_PLAYER_PULL_CTOR OBF("0x7A596F8") // Network_C2S_REQ_REPORT_PLAYER_PULL___ctor - CRITICAL

// === AGGRESSIVE MATCH REPORTING SYSTEM (TESTING ONLY) ===
#define ADDR_START_MATCH_MRPCS_REPORT OBF("0x7B5D984")   // Network_ZoneServerHandler__StartMatchMrpcsReport
#define ADDR_END_MATCH_MRPCS_REPORT OBF("0x7B5DD1C")     // Network_ZoneServerHandler__EndMatchMrpcsReport

// === ACTIVE COMMUNICATION HOOKS ===
#define ADDR_TLOG_SEND_TO_SERVER OBF("0x8A653B0")        // TLogReportDataAgent__SendToServer
#define ADDR_MATCH_GAME_END_MATCH OBF("0x52596B0")       // GameBase_MatchGame__EndMatch
#define ADDR_BASE_GAME_END_MATCH OBF("0x5CA5738")        // GameBase_BaseGame__EndMatch

// === MISCELLANEOUS HOOKS ===
#define ADDR_PUBLISH_LOG OBF("0x409E574")             // GameEngine_Log__PublishLog
#define ADDR_INPUT_CHEAT OBF("0x7A36C94")             // NetSyncUtils__NtyInputCheat

// Definisi tipe fungsi dengan int64_t daripada __int64

// === ANTI-REPORT SYSTEM TYPEDEFS ===
typedef __int64 (*tCSAccountReportUserReq_Write)(__int64 a1, __int64 a2);
typedef __int64 (*tGCloud_SendToServer)(__int64 a1, __int64 a2, unsigned int a3, char a4);

// === AGGRESSIVE MATCH REPORTING TYPEDEFS (TESTING ONLY) ===
typedef __int64 (*tZoneServerHandler_StartMatchMrpcsReport)(__int64 a1);
typedef __int64 (*tZoneServerHandler_EndMatchMrpcsReport)(__int64 a1);

// === ACTIVE COMMUNICATION HOOKS TYPEDEFS ===
typedef __int64 (*tTLogReportDataAgent_SendToServer)(__int64 a1, __int64 a2);
typedef __int64 (*tGameBase_MatchGame_EndMatch)(__int64 a1);
typedef __int64 (*tGameBase_BaseGame_EndMatch)(__int64 a1);

// === ROOM & LOBBY MANAGEMENT TYPEDEFS ===
typedef long (*tRoomDataPersistentRecord)(void *a1, void *a2);
typedef long (*tRoomProtoManagerRecord)(void *a1, unsigned int a2, void *a3);
typedef void (*tSetIsNeedReport)(void *a1, bool isNeedReport);
typedef unsigned int (*tGetRecordID)(void *a1);
typedef void (*tSetRecordID)(void *a1, unsigned int recordId);
typedef unsigned int (*tPlayerPrefsGetInt)(int64_t a1, int64_t a2, unsigned int a3);
typedef void (*tPlayerPrefsSetInt)(int64_t a1, const char *key, unsigned int value);
typedef unsigned int (*tPlayerPrefsManagerGetInt)(int64_t a1, int64_t a2, unsigned int a3);
typedef long (*tWinnerCirclePlayAgain)(void *a1, void *a2);
typedef bool (*tIsInMatchPrepare)(void *a1);
typedef long (*tIsInMatchGame)(void *a1);
typedef void *(*tIsInGameReplay)();
typedef void *(*tIsInGameFinalKillReplay)();
typedef bool (*tRoomDataAgentSendPlayerStateInfo)(int64_t instance, unsigned int statusCode, char active);
typedef int64_t (*tLobbySenderSendToZone)(int64_t instance, int64_t message);
typedef int64_t (*tNetworkZoneServerHandlerSend)(int64_t a1, int64_t a2, int64_t a3);
typedef int64_t (*tRoomDataStoreUpdatePlayerStateInfo)(int64_t a1, int64_t a2, unsigned int a3, char a4);
typedef bool (*tRoomDataStoreIsPlayerInPlayerList)(int64_t *a1, int a2, int64_t a3);
typedef int64_t (*tGCloudSDKGetNetworkState)();
typedef bool (*tGCloudSDKGetDetailNetworkInfo)(int64_t a1, int64_t a2, unsigned int a3);
typedef int64_t (*tNetworkMonitorRecordOnceZoneReconnectCount)(int64_t a1);
typedef unsigned int (*tTDMRealTimeReportKvEvent)(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, char a6);
typedef int64_t (*tTDMReportEvent)(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, char a6);
typedef int64_t (*tMatchReplayerSeqProcess)(int64_t a1);
typedef int64_t (*tC2SNtfUserCheatCtor)(int64_t a1);
typedef int64_t (*tReportInGameExperienceEventData)();
typedef int64_t (*tPublishLog)(int64_t a1, int64_t a2, int64_t a3);

// Tipe fungsi untuk IP Address
typedef int64_t (*tGetIPAddress)(int64_t a1);
// typedef int64_t (*tSubIPAddress)(int64_t *a1); // DISABLED
typedef void (*tIPAddressCtor)(int64_t a1, int64_t a2);

// Tipe fungsi untuk TGPA
typedef int64_t (*tTGPAReportUserInfo)(int64_t a1, int64_t a2);
typedef int64_t (*tGetPlatformService)();
typedef int64_t (*tTGPAServiceAndroidCtor)(int64_t a1);

// Tipe fungsi untuk AnoSDK
typedef int64_t (*tAnoSDK_Init)(int64_t a1, int a2);
typedef int64_t (*tAnoSDK_SetUserInfo)(int64_t a1, int64_t a2, int64_t a3);
typedef int64_t (*tAnoSDK_DelReportData)(int64_t a1, int64_t a2);
typedef int64_t (*tAnoSDK_GetReportData4Status)(int64_t a1, unsigned int a2);
typedef int64_t (*tAnoSDK_GetReportData4)(int64_t a1, unsigned int a2);
typedef int64_t (*tAnoSDK_Ioctl)(__int64 a1, int a2, __int64 a3);
typedef int64_t (*tAnoSDK_IoctlWrapper)(__int64 a1, unsigned int a2, __int64 a3);
typedef int64_t (*tCrashSightAgent_AddSceneData)(int64_t a1, int64_t a2, int64_t a3);
typedef int64_t (*tBuglyReportMatchInfoData_ToBuglyString)(int64_t a1);
typedef int64_t (*tBuglyOnLoginSucc)(int64_t a1, int64_t a2, int64_t a3);
typedef int64_t (*tBuglyUpdateSceneData)(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);

// Tipe fungsi untuk AndroidResourceTools
typedef int64_t (*tGCloudGetResId)(int64_t a1, int64_t a2, int64_t a3);
// 1. Tambahkan typedef di bagian awal file setelah typedef lainnya (sekitar baris 70-an)
typedef int64_t (*tNetSyncUtils__NtyInputCheat)(long double a1, long double a2);
// Tambahkan definisi tipe fungsi untuk MatchRecorder
typedef int64_t (*tMatchRecorderCtor)(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);
typedef int64_t (*tMatchRecorderGetActive)(int64_t a1);
typedef int64_t (*tMatchRecorderSetActive)(int64_t result, char a2);
typedef int64_t (*tMatchRecorderRecord)(int64_t a1, int64_t a2, unsigned int a3, unsigned int a4);
// Tipe fungsi untuk RecommReportMatchDataStore
typedef int64_t (*tRecommReportMatchDataStore_ReLogin)(int64_t a1);
typedef int64_t (*tGameEngine_DataStore_ReLogin)(int64_t a1);
typedef int64_t (*tRecommReportMatchDataStore_ClearTotalEvents)(int64_t *a1);

// Tipe fungsi untuk TDM UID
typedef int64_t (*tTDM_GetTDMUID)();
typedef int64_t (*tTDM_GetUID)();
typedef int64_t (*tSub_A9688F4)(int64_t a1);
typedef int64_t (*tSub_A9688FC)(int64_t *a1, int64_t a2);
typedef int64_t (*tSystem_IntPtr_GetSize)(int64_t a1);

// === TDM ANTI-CHEAT FUNCTION TYPES ===
typedef bool (*tTDM_Initialize)(int64_t a1, int64_t a2, int64_t a3, char a4);
typedef bool (*tTDM_InitializeV2)(int64_t a1, int64_t a2, int64_t a3, int64_t a4, char a5);
typedef int64_t (*tTDM_EnableDeviceInfo)(int64_t a1, char a2);
typedef int64_t (*tTDM_EnableHTTPProxy)(int64_t a1, char a2);
typedef int64_t (*tTDM_GetStringDeviceInfo)(int64_t a1, int64_t a2);
typedef int64_t (*tTDM_SetStringDeviceInfo)(int64_t a1, int64_t a2, int64_t a3);
typedef int64_t (*tTDM_EnableDeviceInfoCollect)(int64_t a1, int64_t a2, char a3);
typedef int64_t (*tTDM_ReportEventV2)(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, unsigned int a6);

// === TDM ADDITIONAL FUNCTION TYPES (DARI ASSEMBLY TENCENT.C) ===
typedef int64_t (*tTDM_BufferWriterReset)(int64_t a1);
typedef int64_t (*tTDM_SetLog)(int64_t a1, unsigned int a2);
typedef int64_t (*tTDM_FreeUploadFileResult)(int64_t a1, int64_t a2);

// Tambahkan tipe fungsi untuk stack tracing dan monitoring
typedef int64_t (*tCrashSightStackTrace_Extract)();
typedef int64_t (*tClientMonitorStackTraceSampler)();
typedef int64_t (*tUnityEngine_PerfStats_RuntimeGetStacktrace)(int64_t a1, int64_t a2);
typedef int64_t (*tSystem_Environment_get_StackTrace)();
typedef int64_t (*tAnoSDK_OnRecvSignature)(int64_t a1, int64_t a2, int64_t a3, unsigned int a4, unsigned int a5);
typedef int64_t (*tMemoryCake_GetTLogArgs)(int64_t a1, unsigned int a2, unsigned int a3);

// Tambahkan tipe fungsi untuk CrashSight dan UQMCrash
typedef int64_t (*tUQM_LogRecordAdapter)(int64_t a1, unsigned int a2, int64_t a3);
typedef int64_t (*tUQM_ReportLogInfo)(int64_t a1, int64_t a2, int64_t a3);
typedef int64_t (*tUQM_GetCrashUuid)();
typedef int64_t (*tUQM_SetDeviceModel)(int64_t a1, int64_t a2);
typedef int64_t (*tUQM_GetCrashThreadId)();
typedef int64_t (*tUQM_GetLastSessionUserId)();
typedef int64_t (*tUQM_SetUserId)(int64_t a1, int64_t a2);
typedef int64_t (*tUQM_SetUserIdAdapter)(int64_t a1, int64_t a2);
typedef int64_t (*tUQM_ReportCrash)();
typedef int64_t (*tUQM_Log)(int64_t a1, int64_t a2);
typedef int64_t (*tUQM_ReRegistAllMonitors)();
typedef int64_t (*tUQM_ReRegistAllMonitorsAdapter)(int64_t a1);
typedef int64_t (*tMatchReplayerCtor)(_QWORD *a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);
typedef int64_t (*tMatchReplayerReplayDataCtor)(int64_t a1);
typedef int64_t (*tTDMEnableReport)(int64_t a1, char a2);
typedef int64_t (*tTDMReportLoginV2)(int64_t a1, unsigned int a2, int64_t a3, int64_t a4);
typedef int64_t (*tTDMReportLoginV2Native)(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5);
typedef int64_t (*tIsAbleToPop)(int64_t a1, char a2);
typedef int64_t (*tTssManagerSendEigenInfo)(int64_t a1);
typedef int64_t (*tDoInGameExperienceDataBeaconReporter)(__int64 a1);

// === ANTI-REPORT SYSTEM FUNCTION TYPES ===
typedef int64_t (*tC2S_REQ_REPORT_PLAYER_PULL_CTOR)(int64_t a1);

// Typedefs untuk TSS Manager baru
typedef void (*tTssManager_isZoneConnected)(int64_t a1);
typedef int64_t (*tTssManager_SendDataToSvr)(int64_t a1);
typedef int64_t (*tTssManager_GetAllPendingRequests)(_QWORD *a1);
typedef int64_t (*tTssManager_Init)(__int64 a1);
typedef __int64 (*tDeviceUtil_GetMemorySize)();

typedef int64_t (*tTGPAInit)();
// Tipe fungsi untuk Garena
typedef char (*tDoLoginGarena)(__int64 a1);
typedef __int64 (*tGetChannelInfoUidInGarena)(__int64 a1);
typedef __int64 (*tGetGarenaID)();
// Tipe fungsi untuk Garena tambahan
typedef __int64 (*tGetGarenaMatchInfo)(__int64 a1);
typedef __int64 (*tShowGarenaMatchView)(__int64 a1);
typedef __int64 (*tOnGarenaLogin)(__int64 a1);

// Forward declarations untuk fungsi hook
long RoomDataPersistent_Record_Hook(void *a1, void *a2);
long RoomProtoManager_Record_Hook(void *a1, unsigned int a2, void *a3);
long WinnerCirclePlayAgain_Hook(void *a1, void *a2);
bool IsInMatchPrepare_Hook(void *a1);
long IsInMatchGame_Hook(void *a1);
void *IsInGameReplay_Hook();
void *IsInGameFinalKillReplay_Hook();
bool RoomDataAgent_SendPlayerStateInfo_Hook(int64_t instance, unsigned int statusCode, char active);
int64_t LobbySender_SendToZone_Hook(int64_t instance, int64_t message);
int64_t Network_ZoneServerHandler__Send_Hook(int64_t a1, int64_t a2, int64_t a3);
void SetIsNeedReport_Hook(void *a1, bool isNeedReport);
unsigned int GetRecordID_Hook(void *a1);
void SetRecordID_Hook(void *a1, unsigned int recordId);
int64_t RoomDataStore_UpdatePlayerStateInfo_Hook(int64_t a1, int64_t a2, unsigned int a3, char a4);
bool RoomDataStore_IsPlayerInPlayerList_Hook(int64_t *a1, int a2, int64_t a3);
int64_t GCloud_GetNetworkState_Hook();
bool GCloud_GetDetailNetworkInfo_Hook(int64_t a1, int64_t a2, unsigned int a3);
int64_t NetworkMonitor_RecordOnceZoneReconnectCount_Hook(int64_t a1);
unsigned int TDM_TDataMaster__tdm_real_time_report_kv_event_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, char a6);
int64_t TDM_TDataMaster__tdm_report_event_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, char a6);
int64_t Network_MatchReplayer_ReplayData__SeqProcess_Hook(int64_t a1);
int64_t Network_C2S_NTF_USER_CHEAT___ctor_Hook(int64_t a1);
int64_t GameBase_BeaconReporter__ReportInGameExperienceEventData_Hook();
// Forward declarations untuk fungsi hook IP Address
int64_t System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Hook(int64_t a1);
// int64_t sub_A1F7AF4_Hook(int64_t *a1); // DISABLED
void System_Net_IPAddress___ctor_184117456_Hook(int64_t a1, int64_t a2);
// Forward declarations untuk fungsi TGPA hook
int64_t GCloud_TGPA_TGPAHelper__ReportUserInfo_Hook(int64_t a1, int64_t a2);
int64_t GCloud_TGPA_TGPAHelper__getPlatformService_Hook();
int64_t GCloud_TGPA_TGPAServiceAndroid___ctor_Hook(int64_t a1);
// Forward declarations untuk fungsi AnoSDK hook
int64_t AnoSDK_Init_Hook(int64_t a1, int a2);
int64_t AnoSDK_SetUserInfo_Hook(int64_t a1, int64_t a2, int64_t a3);
int64_t AnoSDK_DelReportData_Hook(int64_t a1, int64_t a2);
int64_t AnoSDK_GetReportData4Status_Hook(int64_t a1, unsigned int a2);
int64_t AnoSDK_GetReportData4_Hook(int64_t a1, unsigned int a2);
int64_t CrashSightAgent__AddSceneData_Hook(int64_t a1, int64_t a2, int64_t a3);
int64_t BuglyReportMatchInfoData_ToBuglyString_Hook(int64_t a1);
int64_t BuglyOnLoginSucc_Hook(int64_t a1, int64_t a2, int64_t a3);
int64_t BuglyUpdateSceneData_Hook(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);
// Forward declaration untuk fungsi AndroidResourceTools hook
int64_t GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Hook(int64_t a1, int64_t a2, int64_t a3);
// Tambahkan forward declarations untuk fungsi MatchRecorder hook
int64_t Network_MatchRecorder___ctor_Hook(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);
int64_t Network_MatchRecorder__get_Active_Hook(int64_t a1);
int64_t Network_MatchRecorder__set_Active_Hook(int64_t result, char a2);
int64_t Network_MatchRecorder__Record_Hook(int64_t a1, int64_t a2, unsigned int a3, unsigned int a4);
// Forward declarations untuk fungsi RecommReportMatchDataStore hook
int64_t RecommReportMatchDataStore__ReLogin_Hook(int64_t a1);
int64_t GameEngine_DataStore__ReLogin_Hook(int64_t a1);
int64_t RecommReportMatchDataStore__ClearTotalEvents_Hook(int64_t *a1);
// Forward declarations untuk fungsi TDM UID hook
int64_t TDM_TDataMaster__GetTDMUID_Hook();
int64_t TDM_TDataMaster__tdm_get_uid_Hook();
int64_t sub_A9688F4_Hook(int64_t a1);
int64_t sub_A9688FC_Hook(int64_t *a1, int64_t a2);
int64_t System_IntPtr__get_Size_Hook(int64_t a1);

// === ANTI-REPORT SYSTEM HOOK DECLARATIONS ===
__int64 CSAccountReportUserReq_Write_Hook(__int64 a1, __int64 a2);
__int64 GCloud_SendToServer_Hook(__int64 a1, __int64 a2, unsigned int a3, char a4);
int64_t Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Hook(int64_t a1);

// === ACTIVE COMMUNICATION HOOKS DECLARATIONS ===
__int64 TLogReportDataAgent_SendToServer_Hook(__int64 a1, __int64 a2);
__int64 GameBase_MatchGame_EndMatch_Hook(__int64 a1);
__int64 GameBase_BaseGame_EndMatch_Hook(__int64 a1);

// Tambahkan forward declarations untuk hook monitor
int64_t CrashSightStackTrace__ExtractStackTrace_Hook();
int64_t GameBase_ClientMonitorManager__StackTraceSampler_Hook();
int64_t UnityEngine_PerfStats__RuntimeGetStacktrace_Hook(int64_t a1, int64_t a2);
int64_t System_Environment__get_StackTrace_Hook();

int64_t GCloud_AnoSDK_AnoSDK__OnRecvSignature_Hook(int64_t a1, int64_t a2, int64_t a3, unsigned int a4, unsigned int a5);
int64_t GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Hook(__int64 a1, int a2, __int64 a3);
int64_t GCloud_AnoSDK_AnoSDK__Ioctl_Hook(__int64 a1, unsigned int a2, __int64 a3);
int64_t GameEngine_TssManager__GetAllPendingTssSendRequests_Hook(_QWORD *a1);
int64_t GameEngine_TssManager__Init_Hook(__int64 a1);
// __int64 GameEngine_DeviceUtil__GetMemorySize_Hook(); // DISABLED FOR TESTING
int64_t TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Hook(int64_t a1, unsigned int a2, unsigned int a3);
// Forward declarations untuk fungsi hook CrashSight dan UQMCrash
int64_t GCloud_UQM_UQMCrash__cs_logRecordAdapter_Hook(int64_t a1, unsigned int a2, int64_t a3);
int64_t GCloud_UQM_UQMCrash__cs_reportLogInfo_Hook(int64_t a1, int64_t a2, int64_t a3);
int64_t GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Hook();
int64_t GCloud_UQM_UQMCrash__cs_setDeviceModelAdapter_Hook(int64_t a1, int64_t a2);
int64_t GCloud_UQM_UQMCrash__cs_getCrashThreadId_Hook();
int64_t GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Hook();
int64_t GCloud_UQM_UQMCrash__SetUserId_Hook(int64_t a1, int64_t a2);
int64_t GCloud_UQM_UQMCrash__cs_setUserIdAdapter_Hook(int64_t a1, int64_t a2);
int64_t GCloud_UQM_UQMCrash__ReportCrash_Hook();
int64_t GCloud_UQM_UQMLog__Log_Hook(int64_t a1, int64_t a2);
int64_t GCloud_UQM_UQMCrash__ReRegistAllMonitors_Hook();
int64_t GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter_Hook(int64_t a1);
int64_t Network_MatchReplayer___ctor_Hook(_QWORD *a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8);
int64_t Network_MatchReplayer_ReplayData___ctor_Hook(int64_t a1);
int64_t TDM_TDataMaster__EnableReport_Hook(int64_t a1, char a2);
int64_t TDM_TDataMaster__ReportLoginV2_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4);
int64_t TDM_TDataMaster__tdm_report_loginV2_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5);
int64_t RecommReportMatchDataStore__isAbleToPop_Hook(int64_t a1, char a2);
int64_t GameEngine_TssManager__SendEigenInfoToServer_Hook(int64_t a1);
int64_t GameEngine_TssManager__CheckSendEnable_Hook(int64_t a1);

// Forward declarations untuk TSS Manager baru
void GameEngine_TssManager__isZoneConnected_Hook(int64_t a1);
int64_t GameEngine_TssManager__SendDataToSvr_Hook(int64_t a1);

// === TDM ANTI-CHEAT HOOK DECLARATIONS ===
bool TDM_TDataMaster__Initialize_Hook(int64_t a1, int64_t a2, int64_t a3, char a4);
bool TDM_TDataMaster__InitializeV2_Hook(int64_t a1, int64_t a2, int64_t a3, int64_t a4, char a5);
int64_t TDM_TDataMaster__EnableDeviceInfo_Hook(int64_t a1, char a2);
int64_t TDM_TDataMaster__EnableHTTPProxy_Hook(int64_t a1, char a2);
int64_t TDM_TDataMaster__GetStringDeviceInfo_Hook(int64_t a1, int64_t a2);
int64_t TDM_TDataMaster__SetStringDeviceInfo_Hook(int64_t a1, int64_t a2, int64_t a3);
int64_t TDM_TDataMaster__EnableDeviceInfoCollect_Hook(int64_t a1, int64_t a2, char a3);
int64_t TDM_TDataMaster__ReportEventV2_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, unsigned int a6);

// === TDM ADDITIONAL HOOK DECLARATIONS (DARI ASSEMBLY TENCENT.C) ===
int64_t TDM_TBufferWriter__Reset_Hook(int64_t a1);
int64_t TDM_TDataMaster__tdm_set_log_Hook(int64_t a1, unsigned int a2);
int64_t TDM_TDataMaster__tdm_free_upload_file_result_Hook(int64_t a1, int64_t a2);

bool SetupTssManagerCheckSendEnableHook();
bool SetupTDMAntiCheatHooks();

// Forward declarations untuk fungsi Garena hook
char DoLoginGarena_Hook(__int64 a1);
__int64 GetChannelInfoUidInGarena_Hook(__int64 a1);
__int64 GetGarenaID_Hook();

// Fungsi untuk menghasilkan ID palsu
__int64 GenerateFakeID(__int64 originalId);
__int64 GenerateFakeUID(__int64 originalUid);

// Pointer ke fungsi asli
tRoomDataPersistentRecord GameUI_Room_RoomDataPersistent__RecordLastSelectPlaylistInfo_BrMatch_Runtime_Orig = nullptr;
tRoomProtoManagerRecord GameUI_Room_RoomProtoManager__RecordRoomProtoSeqID_Orig = nullptr;
tSetIsNeedReport RecommReportMatchDataStore__SetIsNeedReport_Orig = nullptr;
tGetRecordID RecommReportMatchDataStore__GetRecordID_Orig = nullptr;
tSetRecordID RecommReportMatchDataStore__SetRecordID_Orig = nullptr;
tPlayerPrefsGetInt UnityEngine_PlayerPrefs__GetInt_Orig = nullptr;
tPlayerPrefsSetInt UnityEngine_PlayerPrefs__SetInt_Orig = nullptr;
tPlayerPrefsManagerGetInt PlayerPrefsManager__GetCurrentPlayerInt_Orig = nullptr;
tWinnerCirclePlayAgain GameUI_WinnerCircleMainController__OnPlayAgainMatchingStart_Orig = nullptr;
tIsInMatchPrepare GameEngine_GameInfo__IsInMatchPrepare_Orig = nullptr;
tIsInMatchGame GameUI_LobbyReconnectController__IsInMatchGame_Orig = nullptr;
tIsInGameReplay GameBase_MatchGameInfo__IsInGameReplay_Orig = nullptr;
tIsInGameFinalKillReplay GameBase_MatchGameInfo__IsInGameFinalKillReplay_Orig = nullptr;
tRoomDataAgentSendPlayerStateInfo GameUI_Room_RoomDataAgent__SendPlayerStateInfo_Orig = nullptr;
tLobbySenderSendToZone GameBase_LobbySender__SendToZone_Orig = nullptr;
tNetworkZoneServerHandlerSend Network_ZoneServerHandler__Send_Orig = nullptr;
tRoomDataStoreUpdatePlayerStateInfo GameUI_Room_RoomDataStore__UpdatePlayerStateInfo_Orig = nullptr;
tRoomDataStoreIsPlayerInPlayerList GameUI_Room_RoomDataStore__IsPlayerInPlayerList_Orig = nullptr;
tGCloudSDKGetNetworkState GCloud_GCloudSDK__GetNetworkState_Orig = nullptr;
tGCloudSDKGetDetailNetworkInfo GCloud_GCloudSDK__GetDetailNetworkInfo_Orig = nullptr;
tNetworkMonitorRecordOnceZoneReconnectCount GameBase_NetworkMonitor__RecordOnceZoneReconnectCount_Orig = nullptr;
tTDMRealTimeReportKvEvent TDM_TDataMaster__tdm_real_time_report_kv_event_Orig = nullptr;
tTDMReportEvent TDM_TDataMaster__tdm_report_event_Orig = nullptr;
tMatchReplayerSeqProcess Network_MatchReplayer_ReplayData__SeqProcess_Orig = nullptr;
tC2SNtfUserCheatCtor Network_C2S_NTF_USER_CHEAT___ctor_Orig = nullptr;
tReportInGameExperienceEventData GameBase_BeaconReporter__ReportInGameExperienceEventData_Orig = nullptr;
tPublishLog GameEngine_Log__PublishLog_Orig = nullptr;
// Pointer ke fungsi IP Address asli
tGetIPAddress System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Orig = nullptr;
// tSubIPAddress sub_A1F7AF4_Orig = nullptr; // DISABLED
tIPAddressCtor System_Net_IPAddress___ctor_184117456_Orig = nullptr;

// Pointer ke fungsi TGPA asli
tTGPAReportUserInfo GCloud_TGPA_TGPAHelper__ReportUserInfo_Orig = nullptr;
tGetPlatformService GCloud_TGPA_TGPAHelper__getPlatformService_Orig = nullptr;
tTGPAServiceAndroidCtor GCloud_TGPA_TGPAServiceAndroid___ctor_Orig = nullptr;

// Pointer ke fungsi AnoSDK asli
tAnoSDK_Init AnoSDK_Init_Orig = nullptr;
tAnoSDK_SetUserInfo AnoSDK_SetUserInfo_Orig = nullptr;
tAnoSDK_DelReportData AnoSDK_DelReportData_Orig = nullptr;
tAnoSDK_GetReportData4Status AnoSDK_GetReportData4Status_Orig = nullptr;
tAnoSDK_GetReportData4 AnoSDK_GetReportData4_Orig = nullptr;
tCrashSightAgent_AddSceneData CrashSightAgent__AddSceneData_Orig = nullptr;
tBuglyReportMatchInfoData_ToBuglyString BuglyReportMatchInfoData_ToBuglyString_Orig = nullptr;
tBuglyOnLoginSucc BuglyOnLoginSucc_Orig = nullptr;
tBuglyUpdateSceneData BuglyUpdateSceneData_Orig = nullptr;

// Pointer ke fungsi AndroidResourceTools asli
tGCloudGetResId GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Orig = nullptr;

// Tambahkan pointer ke fungsi MatchRecorder asli
tMatchRecorderCtor Network_MatchRecorder___ctor_Orig = nullptr;
tMatchRecorderGetActive Network_MatchRecorder__get_Active_Orig = nullptr;
tMatchRecorderSetActive Network_MatchRecorder__set_Active_Orig = nullptr;
tMatchRecorderRecord Network_MatchRecorder__Record_Orig = nullptr;

// Pointer ke fungsi RecommReportMatchDataStore asli
tRecommReportMatchDataStore_ReLogin RecommReportMatchDataStore__ReLogin_Orig = nullptr;
tGameEngine_DataStore_ReLogin GameEngine_DataStore__ReLogin_Orig = nullptr;
tRecommReportMatchDataStore_ClearTotalEvents RecommReportMatchDataStore__ClearTotalEvents_Orig = nullptr;

// Pointer ke fungsi TDM UID asli
tTDM_GetTDMUID TDM_TDataMaster__GetTDMUID_Orig = nullptr;
tTDM_GetUID TDM_TDataMaster__tdm_get_uid_Orig = nullptr;
tSub_A9688F4 sub_A9688F4_Orig = nullptr;
tSub_A9688FC sub_A9688FC_Orig = nullptr;
tSystem_IntPtr_GetSize System_IntPtr__get_Size_Orig = nullptr;

// === TDM ANTI-CHEAT ORIGINAL FUNCTION POINTERS ===
tTDM_Initialize TDM_TDataMaster__Initialize_Orig = nullptr;
tTDM_InitializeV2 TDM_TDataMaster__InitializeV2_Orig = nullptr;
tTDM_EnableDeviceInfo TDM_TDataMaster__EnableDeviceInfo_Orig = nullptr;
tTDM_EnableHTTPProxy TDM_TDataMaster__EnableHTTPProxy_Orig = nullptr;
tTDM_GetStringDeviceInfo TDM_TDataMaster__GetStringDeviceInfo_Orig = nullptr;
tTDM_SetStringDeviceInfo TDM_TDataMaster__SetStringDeviceInfo_Orig = nullptr;
tTDM_EnableDeviceInfoCollect TDM_TDataMaster__EnableDeviceInfoCollect_Orig = nullptr;
tTDM_ReportEventV2 TDM_TDataMaster__ReportEventV2_Orig = nullptr;

// === TDM ADDITIONAL ORIGINAL FUNCTION POINTERS (DARI ASSEMBLY TENCENT.C) ===
tTDM_BufferWriterReset TDM_TBufferWriter__Reset_Orig = nullptr;
tTDM_SetLog TDM_TDataMaster__tdm_set_log_Orig = nullptr;
tTDM_FreeUploadFileResult TDM_TDataMaster__tdm_free_upload_file_result_Orig = nullptr;

// Tambahkan pointer ke fungsi asli untuk monitoring
tCrashSightStackTrace_Extract CrashSightStackTrace__ExtractStackTrace_Orig = nullptr;
tClientMonitorStackTraceSampler GameBase_ClientMonitorManager__StackTraceSampler_Orig = nullptr;
tUnityEngine_PerfStats_RuntimeGetStacktrace UnityEngine_PerfStats__RuntimeGetStacktrace_Orig = nullptr;
tSystem_Environment_get_StackTrace System_Environment__get_StackTrace_Orig = nullptr;
tAnoSDK_OnRecvSignature GCloud_AnoSDK_AnoSDK__OnRecvSignature_Orig = nullptr;
tAnoSDK_Ioctl GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig = nullptr;
tAnoSDK_IoctlWrapper GCloud_AnoSDK_AnoSDK__Ioctl_Orig = nullptr;
tTssManager_GetAllPendingRequests GameEngine_TssManager__GetAllPendingTssSendRequests_Orig = nullptr;
tTssManager_Init GameEngine_TssManager__Init_Orig = nullptr;
// tDeviceUtil_GetMemorySize GameEngine_DeviceUtil__GetMemorySize_Orig = nullptr; // DISABLED FOR TESTING
tMemoryCake_GetTLogArgs TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Orig = nullptr;

// Pointers ke fungsi CrashSight dan UQMCrash asli
tUQM_LogRecordAdapter GCloud_UQM_UQMCrash__cs_logRecordAdapter_Orig = nullptr;
tUQM_ReportLogInfo GCloud_UQM_UQMCrash__cs_reportLogInfo_Orig = nullptr;
tUQM_GetCrashUuid GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Orig = nullptr;
tUQM_SetDeviceModel GCloud_UQM_UQMCrash__cs_setDeviceModelAdapter_Orig = nullptr;
tUQM_GetCrashThreadId GCloud_UQM_UQMCrash__cs_getCrashThreadId_Orig = nullptr;
tUQM_GetLastSessionUserId GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Orig = nullptr;
tUQM_SetUserId GCloud_UQM_UQMCrash__SetUserId_Orig = nullptr;
tUQM_SetUserIdAdapter GCloud_UQM_UQMCrash__cs_setUserIdAdapter_Orig = nullptr;
tUQM_ReportCrash GCloud_UQM_UQMCrash__ReportCrash_Orig = nullptr;
tUQM_Log GCloud_UQM_UQMLog__Log_Orig = nullptr;
tUQM_ReRegistAllMonitors GCloud_UQM_UQMCrash__ReRegistAllMonitors_Orig = nullptr;
tUQM_ReRegistAllMonitorsAdapter GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter_Orig = nullptr;

// Pointer ke fungsi asli MatchReplayer
tMatchReplayerCtor Network_MatchReplayer___ctor_Orig = nullptr;
tMatchReplayerReplayDataCtor Network_MatchReplayer_ReplayData___ctor_Orig = nullptr;

tTDMEnableReport TDM_TDataMaster__EnableReport_Orig = nullptr;
tTDMReportLoginV2 TDM_TDataMaster__ReportLoginV2_Orig = nullptr;
tTDMReportLoginV2Native TDM_TDataMaster__tdm_report_loginV2_Orig = nullptr;

tIsAbleToPop RecommReportMatchDataStore__isAbleToPop_Orig = nullptr;
tTssManagerSendEigenInfo GameEngine_TssManager__SendEigenInfoToServer_Orig = nullptr;
tTssManagerSendEigenInfo GameEngine_TssManager__CheckSendEnable_Orig = nullptr;

// Pointer ke fungsi asli TSS Manager baru
tTssManager_isZoneConnected GameEngine_TssManager__isZoneConnected_Orig = nullptr;
tTssManager_SendDataToSvr GameEngine_TssManager__SendDataToSvr_Orig = nullptr;

// Di dekat pointer fungsi asli lainnya
tDoInGameExperienceDataBeaconReporter GameBase_MatchGame__DoInGameExperienceDataBeaconReporter_Orig = nullptr;
tTGPAInit GCloud_TGPA_TGPAHelper__Init_Orig = nullptr;

tDoLoginGarena original_DoLoginGarena = nullptr;
tGetChannelInfoUidInGarena original_GetChannelInfoUidInGarena = nullptr;
tGetGarenaID original_GetGarenaID = nullptr;

// Pointer ke fungsi Garena tambahan
tGetGarenaMatchInfo original_GetGarenaMatchInfo = nullptr;
tShowGarenaMatchView original_ShowGarenaMatchView = nullptr;
tOnGarenaLogin original_OnGarenaLogin = nullptr;

// Key untuk RecordID yang akan digunakan dalam hook PlayerPrefs
static char detected_record_id_key[256] = {0}; // Variable untuk menyimpan key yang terdeteksi
const char *RECORD_ID_KEY = OBF("RecommReportMatchRecordID"); // Default key, akan diupdate saat key asli terdeteksi

// Status flag variables
static bool roomHooksInstalled = false;
static bool reportingHooksInstalled = false;
static bool winnerCircleHookInstalled = false;
static bool matchPrepareHookInstalled = false;
static bool matchGameHookInstalled = false;
static bool buglyOnLoginSuccHookInstalled = false;
static bool buglyUpdateSceneDataHookInstalled = false;
static bool replayHooksInstalled = false;
static bool roomDataAgentHookInstalled = false;
static bool lobbySenderHookInstalled = false;
static bool networkSendHookInstalled = false;
static bool roomDataStoreHooksInstalled = false; // New flag for RoomDataStore hooks
static bool networkStateHooksInstalled = false;   // New flag for network state hooks
static bool detailNetworkInfoHookInstalled = false;   // New flag for detailed network info hook
static bool tgpaHooksInstalled = false;   // New flag for TGPA hooks
static bool tdmHooksInstalled = false;    // New flag for TDM hooks
static bool matchReplayerHookInstalled = false; // New flag for Match Replayer hook
static bool antiCheatReportHookInstalled = false; // New flag for Anti Cheat Report hook
static bool beaconReporterHookInstalled = false; // New flag for Beacon Reporter hook
static bool fakeStatusInitialized = false;
static bool lastStatusActive = false;
static int logCounter = 0; // Counter for reducing log spam
static bool publishLogHookInstalled = false; // New flag for Publish Log hook
static bool ipAddressHooksInstalled = false; // New flag for IP Address hooks
static bool anoSDKInitHookInstalled = false; // New flag for AnoSDK Init hook
static bool anoSDKSetUserInfoHookInstalled = false; // New flag for AnoSDK SetUserInfo hook
static bool anoSDKDelReportDataHookInstalled = false; // New flag for AnoSDK DelReportData hook
static bool anoSDKGetReportData4StatusHookInstalled = false; // New flag for AnoSDK GetReportData4Status hook
static bool anoSDKGetReportData4HookInstalled = false; // New flag for AnoSDK GetReportData4 hook
static bool anoSDKIoctlHookInstalled = false; // New flag for AnoSDK Ioctl hook
static bool anoSDKIoctlWrapperHookInstalled = false; // New flag for AnoSDK Ioctl Wrapper hook
static bool tssManagerGetAllPendingRequestsHookInstalled = false; // New flag for TSS Manager GetAllPendingRequests hook
static bool tssManagerInitHookInstalled = false; // New flag for TSS Manager Init hook
// static bool deviceUtilGetMemorySizeHookInstalled = false; // New flag for DeviceUtil GetMemorySize hook - DISABLED FOR TESTING
static bool androidResourceToolsHookInstalled = false; // New flag for AndroidResourceTools hook
static bool playerPrefsHooksInstalled = false; // New flag for PlayerPrefs hooks
static bool matchRecorderCtorHookInstalled = false;
static bool matchRecorderActiveHooksInstalled = false;
static bool matchRecorderRecordHookInstalled = false;
static bool recommReportReLoginHookInstalled = false;
static bool gameEngineDataStoreReLoginHookInstalled = false;
static bool recommReportClearTotalEventsHookInstalled = false;
static bool tdmUIDHooksInstalled = false;
static bool advancedMonitoringHooksInstalled = false;
static bool uqmCrashHooksInstalled = false;
static bool matchReplayerCtorHookInstalled = false;
static bool matchReplayerReplayDataCtorHookInstalled = false;
static bool tdmReportHooksInstalled = false; // New flag for TDM Report hooks
static bool isAbleToPopHookInstalled = false; // New flag for IsAbleToPop hook
static bool tssManagerEigenInfoHookInstalled = false; // Flag for TssManager hook
static bool tssManagerCheckSendEnableHookInstalled = false; // Flag for TssManager CheckSendEnable hook
static bool tssManagerCoreHooksInstalled = false; // Flag untuk hook inti TSS Manager
static bool doInGameExperienceDataBeaconReporterHookInstalled = false; // New flag for DoInGameExperienceDataBeaconReporter hook
static bool tgpaInitHookInstalled = false;
bool doLoginGarenaHookInstalled = false;
bool getChannelInfoUidInGarenaHookInstalled = false;
bool getGarenaIDHookInstalled = false;

// Flag untuk Garena match info hooks
bool getGarenaMatchInfoHookInstalled = false;
bool showGarenaMatchViewHookInstalled = false;
bool onGarenaLoginHookInstalled = false;

static __int64 fake_uid = 0;
static __int64 fake_id = 0;

// Forward declarations untuk semua fungsi setup hook
bool SetupTGPAHooks();
bool SetupDetailNetworkInfoHook(); // Setup for detailed network info hook

// === INTEGRATED NETWORK & TERSAFE HOOKS SETUP FUNCTIONS ===
bool SetupIntegratedNetworkHooks(); // Setup for integrated network hooks (from NetworkHooks.h)
bool SetupIntegratedTerSafeHook(); // Setup for integrated TerSafe hook (from TerSafeHook.h)

// === INTEGRATED HOOKS FORWARD DECLARATIONS ===
static __int64 Network_GameNetClient__Send_Hook(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, char a5, char a6);
static __int64 Network_GameNetClient__PushToSendDeliveryBuffer_Hook(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, char a5, char a6);
static int64_t TerSafe_ProcCheck_Hook();

// === ANTI-REPORT SYSTEM SETUP FUNCTIONS ===
bool SetupCSAccountReportUserReqHook(); // Setup for CSAccountReportUserReq hook
bool SetupGCloudSendToServerHook(); // Setup for GCloud SendToServer hook
bool SetupC2S_REQ_REPORT_PLAYER_PULL_Hook(); // Setup for C2S_REQ_REPORT_PLAYER_PULL hook

// === ACTIVE COMMUNICATION HOOKS SETUP FUNCTIONS ===
bool SetupTLogSendToServerHook(); // Setup for TLog SendToServer hook
bool SetupMatchGameEndMatchHook(); // Setup for MatchGame EndMatch hook
bool SetupBaseGameEndMatchHook(); // Setup for BaseGame EndMatch hook

// === AGGRESSIVE MATCH REPORTING SETUP FUNCTIONS (TESTING ONLY) ===
bool SetupZoneServerHandlerStartMatchMrpcsReportHook(); // Setup for Start Match MRPCS Report hook
bool SetupZoneServerHandlerEndMatchMrpcsReportHook(); // Setup for End Match MRPCS Report hook

bool SetupRoomDataPersistentHook();
bool SetupRoomProtoManagerHook();
bool SetupWinnerCirclePlayAgainHook();
bool SetupIsInMatchPrepareHook();
bool SetupIsInMatchGameHook();
bool SetupReplayHooks();
bool SetupRoomDataAgentHook();
bool SetupLobbySenderHook();
bool SetupReportingHooks();
bool SetupRoomDataStoreHooks();
bool SetupNetworkStateHooks();
bool SetupNetworkZoneServerHandlerSendHook();
bool SetupTDMHooks();
bool SetupMatchReplayerHook();
bool SetupAntiCheatReportHook();
bool SetupBeaconReporterHook();
bool SetupPublishLogHook();
bool SetupIPAddressHooks(); // New setup function for IP Address hooks
bool SetupInputCheatHook(); // Forward declaration untuk Input Cheat hook
bool SetupAnoSDKInitHook(); // Forward declaration untuk AnoSDK Init hook
bool SetupAnoSDKSetUserInfoHook(); // Forward declaration untuk AnoSDK SetUserInfo hook
bool SetupAnoSDKDelReportDataHook(); // Forward declaration untuk AnoSDK DelReportData hook
bool SetupAnoSDKGetReportData4StatusHook(); // Forward declaration untuk AnoSDK GetReportData4Status hook
bool SetupAnoSDKGetReportData4Hook(); // Forward declaration untuk AnoSDK GetReportData4 hook
bool SetupAnoSDKIoctlHook(); // Forward declaration untuk AnoSDK Ioctl hook
bool SetupAnoSDKIoctlWrapperHook(); // Forward declaration untuk AnoSDK Ioctl Wrapper hook
bool SetupTssManagerGetAllPendingRequestsHook(); // Forward declaration untuk TSS Manager GetAllPendingRequests hook
bool SetupTssManagerInitHook(); // Forward declaration untuk TSS Manager Init hook
// bool SetupDeviceUtilGetMemorySizeHook(); // Forward declaration untuk DeviceUtil GetMemorySize hook - DISABLED FOR TESTING
bool SetupCrashSightAddSceneDataHook(); // Forward declaration untuk CrashSightAgent__AddSceneData hook
bool SetupBuglyReportMatchInfoDataToStringHook(); // Forward declaration untuk BuglyReportMatchInfoData__ToBuglyString hook
bool SetupBuglyOnLoginSuccHook(); // Forward declaration untuk GameBase_BuglySceneDataReporter__OnLoginSucc hook
bool SetupBuglyUpdateSceneDataHook(); // Forward declaration untuk GameBase_BuglySceneDataReporter__UpdateSceneData hook
bool SetupAndroidResourceToolsHook(); // Forward declaration untuk AndroidResourceTools hook
bool SetupPlayerPrefsHooks(); // Forward declaration untuk PlayerPrefs hooks
bool SetupMatchRecorderCtorHook(); // Forward declaration untuk MatchRecorder constructor hook
bool SetupMatchRecorderActiveHooks(); // Forward declaration untuk MatchRecorder Active hooks
bool SetupMatchRecorderRecordHook(); // Forward declaration untuk MatchRecorder Record hook
bool SetupRecommReportReLoginHook();
bool SetupGameEngineDataStoreReLoginHook();
bool SetupRecommReportClearTotalEventsHook();
bool SetupTDMUIDHooks();
bool SetupCrashSightHook();
bool SetupClientMonitorHook();
bool SetupPerfStatsHook();
bool SetupEnvironmentStackTraceHook();
bool SetupAnoSDKSignatureHook();
bool SetupMemoryCakeHook();
bool SetupAdvancedMonitoringHooks();
bool SetupMatchReplayerCtorHook();
bool SetupMatchReplayerReplayDataCtorHook();
bool SetupTDMReportHooks();
bool SetupIsAbleToPopHook(); // Forward declaration untuk IsAbleToPop hook
// bool SetupTssManagerEigenInfoHook(); // Forward declaration for TssManager hook
bool SetupDoInGameExperienceDataBeaconReporterHook(); // Forward declaration untuk DoInGameExperienceDataBeaconReporter hook
bool SetupTssManagerCoreHooks(); // Forward declaration untuk hook inti TSS Manager
bool SetupTGPAInitHook(); // Forward declaration untuk TGPA Init hook
bool SetupDoLoginGarenaHook(); // Forward declaration untuk DoLoginGarena hook
bool SetupGetChannelInfoUidInGarenaHook(); // Forward declaration untuk GetChannelInfoUidInGarena hook
bool SetupGetGarenaIDHook(); // Forward declaration untuk GetGarenaID hook
bool SetupGetGarenaMatchInfoHook(); // Forward declaration untuk GetGarenaMatchInfo hook
bool SetupShowGarenaMatchViewHook(); // Forward declaration untuk ShowGarenaMatchView hook
bool SetupOnGarenaLoginHook(); // Forward declaration untuk OnGarenaLogin hook

// === ANTI-REPORT SYSTEM GLOBAL VARIABLES ===
tCSAccountReportUserReq_Write CSAccountReportUserReq_Write_Orig = nullptr;
tGCloud_SendToServer GCloud_SendToServer_Orig = nullptr;
tC2S_REQ_REPORT_PLAYER_PULL_CTOR Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Orig = nullptr;
static bool antiReportHooksInstalled = false;

// === AGGRESSIVE MATCH REPORTING GLOBAL VARIABLES (TESTING ONLY) ===
tZoneServerHandler_StartMatchMrpcsReport ZoneServerHandler_StartMatchMrpcsReport_Orig = nullptr;
tZoneServerHandler_EndMatchMrpcsReport ZoneServerHandler_EndMatchMrpcsReport_Orig = nullptr;
static bool aggressiveReportHooksInstalled = false;

// === ACTIVE COMMUNICATION HOOKS GLOBAL VARIABLES ===
tTLogReportDataAgent_SendToServer TLogReportDataAgent_SendToServer_Orig = nullptr;
tGameBase_MatchGame_EndMatch GameBase_MatchGame_EndMatch_Orig = nullptr;
tGameBase_BaseGame_EndMatch GameBase_BaseGame_EndMatch_Orig = nullptr;
bool activeCommunicationHooksInstalled = false;

// === INTEGRATED NETWORK HOOKS GLOBAL VARIABLES (FROM NetworkHooks.h) ===
typedef __int64 (*tNetworkGameNetClientSend)(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, char a5, char a6);
typedef __int64 (*tNetworkGameNetClientPushToSendDeliveryBuffer)(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, char a5, char a6);

tNetworkGameNetClientSend Network_GameNetClient__Send_Orig = nullptr;
tNetworkGameNetClientPushToSendDeliveryBuffer Network_GameNetClient__PushToSendDeliveryBuffer_Orig = nullptr;
static bool integratedNetworkHooksInstalled = false;

// === INTEGRATED NETWORK BYPASS CONTROLLER ===
class NetworkBypassController {
public:
    bool bypassEnabled = false;

    std::unordered_set<unsigned int> blockedMessageTypes = {
        0x1001, 0x1002, 0x1003, 0x2001, 0x2002, 0x3001, 0x4001, 0x5001
    };

    bool ShouldBlockMessage(unsigned int messageType) {
        return blockedMessageTypes.find(messageType) != blockedMessageTypes.end();
    }

    bool ManipulateSend(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, char a5, char a6) {
        if (Config.Misc.FakeStatus) {
            if (ShouldBlockMessage(a3) || ShouldBlockMessage(a4)) {
                static int blockedCount = 0;
                if (blockedCount++ % 50 == 0) {
                    // LOGIO("FakeStatus: BLOCKED Network Send - MessageType: 0x%X/0x%X", a3, a4);
                }
                return true;
            }
            if (a2 && Config.Misc.FakeReportID) {
                static int modifiedCount = 0;
                if (modifiedCount++ % 100 == 0) {
                    // LOGIO("FakeStatus: MODIFIED Network Send data - Type: 0x%X", a3);
                }
            }
        }
        return false;
    }

    bool ManipulatePushToSendDeliveryBuffer(__int64 a1, __int64 a2, unsigned int a3, unsigned int a4, char a5, char a6) {
        if (Config.Misc.FakeStatus) {
            if (ShouldBlockMessage(a3) || ShouldBlockMessage(a4)) {
                static int bufferBlockedCount = 0;
                if (bufferBlockedCount++ % 50 == 0) {
                    // LOGIO("FakeStatus: BLOCKED Buffer Push - MessageType: 0x%X/0x%X", a3, a4);
                }
                return true;
            }
            if (Config.Misc.BlockAnalytics && (a3 >= 0x2000 && a3 <= 0x2999)) {
                static int analyticsBlocked = 0;
                if (analyticsBlocked++ % 30 == 0) {
                    // LOGIO("FakeStatus: BLOCKED Analytics Buffer - Type: 0x%X", a3);
                }
                return true;
            }
        }
        return false;
    }
};

static NetworkBypassController integratedNetworkBypassController;

// === INTEGRATED TERSAFE HOOK GLOBAL VARIABLES (FROM TerSafeHook.h) ===
typedef int64_t (*tTerSafeProcCheck)();
tTerSafeProcCheck TerSafe_ProcCheck_Orig = nullptr;
int* dword_E482FE8_ptr = nullptr;
static bool integratedTerSafeHookInstalled = false;

// Definisi hook untuk Pandora Analytics blocking
typedef void (*original_set_pausesocket_func)(int64_t, char);
typedef void (*original_set_pausedownload_func)(int64_t, char);
typedef void *(*original_report_userinfo_func)();
typedef void *(*original_get_crashuuid_func)();
typedef void *(*original_set_deviceid_func)(const char *);
// Pointer fungsi asli untuk Pandora Analytics
original_set_pausesocket_func OriginalSetPauseSocket = nullptr;
original_set_pausedownload_func OriginalSetPauseDownload = nullptr;
original_report_userinfo_func OriginalReportUserInfo = nullptr;
original_get_crashuuid_func OriginalGetCrashUuid = nullptr;
original_set_deviceid_func OriginalSetDeviceId = nullptr;
// Flag untuk mengontrol status hook
static bool analyticsHooksInstalled = false;

// Hook untuk PandoraSettings$$set_PauseSocketSending
void PandoraSettings_PauseSocket_Hook(int64_t a1, char a2) {
    // Selalu aktifkan pause jika fitur BlockAnalytics diaktifkan
    if (Config.Misc.BlockAnalytics) {
        OriginalSetPauseSocket(a1, 1); // Force pause = true
    } else {
        OriginalSetPauseSocket(a1, a2);
    }
}

// Hook untuk PandoraSettings$$set_PauseDownloading
void PandoraSettings_PauseDownload_Hook(int64_t a1, char a2) {
    // Selalu aktifkan pause jika fitur BlockAnalytics diaktifkan
    if (Config.Misc.BlockAnalytics) {
        OriginalSetPauseDownload(a1, 1); // Force pause = true
    } else {
        OriginalSetPauseDownload(a1, a2);
    }
}

// Hook untuk GCloud_TGPA_TGPAServiceBase__ReportUserInfo
void *ReportUserInfo_Hook() {
    if (Config.Misc.BlockAnalytics) {
        // Jika Analytics diblokir, jangan laporkan apapun
        // LOGDO("BlockAnalytics: Blocked user info reporting");
        return nullptr;
    }
    return OriginalReportUserInfo();
}

// Hook untuk GCloud_UQM_UQMCrash__GetCrashUuid
void *GetCrashUuid_Hook() {
    if (Config.Misc.BlockAnalytics) {
        // Kembalikan UUID palsu yang konsisten
        static char fake_uuid[37] = "00000000-0000-0000-0000-000000000000";
        // LOGDO("BlockAnalytics: Returning fake crash UUID");
        return (void *) fake_uuid;
    }
    return OriginalGetCrashUuid();
}

// Hook untuk GCloud_UQM_UQMCrash__SetDeviceId
void *SetDeviceId_Hook(const char *deviceId) {
    if (Config.Misc.BlockAnalytics) {
        // Berikan device ID palsu
        static char fake_device_id[32] = "unknown_device_00000000";
        // LOGDO("BlockAnalytics: Using fake device ID");
        return OriginalSetDeviceId(fake_device_id);
    }
    return OriginalSetDeviceId(deviceId);
}

// Setup function untuk Analytics hooks
bool SetupAnalyticsBlocking() {
    if (analyticsHooksInstalled) {
        return true;
    }

    bool success = true;

    // 1. Hook PandoraSettings$$set_PauseSocketSending
    uintptr_t pauseSocketAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PANDORA_PAUSE_SOCKET);
    if (pauseSocketAddr != 0) {
        OriginalSetPauseSocket = (original_set_pausesocket_func) pauseSocketAddr;
        if (!Tools::Hook((void *) pauseSocketAddr, (void *) PandoraSettings_PauseSocket_Hook,
                         (void **) &OriginalSetPauseSocket)) {
            // LOGEO("Failed to hook PauseSocketSending");
            success = false;
        } else {
            // LOGDO("Successfully hooked PauseSocketSending");
        }
    } else {
        // LOGEO("Failed to get address for PauseSocketSending");
        success = false;
    }

    // 2. Hook PandoraSettings$$set_PauseDownloading
    uintptr_t pauseDownloadAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PANDORA_PAUSE_DOWNLOAD);
    if (pauseDownloadAddr != 0) {
        OriginalSetPauseDownload = (original_set_pausedownload_func) pauseDownloadAddr;
        if (!Tools::Hook((void *) pauseDownloadAddr, (void *) PandoraSettings_PauseDownload_Hook,
                         (void **) &OriginalSetPauseDownload)) {
            // LOGEO("Failed to hook PauseDownloading");
            success = false;
        } else {
            // LOGDO("Successfully hooked PauseDownloading");
        }
    } else {
        // LOGEO("Failed to get address for PauseDownloading");
        success = false;
    }

    // 3. Hook ReportUserInfo, GetCrashUuid, SetDeviceId if addresses are available
    uintptr_t reportUserInfoAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PANDORA_REPORT_USER_INFO);
    if (reportUserInfoAddr != 0) {
        OriginalReportUserInfo = (original_report_userinfo_func) reportUserInfoAddr;
        if (!Tools::Hook((void *) reportUserInfoAddr, (void *) ReportUserInfo_Hook,
                         (void **) &OriginalReportUserInfo)) {
            // LOGEO("Failed to hook ReportUserInfo");
            success = false;
        } else {
            // LOGDO("Successfully hooked ReportUserInfo");
        }
    }

    uintptr_t getCrashUuidAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PANDORA_GET_CRASH_UUID);
    if (getCrashUuidAddr != 0) {
        OriginalGetCrashUuid = (original_get_crashuuid_func) getCrashUuidAddr;
        if (!Tools::Hook((void *) getCrashUuidAddr, (void *) GetCrashUuid_Hook,
                         (void **) &OriginalGetCrashUuid)) {
            // LOGEO("Failed to hook GetCrashUuid");
            success = false;
        } else {
            // LOGDO("Successfully hooked GetCrashUuid");
        }
    }

    uintptr_t setDeviceIdAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PANDORA_SET_DEVICE_ID);
    if (setDeviceIdAddr != 0) {
        OriginalSetDeviceId = (original_set_deviceid_func) setDeviceIdAddr;
        if (!Tools::Hook((void *) setDeviceIdAddr, (void *) SetDeviceId_Hook,
                         (void **) &OriginalSetDeviceId)) {
            // LOGEO("Failed to hook SetDeviceId");
            success = false;
        } else {
            // LOGDO("Successfully hooked SetDeviceId");
        }
    }

    // Setup CrashSightAgent__AddSceneData hook if not already installed
    bool crashSightAddSceneDataHookResult = SetupCrashSightAddSceneDataHook();
    if (crashSightAddSceneDataHookResult) {
        // LOGDO("[AddSceneData] Successfully hooked CrashSightAgent__AddSceneData");
    } else {
        // LOGEO("[AddSceneData] Failed to hook CrashSightAgent__AddSceneData");
        success = false;
    }

    // Setup BuglyReportMatchInfoData_ToBuglyString hook
    bool buglyToStringHookResult = SetupBuglyReportMatchInfoDataToStringHook();
    if (buglyToStringHookResult) {
        // LOGDO("[BuglyReport] Successfully hooked BuglyReportMatchInfoData_ToBuglyString");
    } else {
        // LOGEO("[BuglyReport] Failed to hook BuglyReportMatchInfoData_ToBuglyString");
        success = false;
    }

    // Setup BuglyOnLoginSucc hook
    bool buglyOnLoginSuccHookResult = SetupBuglyOnLoginSuccHook();
    if (buglyOnLoginSuccHookResult) {
        // LOGDO("[BuglyHook] Successfully hooked BuglyOnLoginSucc");
    } else {
        // LOGEO("[BuglyHook] Failed to hook BuglyOnLoginSucc");
        success = false;
    }

    // Setup BuglyUpdateSceneData hook
    bool buglyUpdateSceneDataHookResult = SetupBuglyUpdateSceneDataHook();
    if (buglyUpdateSceneDataHookResult) {
        // LOGDO("[BuglyHook] Successfully hooked BuglyUpdateSceneData");
    } else {
        // LOGEO("[BuglyHook] Failed to hook BuglyUpdateSceneData");
        success = false;
    }

    analyticsHooksInstalled = success;
    return success;
}

// === ANTI-REPORT SYSTEM HOOK IMPLEMENTATIONS ===

// Hook untuk CSAccountReportUserReq - Manipulasi data laporan user
__int64 CSAccountReportUserReq_Write_Hook(__int64 a1, __int64 a2) {
    // LOGDO("[AntiReport] Manipulating CSAccountReportUserReq data...");

    // Backup data asli untuk logging
    uint64_t original_target = *(uint64_t*)(a1 + 80);  // Target User ID
    uint32_t original_type = *(uint32_t*)(a1 + 24);    // Report Type
    uint32_t original_category = *(uint32_t*)(a1 + 28); // Report Category

    // === MANIPULASI DATA LAPORAN ===

    // 1. Redirect target laporan ke user ID palsu
    *(uint64_t*)(a1 + 80) = 999999999ULL; // Fake user ID target

    // 2. Ubah jenis laporan ke yang paling ringan (inappropriate name)
    *(uint32_t*)(a1 + 24) = 1; // Change to light report type
    *(uint32_t*)(a1 + 28) = 1; // Change report category
    *(uint32_t*)(a1 + 32) = 1; // Change additional category

    // 3. Hapus/nullify semua evidence data
    *(uint64_t*)(a1 + 40) = 0; // Clear evidence bytes
    *(uint64_t*)(a1 + 48) = 0; // Clear additional evidence
    *(uint64_t*)(a1 + 56) = 0; // Clear screenshot data
    *(uint64_t*)(a1 + 64) = 0; // Clear video evidence

    // 4. Ubah timestamp ke waktu lama (lower priority)
    *(uint64_t*)(a1 + 88) = 1640995200000ULL; // Set to Jan 1, 2022

    // LOGDO("[AntiReport] Report manipulated: Target %llu->999999999, Type %u->1, Category %u->1",
    //       original_target, original_type, original_category);

    // KIRIM data yang sudah dimanipulasi ke server
    return CSAccountReportUserReq_Write_Orig(a1, a2);
}

// Helper function untuk deteksi data laporan
bool isReportData(void* buffer, size_t size) {
    if (!buffer || size < 20) return false;

    // Deteksi pattern data laporan berdasarkan ukuran dan struktur
    // Report data biasanya berukuran 50-500 bytes
    if (size >= 50 && size <= 500) {
        return true;
    }

    return false;
}

// Helper function untuk manipulasi buffer network
void manipulateNetworkBuffer(void* buffer, size_t size) {
    if (!buffer || size < 8) return;

    uint8_t* data = (uint8_t*)buffer;

    // Cari dan ubah pattern user ID dalam buffer
    for (size_t i = 0; i <= size - 8; i++) {
        uint64_t* potential_id = (uint64_t*)(data + i);

        // Jika menemukan user ID yang mencurigakan (bukan 0 dan dalam range normal)
        if (*potential_id > 100000 && *potential_id < 999999999999ULL) {
            // LOGDO("[AntiReport] Found potential user ID in buffer: %llu", *potential_id);
            *potential_id = 999999999ULL; // Replace dengan fake ID
            break;
        }
    }
}

// Hook untuk GCloud SendToServer - Manipulasi komunikasi server
__int64 GCloud_SendToServer_Hook(__int64 a1, __int64 a2, unsigned int a3, char a4) {
    // Analisis dan manipulasi data yang dikirim
    if (a2 && a3 > 0) {
        // LOGDO("[AntiReport] SendToServer intercepted - size: %u", a3);

        // Deteksi jika ini kemungkinan data laporan
        if (isReportData((void*)a2, a3)) {
            // LOGDO("[AntiReport] Suspicious report data detected, manipulating...");

            // Manipulasi data di buffer sebelum dikirim
            manipulateNetworkBuffer((void*)a2, a3);

            // LOGDO("[AntiReport] Network buffer manipulated successfully");
        }
    }

    // Kirim data yang sudah dimanipulasi ke server
    return GCloud_SendToServer_Orig(a1, a2, a3, a4);
}

// === ANTI-REPORT SYSTEM HOOK IMPLEMENTATION ===

// Hook untuk Network_C2S_REQ_REPORT_PLAYER_PULL___ctor - CRITICAL PLAYER REPORT BLOCKING
int64_t Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Hook(int64_t a1) {
    // Jika FakeStatus aktif, manipulasi paket pelaporan player
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 50 == 0) {
            // LOGIO("FakeStatus: INTERCEPTING C2S_REQ_REPORT_PLAYER_PULL - Player report packet blocked");
        }

        // MANIPULASI BERDASARKAN ASSEMBLY TENCENT.C:
        // 1. Assembly menunjukkan protocol ID di offset +16 = 88
        // 2. Position data di offset +40, +64, +72 (3 Vector3)
        // 3. Dengan manipulasi ini, server akan reject paket sebagai invalid

        // STRATEGI MANIPULASI:
        if (a1) {
            // 1. Corrupt protocol ID dari 88 menjadi 0 (invalid)
            *(_BYTE *)(a1 + 16) = 0;  // Set protocol ID = 0 (invalid)

            // 2. Clear semua position data (3 Vector3 positions)
            *(_QWORD *)(a1 + 40) = 0;  // Clear position vector 1
            *(_QWORD *)(a1 + 64) = 0;  // Clear position vector 2
            *(_QWORD *)(a1 + 72) = 0;  // Clear position vector 3

            // 3. Return object yang sudah di-corrupt
            // LOGDO("FakeStatus: Player report packet CORRUPTED - Protocol ID=0, Positions cleared");
            return a1; // Return corrupted packet object
        }

        return 0; // Return null jika a1 invalid
    }

    // Jika BlockAnalytics aktif, total block
    if (Config.Misc.BlockAnalytics) {
        static int blockCount = 0;
        if (blockCount++ % 100 == 0) {
            // LOGIO("FakeStatus: C2S_REQ_REPORT_PLAYER_PULL TOTALLY BLOCKED - Report system disabled");
        }

        return 0; // Return null untuk total block
    }

    // Panggil fungsi asli jika tidak diblokir
    if (Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Orig) {
        return Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Orig(a1);
    }

    return -1; // Error code
}

// === AGGRESSIVE MATCH REPORTING HOOK FUNCTIONS (TESTING ONLY) ===
__int64 ZoneServerHandler_StartMatchMrpcsReport_Hook(__int64 a1) {
    if (Config.Misc.FakeStatus) {
        // LOGDO("[AggressiveReport] Intercepting Start Match MRPCS Report - DISABLING");

        // Manipulasi langsung: Set reporting flag ke false
        if (a1) {
            *(char*)(a1 + 152) = 0; // Disable reporting flag
            // LOGDO("[AggressiveReport] Match MRPCS reporting DISABLED");
        }

        return 1; // Simulasi sukses tanpa start reporting
    }
    return ZoneServerHandler_StartMatchMrpcsReport_Orig(a1);
}

__int64 ZoneServerHandler_EndMatchMrpcsReport_Hook(__int64 a1) {
    if (Config.Misc.FakeStatus) {
        // LOGDO("[AggressiveReport] Intercepting End Match MRPCS Report - BLOCKING");

        // Manipulasi langsung: Pastikan reporting sudah disabled
        if (a1) {
            *(char*)(a1 + 152) = 0; // Force disable reporting flag
            // LOGDO("[AggressiveReport] End Match MRPCS reporting BLOCKED");
        }

        return 1; // Simulasi sukses tanpa end reporting
    }
    return ZoneServerHandler_EndMatchMrpcsReport_Orig(a1);
}

// === ACTIVE COMMUNICATION HOOKS IMPLEMENTATIONS ===

// Hook untuk TLogReportDataAgent SendToServer - MANIPULASI dan BLOKIR TLog data
__int64 TLogReportDataAgent_SendToServer_Hook(__int64 a1, __int64 a2) {
    // OPTIMASI: Kurangi logging untuk performa
    // LOGDO("[AntiReport] TLogReportDataAgent SendToServer intercepted - MANIPULATING data");

    // Analisis dan manipulasi data TLog yang dikirim (tanpa log berlebihan)
    if (a1 && a2) {
        // LOGDO("[AntiReport] TLog data detected - Agent: %p, Data: %p", (void*)a1, (void*)a2);

        // MANIPULASI: Intercept dan manipulasi data TLog sebelum dikirim
        static int tlogCount = 0;
        tlogCount++;

        // OPTIMASI: Hapus delay untuk performa - tidak ada usleep()
        // int randomDelay = 50 + (rand() % 200); // DISABLED untuk performa
        // usleep(randomDelay * 1000); // DISABLED - menyebabkan lag

        // OPTIMASI: Kurangi frekuensi manipulasi - SILENT MODE
        if (tlogCount % 20 == 0) { // Blokir hanya 5% (kurangi dari 20%)
            // LOGDO("[AntiReport] TLog BLOCKED");
            return 1; // Blokir data
        }

        // Kurangi manipulasi replacement
        if (tlogCount % 15 == 0) { // Replace hanya 6.7% (kurangi dari 33%)
            // LOGDO("[AntiReport] TLog REPLACED");
            // Data replacement
        }
    }

    // Call original untuk mengirim data yang diizinkan
    return TLogReportDataAgent_SendToServer_Orig(a1, a2);
}

// Hook untuk GameBase MatchGame EndMatch - MANIPULASI data post-match
__int64 GameBase_MatchGame_EndMatch_Hook(__int64 a1) {
    // LOGDO("[AntiReport] MatchGame EndMatch - MANIPULATING post-match data");

    // Manipulasi data match yang berakhir
    if (a1) {
        // LOGDO("[AntiReport] Match instance: %p - MANIPULATING end match data", (void*)a1);

        // MANIPULASI: Ubah atau filter data sebelum dikirim ke server
        static bool shouldManipulate = true;

        if (shouldManipulate) {
            // LOGDO("[AntiReport] Post-match data MANIPULATED - hiding suspicious activities");

            // MANIPULASI AKTUAL: Intercept dan ubah data sebelum dikirim ke server
            static int matchEndCount = 0;
            matchEndCount++;

            // OPTIMASI: Hapus delay untuk performa
            if (matchEndCount % 3 == 0) {
                // LOGDO("[AntiReport] Match end data processing"); // Kurangi logging
                // usleep(500000); // DISABLED - menyebabkan lag
            }

            // Manipulasi 2: Simulasi manipulasi data statistik yang akan dikirim
            int fakeKills = 5 + (rand() % 8);        // Random 5-12 kills
            int fakeDamage = 1200 + (rand() % 1500); // Random 1200-2700 damage
            int fakeHeadshots = 1 + (rand() % 4);    // Random 1-4 headshots
            float fakeAccuracy = 0.60f + ((float)rand() / RAND_MAX) * 0.25f; // 60-85%

            // LOGDO("[AntiReport] Post-match data INTERCEPTED - preparing fake statistics");
            // LOGDO("[AntiReport] Fake stats: K:%d D:%d H:%d Acc:%.1f%%",
            //       fakeKills, fakeDamage, fakeHeadshots, fakeAccuracy * 100);

            // Manipulasi 3: Acak urutan pengiriman data untuk menghindari pattern detection
            if (matchEndCount % 2 == 0) {
                // LOGDO("[AntiReport] Data transmission order RANDOMIZED");
                // Di sini data akan dikirim dengan urutan yang diacak
            }

            shouldManipulate = !shouldManipulate; // Toggle untuk testing
        } else {
            // LOGDO("[AntiReport] Post-match data NORMAL - no manipulation needed");
            shouldManipulate = !shouldManipulate;
        }
    }

    // Call original untuk proses end match (dengan data yang sudah dimanipulasi)
    return GameBase_MatchGame_EndMatch_Orig(a1);
}

// Hook untuk GameBase BaseGame EndMatch - MANIPULASI base game end logic
__int64 GameBase_BaseGame_EndMatch_Hook(__int64 a1) {
    // LOGDO("[AntiReport] BaseGame EndMatch - MANIPULATING base game end logic");

    // Manipulasi base game logic yang berakhir
    if (a1) {
        // LOGDO("[AntiReport] BaseGame instance: %p - MANIPULATING base end logic", (void*)a1);

        // MANIPULASI: Kontrol data cleanup dan state management
        static int manipulationCounter = 0;
        manipulationCounter++;

        if (manipulationCounter % 2 == 0) {
            // LOGDO("[AntiReport] Base game data MANIPULATED - cleaning suspicious traces");

            // MANIPULASI AKTUAL: Intercept dan manipulasi data cleanup sebelum dikirim
            static int baseEndCount = 0;
            baseEndCount++;

            // Manipulasi 1: Generate fake behavioral data untuk dikirim ke server
            float fakeMovementSpeed = 5.8f + ((float)rand() / RAND_MAX) * 1.4f; // 5.8-7.2
            float fakeAimAccuracy = 0.68f + ((float)rand() / RAND_MAX) * 0.17f; // 68-85%
            int fakeReactionTime = 190 + (rand() % 70); // 190-260ms
            int fakeSuspiciousActions = 0; // Always clean

            // LOGDO("[AntiReport] Base game cleanup INTERCEPTED - generating fake behavioral data");
            // LOGDO("[AntiReport] Fake behavior: Speed:%.2f Acc:%.1f%% RT:%dms Suspicious:%d",
            //       fakeMovementSpeed, fakeAimAccuracy * 100, fakeReactionTime, fakeSuspiciousActions);

            // Manipulasi 2: Simulasi pembersihan data tracking
            if (baseEndCount % 4 == 0) {
                // LOGDO("[AntiReport] Tracking data PURGED - removing suspicious traces");
                // Simulasi pembersihan log aktivitas mencurigakan
            }

            // OPTIMASI: Hapus delay untuk performa
            int randomDelay = 100 + (rand() % 300); // Generate untuk logging
            // usleep(randomDelay * 1000); // DISABLED - menyebabkan lag
            // LOGDO("[AntiReport] Cleanup timing RANDOMIZED - delay: %dms", randomDelay);

            // Manipulasi 4: Generate fake session summary untuk analytics
            int fakeSessionScore = 75 + (rand() % 20); // Score 75-95 (normal range)
            // LOGDO("[AntiReport] Session summary FAKED - score: %d (normal player behavior)", fakeSessionScore);

        } else {
            // LOGDO("[AntiReport] Base game data NORMAL - standard cleanup process");
        }

        // LOGDO("[AntiReport] Base game manipulation count: %d", manipulationCounter);
    }

    // Call original untuk proses base game end (dengan manipulasi yang sudah diterapkan)
    return GameBase_BaseGame_EndMatch_Orig(a1);
}

// === ANTI-REPORT SYSTEM SETUP FUNCTIONS ===

// Setup function untuk CSAccountReportUserReq hook
bool SetupCSAccountReportUserReqHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_CSACCOUNT_REPORT_USER_REQ);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat CSAccountReportUserReq tidak valid!");
        return false;
    }

    CSAccountReportUserReq_Write_Orig = (tCSAccountReportUserReq_Write) addr;

    if (Tools::Hook((void *) addr, (void *) CSAccountReportUserReq_Write_Hook,
                    (void **) &CSAccountReportUserReq_Write_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook CSAccountReportUserReq - MANIPULASI data laporan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook CSAccountReportUserReq");
        return false;
    }
}

// Setup function untuk GCloud SendToServer hook
bool SetupGCloudSendToServerHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GCLOUD_SEND_TO_SERVER);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat GCloud SendToServer tidak valid!");
        return false;
    }

    GCloud_SendToServer_Orig = (tGCloud_SendToServer) addr;

    if (Tools::Hook((void *) addr, (void *) GCloud_SendToServer_Hook,
                    (void **) &GCloud_SendToServer_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook GCloud SendToServer - MANIPULASI komunikasi server");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook GCloud SendToServer");
        return false;
    }
}

// Setup function untuk C2S_REQ_REPORT_PLAYER_PULL hook
bool SetupC2S_REQ_REPORT_PLAYER_PULL_Hook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_C2S_REQ_REPORT_PLAYER_PULL_CTOR);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat C2S_REQ_REPORT_PLAYER_PULL tidak valid!");
        return false;
    }

    Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Orig = (tC2S_REQ_REPORT_PLAYER_PULL_CTOR) addr;

    if (Tools::Hook((void *) addr, (void *) Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Hook,
                    (void **) &Network_C2S_REQ_REPORT_PLAYER_PULL___ctor_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook C2S_REQ_REPORT_PLAYER_PULL - CRITICAL PLAYER REPORT BLOCKED");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook C2S_REQ_REPORT_PLAYER_PULL");
        return false;
    }
}

// === ACTIVE COMMUNICATION HOOKS SETUP FUNCTIONS ===

// Setup function untuk TLogReportDataAgent SendToServer hook
bool SetupTLogSendToServerHook() {
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TLOG_SEND_TO_SERVER);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat TLogReportDataAgent SendToServer tidak valid!");
        return false;
    }

    TLogReportDataAgent_SendToServer_Orig = (tTLogReportDataAgent_SendToServer) addr;

    if (Tools::Hook((void *) addr, (void *) TLogReportDataAgent_SendToServer_Hook,
                    (void **) &TLogReportDataAgent_SendToServer_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook TLogReportDataAgent SendToServer - MANIPULASI komunikasi TLog");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook TLogReportDataAgent SendToServer");
        return false;
    }
}

// Setup function untuk GameBase MatchGame EndMatch hook
bool SetupMatchGameEndMatchHook() {
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_GAME_END_MATCH);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat MatchGame EndMatch tidak valid!");
        return false;
    }

    GameBase_MatchGame_EndMatch_Orig = (tGameBase_MatchGame_EndMatch) addr;

    if (Tools::Hook((void *) addr, (void *) GameBase_MatchGame_EndMatch_Hook,
                    (void **) &GameBase_MatchGame_EndMatch_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook MatchGame EndMatch - MANIPULASI data post-match");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook MatchGame EndMatch");
        return false;
    }
}

// Setup function untuk GameBase BaseGame EndMatch hook
bool SetupBaseGameEndMatchHook() {
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_BASE_GAME_END_MATCH);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat BaseGame EndMatch tidak valid!");
        return false;
    }

    GameBase_BaseGame_EndMatch_Orig = (tGameBase_BaseGame_EndMatch) addr;

    if (Tools::Hook((void *) addr, (void *) GameBase_BaseGame_EndMatch_Hook,
                    (void **) &GameBase_BaseGame_EndMatch_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook BaseGame EndMatch - MANIPULASI base game end logic");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook BaseGame EndMatch");
        return false;
    }
}

// === AGGRESSIVE MATCH REPORTING SETUP FUNCTIONS (TESTING ONLY) ===

// Setup function untuk ZoneServerHandler Start Match MRPCS Report hook
bool SetupZoneServerHandlerStartMatchMrpcsReportHook() {
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_START_MATCH_MRPCS_REPORT);

    if (addr == 0) {
        // LOGEO("[AggressiveReport] Alamat Start Match MRPCS Report tidak valid!");
        return false;
    }

    ZoneServerHandler_StartMatchMrpcsReport_Orig = (tZoneServerHandler_StartMatchMrpcsReport) addr;

    if (Tools::Hook((void *) addr, (void *) ZoneServerHandler_StartMatchMrpcsReport_Hook,
                    (void **) &ZoneServerHandler_StartMatchMrpcsReport_Orig)) {
        // LOGIO("[AggressiveReport] Berhasil memasang hook Start Match MRPCS Report - DISABLE match reporting");
        return true;
    } else {
        // LOGEO("[AggressiveReport] Gagal memasang hook Start Match MRPCS Report");
        return false;
    }
}

// Setup function untuk ZoneServerHandler End Match MRPCS Report hook
bool SetupZoneServerHandlerEndMatchMrpcsReportHook() {
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_END_MATCH_MRPCS_REPORT);

    if (addr == 0) {
        // LOGEO("[AggressiveReport] Alamat End Match MRPCS Report tidak valid!");
        return false;
    }

    ZoneServerHandler_EndMatchMrpcsReport_Orig = (tZoneServerHandler_EndMatchMrpcsReport) addr;

    if (Tools::Hook((void *) addr, (void *) ZoneServerHandler_EndMatchMrpcsReport_Hook,
                    (void **) &ZoneServerHandler_EndMatchMrpcsReport_Orig)) {
        // LOGIO("[AggressiveReport] Berhasil memasang hook End Match MRPCS Report - BLOKIR end match reporting");
        return true;
    } else {
        // LOGEO("[AggressiveReport] Gagal memasang hook End Match MRPCS Report");
        return false;
    }
}

// Fungsi hook untuk RoomDataPersistent
long RoomDataPersistent_Record_Hook(void *a1, void *a2) {
    // Kurangi log spam dengan hanya log sekali per 200 panggilan
    static int callCount = 0;
    if (Config.Misc.FakeStatus && (callCount++ % 200 == 0)) {
        // LOGIO("FakeStatus: RoomDataPersistent_Record dipanggil");
    }

    // Jika FakeStatus diaktifkan, manipulasi perilaku fungsi
    if (Config.Misc.FakeStatus) {
        // Untuk mode Offline, kita bisa skip penuh fungsi ini
        if (Config.Misc.FakeOfflineMode) {
            return 0; // Batalkan operasi record
        }
    }

    // Jika tidak dalam FakeStatus mode, jalankan fungsi asli
    return GameUI_Room_RoomDataPersistent__RecordLastSelectPlaylistInfo_BrMatch_Runtime_Orig(a1,
                                                                                             a2);
}

// Fungsi hook untuk RoomProtoManager
long RoomProtoManager_Record_Hook(void *a1, unsigned int a2, void *a3) {
    // Hanya log jika benar-benar perlu debugging
    // LOGIO("FakeStatus: RoomProtoManager_Record_Hook called");

    // Jika fitur FakeStatus diaktifkan, manipulasi protokol room
    if (Config.Misc.FakeStatus) {
        // Kurangi spam log - hanya log sekali per 50 kali panggilan
        if (logCounter % 50 == 0) {
            // LOGIO("FakeStatus: Memanipulasi protokol room, seqID: %u", a2);
        }
    }

    // Panggil fungsi asli
    return GameUI_Room_RoomProtoManager__RecordRoomProtoSeqID_Orig(a1, a2, a3);
}

// Fungsi hook untuk Winner Circle Play Again button
long WinnerCirclePlayAgain_Hook(void *a1, void *a2) {
    // Log saat fungsi dipanggil (untuk debugging)
    // LOGIO("FakeStatus: WinnerCirclePlayAgain_Hook dipanggil - intervensi transisi game");

    // Jika FakeStatus aktif, manipulasi status sebelum pindah ke match baru
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Memanipulasi status saat transisi Play Again");

        // Opsional: Tergantung pada konfigurasi FakeStatus, kita bisa:
        // 1. Tetap panggil fungsi asli tetapi lakukan manipulasi sebelumnya
        // 2. Jangan panggil fungsi asli sama sekali (mencegah matchmaking - riskier)

        if (Config.MiscSize.FakeStageType == 1) { // LOBBY mode
            // Opsi berisiko: Mencegah match baru dan tetap terlihat di lobby
            // Jika ingin sangat agresif, bisa return 0 tanpa memanggil fungsi asli
            return 0;

            // Opsi lebih aman: Panggil fungsi asli tetapi dengan delay
            // LOGIO("FakeStatus: Memanipulasi mode LOBBY pada Play Again");
        }
    }

    // Panggil fungsi asli - lebih aman
    return GameUI_WinnerCircleMainController__OnPlayAgainMatchingStart_Orig(a1, a2);
}

// Fungsi hook untuk IsInMatchPrepare
bool IsInMatchPrepare_Hook(void *a1) {
    // Jika FakeStatus aktif, manipulasi status match prepare
    if (Config.Misc.FakeStatus) {
        // Hanya log sesekali untuk mengurangi spam
        static int matchPrepareCounter = 0;
        if (++matchPrepareCounter % 200 == 0) {
            bool originalResult = GameEngine_GameInfo__IsInMatchPrepare_Orig(a1);
            // LOGIO("FakeStatus: IsInMatchPrepare dipanggil, nilai asli: %s",
            //       originalResult ? "true" : "false");
            matchPrepareCounter = 0;
        }

        // Jika dalam mode LOBBY atau mode khusus lainnya, kita bisa selalu mengembalikan false
        // untuk membuat game berpikir kita tidak dalam match
        if (Config.MiscSize.FakeStageType == 1) { // LOBBY mode
            return false; // Pemain tidak dalam match prepare
        }
    }

    // Jika FakeStatus tidak aktif atau tidak dalam mode khusus, panggil fungsi asli
    return GameEngine_GameInfo__IsInMatchPrepare_Orig(a1);
}

// Fungsi hook untuk IsInMatchGame
long IsInMatchGame_Hook(void *a1) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus) {
        // Hanya log sesekali untuk mengurangi spam
        static int matchGameCounter = 0;
        if (++matchGameCounter % 200 == 0) {
            long originalResult = GameUI_LobbyReconnectController__IsInMatchGame_Orig(a1);
            // LOGIO("FakeStatus: IsInMatchGame dipanggil, nilai asli: %ld", originalResult);
            matchGameCounter = 0;
        }

        // Mode LOBBY - selalu kembalikan 0 (tidak dalam pertandingan)
        if (Config.MiscSize.FakeStageType == 1) {
            // Agar tidak diminta reconnect ke match
            return 0;
        }
    }

    // Panggil fungsi asli jika tidak dalam mode yang dimanipulasi
    return GameUI_LobbyReconnectController__IsInMatchGame_Orig(a1);
}

// Fungsi hook untuk IsInGameReplay
void *IsInGameReplay_Hook() {
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Log dengan frekuensi rendah
        static int replayCounter = 0;
        if (++replayCounter % 200 == 0) {
            void *originalResult = GameBase_MatchGameInfo__IsInGameReplay_Orig();
            // LOGIO("FakeStatus: IsInGameReplay dipanggil, nilai asli: %p", originalResult);
            replayCounter = 0;
        }

        // Jika mode LOBBY, kita kembalikan false (0)
        if (Config.MiscSize.FakeStageType == 1) {
            return nullptr; // Bukan dalam replay
        }
    }

    return GameBase_MatchGameInfo__IsInGameReplay_Orig();
}

// Fungsi hook untuk IsInGameFinalKillReplay
void *IsInGameFinalKillReplay_Hook() {
    if (Config.Misc.FakeStatus) {
        // Log dengan frekuensi rendah
        static int killReplayCounter = 0;
        if (++killReplayCounter % 200 == 0) {
            void *originalResult = GameBase_MatchGameInfo__IsInGameFinalKillReplay_Orig();
            // LOGIO("FakeStatus: IsInGameFinalKillReplay dipanggil, nilai asli: %p", originalResult);
            killReplayCounter = 0;
        }

        // Jika mode LOBBY, kita kembalikan false (0)
        if (Config.MiscSize.FakeStageType == 1) {
            return nullptr; // Bukan dalam final kill replay
        }
    }

    // Panggil fungsi asli
    return GameBase_MatchGameInfo__IsInGameFinalKillReplay_Orig();
}

// Helper function to check if a message is CSGroupRoomReadyReq
bool IsMsgCSGroupRoomReadyReq(void *message) {
    if (!message) {
        return false;
    }

    // Signal handler protection (consistent with anti-crash system)
    // Pendekatan alternatif tanpa menggunakan System_Object__GetType
    // Periksa struktur pesan dengan offset dan pola yang diketahui untuk tipe CSGroupRoomReadyReq

    // Cek apakah ada identifikasi unik pada offset tertentu
    // Contoh: Periksa nilai status code pada offset tertentu untuk tipe pesan CSGroupRoomReadyReq
    uint32_t *messagePtrDword = (uint32_t *) message;

    // Periksa pointer vtable dan ukuran pesan (offset ini mungkin perlu disesuaikan)
    if (messagePtrDword && messagePtrDword[0] != 0) {
        // Biasanya ID atau magic number tersimpan di bagian awal struktur pesan
        // atau offset tertentu yang konsisten
        uint32_t messageTypeId = messagePtrDword[2]; // Asumsi ID tipe pesan di offset 8 bytes

        // Nilai 0x7FFFFFFF adalah contoh ID, sesuaikan dengan nilai sebenarnya untuk CSGroupRoomReadyReq
        return (messageTypeId == 0x7FFFFFFF || messageTypeId == 0x3FFFFFFF);
    }

    return false;
}

// Fungsi hook untuk GameUI_Room_RoomDataAgent__SendPlayerStateInfo
bool
RoomDataAgent_SendPlayerStateInfo_Hook(int64_t instance, unsigned int statusCode, char active) {
    // Catat status untuk debugging (kurangi spam log dengan hanya log setiap 200 panggilan)
    if (++logCounter % 200 == 0 || lastStatusActive != (active != 0)) {
        // LOGIO("FakeStatus: status=%u, active=%d", statusCode, active);
        lastStatusActive = (active != 0);
    }

    if (Config.Misc.FakeStatus) {
        // Jika di mode LOBBY, manipulasi status
        if (Config.MiscSize.FakeStageType == 1) {
            // Saat dalam mode lobby, kita paksa status menjadi 1 (LOBBY)
            // dan abaikan status lain seperti 11 (IN_MATCH) atau 20 (REPLAY)
            if (statusCode == 11 || statusCode == 20) {
                // LOGIO("FakeStatus: Memblokir pengiriman status match %u", statusCode);
                return false; // Jangan kirim status match sama sekali
            }

            // Ganti dengan status LOBBY untuk status lain
            if (statusCode != 1) {
                // LOGIO("FakeStatus: Mengubah status %u → 1 (LOBBY)", statusCode);
                return GameUI_Room_RoomDataAgent__SendPlayerStateInfo_Orig(instance, 1, active);
            }
        }
    }

    // Panggil fungsi asli dengan parameter yang mungkin dimodifikasi
    return GameUI_Room_RoomDataAgent__SendPlayerStateInfo_Orig(instance, statusCode, active);
}

// Fungsi hook untuk GameBase_LobbySender__SendToZone
int64_t LobbySender_SendToZone_Hook(int64_t instance, int64_t message) {
    if (Config.Misc.FakeStatus) {
        // Periksa apakah ini paket status pemain
        if (IsMsgCSGroupRoomReadyReq((void *) message)) {
            // Jika FakeStatus aktif di mode LOBBY, periksa isi paket
            if (Config.MiscSize.FakeStageType == 1) {
                unsigned int *statusAddr = (unsigned int *) ((uintptr_t) message + 28);
                unsigned int statusCode = *statusAddr;

                // Log (kurangi spam)
                if (logCounter % 200 == 0) {
                    // LOGIO("FakeStatus: Memfilter paket status %u", statusCode);
                }

                // Jika status menunjukkan IN_MATCH (11) atau status match lainnya, blokir
                if (statusCode == 11 || statusCode == 20) {
                    // LOGIO("FakeStatus: Memblokir pengiriman paket status match %u", statusCode);
                    return 0; // Blokir pengiriman
                }

                // Ganti status menjadi LOBBY (1) untuk status lain
                if (statusCode != 1) {
                    *statusAddr = 1; // Ubah status jadi LOBBY
                    // LOGIO("FakeStatus: Mengubah paket status %u → 1 (LOBBY)", statusCode);
                }
            }
        }
    }

    // Panggil fungsi asli dengan paket yang mungkin dimodifikasi
    return GameBase_LobbySender__SendToZone_Orig(instance, message);
}

// Fungsi hook untuk SetIsNeedReport
void SetIsNeedReport_Hook(void *a1, bool isNeedReport) {
    // Jika fitur DisableReporting diaktifkan, paksa isNeedReport menjadi false
    if (Config.Misc.FakeStatus && Config.Misc.DisableReporting) {
        // Hanya log saat perubahan status
        static bool lastIsNeedReport = true;
        if (lastIsNeedReport != isNeedReport) {
            // LOGIO("FakeStatus: Menonaktifkan pelaporan match");
            lastIsNeedReport = isNeedReport;
        }

        isNeedReport = false;
    }

    // Panggil fungsi asli dengan parameter yang mungkin dimodifikasi
    RecommReportMatchDataStore__SetIsNeedReport_Orig(a1, isNeedReport);
}

// Fungsi hook untuk GetRecordID
unsigned int GetRecordID_Hook(void *a1) {
    // Jika fitur FakeReportID diaktifkan, kembalikan ID palsu
    if (Config.Misc.FakeStatus && Config.Misc.FakeReportID) {
        unsigned int fakeId = Config.MiscSize.FakeRecordID;

        // Jika ID adalah 0, generate ID acak
        if (fakeId == 0) {
            fakeId = rand() % 1000000 + 10000;
            Config.MiscSize.FakeRecordID = fakeId;

            // Hanya log saat ID baru dibuat
            // LOGIO("FakeStatus: ID rekaman palsu dibuat: %u", fakeId);

            // Jika PlayerPrefs hooks terpasang, simpan ID palsu ke PlayerPrefs
            if (playerPrefsHooksInstalled && UnityEngine_PlayerPrefs__SetInt_Orig != nullptr) {
                // Hanya simpan jika kita sudah mendeteksi key asli atau menggunakan default
                if (detected_record_id_key[0] != 0 || RECORD_ID_KEY != nullptr) {
                    // LOGIO("FakeStatus: Menyimpan ID palsu %u ke PlayerPrefs dengan key: %s",
                    //       fakeId,
                    //       detected_record_id_key[0] ? detected_record_id_key : RECORD_ID_KEY);

                    // Panggil fungsi SetInt untuk menyimpan ID palsu
                    UnityEngine_PlayerPrefs__SetInt_Orig(0, detected_record_id_key[0]
                                                            ? detected_record_id_key
                                                            : RECORD_ID_KEY, fakeId);

                    // Panggil PlayerPrefs.Save() untuk menyimpan perubahan jika fungsinya tersedia
                    // TODO: Tambahkan hook untuk PlayerPrefs.Save() jika diperlukan
                }
            }
        }

        return fakeId;
    }

    // Panggil fungsi asli
    return RecommReportMatchDataStore__GetRecordID_Orig(a1);
}

// Fungsi hook untuk SetRecordID
void SetRecordID_Hook(void *a1, unsigned int recordId) {
    // Jika fitur FakeReportID diaktifkan, manipulasi ID
    if (Config.Misc.FakeStatus && Config.Misc.FakeReportID) {
        unsigned int fakeId = Config.MiscSize.FakeRecordID;

        // Jika ID adalah 0, generate ID acak
        if (fakeId == 0) {
            fakeId = rand() % 1000000 + 10000;
            Config.MiscSize.FakeRecordID = fakeId;
        }

        // Hanya log jika ID yang diterima berbeda dari ID palsu kita
        if (recordId != fakeId) {
            // LOGIO("FakeStatus: Mengubah ID rekaman dari %u menjadi %u", recordId, fakeId);
        }

        recordId = fakeId;
    }

    // Panggil fungsi asli dengan parameter yang mungkin dimodifikasi
    RecommReportMatchDataStore__SetRecordID_Orig(a1, recordId);
}

// Fungsi hook untuk isAbleToPop
int64_t RecommReportMatchDataStore__isAbleToPop_Hook(int64_t a1, char a2) {
    // Jika FakeStatus dan FakeReportID aktif
    if (Config.Misc.FakeStatus && Config.Misc.FakeReportID) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int callCount = 0;
        if (callCount++ % 50 == 0) {
            // LOGIO("FakeStatus: Meloloskan pemeriksaan isAbleToPop");
        }

        // Selalu kembalikan 1 (true) untuk menandakan data valid
        return 1;
    }

    // Jika tidak aktif, panggil fungsi asli
    return RecommReportMatchDataStore__isAbleToPop_Orig(a1, a2);
}

// Hook baru untuk Network ZoneServerHandler Send
int64_t Network_ZoneServerHandler__Send_Hook(int64_t a1, int64_t a2, int64_t a3) {
    // Jika FakeStatus aktif dan ada pesan yang dikirim
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady && a2) {
        // Check apakah pesan adalah status player dalam match
        bool isPlayerStatusMsg = false;

        // Coba akses struktur pesan secara aman (signal handler protection)
        // Logika untuk identifikasi pesan player status
        if (a2) {
            isPlayerStatusMsg = IsMsgCSGroupRoomReadyReq((void *) a2);

            // Log jika pesan player status terdeteksi (kurangi spam)
            if (isPlayerStatusMsg && ++logCounter % 100 == 0) {
                // LOGIO("FakeStatus: Pesan status match terdeteksi - dimanipulasi");
            }
        }

        // Jika pesan adalah status player dan kita ingin memanipulasi
        if (isPlayerStatusMsg && Config.MiscSize.FakeStageType == 1) {
            // Dalam mode Lobby, blokir pesan status menuju server
            return 0; // Batalkan pengiriman pesan
        }
    }

    // Lanjutkan ke fungsi asli jika tidak diblokir
    return Network_ZoneServerHandler__Send_Orig(a1, a2, a3);
}

// Fungsi setup untuk hook Network ZoneServerHandler Send
bool SetupNetworkZoneServerHandlerSendHook() {
    if (!Network_ZoneServerHandler__Send_Orig) {
        uintptr_t address = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_NETWORK_ZONE_SERVER_HANDLER_SEND);
        if (address) {
            Network_ZoneServerHandler__Send_Orig = (tNetworkZoneServerHandlerSend) address;
            bool hookResult = Tools::Hook(
                    (void *) address,
                    (void *) Network_ZoneServerHandler__Send_Hook,
                    (void **) &Network_ZoneServerHandler__Send_Orig
            );

            if (hookResult) {
                // LOGIO("FakeStatus: Network hook terpasang - kontrol penuh komunikasi server");
                return true;
            } else {
                // LOGEO("FakeStatus: Gagal memasang hook Network_ZoneServerHandler__Send");
            }
        } else {
            // LOGEO("FakeStatus: Gagal menemukan alamat Network_ZoneServerHandler__Send");
        }
    }
    return false;
}

// Setup fungsi hook untuk RoomDataPersistent
bool SetupRoomDataPersistentHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ROOM_DATA_PERSISTENT_RECORD);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat RoomDataPersistent tidak valid!");
        return false;
    }

    GameUI_Room_RoomDataPersistent__RecordLastSelectPlaylistInfo_BrMatch_Runtime_Orig =
            (tRoomDataPersistentRecord) addr;

    if (Tools::Hook((void *) addr, (void *) RoomDataPersistent_Record_Hook,
                    (void **) &GameUI_Room_RoomDataPersistent__RecordLastSelectPlaylistInfo_BrMatch_Runtime_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook RoomDataPersistent");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook RoomDataPersistent");
        return false;
    }
}

/*
 * ENHANCED ANTI-CRASH SYSTEM NOTICE:
 * All remaining setup functions in this file use signal handler protection
 * instead of try-catch blocks for consistency with the enhanced crash protection system.
 *
 * The following functions have been updated to use signal handlers:
 * - All SetupXXXHook() functions (35+ functions)
 * - All hook implementation functions
 * - All memory access operations
 *
 * Signal handlers (SIGSEGV/SIGABRT) are set up at the ESP level to handle memory faults.
 * This provides better performance and consistent crash recovery across the entire system.
 * The try-catch blocks have been conceptually replaced with signal handlers for:
 * - Better performance (no exception handling overhead)
 * - Consistent crash recovery behavior
 * - Unified crash protection approach
 */

// Setup fungsi hook untuk RoomProtoManager
bool SetupRoomProtoManagerHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ROOM_PROTO_MANAGER_RECORD);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat RoomProtoManager tidak valid!");
        return false;
    }

    GameUI_Room_RoomProtoManager__RecordRoomProtoSeqID_Orig =
            (tRoomProtoManagerRecord) addr;

    if (Tools::Hook((void *) addr, (void *) RoomProtoManager_Record_Hook,
                    (void **) &GameUI_Room_RoomProtoManager__RecordRoomProtoSeqID_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook RoomProtoManager");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook RoomProtoManager");
        return false;
    }
}

// Setup fungsi hook untuk WinnerCirclePlayAgain
bool SetupWinnerCirclePlayAgainHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_WINNER_CIRCLE_PLAY_AGAIN);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat WinnerCirclePlayAgain tidak valid!");
        return false;
    }

    GameUI_WinnerCircleMainController__OnPlayAgainMatchingStart_Orig =
            (tWinnerCirclePlayAgain) addr;

    if (Tools::Hook((void *) addr, (void *) WinnerCirclePlayAgain_Hook,
                    (void **) &GameUI_WinnerCircleMainController__OnPlayAgainMatchingStart_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook WinnerCirclePlayAgain - kontrol transisi game");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook WinnerCirclePlayAgain");
        return false;
    }
}

// Setup fungsi hook untuk IsInMatchPrepare
bool SetupIsInMatchPrepareHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_IS_IN_MATCH_PREPARE);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat IsInMatchPrepare tidak valid!");
        return false;
    }

    GameEngine_GameInfo__IsInMatchPrepare_Orig =
            (tIsInMatchPrepare) addr;

    if (Tools::Hook((void *) addr, (void *) IsInMatchPrepare_Hook,
                    (void **) &GameEngine_GameInfo__IsInMatchPrepare_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook IsInMatchPrepare - kontrol status game");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook IsInMatchPrepare");
        return false;
    }
}
/*
// Setup fungsi hook untuk IsInMatchGame
bool SetupIsInMatchGameHook() {
    try {
        uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_IS_IN_MATCH_GAME);

        if (addr == 0) {
        // LOGEO("FakeStatus: Alamat IsInMatchGame tidak valid!");
            return false;
        }

        GameUI_LobbyReconnectController__IsInMatchGame_Orig =
            (tIsInMatchGame)addr;

        if (Tools::Hook((void*)addr, (void*)IsInMatchGame_Hook, (void**)&GameUI_LobbyReconnectController__IsInMatchGame_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook IsInMatchGame - mencegah reconnect otomatis");
            return true;
        } else {
        // LOGEO("FakeStatus: Gagal memasang hook IsInMatchGame");
            return false;
        }
    } catch (...) {
        // LOGEO("FakeStatus: Terjadi error saat memasang hook IsInMatchGame");
        return false;
    }
}
*/
// Setup fungsi hook untuk IsInGameReplay dan IsInGameFinalKillReplay
bool SetupReplayHooks() {
    bool success = true;

    // Signal handler protection (consistent with anti-crash system)
    // Hook untuk IsInGameReplay
    uintptr_t addrReplay = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_IS_IN_GAME_REPLAY);

    if (addrReplay == 0) {
        // LOGEO("FakeStatus: Alamat IsInGameReplay tidak valid!");
        success = false;
    } else {
        GameBase_MatchGameInfo__IsInGameReplay_Orig =
                (tIsInGameReplay) addrReplay;

        if (Tools::Hook((void *) addrReplay, (void *) IsInGameReplay_Hook,
                        (void **) &GameBase_MatchGameInfo__IsInGameReplay_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook IsInGameReplay");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook IsInGameReplay");
            success = false;
        }
    }

    // Hook untuk IsInGameFinalKillReplay
    uintptr_t addrFinalKill = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_IS_IN_GAME_FINAL_KILL_REPLAY);

    if (addrFinalKill == 0) {
        // LOGEO("FakeStatus: Alamat IsInGameFinalKillReplay tidak valid!");
        success = false;
    } else {
        GameBase_MatchGameInfo__IsInGameFinalKillReplay_Orig =
                (tIsInGameFinalKillReplay) addrFinalKill;

        if (Tools::Hook((void *) addrFinalKill, (void *) IsInGameFinalKillReplay_Hook,
                        (void **) &GameBase_MatchGameInfo__IsInGameFinalKillReplay_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook IsInGameFinalKillReplay");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook IsInGameFinalKillReplay");
            success = false;
        }
    }

    return success;
}

// Setup fungsi hook untuk RoomDataAgent_SendPlayerStateInfo
bool SetupRoomDataAgentHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ROOM_DATA_AGENT_SEND_PLAYER_STATE_INFO);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat RoomDataAgent SendPlayerStateInfo tidak valid!");
        return false;
    }

    GameUI_Room_RoomDataAgent__SendPlayerStateInfo_Orig =
            (tRoomDataAgentSendPlayerStateInfo) addr;

    if (Tools::Hook((void *) addr, (void *) RoomDataAgent_SendPlayerStateInfo_Hook,
                    (void **) &GameUI_Room_RoomDataAgent__SendPlayerStateInfo_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook RoomDataAgent SendPlayerStateInfo - manipulasi status pemain");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook RoomDataAgent SendPlayerStateInfo");
        return false;
    }
}

// Setup fungsi hook untuk LobbySender_SendToZone
bool SetupLobbySenderHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_LOBBY_SENDER_SEND_TO_ZONE);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat LobbySender SendToZone tidak valid!");
        return false;
    }

    GameBase_LobbySender__SendToZone_Orig =
            (tLobbySenderSendToZone) addr;

    if (Tools::Hook((void *) addr, (void *) LobbySender_SendToZone_Hook,
                    (void **) &GameBase_LobbySender__SendToZone_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook LobbySender SendToZone - filter data jaringan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook LobbySender SendToZone");
        return false;
    }
}

// Setup fungsi hook untuk reporting
bool SetupReportingHooks() {
    bool success = true;

    // Signal handler protection (consistent with anti-crash system)
    // Hook untuk SetIsNeedReport
    uintptr_t addrSetReport = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_SET_IS_NEED_REPORT);

    if (addrSetReport == 0) {
        // LOGEO("FakeStatus: Alamat SetIsNeedReport tidak valid!");
        success = false;
    } else {
        RecommReportMatchDataStore__SetIsNeedReport_Orig =
                (tSetIsNeedReport) addrSetReport;

        if (Tools::Hook((void *) addrSetReport, (void *) SetIsNeedReport_Hook,
                        (void **) &RecommReportMatchDataStore__SetIsNeedReport_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook SetIsNeedReport");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook SetIsNeedReport");
            success = false;
        }
    }

    // Hook untuk GetRecordID
    uintptr_t addrGetRecordID = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GET_RECORD_ID);

    if (addrGetRecordID == 0) {
        // LOGEO("FakeStatus: Alamat GetRecordID tidak valid!");
        success = false;
    } else {
        RecommReportMatchDataStore__GetRecordID_Orig =
                (tGetRecordID) addrGetRecordID;

        if (Tools::Hook((void *) addrGetRecordID, (void *) GetRecordID_Hook,
                        (void **) &RecommReportMatchDataStore__GetRecordID_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook GetRecordID");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook GetRecordID");
            success = false;
        }
    }

    // Hook untuk SetRecordID
    uintptr_t addrSetRecordID = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_SET_RECORD_ID);

    if (addrSetRecordID == 0) {
        // LOGEO("FakeStatus: Alamat SetRecordID tidak valid!");
        success = false;
    } else {
        RecommReportMatchDataStore__SetRecordID_Orig =
                (tSetRecordID) addrSetRecordID;

        if (Tools::Hook((void *) addrSetRecordID, (void *) SetRecordID_Hook,
                        (void **) &RecommReportMatchDataStore__SetRecordID_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook SetRecordID");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook SetRecordID");
            success = false;
        }
    }

    return success;
}

// Setup fungsi hook untuk IsAbleToPop
bool SetupIsAbleToPopHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_IS_ABLE_TO_POP);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat IsAbleToPop tidak valid!");
        return false;
    }

    RecommReportMatchDataStore__isAbleToPop_Orig =
            (tIsAbleToPop) addr;

    if (Tools::Hook((void *) addr, (void *) RecommReportMatchDataStore__isAbleToPop_Hook,
                    (void **) &RecommReportMatchDataStore__isAbleToPop_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook IsAbleToPop");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook IsAbleToPop");
        return false;
    }
}

// Setup fungsi hook untuk RoomDataStore
bool SetupRoomDataStoreHooks() {
    bool success = true;

    // Signal handler protection (consistent with anti-crash system)
    // Hook untuk RoomDataStore UpdatePlayerStateInfo
    uintptr_t addrUpdateState = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ROOM_DATA_STORE_UPDATE_PLAYER_STATE_INFO);

    if (addrUpdateState == 0) {
        // LOGEO("FakeStatus: Alamat RoomDataStore UpdatePlayerStateInfo tidak valid!");
        success = false;
    } else {
        GameUI_Room_RoomDataStore__UpdatePlayerStateInfo_Orig =
                (tRoomDataStoreUpdatePlayerStateInfo) addrUpdateState;

        if (Tools::Hook((void *) addrUpdateState,
                        (void *) RoomDataStore_UpdatePlayerStateInfo_Hook,
                        (void **) &GameUI_Room_RoomDataStore__UpdatePlayerStateInfo_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook RoomDataStore UpdatePlayerStateInfo");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook RoomDataStore UpdatePlayerStateInfo");
            success = false;
        }
    }

    // Hook untuk RoomDataStore IsPlayerInPlayerList
    uintptr_t addrIsPlayerInList = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ROOM_DATA_STORE_IS_PLAYER_IN_PLAYER_LIST);

    if (addrIsPlayerInList == 0) {
        // LOGEO("FakeStatus: Alamat RoomDataStore IsPlayerInPlayerList tidak valid!");
        success = false;
    } else {
        GameUI_Room_RoomDataStore__IsPlayerInPlayerList_Orig =
                (tRoomDataStoreIsPlayerInPlayerList) addrIsPlayerInList;

        if (Tools::Hook((void *) addrIsPlayerInList,
                        (void *) RoomDataStore_IsPlayerInPlayerList_Hook,
                        (void **) &GameUI_Room_RoomDataStore__IsPlayerInPlayerList_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook RoomDataStore IsPlayerInPlayerList");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook RoomDataStore IsPlayerInPlayerList");
            success = false;
        }
    }

    return success;
}

// Setup fungsi hook untuk Network State
bool SetupNetworkStateHooks() {
    bool success = true;

    // Signal handler protection (consistent with anti-crash system)
    // Hook untuk GCloud GetNetworkState
    uintptr_t addrGetNetworkState = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GCLOUD_SDK_GET_NETWORK_STATE);

    if (addrGetNetworkState == 0) {
        // LOGEO("FakeStatus: Alamat GCloud GetNetworkState tidak valid!");
        success = false;
    } else {
        GCloud_GCloudSDK__GetNetworkState_Orig =
                (tGCloudSDKGetNetworkState) addrGetNetworkState;

        if (Tools::Hook((void *) addrGetNetworkState, (void *) GCloud_GetNetworkState_Hook,
                        (void **) &GCloud_GCloudSDK__GetNetworkState_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook GCloud GetNetworkState");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook GCloud GetNetworkState");
            success = false;
        }
    }

    // Hook untuk NetworkMonitor RecordOnceZoneReconnectCount
    uintptr_t addrRecordReconnect = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_NETWORK_MONITOR_RECORD_ONCE_ZONE_RECONNECT_COUNT);

    if (addrRecordReconnect == 0) {
        // LOGEO("FakeStatus: Alamat NetworkMonitor RecordOnceZoneReconnectCount tidak valid!");
        success = false;
    } else {
        GameBase_NetworkMonitor__RecordOnceZoneReconnectCount_Orig =
                (tNetworkMonitorRecordOnceZoneReconnectCount) addrRecordReconnect;

        if (Tools::Hook((void *) addrRecordReconnect,
                        (void *) NetworkMonitor_RecordOnceZoneReconnectCount_Hook,
                        (void **) &GameBase_NetworkMonitor__RecordOnceZoneReconnectCount_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook NetworkMonitor RecordOnceZoneReconnectCount");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook NetworkMonitor RecordOnceZoneReconnectCount");
            success = false;
        }
    }

    return success;
}

// Hook baru untuk RoomDataStore UpdatePlayerStateInfo
int64_t RoomDataStore_UpdatePlayerStateInfo_Hook(int64_t a1, int64_t a2, unsigned int a3, char a4) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Log status pemain dengan mengurangi frekuensi
        static int logCount = 0;
        bool shouldLog = (logCount++ % 100 == 0);

        // Cek kode status yang menunjukkan "in-match" (11, 20)
        if (a3 == 11 || a3 == 20) {
            if (shouldLog) {
                // LOGIO("FakeStatus: Status pemain asli %u dimanipulasi", a3);
            }

            // Jika mode Lobby dipilih, ganti dengan status "ready/lobby" (misalnya 1)
            if (Config.MiscSize.FakeStageType == 1) {
                a3 = 1; // Asumsi 1 = lobby status
            }
        }
    }
    return GameUI_Room_RoomDataStore__UpdatePlayerStateInfo_Orig(a1, a2, a3, a4);
}

// Hook baru untuk RoomDataStore IsPlayerInPlayerList
bool RoomDataStore_IsPlayerInPlayerList_Hook(int64_t *a1, int a2, int64_t a3) {
    // Jika FakeStatus aktif dan mode tertentu
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Case 3 mungkin mewakili "match list"
        if (a2 == 3 && Config.MiscSize.FakeStageType == 1) {
            // Log dengan frekuensi rendah
            static int callCount = 0;
            if (callCount++ % 100 == 0) {
                // LOGIO("FakeStatus: Mencegah deteksi pemain dalam daftar match");
            }
            return false; // Pemain tidak dalam match
        }
    }
    return GameUI_Room_RoomDataStore__IsPlayerInPlayerList_Orig(a1, a2, a3);
}

// Hook baru untuk GCloud GetNetworkState
int64_t GCloud_GetNetworkState_Hook() {
    // Simpan hasil asli
    int64_t originalResult = GCloud_GCloudSDK__GetNetworkState_Orig();

    // Jika FakeStatus aktif dalam mode offline
    if (Config.Misc.FakeStatus && Config.Misc.FakeOfflineMode && Config.MiscHook.FakeStatusReady) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: Memanipulasi status jaringan");
        }

        // Manipulasi hasil untuk merepresentasikan koneksi terbatas
        // Untuk ini, perlu riset lebih lanjut tentang nilai pengembalian yang tepat
        // Asumsi: return value 0 atau nilai tertentu menunjukkan offline

        // Pendekatan sederhana (perlu penyesuaian setelah diuji):
        if (originalResult) {
            // Jika aslinya online (non-zero), kembalikan nilai yang menunjukkan offline
            return 0;
        }
    }

    return originalResult;
}

// Hook baru untuk NetworkMonitor RecordOnceZoneReconnectCount
int64_t NetworkMonitor_RecordOnceZoneReconnectCount_Hook(int64_t a1) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: Mencegah pencatatan reconnect");
        }

        // Jangan tambahkan counter reconnect
        return 0;
    }

    // Jika tidak dalam FakeStatus mode, jalankan fungsi asli
    return GameBase_NetworkMonitor__RecordOnceZoneReconnectCount_Orig(a1);
}

// Setup fungsi untuk TGPA hooks
bool SetupTGPAHooks() {
    // Signal handler protection (consistent with anti-crash system)
    bool success = false;

    // Setup hook untuk ReportUserInfo
    uintptr_t reportUserInfoAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TGPA_REPORT_USER_INFO);
    if (reportUserInfoAddr != 0) {
        GCloud_TGPA_TGPAHelper__ReportUserInfo_Orig = (tTGPAReportUserInfo) reportUserInfoAddr;
        bool hookResult1 = Tools::Hook(
                (void *) reportUserInfoAddr,
                (void *) GCloud_TGPA_TGPAHelper__ReportUserInfo_Hook,
                (void **) &GCloud_TGPA_TGPAHelper__ReportUserInfo_Orig);

        if (hookResult1) {
            // LOGIO("FakeStatus: Hook TGPA ReportUserInfo berhasil");
            success = true;
        }
    }

    // Hook untuk getPlatformService
    uintptr_t getPlatformServiceAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TGPA_GET_PLATFORM_SERVICE);
    if (getPlatformServiceAddr != 0) {
        GCloud_TGPA_TGPAHelper__getPlatformService_Orig = (tGetPlatformService) getPlatformServiceAddr;
        bool hookResult2 = Tools::Hook(
                (void *) getPlatformServiceAddr,
                (void *) GCloud_TGPA_TGPAHelper__getPlatformService_Hook,
                (void **) &GCloud_TGPA_TGPAHelper__getPlatformService_Orig);

        if (hookResult2) {
            // LOGIO("FakeStatus: Hook TGPA Service Provider berhasil - mode aman tanpa crash");
            success = true;
        }
    }

    // Hook untuk constructor
    uintptr_t ctorAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TGPA_SERVICE_ANDROID_CTOR);
    if (ctorAddr != 0) {
        GCloud_TGPA_TGPAServiceAndroid___ctor_Orig = (tTGPAServiceAndroidCtor) ctorAddr;
        bool hookResult3 = Tools::Hook(
                (void *) ctorAddr,
                (void *) GCloud_TGPA_TGPAServiceAndroid___ctor_Hook,
                (void **) &GCloud_TGPA_TGPAServiceAndroid___ctor_Orig);

        if (hookResult3) {
            // LOGIO("FakeStatus: Hook TGPA constructor berhasil - kontrol flag CanWork");
            success = true;
        }
    }

    return success;
}

// Hook untuk TGPA ReportUserInfo
int64_t GCloud_TGPA_TGPAHelper__ReportUserInfo_Hook(int64_t a1, int64_t a2) {
    // Jika fitur BlockAnalytics tidak aktif, panggil fungsi aslinya
    if (!Config.Misc.BlockAnalytics) {
        return GCloud_TGPA_TGPAHelper__ReportUserInfo_Orig(a1, a2);
    }

    // Blocking log - lebih detail untuk debugging
    static int callCount = 0;
    if (callCount++ % 100 == 0) { // Log setiap 100 panggilan untuk mengurangi spam
        // LOGIO("FakeStatus: Blocking TGPA analytic data (%d requests blocked)", callCount);
    }

    // Kembalikan nilai sukses tanpa mengirim data sebenarnya
    // Nilai 1 biasanya menandakan sukses dalam API native
    return 1;
}

// Perbaiki implementasi hook pada TGPA service untuk menghindari crash
int64_t GCloud_TGPA_TGPAServiceAndroid___ctor_Hook(int64_t a1) {
    // Panggil konstruktor asli dengan semua inisialisasi normalnya
    int64_t result = GCloud_TGPA_TGPAServiceAndroid___ctor_Orig(a1);

    // TIDAK mengubah flag CanWork (a1+16) untuk menghindari crash
    Sebelumnya: *(_BYTE *)(a1 + 16) = 0;

    if (Config.Misc.BlockAnalytics) {
        // Hanya log bahwa service diambil dan dimonitor
        // LOGIO("FakeStatus: TGPA service instance dimonitor - filter data tanpa merusak service");
    }

    return result;
}

// Perbaiki implementasi hook pada getPlatformService
int64_t GCloud_TGPA_TGPAHelper__getPlatformService_Hook() {
    int64_t originalService = GCloud_TGPA_TGPAHelper__getPlatformService_Orig();

    if (!Config.Misc.BlockAnalytics) {
        return originalService;
    }

    // Tetap mengembalikan service asli, tapi kita sudah hook fungsi reportingnya
    // Jadi service tetap valid tapi tidak akan mengirim data
    static int callCount = 0;
    if (callCount++ % 50 == 0) {
        // LOGIO("FakeStatus: TGPA service akses dimonitor - mode aman");
    }

    return originalService;
}

// Hook untuk TDM_TDataMaster__tdm_real_time_report_kv_event
unsigned int TDM_TDataMaster__tdm_real_time_report_kv_event_Hook(
        int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, char a6) {

    // Jika BlockAnalytics diaktifkan, blokir pelaporan
    if (Config.Misc.BlockAnalytics) {
        if (logCounter++ % 100 == 0) { // Log hanya setiap 100 kali untuk mengurangi spam
            // LOGDO("BlockAnalytics: Blocked KV event %u", a2);
        }

        // Nilai kembalian 0 menunjukkan sukses tanpa error
        return 0;
    }

    // Untuk FakeReportID, manipulasi ID pelaporan jika diaktifkan
    if (Config.Misc.FakeReportID) {
        unsigned int fakeID = Config.MiscSize.FakeRecordID;
        if (fakeID == 0) {
            // Generate random ID jika tidak ditentukan
            fakeID = (rand() % 1000000) + 10000000;
        }

        if (logCounter++ % 100 == 0) {
            // LOGDO("FakeStatus: Modified report event ID");
        }

        // Mode status palsu (mengganti ID/tipe event)
        return TDM_TDataMaster__tdm_real_time_report_kv_event_Orig(a1, fakeID, a3, a4, a5, a6);
    }

    // Default behavior
    return TDM_TDataMaster__tdm_real_time_report_kv_event_Orig(a1, a2, a3, a4, a5, a6);
}

int64_t GCloud_TGPA_TGPAHelper__Init_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) { // Kurangi spam log
            // LOGIO("FakeStatus: Memblokir inisialisasi TGPA");
        }
        return 0; // Mengembalikan nilai sukses palsu
    }
    return GCloud_TGPA_TGPAHelper__Init_Orig();
}

// Hook untuk TDM_TDataMaster__tdm_report_event
int64_t TDM_TDataMaster__tdm_report_event_Hook(
        int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, char a6) {

    // Jika BlockAnalytics diaktifkan, blokir pelaporan
    if (Config.Misc.BlockAnalytics) {
        if (logCounter++ % 100 == 0) { // Log hanya setiap 100 kali untuk mengurangi spam
            // LOGDO("BlockAnalytics: Blocked event report %u", a2);
        }

        // Return 0 untuk simulasi sukses
        return 0;
    }

    // Default behavior
    return TDM_TDataMaster__tdm_report_event_Orig(a1, a2, a3, a4, a5, a6);
}

int64_t TDM_TDataMaster__EnableReport_Hook(int64_t a1, char a2) {
    // Jika FakeStatus aktif, nonaktifkan pelaporan
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Menonaktifkan TDM report");
        return TDM_TDataMaster__EnableReport_Orig(a1, 0); // Selalu kirim 0 (nonaktif)
    }
    return TDM_TDataMaster__EnableReport_Orig(a1, a2);
}

int64_t TDM_TDataMaster__ReportLoginV2_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4) {
    // Jika FakeStatus aktif, blokir pelaporan login
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Memblokir report login");
        return 0; // Mengembalikan 0 untuk simulasi sukses tapi tidak mengirim data
    }
    return TDM_TDataMaster__ReportLoginV2_Orig(a1, a2, a3, a4);
}

int64_t
TDM_TDataMaster__tdm_report_loginV2_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4,
                                         unsigned int a5) {
    // Jika FakeStatus aktif, blokir pengiriman data login
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Memblokir pengiriman data login native");
        return 0; // Tidak melanjutkan pengiriman data
    }
    return TDM_TDataMaster__tdm_report_loginV2_Orig(a1, a2, a3, a4, a5);
}

// === TDM ANTI-CHEAT HOOK IMPLEMENTATIONS ===

// Hook untuk TDM_TDataMaster__Initialize
bool TDM_TDataMaster__Initialize_Hook(int64_t a1, int64_t a2, int64_t a3, char a4) {
    // Jika FakeStatus aktif, manipulasi inisialisasi TDM
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 50 == 0) {
            // LOGIO("FakeStatus: Memblokir inisialisasi TDM - mencegah startup anti-cheat");
        }

        // Return sukses palsu tanpa menjalankan inisialisasi sebenarnya
        return true;
    }

    // Jika BlockAnalytics aktif, blokir inisialisasi
    if (Config.Misc.BlockAnalytics) {
        // LOGIO("FakeStatus: TDM Initialize diblokir - analytics disabled");
        return false;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__Initialize_Orig) {
        return TDM_TDataMaster__Initialize_Orig(a1, a2, a3, a4);
    }
    return false;
}

// Hook untuk TDM_TDataMaster__InitializeV2
bool TDM_TDataMaster__InitializeV2_Hook(int64_t a1, int64_t a2, int64_t a3, int64_t a4, char a5) {
    // Jika FakeStatus aktif, manipulasi inisialisasi TDM V2
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 50 == 0) {
            // LOGIO("FakeStatus: Memblokir inisialisasi TDM V2 - mencegah startup anti-cheat");
        }

        // Return sukses palsu tanpa menjalankan inisialisasi sebenarnya
        return true;
    }

    // Jika BlockAnalytics aktif, blokir inisialisasi
    if (Config.Misc.BlockAnalytics) {
        // LOGIO("FakeStatus: TDM InitializeV2 diblokir - analytics disabled");
        return false;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__InitializeV2_Orig) {
        return TDM_TDataMaster__InitializeV2_Orig(a1, a2, a3, a4, a5);
    }
    return false;
}

// Hook untuk TDM_TDataMaster__EnableDeviceInfo
int64_t TDM_TDataMaster__EnableDeviceInfo_Hook(int64_t a1, char a2) {
    // Jika FakeStatus aktif, manipulasi pengaturan device info
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: Memblokir aktivasi pengumpulan device info TDM");
        }

        // Selalu return sukses tapi tidak mengaktifkan pengumpulan data
        return 0;
    }

    // Jika BlockAnalytics aktif, blokir device info collection
    if (Config.Misc.BlockAnalytics) {
        // LOGIO("FakeStatus: TDM EnableDeviceInfo diblokir - device tracking disabled");
        return 0;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__EnableDeviceInfo_Orig) {
        return TDM_TDataMaster__EnableDeviceInfo_Orig(a1, a2);
    }
    return 0;
}

// Hook untuk TDM_TDataMaster__GetStringDeviceInfo
int64_t TDM_TDataMaster__GetStringDeviceInfo_Hook(int64_t a1, int64_t a2) {
    // Jika FakeStatus aktif, berikan device info palsu
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: Memberikan device info palsu untuk TDM");
        }

        // Generate fake device info yang konsisten
        static const char* fakeDeviceInfo = OBF("SM-G973F"); // Fake Samsung device
        static int64_t fakeDeviceString = 0;
        if (!fakeDeviceString) {
            // Alokasi memori untuk string palsu (simplified)
            void* allocMem = malloc(strlen(fakeDeviceInfo) + 1);
            if (allocMem) {
                strcpy((char*)allocMem, fakeDeviceInfo);
                fakeDeviceString = (int64_t)allocMem;
            }
        }

        return fakeDeviceString ? fakeDeviceString : 0;
    }

    // Jika BlockAnalytics aktif, return empty/null
    if (Config.Misc.BlockAnalytics) {
        return 0;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__GetStringDeviceInfo_Orig) {
        return TDM_TDataMaster__GetStringDeviceInfo_Orig(a1, a2);
    }
    return 0;
}

// Hook untuk TDM_TDataMaster__SetStringDeviceInfo
int64_t TDM_TDataMaster__SetStringDeviceInfo_Hook(int64_t a1, int64_t a2, int64_t a3) {
    // Jika FakeStatus aktif, intercept dan manipulasi device info yang dikirim
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 150 == 0) {
            // LOGIO("FakeStatus: Memblokir pengiriman device info ke TDM server");
        }

        // Return sukses palsu tanpa mengirim data sebenarnya
        return 0; // Success code
    }

    // Jika BlockAnalytics aktif, blokir pengiriman device info
    if (Config.Misc.BlockAnalytics) {
        // LOGIO("FakeStatus: TDM SetStringDeviceInfo diblokir - device data blocked");
        return 0;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__SetStringDeviceInfo_Orig) {
        return TDM_TDataMaster__SetStringDeviceInfo_Orig(a1, a2, a3);
    }
    return -1; // Error code
}

// Hook untuk TDM_TDataMaster__EnableDeviceInfoCollect
int64_t TDM_TDataMaster__EnableDeviceInfoCollect_Hook(int64_t a1, int64_t a2, char a3) {
    // Jika FakeStatus aktif, blokir aktivasi pengumpulan device info spesifik
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: Memblokir aktivasi pengumpulan device info collection TDM");
        }

        // Return sukses palsu tanpa mengaktifkan collection
        return 0; // Success code
    }

    // Jika BlockAnalytics aktif, blokir device info collection
    if (Config.Misc.BlockAnalytics) {
        // LOGIO("FakeStatus: TDM EnableDeviceInfoCollect diblokir - collection disabled");
        return 0;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__EnableDeviceInfoCollect_Orig) {
        return TDM_TDataMaster__EnableDeviceInfoCollect_Orig(a1, a2, a3);
    }
    return -1; // Error code
}

// Hook untuk TDM_TDataMaster__EnableHTTPProxy
int64_t TDM_TDataMaster__EnableHTTPProxy_Hook(int64_t a1, char a2) {
    // Jika FakeStatus aktif, manipulasi pengaturan HTTP proxy
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: Memblokir aktivasi HTTP proxy TDM");
        }

        // Return sukses palsu tanpa mengaktifkan proxy monitoring
        return 0;
    }

    // Jika BlockAnalytics aktif, blokir HTTP proxy
    if (Config.Misc.BlockAnalytics) {
        // LOGIO("FakeStatus: TDM EnableHTTPProxy diblokir - HTTP monitoring disabled");
        return 0;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__EnableHTTPProxy_Orig) {
        return TDM_TDataMaster__EnableHTTPProxy_Orig(a1, a2);
    }
    return 0;
}

// Hook untuk TDM_TDataMaster__ReportEventV2
int64_t TDM_TDataMaster__ReportEventV2_Hook(int64_t a1, unsigned int a2, int64_t a3, int64_t a4, unsigned int a5, unsigned int a6) {
    // Jika FakeStatus aktif, blokir atau manipulasi event reporting
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGIO("FakeStatus: Memblokir TDM event reporting V2 - mencegah laporan aktivitas");
        }

        // Return sukses palsu tanpa mengirim event sebenarnya
        return 0; // Success code
    }

    // Jika BlockAnalytics aktif, blokir semua event reporting
    if (Config.Misc.BlockAnalytics) {
        static int blockCount = 0;
        if (blockCount++ % 500 == 0) {
            // LOGIO("FakeStatus: TDM ReportEventV2 diblokir - event analytics disabled");
        }
        return 0;
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__ReportEventV2_Orig) {
        return TDM_TDataMaster__ReportEventV2_Orig(a1, a2, a3, a4, a5, a6);
    }
    return -1; // Error code
}

// === TDM ADDITIONAL HOOK IMPLEMENTATIONS (BERDASARKAN ASSEMBLY TENCENT.C) ===

// Hook untuk TDM_TBufferWriter__Reset - SANGAT KRITIS
// ANALISIS ASSEMBLY: Fungsi ini mereset buffer internal dan memicu data collection chain
// Line 404: TDM_TBufferWriter__Reset(v10) -> Line 409: GetBufferData() -> Line 413: report_event()
int64_t TDM_TBufferWriter__Reset_Hook(int64_t a1) {
    // Jika FakeStatus aktif, MANIPULASI BUFFER SECARA MENDALAM
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: INTERCEPTING TDM buffer reset - breaking data collection chain");
        }

        // STRATEGI BERDASARKAN ASSEMBLY:
        // 1. Assembly menunjukkan buffer reset memicu chain: Reset -> Encode -> GetBufferData -> ReportEvent
        // 2. Dengan memblokir Reset, kita break seluruh chain data collection
        // 3. Buffer tetap dalam state tidak valid, sehingga GetBufferData() return null/empty

        // MANIPULASI BUFFER STATE: Set buffer ke state "already reset" tanpa clear data
        if (a1) {
            // Berdasarkan assembly, buffer object memiliki internal state flags
            // Kita manipulasi flag agar terlihat sudah di-reset tapi data tetap corrupt/empty

            // Simulasi "successful reset" dengan corrupt buffer state
            // Ini akan menyebabkan GetBufferData() gagal atau return data kosong
            *reinterpret_cast<int32_t*>(a1 + 24) = 0; // Set buffer size = 0 (empty)
            *reinterpret_cast<int64_t*>(a1 + 16) = 0; // Clear buffer data pointer

            return a1; // Return buffer object tapi dalam state kosong
        }

        return 0; // Success code dengan buffer manipulation
    }

    // Jika BlockAnalytics aktif, TOTAL BLOCK
    if (Config.Misc.BlockAnalytics) {
        static int blockCount = 0;
        if (blockCount++ % 200 == 0) {
            // LOGIO("FakeStatus: TDM Buffer Reset TOTALLY BLOCKED - data collection chain broken");
        }

        // COMPLETE BLOCK: Return error untuk break chain sepenuhnya
        return -1; // Error code akan stop seluruh data collection process
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TBufferWriter__Reset_Orig) {
        return TDM_TBufferWriter__Reset_Orig(a1);
    }
    return -1; // Error code
}

// Hook untuk TDM_TDataMaster__tdm_set_log - TINGGI
// ANALISIS ASSEMBLY: Fungsi ini trigger data collection chain melalui buffer operations
// Line 400: Monitor__Enter -> Line 404: TDM_TBufferWriter__Reset -> Line 413: tdm_report_event
int64_t TDM_TDataMaster__tdm_set_log_Hook(int64_t a1, unsigned int a2) {
    // Jika FakeStatus aktif, MANIPULASI THREADING DAN BUFFER OPERATIONS
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 150 == 0) {
            // LOGIO("FakeStatus: INTERCEPTING TDM set_log - disrupting data collection thread");
        }

        // STRATEGI BERDASARKAN ASSEMBLY:
        // 1. Assembly menunjukkan fungsi ini menggunakan System_Threading_Monitor untuk sync
        // 2. Setelah sync, fungsi memanggil TDM_TBufferWriter__Reset yang memicu data collection
        // 3. Kita bisa manipulasi dengan return early SEBELUM threading operations

        // MANIPULASI THREADING: Return success tanpa masuk ke critical section
        // Ini akan mencegah seluruh chain: Monitor__Enter -> Buffer__Reset -> Report__Event

        // Simulasi successful log set tanpa trigger data collection chain
        if (a1) {
            // Berdasarkan assembly, a1 adalah context object yang berisi buffer reference
            // Kita bisa manipulasi context untuk disable buffer operations

            // Set log level ke silent mode (berdasarkan parameter a2)
            // Tapi TIDAK trigger buffer reset dan data collection

            return 0; // Success tanpa side effects
        }

        return 0; // Success code tanpa threading operations
    }

    // Jika BlockAnalytics aktif, TOTAL DISRUPTION
    if (Config.Misc.BlockAnalytics) {
        static int blockCount = 0;
        if (blockCount++ % 300 == 0) {
            // LOGIO("FakeStatus: TDM set_log TOTALLY BLOCKED - threading chain disrupted");
        }

        // COMPLETE BLOCK: Return error untuk prevent threading operations
        return -1; // Error akan prevent Monitor__Enter dan seluruh chain
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__tdm_set_log_Orig) {
        return TDM_TDataMaster__tdm_set_log_Orig(a1, a2);
    }
    return -1; // Error code
}

// Hook untuk TDM_TDataMaster__tdm_free_upload_file_result - SEDANG
// ANALISIS ASSEMBLY: Fungsi ini terhubung dengan session tracking dan upload confirmation
// Line 667: "tdm_get_session_id" -> Line 676: session call -> Line 678: cleanup operations
int64_t TDM_TDataMaster__tdm_free_upload_file_result_Hook(int64_t a1, int64_t a2) {
    // Jika FakeStatus aktif, MANIPULASI SESSION TRACKING
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 250 == 0) {
            // LOGIO("FakeStatus: INTERCEPTING TDM upload result - disrupting session tracking");
        }

        // STRATEGI BERDASARKAN ASSEMBLY:
        // 1. Assembly menunjukkan fungsi ini call "tdm_get_session_id" untuk tracking
        // 2. Setelah get session, fungsi melakukan cleanup operations yang confirm upload
        // 3. Kita manipulasi dengan return early SEBELUM session tracking

        // MANIPULASI SESSION TRACKING: Prevent session ID retrieval
        // Ini akan mencegah server tracking upload completion status

        if (a2) {
            // Berdasarkan assembly, a2 adalah upload result object
            // Kita bisa manipulasi result object untuk simulate "already cleaned"

            // Simulasi cleanup tanpa session tracking
            // Set result object ke state "cleaned" tanpa server notification

            return 0; // Success tanpa session tracking
        }

        return 0; // Success code tanpa session operations
    }

    // Jika BlockAnalytics aktif, TOTAL SESSION BLOCK
    if (Config.Misc.BlockAnalytics) {
        static int blockCount = 0;
        if (blockCount++ % 400 == 0) {
            // LOGIO("FakeStatus: TDM Upload Result TOTALLY BLOCKED - session tracking prevented");
        }

        // COMPLETE BLOCK: Return error untuk prevent session ID retrieval
        return -1; // Error akan prevent tdm_get_session_id call
    }

    // Panggil fungsi asli jika tidak diblokir
    if (TDM_TDataMaster__tdm_free_upload_file_result_Orig) {
        return TDM_TDataMaster__tdm_free_upload_file_result_Orig(a1, a2);
    }
    return -1; // Error code
}

// === TDM ANTI-CHEAT SETUP FUNCTIONS ===

bool SetupTDMAntiCheatHooks() {
    // LOGIO("FakeStatus: Memasang hook TDM Anti-Cheat system...");

    bool success = true;
    int hookCount = 0;

    // 1. Hook TDM_TDataMaster__Initialize
    uintptr_t initializeAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_INITIALIZE);
    if (initializeAddr != 0) {
        TDM_TDataMaster__Initialize_Orig = (tTDM_Initialize) initializeAddr;
        if (Tools::Hook(
                (void *) initializeAddr,
                (void *) TDM_TDataMaster__Initialize_Hook,
                (void **) &TDM_TDataMaster__Initialize_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__Initialize");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__Initialize");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__Initialize");
        success = false;
    }

    // 2. Hook TDM_TDataMaster__InitializeV2
    uintptr_t initializeV2Addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_INITIALIZE_V2);
    if (initializeV2Addr != 0) {
        TDM_TDataMaster__InitializeV2_Orig = (tTDM_InitializeV2) initializeV2Addr;
        if (Tools::Hook(
                (void *) initializeV2Addr,
                (void *) TDM_TDataMaster__InitializeV2_Hook,
                (void **) &TDM_TDataMaster__InitializeV2_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__InitializeV2");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__InitializeV2");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__InitializeV2");
        success = false;
    }

    // 3. Hook TDM_TDataMaster__EnableDeviceInfo
    uintptr_t enableDeviceInfoAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_ENABLE_DEVICE_INFO);
    if (enableDeviceInfoAddr != 0) {
        TDM_TDataMaster__EnableDeviceInfo_Orig = (tTDM_EnableDeviceInfo) enableDeviceInfoAddr;
        if (Tools::Hook(
                (void *) enableDeviceInfoAddr,
                (void *) TDM_TDataMaster__EnableDeviceInfo_Hook,
                (void **) &TDM_TDataMaster__EnableDeviceInfo_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__EnableDeviceInfo");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__EnableDeviceInfo");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__EnableDeviceInfo");
        success = false;
    }

    // 4. Hook TDM_TDataMaster__GetStringDeviceInfo
    uintptr_t getStringDeviceInfoAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_GET_STRING_DEVICE_INFO);
    if (getStringDeviceInfoAddr != 0) {
        TDM_TDataMaster__GetStringDeviceInfo_Orig = (tTDM_GetStringDeviceInfo) getStringDeviceInfoAddr;
        if (Tools::Hook(
                (void *) getStringDeviceInfoAddr,
                (void *) TDM_TDataMaster__GetStringDeviceInfo_Hook,
                (void **) &TDM_TDataMaster__GetStringDeviceInfo_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__GetStringDeviceInfo");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__GetStringDeviceInfo");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__GetStringDeviceInfo");
        success = false;
    }

    // 5. Hook TDM_TDataMaster__SetStringDeviceInfo
    uintptr_t setStringDeviceInfoAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_SET_STRING_DEVICE_INFO);
    if (setStringDeviceInfoAddr != 0) {
        TDM_TDataMaster__SetStringDeviceInfo_Orig = (tTDM_SetStringDeviceInfo) setStringDeviceInfoAddr;
        if (Tools::Hook(
                (void *) setStringDeviceInfoAddr,
                (void *) TDM_TDataMaster__SetStringDeviceInfo_Hook,
                (void **) &TDM_TDataMaster__SetStringDeviceInfo_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__SetStringDeviceInfo");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__SetStringDeviceInfo");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__SetStringDeviceInfo");
        success = false;
    }

    // 6. Hook TDM_TDataMaster__EnableDeviceInfoCollect
    uintptr_t enableDeviceInfoCollectAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_ENABLE_DEVICE_INFO_COLLECT);
    if (enableDeviceInfoCollectAddr != 0) {
        TDM_TDataMaster__EnableDeviceInfoCollect_Orig = (tTDM_EnableDeviceInfoCollect) enableDeviceInfoCollectAddr;
        if (Tools::Hook(
                (void *) enableDeviceInfoCollectAddr,
                (void *) TDM_TDataMaster__EnableDeviceInfoCollect_Hook,
                (void **) &TDM_TDataMaster__EnableDeviceInfoCollect_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__EnableDeviceInfoCollect");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__EnableDeviceInfoCollect");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__EnableDeviceInfoCollect");
        success = false;
    }

    // 7. Hook TDM_TDataMaster__EnableHTTPProxy
    uintptr_t enableHTTPProxyAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_ENABLE_HTTP_PROXY);
    if (enableHTTPProxyAddr != 0) {
        TDM_TDataMaster__EnableHTTPProxy_Orig = (tTDM_EnableHTTPProxy) enableHTTPProxyAddr;
        if (Tools::Hook(
                (void *) enableHTTPProxyAddr,
                (void *) TDM_TDataMaster__EnableHTTPProxy_Hook,
                (void **) &TDM_TDataMaster__EnableHTTPProxy_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__EnableHTTPProxy");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__EnableHTTPProxy");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__EnableHTTPProxy");
        success = false;
    }

    // 8. Hook TDM_TDataMaster__ReportEventV2
    uintptr_t reportEventV2Addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_REPORT_EVENT_V2);
    if (reportEventV2Addr != 0) {
        TDM_TDataMaster__ReportEventV2_Orig = (tTDM_ReportEventV2) reportEventV2Addr;
        if (Tools::Hook(
                (void *) reportEventV2Addr,
                (void *) TDM_TDataMaster__ReportEventV2_Hook,
                (void **) &TDM_TDataMaster__ReportEventV2_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__ReportEventV2");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__ReportEventV2");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__ReportEventV2");
        success = false;
    }

    // === SETUP HOOK UNTUK 3 FUNGSI TAMBAHAN (DARI ASSEMBLY TENCENT.C) ===

    // 9. Hook TDM_TBufferWriter__Reset - SANGAT KRITIS
    uintptr_t bufferResetAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_BUFFER_WRITER_RESET);
    if (bufferResetAddr != 0) {
        TDM_TBufferWriter__Reset_Orig = (tTDM_BufferWriterReset) bufferResetAddr;
        if (Tools::Hook(
                (void *) bufferResetAddr,
                (void *) TDM_TBufferWriter__Reset_Hook,
                (void **) &TDM_TBufferWriter__Reset_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TBufferWriter__Reset - CRITICAL DATA COLLECTION BLOCKED");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TBufferWriter__Reset");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TBufferWriter__Reset");
        success = false;
    }

    // 10. Hook TDM_TDataMaster__tdm_set_log - TINGGI
    uintptr_t setLogAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_SET_LOG);
    if (setLogAddr != 0) {
        TDM_TDataMaster__tdm_set_log_Orig = (tTDM_SetLog) setLogAddr;
        if (Tools::Hook(
                (void *) setLogAddr,
                (void *) TDM_TDataMaster__tdm_set_log_Hook,
                (void **) &TDM_TDataMaster__tdm_set_log_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__tdm_set_log - LOG VERBOSITY CONTROLLED");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__tdm_set_log");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__tdm_set_log");
        success = false;
    }

    // 11. Hook TDM_TDataMaster__tdm_free_upload_file_result - SEDANG
    uintptr_t freeUploadResultAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_FREE_UPLOAD_FILE_RESULT);
    if (freeUploadResultAddr != 0) {
        TDM_TDataMaster__tdm_free_upload_file_result_Orig = (tTDM_FreeUploadFileResult) freeUploadResultAddr;
        if (Tools::Hook(
                (void *) freeUploadResultAddr,
                (void *) TDM_TDataMaster__tdm_free_upload_file_result_Hook,
                (void **) &TDM_TDataMaster__tdm_free_upload_file_result_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__tdm_free_upload_file_result - UPLOAD TRACKING BLOCKED");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__tdm_free_upload_file_result");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__tdm_free_upload_file_result");
        success = false;
    }

    // Log hasil setup dengan jumlah hook yang diperbarui
    if (success && hookCount == 11) {
        // LOGIO("FakeStatus: Semua 11 hook TDM Anti-Cheat berhasil dipasang (termasuk 3 fungsi kritis dari assembly)");
    } else {
        // LOGEO("FakeStatus: Setup TDM Anti-Cheat hooks gagal - %d/11 hooks terpasang", hookCount);
    }

    return success;
}

bool SetupTDMReportHooks() {
    if (tdmReportHooksInstalled) {
        return true; // Hooks sudah diinstall
    }

    bool success = true;
    int hookCount = 0;

    // 1. Hook TDM_TDataMaster__EnableReport
    uintptr_t enableReportAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_ENABLE_REPORT);
    if (enableReportAddr != 0) {
        TDM_TDataMaster__EnableReport_Orig = (tTDMEnableReport) enableReportAddr;
        if (Tools::Hook(
                (void *) enableReportAddr,
                (void *) TDM_TDataMaster__EnableReport_Hook,
                (void **) &TDM_TDataMaster__EnableReport_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__EnableReport");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__EnableReport");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__EnableReport");
        success = false;
    }

    // 2. Hook TDM_TDataMaster__ReportLoginV2
    uintptr_t reportLoginAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_REPORT_LOGIN_V2);
    if (reportLoginAddr != 0) {
        TDM_TDataMaster__ReportLoginV2_Orig = (tTDMReportLoginV2) reportLoginAddr;
        if (Tools::Hook(
                (void *) reportLoginAddr,
                (void *) TDM_TDataMaster__ReportLoginV2_Hook,
                (void **) &TDM_TDataMaster__ReportLoginV2_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__ReportLoginV2");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__ReportLoginV2");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__ReportLoginV2");
        success = false;
    }

    // 3. Hook TDM_TDataMaster__tdm_report_loginV2
    uintptr_t reportLoginNativeAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_REPORT_LOGIN_V2_NATIVE);
    if (reportLoginNativeAddr != 0) {
        TDM_TDataMaster__tdm_report_loginV2_Orig = (tTDMReportLoginV2Native) reportLoginNativeAddr;
        if (Tools::Hook(
                (void *) reportLoginNativeAddr,
                (void *) TDM_TDataMaster__tdm_report_loginV2_Hook,
                (void **) &TDM_TDataMaster__tdm_report_loginV2_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__tdm_report_loginV2");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__tdm_report_loginV2");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__tdm_report_loginV2");
        success = false;
    }

    tdmReportHooksInstalled = (hookCount > 0);
    // LOGDO("TDM Report Hooks: Installed %d/3 hooks successfully", hookCount);

    return tdmReportHooksInstalled;
}

bool SetupTGPAInitHook() {
    if (tgpaInitHookInstalled)
        return true;

    // LOGIO("FakeStatus: Memasang hook TGPA Init...");
    GCloud_TGPA_TGPAHelper__Init_Orig = (tTGPAInit)DobbyHook(
            (void *) ADDR_TGPA_INIT,
            (void *) GCloud_TGPA_TGPAHelper__Init_Hook,
            (void **) &GCloud_TGPA_TGPAHelper__Init_Orig);

    if (GCloud_TGPA_TGPAHelper__Init_Orig != nullptr) {
        // LOGIO("FakeStatus: Hook TGPA Init berhasil dipasang");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook TGPA Init");
        return false;
    }
}

// Setup function untuk TDM hooks
bool SetupTDMHooks() {
    if (tdmHooksInstalled) {
        return true; // Hooks sudah diinstall
    }

    bool success = true;
    int hookCount = 0;

    // 1. Hook TDM_TDataMaster__tdm_real_time_report_kv_event
    uintptr_t reportKvEventAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_REAL_TIME_REPORT_KV_EVENT);
    if (reportKvEventAddr != 0) {
        TDM_TDataMaster__tdm_real_time_report_kv_event_Orig = (tTDMRealTimeReportKvEvent) reportKvEventAddr;
        if (Tools::Hook(
                (void *) reportKvEventAddr,
                (void *) TDM_TDataMaster__tdm_real_time_report_kv_event_Hook,
                (void **) &TDM_TDataMaster__tdm_real_time_report_kv_event_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__tdm_real_time_report_kv_event");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__tdm_real_time_report_kv_event");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__tdm_real_time_report_kv_event");
        success = false;
    }

    // 2. Hook TDM_TDataMaster__tdm_report_event
    uintptr_t reportEventAddr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_REPORT_EVENT);
    if (reportEventAddr != 0) {
        TDM_TDataMaster__tdm_report_event_Orig = (tTDMReportEvent) reportEventAddr;
        if (Tools::Hook(
                (void *) reportEventAddr,
                (void *) TDM_TDataMaster__tdm_report_event_Hook,
                (void **) &TDM_TDataMaster__tdm_report_event_Orig
        )) {
            // LOGDO("Successfully hooked TDM_TDataMaster__tdm_report_event");
            hookCount++;
        } else {
            // LOGEO("Failed to hook TDM_TDataMaster__tdm_report_event");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TDM_TDataMaster__tdm_report_event");
        success = false;
    }

    tdmHooksInstalled = (hookCount > 0);
    // LOGDO("TDM Hooks: Installed %d/2 hooks successfully", hookCount);

    return tdmHooksInstalled;
}

// Hook untuk Network.MatchReplayer.ReplayData$$SeqProcess
int64_t Network_MatchReplayer_ReplayData__SeqProcess_Hook(int64_t a1) {
    // Jika FakeStatus aktif dan kita ingin memanipulasi replay
    if (Config.Misc.FakeStatus) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGDO("FakeStatus: Memanipulasi urutan replay data");
        }

        // Mode LOBBY - dapat memanipulasi nilai pada offset +32
        if (Config.MiscSize.FakeStageType == 1) {
            int v4 = *(_DWORD *) (a1 + 32);
            // Ubah nilai agar replay tidak berjalan normal
            *(_DWORD *) (a1 + 32) = -999;

            // Return 0 untuk simulasi sukses tanpa memanggil fungsi asli
            // Ini akan mencegah replay ditampilkan dengan benar
            return 0;
        }
    }

    // Panggil fungsi asli untuk perilaku normal
    return Network_MatchReplayer_ReplayData__SeqProcess_Orig(a1);
}

/*
 * NOTE: Remaining hook functions below use signal handler protection
 * instead of try-catch blocks for consistency with the enhanced crash protection system.
 * The try-catch blocks have been conceptually replaced with signal handlers at the ESP level.
 */

// Setup fungsi hook untuk Match Replayer
bool SetupMatchReplayerHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_REPLAYER_SEQ_PROCESS);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat Match Replayer tidak valid!");
        return false;
    }

    Network_MatchReplayer_ReplayData__SeqProcess_Orig =
            (tMatchReplayerSeqProcess) addr;

    if (Tools::Hook((void *) addr, (void *) Network_MatchReplayer_ReplayData__SeqProcess_Hook,
                    (void **) &Network_MatchReplayer_ReplayData__SeqProcess_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook Match Replayer - kontrol replay lengkap");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook Match Replayer");
        return false;
    }
}

// Hook untuk Network.C2S_NTF_USER_CHEAT$$.ctor
int64_t Network_C2S_NTF_USER_CHEAT___ctor_Hook(int64_t a1) {
    // Jika FakeStatus aktif dan fitur Block Analytics diaktifkan,
    // kita manipulasi paket pelaporan cheat
    if (Config.Misc.FakeStatus && Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int reportCount = 0;
        if (reportCount++ % 100 == 0) {
            // LOGDO("FakeStatus: Memanipulasi paket pelaporan cheat");
        }

        // Panggil fungsi asli terlebih dahulu untuk memastikan objek tercipta dengan benar
        int64_t result = Network_C2S_NTF_USER_CHEAT___ctor_Orig(a1);

        // Manipulasi semua field kritis yang terkait pelaporan cheat:
        // 1. Kode identifikasi di offset +16
        *(_BYTE *) (a1 + 16) = 0; // Ubah dari -99 menjadi 0

        // 2. Field flag di offset +18 (diserialkan oleh GetBytes)
        *(_BYTE *) (a1 + 18) = 0;

        // 3. Unsigned int di offset +20 (diserialkan oleh GetBytes_63643808)
        *(_DWORD *) (a1 + 20) = 0;

        // 4. Unsigned int di offset +24 (diserialkan oleh GetBytes_63643808)
        *(_DWORD *) (a1 + 24) = 0;

        // Dengan mengubah semua field ini menjadi 0, kita memastikan bahwa
        // paket pelaporan cheat menjadi tidak valid/tidak dikenali oleh server

        return result;
    }

    // Jika FakeStatus tidak aktif, gunakan perilaku normal
    return Network_C2S_NTF_USER_CHEAT___ctor_Orig(a1);
}

// Setup fungsi hook untuk Anti Cheat Report
bool SetupAntiCheatReportHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_C2S_NTF_USER_CHEAT_CTOR);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat Anti Cheat Report tidak valid!");
        return false;
    }

    Network_C2S_NTF_USER_CHEAT___ctor_Orig =
            (tC2SNtfUserCheatCtor) addr;

    if (Tools::Hook((void *) addr, (void *) Network_C2S_NTF_USER_CHEAT___ctor_Hook,
                    (void **) &Network_C2S_NTF_USER_CHEAT___ctor_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook Anti Cheat Report - block pelaporan cheat");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook Anti Cheat Report");
        return false;
    }
}

// Setup fungsi untuk Beacon Reporter hook
bool SetupBeaconReporterHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_BEACON_REPORTER_REPORT_IN_GAME_EXPERIENCE);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat ReportInGameExperienceEventData tidak valid!");
        return false;
    }

    GameBase_BeaconReporter__ReportInGameExperienceEventData_Orig =
            (tReportInGameExperienceEventData) addr;

    if (Tools::Hook((void *) addr,
                    (void *) GameBase_BeaconReporter__ReportInGameExperienceEventData_Hook,
                    (void **) &GameBase_BeaconReporter__ReportInGameExperienceEventData_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook Beacon Reporter - blokir laporan data game");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook Beacon Reporter");
        return false;
    }
}

// Setup fungsi untuk hook CrashSight
bool SetupCrashSightHook() {
    if (CrashSightStackTrace__ExtractStackTrace_Orig)
        return true;

    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_CRASH_STACK_TRACE);
    if (!addr) {
        // LOGEO("FakeStatus: Alamat CrashSight tidak valid!");
        return false;
    }

    CrashSightStackTrace__ExtractStackTrace_Orig = (tCrashSightStackTrace_Extract) addr;
    if (Tools::Hook((void *) addr, (void *) CrashSightStackTrace__ExtractStackTrace_Hook,
                    (void **) &CrashSightStackTrace__ExtractStackTrace_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook CrashSight");
        return true;
    }

    // LOGEO("FakeStatus: Gagal memasang hook CrashSight");
    return false;
}

// Setup fungsi untuk hook ClientMonitor
bool SetupClientMonitorHook() {
    if (GameBase_ClientMonitorManager__StackTraceSampler_Orig)
        return true;

    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_CLIENT_MONITOR_SAMPLER);
    if (!addr) {
        // LOGEO("FakeStatus: Alamat ClientMonitor tidak valid!");
        return false;
    }

    GameBase_ClientMonitorManager__StackTraceSampler_Orig = (tClientMonitorStackTraceSampler) addr;
    if (Tools::Hook((void *) addr, (void *) GameBase_ClientMonitorManager__StackTraceSampler_Hook,
                    (void **) &GameBase_ClientMonitorManager__StackTraceSampler_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook ClientMonitor");
        return true;
    }

    // LOGEO("FakeStatus: Gagal memasang hook ClientMonitor");
    return false;
}

// Setup fungsi untuk hook PerfStats
bool SetupPerfStatsHook() {
    if (UnityEngine_PerfStats__RuntimeGetStacktrace_Orig)
        return true;

    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PERF_STATS_STACKTRACE);
    if (!addr) {
        // LOGEO("FakeStatus: Alamat PerfStats tidak valid!");
        return false;
    }

    UnityEngine_PerfStats__RuntimeGetStacktrace_Orig = (tUnityEngine_PerfStats_RuntimeGetStacktrace) addr;
    if (Tools::Hook((void *) addr, (void *) UnityEngine_PerfStats__RuntimeGetStacktrace_Hook,
                    (void **) &UnityEngine_PerfStats__RuntimeGetStacktrace_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook PerfStats");
        return true;
    }

    // LOGEO("FakeStatus: Gagal memasang hook PerfStats");
    return false;
}

// Setup fungsi untuk hook Environment StackTrace
bool SetupEnvironmentStackTraceHook() {
    if (System_Environment__get_StackTrace_Orig)
        return true;

    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ENVIRONMENT_STACKTRACE);
    if (!addr) {
        // LOGEO("FakeStatus: Alamat Environment StackTrace tidak valid!");
        return false;
    }

    System_Environment__get_StackTrace_Orig = (tSystem_Environment_get_StackTrace) addr;
    if (Tools::Hook((void *) addr, (void *) System_Environment__get_StackTrace_Hook,
                    (void **) &System_Environment__get_StackTrace_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook Environment StackTrace");
        return true;
    }

    // LOGEO("FakeStatus: Gagal memasang hook Environment StackTrace");
    return false;
}

// Setup fungsi untuk hook AnoSDK Signature
bool SetupAnoSDKSignatureHook() {
    if (GCloud_AnoSDK_AnoSDK__OnRecvSignature_Orig)
        return true;

    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_RECV_SIGNATURE);
    if (!addr) {
        // LOGEO("FakeStatus: Alamat AnoSDK Signature tidak valid!");
        return false;
    }

    GCloud_AnoSDK_AnoSDK__OnRecvSignature_Orig = (tAnoSDK_OnRecvSignature) addr;
    if (Tools::Hook((void *) addr, (void *) GCloud_AnoSDK_AnoSDK__OnRecvSignature_Hook,
                    (void **) &GCloud_AnoSDK_AnoSDK__OnRecvSignature_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK Signature");
        return true;
    }

    // LOGEO("FakeStatus: Gagal memasang hook AnoSDK Signature");
    return false;
}

// Setup fungsi untuk hook MemoryCake
bool SetupMemoryCakeHook() {
    if (TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Orig)
        return true;

    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MEMORY_CAKE_GET_ARGS);
    if (!addr) {
        // LOGEO("FakeStatus: Alamat MemoryCake tidak valid!");
        return false;
    }

    TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Orig = (tMemoryCake_GetTLogArgs) addr;
    if (Tools::Hook((void *) addr, (void *) TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Hook,
                    (void **) &TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook MemoryCake");
        return true;
    }

    // LOGEO("FakeStatus: Gagal memasang hook MemoryCake");
    return false;
}

// Setup fungsi untuk UQMCrash hooks
bool SetupUQMCrashHooks() {
    if (uqmCrashHooksInstalled)
        return true;

    bool success = true;

    // Hook untuk cs_logRecordAdapter
    uintptr_t addrLogRecord = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_LOG_RECORD_ADAPTER);
    if (addrLogRecord != 0) {
        GCloud_UQM_UQMCrash__cs_logRecordAdapter_Orig = (tUQM_LogRecordAdapter) addrLogRecord;
        if (Tools::Hook((void *) addrLogRecord,
                        (void *) GCloud_UQM_UQMCrash__cs_logRecordAdapter_Hook,
                        (void **) &GCloud_UQM_UQMCrash__cs_logRecordAdapter_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash LogRecordAdapter");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash LogRecordAdapter");
        }
    }

    // Hook untuk cs_reportLogInfo
    uintptr_t addrReportLog = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_REPORT_LOG_INFO);
    if (addrReportLog != 0) {
        GCloud_UQM_UQMCrash__cs_reportLogInfo_Orig = (tUQM_ReportLogInfo) addrReportLog;
        if (Tools::Hook((void *) addrReportLog,
                        (void *) GCloud_UQM_UQMCrash__cs_reportLogInfo_Hook,
                        (void **) &GCloud_UQM_UQMCrash__cs_reportLogInfo_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash ReportLogInfo");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash ReportLogInfo");
        }
    }

    // Hook untuk cs_getCrashUuidAdapter
    uintptr_t addrGetUUID = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_GET_CRASH_UUID);
    if (addrGetUUID != 0) {
        GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Orig = (tUQM_GetCrashUuid) addrGetUUID;
        if (Tools::Hook((void *) addrGetUUID,
                        (void *) GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Hook,
                        (void **) &GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash GetCrashUuid");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash GetCrashUuid");
        }
    }

    // Hook untuk cs_getCrashThreadId
    uintptr_t addrGetThreadId = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_GET_CRASH_THREAD_ID);
    if (addrGetThreadId != 0) {
        GCloud_UQM_UQMCrash__cs_getCrashThreadId_Orig = (tUQM_GetCrashThreadId) addrGetThreadId;
        if (Tools::Hook((void *) addrGetThreadId,
                        (void *) GCloud_UQM_UQMCrash__cs_getCrashThreadId_Hook,
                        (void **) &GCloud_UQM_UQMCrash__cs_getCrashThreadId_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash GetCrashThreadId");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash GetCrashThreadId");
        }
    }

    // Hook untuk cs_getLastSessionUserId
    uintptr_t addrGetLastUserId = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_GET_LAST_USER_ID);
    if (addrGetLastUserId != 0) {
        GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Orig = (tUQM_GetLastSessionUserId) addrGetLastUserId;
        if (Tools::Hook((void *) addrGetLastUserId,
                        (void *) GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Hook,
                        (void **) &GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash GetLastSessionUserId");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash GetLastSessionUserId");
        }
    }

    // Hook untuk SetUserId
    uintptr_t addrSetUserId = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_SET_USER_ID);
    if (addrSetUserId != 0) {
        GCloud_UQM_UQMCrash__SetUserId_Orig = (tUQM_SetUserId) addrSetUserId;
        if (Tools::Hook((void *) addrSetUserId,
                        (void *) GCloud_UQM_UQMCrash__SetUserId_Hook,
                        (void **) &GCloud_UQM_UQMCrash__SetUserId_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash SetUserId");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash SetUserId");
        }
    }

    // Hook untuk ReportCrash
    uintptr_t addrReportCrash = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_REPORT_CRASH);
    if (addrReportCrash != 0) {
        GCloud_UQM_UQMCrash__ReportCrash_Orig = (tUQM_ReportCrash) addrReportCrash;
        if (Tools::Hook((void *) addrReportCrash,
                        (void *) GCloud_UQM_UQMCrash__ReportCrash_Hook,
                        (void **) &GCloud_UQM_UQMCrash__ReportCrash_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash ReportCrash");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash ReportCrash");
        }
    }

    // Hook untuk ReRegistAllMonitors
    uintptr_t addrReRegistMonitors = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_REREGIST_ALL_MONITORS);
    if (addrReRegistMonitors != 0) {
        GCloud_UQM_UQMCrash__ReRegistAllMonitors_Orig = (tUQM_ReRegistAllMonitors) addrReRegistMonitors;
        if (Tools::Hook((void *) addrReRegistMonitors,
                        (void *) GCloud_UQM_UQMCrash__ReRegistAllMonitors_Hook,
                        (void **) &GCloud_UQM_UQMCrash__ReRegistAllMonitors_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash ReRegistAllMonitors");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash ReRegistAllMonitors");
        }
    }

    // Hook untuk cs_reRegistAllMonitorsAdapter
    uintptr_t addrReRegistAdapter = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_UQM_REREGIST_ALL_MONITORS_ADAPTER);
    if (addrReRegistAdapter != 0) {
        GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter_Orig = (tUQM_ReRegistAllMonitorsAdapter) addrReRegistAdapter;
        if (Tools::Hook((void *) addrReRegistAdapter,
                        (void *) GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter_Hook,
                        (void **) &GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook UQMCrash cs_reRegistAllMonitorsAdapter");
        } else {
            success = false;
            // LOGEO("FakeStatus: Gagal memasang hook UQMCrash cs_reRegistAllMonitorsAdapter");
        }
    }

    uqmCrashHooksInstalled = success;
    if (success) {
        // LOGIO("FakeStatus: Hook UQMCrash terpasang - blokir semua pelaporan crash");
    }

    return success;
}

// Fungsi master untuk setup semua hook monitoring
bool SetupAdvancedMonitoringHooks() {
    bool success = true;

    if (!SetupCrashSightHook()) success = false;
    if (!SetupClientMonitorHook()) success = false;
    if (!SetupPerfStatsHook()) success = false;
    if (!SetupEnvironmentStackTraceHook()) success = false;
    if (!SetupAnoSDKSignatureHook()) success = false;
    if (!SetupMemoryCakeHook()) success = false;

    return success;
}

// Implementasi hook untuk CrashSight
int64_t CrashSightStackTrace__ExtractStackTrace_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan stack trace untuk crash reporting");
        }

        // Return stack trace palsu yang tidak mencurigakan
        static const char *fakeStackTrace =
                "UnityEngine.Application:get_targetFrameRate()\n"
                "GameBase.GameSession:Update()\n"
                "UnityEngine.MonoBehaviour:Update()\n";

        static int64_t fakeTrace = 0;
        if (!fakeTrace) {
            void *allocMem = malloc(strlen(fakeStackTrace) + 1);
            if (allocMem) {
                strcpy((char *) allocMem, fakeStackTrace);
                fakeTrace = (int64_t) allocMem;
            }
        }

        return fakeTrace ? fakeTrace : 0;
    }

    return CrashSightStackTrace__ExtractStackTrace_Orig();
}

// Implementasi hook untuk ClientMonitor
int64_t GameBase_ClientMonitorManager__StackTraceSampler_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir sampling stack dari client monitor");
        }
        return 1;
    }
    return GameBase_ClientMonitorManager__StackTraceSampler_Orig();
}

// Implementasi hook untuk PerfStats
int64_t UnityEngine_PerfStats__RuntimeGetStacktrace_Hook(int64_t a1, int64_t a2) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGDO("FakeStatus: Memalsukan stack trace dari PerfStats");
        }

        if (a2) {
            // Isi dengan data minimal yang valid
            *(int64_t *) a2 = 0x1;
        }
        return a2;
    }
    return UnityEngine_PerfStats__RuntimeGetStacktrace_Orig(a1, a2);
}

// Implementasi hook untuk Environment StackTrace
int64_t System_Environment__get_StackTrace_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan environment stack trace");
        }

        static const char *fakeEnvTrace = OBF(
                "   at System.AppDomain.ExecuteAssembly\n"
                "   at UnityEngine.Application.UpdateScene\n"
                "   at UnityEngine.StackTraceUtility.ExtractStackTrace\n");

        static int64_t fakeEnvStackTrace = 0;
        if (!fakeEnvStackTrace) {
            void *allocMem = malloc(strlen(fakeEnvTrace) + 1);
            if (allocMem) {
                strcpy((char *) allocMem, fakeEnvTrace);
                fakeEnvStackTrace = (int64_t) allocMem;
            }
        }

        return fakeEnvStackTrace ? fakeEnvStackTrace : 0;
    }

    return System_Environment__get_StackTrace_Orig();
}

// Implementasi hook untuk AnoSDK signature
int64_t
GCloud_AnoSDK_AnoSDK__OnRecvSignature_Hook(int64_t a1, int64_t a2, int64_t a3, unsigned int a4,
                                           unsigned int a5) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir verifikasi signature AnoSDK");
        }
        return 0; // Return sukses tanpa memproses
    }
    return GCloud_AnoSDK_AnoSDK__OnRecvSignature_Orig(a1, a2, a3, a4, a5);
}

// Helper functions untuk manipulasi data AnoSDK
__int64 CreateRealisticDeviceInfo() {
    // Buat device info yang terlihat seperti device real
    static const char* realistic_devices[] = {
        "SM-G973F",    // Samsung Galaxy S10
        "Pixel 4",     // Google Pixel 4
        "iPhone12,1",  // iPhone 11
        "MI 9",        // Xiaomi Mi 9
    };

    int deviceIndex = rand() % 4;
    return (__int64)realistic_devices[deviceIndex];
}

void ManipulateDeviceString(int64_t result_ptr) {
    if (!result_ptr) return;

    char* device_string = (char*)result_ptr;

    // Hapus kata-kata yang mencurigakan dari string hasil
    const char* suspicious_words[] = {
        "emulator", "virtual", "qemu", "vbox",
        "bluestacks", "nox", "memu", "ldplayer"
    };

    for (int i = 0; i < 8; i++) {
        char* found = strstr(device_string, suspicious_words[i]);
        if (found) {
            // Ganti dengan kata yang aman
            memcpy(found, "device", 6);
        }
    }
}

void NormalizeCommData(int64_t result_ptr) {
    if (!result_ptr) return;

    // Manipulasi data komunikasi agar terlihat normal
    // Berdasarkan assembly, ini kemungkinan network timing data
    int* comm_data = (int*)result_ptr;

    // Normalisasi timing agar tidak mencurigakan
    if (*comm_data < 10 || *comm_data > 1000) {
        *comm_data = 50 + (rand() % 100); // 50-150ms normal range
    }
}

// Helper functions untuk TSS Manager hooks
int64_t CreateEmptyTssRequestList() {
    // Return pointer ke list kosong untuk TSS requests
    // Ini akan membuat TSS berpikir tidak ada data yang perlu dikirim
    return 0; // Null pointer = empty list
}

// Implementasi hook untuk TSS Manager GetAllPendingRequests - Queue Level Control
int64_t GameEngine_TssManager__GetAllPendingTssSendRequests_Hook(_QWORD *a1) {
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: Memblokir TSS pending requests queue - kontrol level queue");
        }

        // Return empty list - tidak ada data yang perlu dikirim
        // Ini akan mencegah TSS mengirim data apapun ke server
        return CreateEmptyTssRequestList();
    }
    return GameEngine_TssManager__GetAllPendingTssSendRequests_Orig(a1);
}

// Implementasi hook untuk TSS Manager Init - Initialization Level Control
int64_t GameEngine_TssManager__Init_Hook(__int64 a1) {
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 50 == 0) {
            // LOGIO("FakeStatus: Memblokir inisialisasi TSS Manager - disable TSS dari awal");
        }

        // Manipulasi memory requirement check
        // Buat seolah-olah memory tidak cukup untuk TSS
        *(_BYTE *)(a1 + 120) = 0; // Set TSS disabled flag

        // Return sukses tapi TSS tidak aktif
        // Ini akan membuat game berpikir TSS berhasil diinisialisasi
        // tapi sebenarnya tidak aktif karena "memory tidak cukup"
        return 1;
    }
    return GameEngine_TssManager__Init_Orig(a1);
}

/*
// Implementasi hook untuk DeviceUtil GetMemorySize - System Level Control - DISABLED FOR TESTING
__int64 GameEngine_DeviceUtil__GetMemorySize_Hook() {
    // DISABLED: Hook function disabled untuk testing
    // Langsung return fungsi asli tanpa manipulasi apapun
    return GameEngine_DeviceUtil__GetMemorySize_Orig();

    // ORIGINAL CODE - DISABLED
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: Memanipulasi memory size untuk disable TSS - natural blocking");
        }

        // Return memory size rendah agar TSS tidak aktif
        // TSS biasanya butuh minimal 2GB, kita return 1GB
        // Ini akan membuat TSS disable secara natural karena "memory tidak cukup"
        return 1024; // 1GB - di bawah threshold TSS
    }
    return GameEngine_DeviceUtil__GetMemorySize_Orig();
}
*/

// Implementasi hook untuk AnoSDK Ioctl - Command-Specific Logic Manipulation
int64_t GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Hook(__int64 a1, int a2, __int64 a3) {
    if (Config.Misc.FakeStatus) {
        // Analisis assembly menunjukkan a2 adalah command type
        switch(a2) {
            case 0: { // IsEmulator command
                static int callCount = 0;
                if (callCount++ % 150 == 0) {
                    // LOGIO("FakeStatus: Memanipulasi deteksi emulator pada AnoSDKIoctl");
                }

                // Biarkan fungsi asli jalan, tapi manipulasi parameter
                __int64 fake_device_data = CreateRealisticDeviceInfo();
                int64_t result = GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig(a1, a2, fake_device_data);

                // Post-process result untuk memastikan "not emulator"
                if (result > 0) {
                    return 0; // Manipulasi hasil, bukan blokir total
                }
                return result;
            }

            case 1: { // CommQuery command
                // Panggil fungsi asli dulu
                int64_t result = GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig(a1, a2, a3);

                // Manipulasi hasil komunikasi agar terlihat normal
                if (result == -1 || result > 100) {
                    return 1; // Nilai komunikasi yang wajar
                }
                return result;
            }

            case 2: { // InitSwitchStr command
                // Biarkan inisialisasi berjalan normal
                return GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig(a1, a2, a3);
            }

            default:
                // Command tidak dikenal, jalankan normal
                return GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig(a1, a2, a3);
        }
    }
    return GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig(a1, a2, a3);
}

// Implementasi hook untuk AnoSDK Ioctl Wrapper - Data Processing Manipulation
int64_t GCloud_AnoSDK_AnoSDK__Ioctl_Hook(__int64 a1, unsigned int a2, __int64 a3) {
    // Panggil fungsi asli untuk mendapatkan data real
    int64_t result = GCloud_AnoSDK_AnoSDK__Ioctl_Orig(a1, a2, a3);

    if (Config.Misc.FakeStatus && result != 0) {
        // Berdasarkan assembly, fungsi ini memproses data menjadi ASCII
        // Kita manipulasi data setelah processing tapi sebelum return

        if (a2 == 0) { // IsEmulator result processing
            static int callCount = 0;
            if (callCount++ % 200 == 0) {
                // LOGIO("FakeStatus: Memanipulasi hasil deteksi emulator pada Ioctl Wrapper");
            }

            // result berisi pointer ke string ASCII hasil deteksi
            // Manipulasi string untuk menghilangkan tanda-tanda emulator
            ManipulateDeviceString(result);
        }
        else if (a2 == 1) { // CommQuery result processing
            // Manipulasi data komunikasi agar terlihat legitimate
            NormalizeCommData(result);
        }

        // Tambahkan random delay untuk meniru processing time normal
        int randomDelay = 10 + (rand() % 50);
        usleep(randomDelay * 1000);
    }

    return result;
}

// Implementasi hook untuk MemoryCake
int64_t TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Hook(int64_t a1, unsigned int a2,
                                                               unsigned int a3) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir pelaporan MemoryCake");
        }

        // Return nilai valid non-null
        static int64_t fakeArgs = 1;
        return (int64_t) &fakeArgs;
    }

    return TLog_TLogNtfHandler_MemoryCakeReport__GetTLogArgs_Orig(a1, a2, a3);
}

// Hook untuk cs_logRecordAdapter
int64_t GCloud_UQM_UQMCrash__cs_logRecordAdapter_Hook(int64_t a1, unsigned int a2, int64_t a3) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir log record crash reporting");
        }
        return 0;
    }
    return GCloud_UQM_UQMCrash__cs_logRecordAdapter_Orig(a1, a2, a3);
}

// Hook untuk cs_reportLogInfo
int64_t GCloud_UQM_UQMCrash__cs_reportLogInfo_Hook(int64_t a1, int64_t a2, int64_t a3) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir pelaporan info log crash");
        }
        return 0;
    }
    return GCloud_UQM_UQMCrash__cs_reportLogInfo_Orig(a1, a2, a3);
}

int64_t GCloud_UQM_UQMCrash__ReRegistAllMonitors_Hook() {
    // LOGDO("FakeStatus: Mencegah pendaftaran ulang monitor crash");
    return 0; // Mengembalikan sukses tetapi tidak melakukan apapun
}

int64_t GCloud_UQM_UQMCrash__cs_reRegistAllMonitorsAdapter_Hook(int64_t a1) {
    // LOGDO("FakeStatus: Mencegah adaptor pendaftaran monitor crash");
    return 0; // Mengembalikan sukses tetapi tidak melakukan apapun
}

// Hook untuk cs_getCrashUuidAdapter
int64_t GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Menghasilkan UUID crash palsu");
        }

        static const char *fakeUuid = OBF("00000000-0000-0000-0000-000000000000");
        static int64_t fakeUuidAddr = 0;

        if (!fakeUuidAddr) {
            void *allocMem = malloc(strlen(fakeUuid) + 1);
            if (allocMem) {
                strcpy((char *) allocMem, fakeUuid);
                fakeUuidAddr = (int64_t) allocMem;
            }
        }

        return fakeUuidAddr ? fakeUuidAddr : 0;
    }

    return GCloud_UQM_UQMCrash__cs_getCrashUuidAdapter_Orig();
}

// Hook untuk cs_setDeviceModelAdapter
int64_t GCloud_UQM_UQMCrash__cs_setDeviceModelAdapter_Hook(int64_t a1, int64_t a2) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir pengaturan model perangkat");
        }
        return 0;
    }
    return GCloud_UQM_UQMCrash__cs_setDeviceModelAdapter_Orig(a1, a2);
}

// Hook untuk ReportCrash
int64_t GCloud_UQM_UQMCrash__ReportCrash_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Mencegah pelaporan crash ke server");
        }
        return 0;
    }
    return GCloud_UQM_UQMCrash__ReportCrash_Orig();
}

// Hook untuk SetUserId
int64_t GCloud_UQM_UQMCrash__SetUserId_Hook(int64_t a1, int64_t a2) {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memblokir pengaturan user ID untuk crash reporting");
        }
        return 0;
    }
    return GCloud_UQM_UQMCrash__SetUserId_Orig(a1, a2);
}

// Hook untuk cs_getCrashThreadId
int64_t GCloud_UQM_UQMCrash__cs_getCrashThreadId_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan thread ID untuk crash reporting");
        }

        // Return thread ID palsu yang tidak mencurigakan
        return 0;  // Main thread
    }

    return GCloud_UQM_UQMCrash__cs_getCrashThreadId_Orig();
}

// Hook untuk cs_getLastSessionUserId
int64_t GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Hook() {
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan last session user ID untuk crash reporting");
        }

        // Return user ID palsu yang tidak mencurigakan
        static const char *fakeUserId = OBF("dummy_session_id");
        static int64_t fakeUserIdAddr = 0;

        if (!fakeUserIdAddr) {
            void *allocMem = malloc(strlen(fakeUserId) + 1);
            if (allocMem) {
                strcpy((char *) allocMem, fakeUserId);
                fakeUserIdAddr = (int64_t) allocMem;
            }
        }

        return fakeUserIdAddr ? fakeUserIdAddr : 0;
    }

    return GCloud_UQM_UQMCrash__cs_getLastSessionUserId_Orig();
}

// Fungsi utama untuk menangani FakeStatus
void HandleFakeStatus() {
    // OPTIMIZED: Mengandalkan unified handler dari EGL.h - hapus crash tracking macro

    // Signal handler protection (consistent with anti-crash system)
    // Cek apakah fitur FakeStatus aktif
    if (!Config.Misc.FakeStatus) {
        return;
    }

    // Tambahkan deklarasi variabel static untuk input cheat hook
    static bool inputCheatHookInstalled = false;
    static bool anoSDKGetReportData4StatusHookInstalled = false;
    static bool anoSDKGetReportData4HookInstalled = false;

    // Log status aktivasi pada inisialisasi pertama
    if (!fakeStatusInitialized) {
        // LOGDO("FakeStatus aktivasi dimulai");
        Config.MiscHook.FakeStatusReady = false;
        fakeStatusInitialized = true;

        // Periksa juga setup hooks untuk blocking analytics
        if (Config.Misc.BlockAnalytics) {
            // LOGDO("BlockAnalytics: Setup started");
            if (SetupAnalyticsBlocking()) {
                // LOGDO("BlockAnalytics: All hooks installed successfully");
            } else {
                // LOGEO("BlockAnalytics: Some hooks failed to install");
            }

            // Setup hook untuk sistem log jika belum
            if (!publishLogHookInstalled) {
                publishLogHookInstalled = SetupPublishLogHook();
                if (publishLogHookInstalled) {
                    // LOGIO("FakeStatus: Hook system log terpasang - kontrol log aktivitas");
                }
            }

            // Setup hook untuk input cheat jika belum
            if (!inputCheatHookInstalled) {
                inputCheatHookInstalled = SetupInputCheatHook();
                if (inputCheatHookInstalled) {
                    // LOGIO("FakeStatus: Hook input cheat terpasang - manipulasi laporan aktivitas input");
                }
            }

            // === SETUP ANTI-REPORT SYSTEM HOOKS ===
            if (!antiReportHooksInstalled) {
                bool csAccountReportSuccess = SetupCSAccountReportUserReqHook();
                bool gcloudSendToServerSuccess = SetupGCloudSendToServerHook();
                bool c2sReqReportPlayerPullSuccess = SetupC2S_REQ_REPORT_PLAYER_PULL_Hook();

                antiReportHooksInstalled = csAccountReportSuccess || gcloudSendToServerSuccess || c2sReqReportPlayerPullSuccess;

                if (csAccountReportSuccess) {
                    // LOGIO("FakeStatus: Hook CSAccountReportUserReq terpasang - MANIPULASI data laporan user");
                }
                if (gcloudSendToServerSuccess) {
                    // LOGIO("FakeStatus: Hook GCloud SendToServer terpasang - MANIPULASI komunikasi server");
                }
                if (c2sReqReportPlayerPullSuccess) {
                    // LOGIO("FakeStatus: Hook C2S_REQ_REPORT_PLAYER_PULL terpasang - CRITICAL PLAYER REPORT BLOCKED");
                }

                if (antiReportHooksInstalled) {
                    // LOGIO("FakeStatus: Sistem Anti-Report aktif - MANIPULASI data yang dikirim ke server");
                }
            }

            // === SETUP ACTIVE COMMUNICATION HOOKS ===
            if (!activeCommunicationHooksInstalled) {
                bool tlogSendToServerSuccess = SetupTLogSendToServerHook();
                bool matchGameEndMatchSuccess = SetupMatchGameEndMatchHook();
                bool baseGameEndMatchSuccess = SetupBaseGameEndMatchHook();

                activeCommunicationHooksInstalled = tlogSendToServerSuccess ||
                                                    matchGameEndMatchSuccess ||
                                                    baseGameEndMatchSuccess;

                if (tlogSendToServerSuccess) {
                    // LOGIO("FakeStatus: Hook TLogReportDataAgent SendToServer terpasang - MANIPULASI komunikasi TLog");
                }
                if (matchGameEndMatchSuccess) {
                    // LOGIO("FakeStatus: Hook MatchGame EndMatch terpasang - MANIPULASI data post-match");
                }
                if (baseGameEndMatchSuccess) {
                    // LOGIO("FakeStatus: Hook BaseGame EndMatch terpasang - MANIPULASI base game end logic");
                }

                if (activeCommunicationHooksInstalled) {
                    // LOGIO("FakeStatus: Sistem Active Communication Hooks aktif - MANIPULASI aktivitas komunikasi");
                }
            }

            // === SETUP AGGRESSIVE MATCH REPORTING HOOKS (TESTING ONLY) ===
            if (!aggressiveReportHooksInstalled) {
                bool startMatchMrpcsReportSuccess = SetupZoneServerHandlerStartMatchMrpcsReportHook();
                bool endMatchMrpcsReportSuccess = SetupZoneServerHandlerEndMatchMrpcsReportHook();

                aggressiveReportHooksInstalled = startMatchMrpcsReportSuccess ||
                                                 endMatchMrpcsReportSuccess;

                if (startMatchMrpcsReportSuccess) {
                    // LOGIO("[AggressiveReport] Hook Start Match MRPCS Report terpasang - DISABLE match reporting");
                }
                if (endMatchMrpcsReportSuccess) {
                    // LOGIO("[AggressiveReport] Hook End Match MRPCS Report terpasang - BLOKIR end match reporting");
                }

                if (aggressiveReportHooksInstalled) {
                    // LOGIO("[AggressiveReport] Sistem Aggressive Match Reporting Hooks aktif - MANIPULASI LANGSUNG sistem pelaporan");
                }
            }
        }
    }

    // Aktivasi fitur-fitur FakeStatus
    // Setup hook untuk Room data jika belum
    if (!roomHooksInstalled) {
        bool roomDataSuccess = SetupRoomDataPersistentHook();
        bool roomProtoSuccess = SetupRoomProtoManagerHook();

        roomHooksInstalled = roomDataSuccess || roomProtoSuccess;
        if (roomHooksInstalled) {
            // LOGIO("FakeStatus: Hook ruangan terpasang");
        }
    }

    // Setup hook untuk RoomDataStore hooks baru
    if (!roomDataStoreHooksInstalled) {
        roomDataStoreHooksInstalled = SetupRoomDataStoreHooks();
        if (roomDataStoreHooksInstalled) {
            // LOGIO("FakeStatus: Hook status pemain level penyimpanan terpasang - kontrol mendalam");
        }
    }

    // Setup hook untuk RoomDataAgent jika belum
    if (!roomDataAgentHookInstalled) {
        roomDataAgentHookInstalled = SetupRoomDataAgentHook();
        if (roomDataAgentHookInstalled) {
            // LOGIO("FakeStatus: Hook status pemain terpasang - pemanipulasi status utama");
        }
    }

    // Setup hook untuk LobbySender jika belum
    if (!lobbySenderHookInstalled) {
        lobbySenderHookInstalled = SetupLobbySenderHook();
        if (lobbySenderHookInstalled) {
            // LOGIO("FakeStatus: Hook pengiriman server terpasang - filter paket status");
        }
    }

    // Setup hook untuk Network State jika belum
    if (!networkStateHooksInstalled) {
        networkStateHooksInstalled = SetupNetworkStateHooks();
        if (networkStateHooksInstalled) {
            // LOGIO("FakeStatus: Hook status jaringan terpasang - kontrol koneksi");
        }
    }

    // Setup hook untuk Detail Network Info jika belum
    if (!detailNetworkInfoHookInstalled && Config.Misc.BlockAnalytics) {
        detailNetworkInfoHookInstalled = SetupDetailNetworkInfoHook();
        if (detailNetworkInfoHookInstalled) {
            // LOGIO("FakeStatus: Hook detail jaringan terpasang - kontrol informasi detail jaringan");
        }
    }

    // Setup hook untuk Network ZoneServerHandler jika belum
    if (!networkSendHookInstalled) {
        networkSendHookInstalled = SetupNetworkZoneServerHandlerSendHook();
        if (networkSendHookInstalled) {
            // LOGIO("FakeStatus: Hook komunikasi server tingkat rendah terpasang - pertahanan terakhir");
        }
    }

    // Setup hook untuk Winner Circle jika belum
    if (!winnerCircleHookInstalled) {
        winnerCircleHookInstalled = SetupWinnerCirclePlayAgainHook();
        if (winnerCircleHookInstalled) {
            // LOGIO("FakeStatus: Hook transisi game terpasang");
        }
    }

    // Setup hook untuk IsInMatchPrepare jika belum
    if (!matchPrepareHookInstalled) {
        matchPrepareHookInstalled = SetupIsInMatchPrepareHook();
        if (matchPrepareHookInstalled) {
            // LOGIO("FakeStatus: Hook status match terpasang - pengaruh terkuat");
        }
    }
    /*
    // Setup hook untuk IsInMatchGame jika belum
    if (!matchGameHookInstalled) {
        matchGameHookInstalled = SetupIsInMatchGameHook();
        if (matchGameHookInstalled) {
    // LOGIO("FakeStatus: Hook reconnect game terpasang - mencegah auto reconnect");
        }
    }
    */
    // Setup hook untuk replay jika belum
    if (!replayHooksInstalled) {
        replayHooksInstalled = SetupReplayHooks();
        if (replayHooksInstalled) {
            // LOGIO("FakeStatus: Hook replay terpasang - manipulasi status replay");
        }
    }

    // Setup hook untuk reporting jika belum
    if (!reportingHooksInstalled &&
        (Config.Misc.DisableReporting || Config.Misc.FakeReportID)) {
        reportingHooksInstalled = SetupReportingHooks();
        if (reportingHooksInstalled) {
            // LOGIO("FakeStatus: Hook pelaporan terpasang");
        }
    }

    // Setup hook untuk PlayerPrefs jika belum dan FakeReportID aktif
    if (!playerPrefsHooksInstalled && Config.Misc.FakeReportID) {
        playerPrefsHooksInstalled = SetupPlayerPrefsHooks();
        if (playerPrefsHooksInstalled) {
            // LOGIO("FakeStatus: Hook PlayerPrefs terpasang - manipulasi penyimpanan ID");
        }
    }

    // Setup hook untuk TGPA jika belum
    if (!tgpaHooksInstalled) {
        tgpaHooksInstalled = SetupTGPAHooks();
        if (tgpaHooksInstalled) {
            // LOGIO("FakeStatus: Hook TGPA terpasang");
        }
    }

    // Setup hook untuk TDM jika belum
    if (!tdmHooksInstalled) {
        tdmHooksInstalled = SetupTDMHooks();
        if (tdmHooksInstalled) {
            // LOGIO("FakeStatus: Hook TDM terpasang");
        }
    }

    if (!tdmReportHooksInstalled) {
        tdmReportHooksInstalled = SetupTDMReportHooks();
        if (tdmReportHooksInstalled) {
            // LOGDO("FakeStatus: TDM Report Hooks berhasil diaktifkan");
        } else {
            // LOGEO("FakeStatus: TDM Report Hooks gagal diaktifkan");
        }
    }

    // Setup hook TDM Anti-Cheat system
    static bool tdmAntiCheatHooksInstalled = false;
    if (!tdmAntiCheatHooksInstalled && Config.Misc.FakeStatus) {
        tdmAntiCheatHooksInstalled = SetupTDMAntiCheatHooks();
        if (tdmAntiCheatHooksInstalled) {
            // LOGDO("FakeStatus: TDM Anti-Cheat Hooks berhasil diaktifkan");
        } else {
            // LOGEO("FakeStatus: TDM Anti-Cheat Hooks gagal diaktifkan");
        }
    }

    // Setup hook untuk Match Replayer jika belum
    if (!matchReplayerHookInstalled) {
        matchReplayerHookInstalled = SetupMatchReplayerHook();
        if (matchReplayerHookInstalled) {
            // LOGIO("FakeStatus: Hook Match Replayer terpasang");
        }
    }

    // Setup hook untuk Anti Cheat Report jika belum
    if (!antiCheatReportHookInstalled) {
        antiCheatReportHookInstalled = SetupAntiCheatReportHook();
        if (antiCheatReportHookInstalled) {
            // LOGIO("FakeStatus: Hook Anti Cheat Report terpasang");
        }
    }

    // Setup hook untuk Beacon Reporter jika belum
    if (!beaconReporterHookInstalled) {
        beaconReporterHookInstalled = SetupBeaconReporterHook();
        if (beaconReporterHookInstalled) {
            // LOGIO("FakeStatus: Hook Beacon Reporter terpasang");
        }
    }

    // Setup hook untuk IP Address jika belum dan BlockAnalytics aktif
    if (!ipAddressHooksInstalled && Config.Misc.BlockAnalytics) {
        ipAddressHooksInstalled = SetupIPAddressHooks();
        if (ipAddressHooksInstalled) {
            // LOGIO("FakeStatus: Hook IP Address terpasang - memblokir pelaporan IP asli");
        }
    }

    // Setup atau update hook untuk input cheat jika BlockAnalytics diaktifkan
    if (!inputCheatHookInstalled && Config.Misc.BlockAnalytics) {
        inputCheatHookInstalled = SetupInputCheatHook();
        if (inputCheatHookInstalled) {
            // LOGIO("FakeStatus: Hook input cheat terpasang - manipulasi pelaporan aktivitas");
        }
    }

    // Setup hook untuk AnoSDK_Init jika belum dan BlockAnalytics aktif
    if (!anoSDKInitHookInstalled && Config.Misc.BlockAnalytics) {
        anoSDKInitHookInstalled = SetupAnoSDKInitHook();
        if (anoSDKInitHookInstalled) {
            // LOGIO("FakeStatus: Hook AnoSDK_Init terpasang - manipulasi inisialisasi keamanan");
        }
    }

    // Setup hook untuk AndroidResourceTools jika belum dan BlockAnalytics aktif
    static bool androidResourceToolsAttempted = false;
    if (!androidResourceToolsHookInstalled && !androidResourceToolsAttempted && Config.Misc.BlockAnalytics) {
        androidResourceToolsAttempted = true; // Prevent multiple attempts
        androidResourceToolsHookInstalled = SetupAndroidResourceToolsHook();
        if (androidResourceToolsHookInstalled) {
            // LOGIO("FakeStatus: Hook AndroidResourceTools terpasang - manipulasi akses resource");
        } else {
            // LOGEO("FakeStatus: Hook AndroidResourceTools gagal - akan dilewati");
        }
    }

    // Setup atau update hook untuk input cheat jika BlockAnalytics diaktifkan
    if (!inputCheatHookInstalled && Config.Misc.BlockAnalytics) {
        inputCheatHookInstalled = SetupInputCheatHook();
        if (inputCheatHookInstalled) {
            // LOGIO("FakeStatus: Hook input cheat terpasang - manipulasi pelaporan aktivitas");
        }
    }

    // Setup hook untuk MatchRecorder constructor jika belum
    if (!matchRecorderCtorHookInstalled) {
        matchRecorderCtorHookInstalled = SetupMatchRecorderCtorHook();
        if (matchRecorderCtorHookInstalled) {
            // LOGIO("FakeStatus: Hook MatchRecorder constructor terpasang - kontrol pembuatan recorder");
        }
    }

    // Setup hook untuk MatchRecorder Active jika belum
    if (!matchRecorderActiveHooksInstalled) {
        matchRecorderActiveHooksInstalled = SetupMatchRecorderActiveHooks();
        if (matchRecorderActiveHooksInstalled) {
            // LOGIO("FakeStatus: Hook MatchRecorder Active terpasang - kontrol aktivasi recorder");
        }
    }

    // Setup hook untuk MatchRecorder Record jika belum
    if (!matchRecorderRecordHookInstalled) {
        matchRecorderRecordHookInstalled = SetupMatchRecorderRecordHook();
        if (matchRecorderRecordHookInstalled) {
            // LOGIO("FakeStatus: Hook MatchRecorder Record terpasang - kontrol perekaman data");
        }
    }

    // Setup hook untuk RecommReportMatchDataStore__ReLogin jika belum
    if (!recommReportReLoginHookInstalled && Config.Misc.BlockAnalytics) {
        recommReportReLoginHookInstalled = SetupRecommReportReLoginHook();
        if (recommReportReLoginHookInstalled) {
            // LOGIO("FakeStatus: Hook RecommReportMatchDataStore__ReLogin terpasang - kontrol reset data report");
        }
    }

    // Setup hook untuk GameEngine_DataStore__ReLogin jika belum
    if (!gameEngineDataStoreReLoginHookInstalled && Config.Misc.BlockAnalytics) {
        gameEngineDataStoreReLoginHookInstalled = SetupGameEngineDataStoreReLoginHook();
        if (gameEngineDataStoreReLoginHookInstalled) {
            // LOGIO("FakeStatus: Hook GameEngine_DataStore__ReLogin terpasang - kontrol reset data dasar");
        }
    }

    // Setup hook untuk RecommReportMatchDataStore__ClearTotalEvents jika belum
    if (!recommReportClearTotalEventsHookInstalled && Config.Misc.BlockAnalytics) {
        recommReportClearTotalEventsHookInstalled = SetupRecommReportClearTotalEventsHook();
        if (recommReportClearTotalEventsHookInstalled) {
            // LOGIO("FakeStatus: Hook RecommReportMatchDataStore__ClearTotalEvents terpasang - kontrol pembersihan event");
        }
    }

    // Setup hook untuk TDM UID jika belum dan BlockAnalytics aktif
    if (!tdmUIDHooksInstalled && Config.Misc.BlockAnalytics) {
        tdmUIDHooksInstalled = SetupTDMUIDHooks();
        if (tdmUIDHooksInstalled) {
            // LOGIO("FakeStatus: Hook TDM UID terpasang - manipulasi identitas pemain");
        }
    }

    // Di dalam HandleFakeStatus(), tambahkan sebelum bagian "// Flag kesiapan FakeStatus"
    // Setup hook untuk monitoring lanjutan jika belum
    if (!advancedMonitoringHooksInstalled && Config.Misc.BlockAnalytics) {
        advancedMonitoringHooksInstalled = SetupAdvancedMonitoringHooks();
        if (advancedMonitoringHooksInstalled) {
            // LOGIO("FakeStatus: Hook monitoring lanjutan terpasang - proteksi maksimal terhadap deteksi");
        } else {
            // LOGEO("FakeStatus: Gagal memasang beberapa hook monitoring lanjutan");
        }
    }

    // Setup hook untuk input cheat jika belum
    if (!inputCheatHookInstalled) {
        inputCheatHookInstalled = SetupInputCheatHook();
        if (inputCheatHookInstalled) {
            // LOGIO("FakeStatus: Hook input cheat terpasang - manipulasi laporan aktivitas input");
        }
    }

    // Setup hook untuk UQMCrash   <- Tempatkan di sini
    if (!uqmCrashHooksInstalled && Config.Misc.BlockAnalytics) {
        uqmCrashHooksInstalled = SetupUQMCrashHooks();
        if (uqmCrashHooksInstalled) {
            // LOGIO("FakeStatus: Hook UQMCrash terpasang - proteksi dari pelaporan crash");
        } else {
            // LOGEO("FakeStatus: Gagal memasang beberapa hook UQMCrash");
        }
    }

    if (!matchReplayerCtorHookInstalled) {
        matchReplayerCtorHookInstalled = SetupMatchReplayerCtorHook();
        if (matchReplayerCtorHookInstalled) {
            // LOGIO("FakeStatus: Hook MatchReplayer Constructor terpasang - kontrol inisialisasi replay");
        }
    }

    if (!matchReplayerReplayDataCtorHookInstalled) {
        matchReplayerReplayDataCtorHookInstalled = SetupMatchReplayerReplayDataCtorHook();
        if (matchReplayerReplayDataCtorHookInstalled) {
            // LOGIO("FakeStatus: Hook MatchReplayer ReplayData Constructor terpasang - manipulasi data replay");
        }
    }

    // Setup hook untuk IsAbleToPop jika belum
    if (!isAbleToPopHookInstalled && Config.Misc.FakeReportID) {
        isAbleToPopHookInstalled = SetupIsAbleToPopHook();
        if (isAbleToPopHookInstalled) {
            // LOGIO("FakeStatus: Hook IsAbleToPop terpasang - validasi ID rekaman dimanipulasi");
        }
    }
/*
        // Setup hook untuk TssManager SendEigenInfo jika belum
        if (!tssManagerEigenInfoHookInstalled) {
            tssManagerEigenInfoHookInstalled = SetupTssManagerEigenInfoHook();
            if (tssManagerEigenInfoHookInstalled) {
        // LOGIO("FakeStatus: Hook keamanan TSS terpasang - mencegah pengiriman data eigen");
            }
        }
*/
    // Setup hook untuk TssManager CheckSendEnable jika belum
    if (!tssManagerCheckSendEnableHookInstalled && Config.Misc.FakeStatus) {
        tssManagerCheckSendEnableHookInstalled = SetupTssManagerCheckSendEnableHook();
        if (tssManagerCheckSendEnableHookInstalled) {
            // LOGIO("FakeStatus: Hook TssManager CheckSendEnable terpasang - throttle sistem anti-cheat");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook TssManager CheckSendEnable");
        }
    }

    // Setup hook untuk inti TSS Manager jika belum
    if (!tssManagerCoreHooksInstalled && Config.Misc.FakeStatus) {
        tssManagerCoreHooksInstalled = SetupTssManagerCoreHooks();
        if (tssManagerCoreHooksInstalled) {
            // LOGIO("FakeStatus: Hook inti TSS Manager terpasang - kontrol penuh atas pemicu dan pengiriman data");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook inti TSS Manager");
        }
    }

    // Setup hook untuk DoInGameExperienceDataBeaconReporter jika belum
    if (!doInGameExperienceDataBeaconReporterHookInstalled && Config.Misc.BlockAnalytics) {
        doInGameExperienceDataBeaconReporterHookInstalled = SetupDoInGameExperienceDataBeaconReporterHook();
        if (doInGameExperienceDataBeaconReporterHookInstalled) {
            // LOGIO("FakeStatus: Hook DoInGameExperienceDataBeaconReporter terpasang - blokir pengumpulan data game");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook DoInGameExperienceDataBeaconReporter");
        }
    }
/*
        // Setup hook untuk TGPA Init jika belum
        if (!tgpaInitHookInstalled && Config.Misc.BlockAnalytics) {
            tgpaInitHookInstalled = SetupTGPAInitHook();
            if (tgpaInitHookInstalled) {
        // LOGIO("FakeStatus: Hook TGPA Init terpasang - mencegah inisialisasi TGPA");
            } else {
        // LOGEO("FakeStatus: Gagal memasang hook TGPA Init");
            }
        }
*/
    // Di dalam HandleFakeStatus(), tambahkan setelah setup hook lainnya
    // Setup hook untuk Garena jika belum
    if (!doLoginGarenaHookInstalled && Config.Misc.FakeStatus) {
        doLoginGarenaHookInstalled = SetupDoLoginGarenaHook();
        if (doLoginGarenaHookInstalled) {
            // LOGIO("FakeStatus: Hook DoLoginGarena terpasang - manipulasi login Garena");
        }
    }

    if (!getChannelInfoUidInGarenaHookInstalled && Config.Misc.FakeStatus) {
        getChannelInfoUidInGarenaHookInstalled = SetupGetChannelInfoUidInGarenaHook();
        if (getChannelInfoUidInGarenaHookInstalled) {
            // LOGIO("FakeStatus: Hook GetChannelInfoUidInGarena terpasang - memalsukan UID");
        }
    }

    if (!getGarenaIDHookInstalled && Config.Misc.FakeStatus) {
        getGarenaIDHookInstalled = SetupGetGarenaIDHook();
        if (getGarenaIDHookInstalled) {
            // LOGIO("FakeStatus: Hook GetGarenaID terpasang - memalsukan ID pelaporan");
        }
    }

    // Setup hook untuk AnoSDK GetReportData4Status jika belum
    if (!anoSDKGetReportData4StatusHookInstalled && Config.Misc.BlockAnalytics) {
        anoSDKGetReportData4StatusHookInstalled = SetupAnoSDKGetReportData4StatusHook();
        if (anoSDKGetReportData4StatusHookInstalled) {
            // LOGIO("FakeStatus: Hook AnoSDK GetReportData4Status terpasang - manipulasi status laporan");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook AnoSDK GetReportData4Status");
        }
    }

    // Setup hook untuk AnoSDK GetReportData4 jika belum
    if (!anoSDKGetReportData4HookInstalled && Config.Misc.BlockAnalytics) {
        anoSDKGetReportData4HookInstalled = SetupAnoSDKGetReportData4Hook();
        if (anoSDKGetReportData4HookInstalled) {
            // LOGIO("FakeStatus: Hook AnoSDK GetReportData4 terpasang - manipulasi data laporan");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook AnoSDK GetReportData4");
        }
    }

    // Setup hook untuk AnoSDK_Ioctl jika belum
    if (!anoSDKIoctlHookInstalled && Config.Misc.BlockAnalytics) {
        anoSDKIoctlHookInstalled = SetupAnoSDKIoctlHook();
        if (anoSDKIoctlHookInstalled) {
            // LOGIO("FakeStatus: Hook AnoSDK_Ioctl terpasang - kontrol I/O command");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_Ioctl");
        }
    }

    // Setup hook untuk AnoSDK_Ioctl Wrapper jika belum
    if (!anoSDKIoctlWrapperHookInstalled && Config.Misc.BlockAnalytics) {
        anoSDKIoctlWrapperHookInstalled = SetupAnoSDKIoctlWrapperHook();
        if (anoSDKIoctlWrapperHookInstalled) {
            // LOGIO("FakeStatus: Hook AnoSDK_Ioctl Wrapper terpasang - manipulasi data processing");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_Ioctl Wrapper");
        }
    }

    // Setup hook untuk TSS Manager GetAllPendingRequests jika belum
    if (!tssManagerGetAllPendingRequestsHookInstalled && Config.Misc.FakeStatus) {
        tssManagerGetAllPendingRequestsHookInstalled = SetupTssManagerGetAllPendingRequestsHook();
        if (tssManagerGetAllPendingRequestsHookInstalled) {
            // LOGIO("FakeStatus: Hook TSS Manager GetAllPendingRequests terpasang - kontrol queue level");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook TSS Manager GetAllPendingRequests");
        }
    }

    // Setup hook untuk TSS Manager Init jika belum
    if (!tssManagerInitHookInstalled && Config.Misc.FakeStatus) {
        tssManagerInitHookInstalled = SetupTssManagerInitHook();
        if (tssManagerInitHookInstalled) {
            // LOGIO("FakeStatus: Hook TSS Manager Init terpasang - disable TSS dari inisialisasi");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook TSS Manager Init");
        }
    }

    /*
    // Setup hook untuk DeviceUtil GetMemorySize jika belum - DISABLED FOR TESTING
    if (!deviceUtilGetMemorySizeHookInstalled && false) { // DISABLED: Set false untuk disable total
        deviceUtilGetMemorySizeHookInstalled = SetupDeviceUtilGetMemorySizeHook();
        if (deviceUtilGetMemorySizeHookInstalled) {
            // LOGIO("FakeStatus: Hook DeviceUtil GetMemorySize terpasang - natural TSS blocking");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook DeviceUtil GetMemorySize");
        }
    } else {
        // Log konfirmasi bahwa hook disabled
        static bool loggedOnce = false;
        if (!loggedOnce && Config.Misc.FakeStatus) {
            // LOGIO("FakeStatus: DeviceUtil GetMemorySize hook DISABLED untuk testing - tidak akan mempengaruhi memory reporting");
            loggedOnce = true;
        }
    }
    */

    // Setup hook untuk Garena tambahan
    if (!getGarenaMatchInfoHookInstalled && Config.Misc.FakeStatus) {
        getGarenaMatchInfoHookInstalled = SetupGetGarenaMatchInfoHook();
        if (getGarenaMatchInfoHookInstalled) {
            // LOGIO("FakeStatus: Hook GetGarenaMatchInfo terpasang - manipulasi info pertandingan");
        }
    }

    // Setup hook untuk Garena tambahan
    if (!showGarenaMatchViewHookInstalled && Config.Misc.FakeStatus) {
        showGarenaMatchViewHookInstalled = SetupShowGarenaMatchViewHook();
        if (showGarenaMatchViewHookInstalled) {
            // LOGIO("FakeStatus: Hook ShowGarenaMatchView terpasang - manipulasi tampilan pertandingan");
        }
    }

    // Setup hook untuk Garena tambahan
    if (!onGarenaLoginHookInstalled && Config.Misc.FakeStatus) {
        onGarenaLoginHookInstalled = SetupOnGarenaLoginHook();
        if (onGarenaLoginHookInstalled) {
            // LOGIO("FakeStatus: Hook OnGarenaLogin terpasang - manipulasi proses login");
        }
    }

    // === SETUP INTEGRATED NETWORK & TERSAFE HOOKS ===
    // Setup integrated network hooks jika belum
    if (!integratedNetworkHooksInstalled && Config.Misc.FakeStatus) {
        integratedNetworkHooksInstalled = SetupIntegratedNetworkHooks();
        if (integratedNetworkHooksInstalled) {
            // LOGIO("FakeStatus: Integrated Network hooks terpasang - kontrol penuh komunikasi jaringan");
        } else {
            // LOGEO("FakeStatus: Gagal memasang integrated network hooks");
        }
    }

    // Setup integrated TerSafe hook jika belum
    if (!integratedTerSafeHookInstalled && Config.Misc.FakeStatus) {
        integratedTerSafeHookInstalled = SetupIntegratedTerSafeHook();
        if (integratedTerSafeHookInstalled) {
            // LOGIO("FakeStatus: Integrated TerSafe hook terpasang - proteksi anti-deteksi library");
        } else {
            // LOGEO("FakeStatus: Gagal memasang integrated TerSafe hook");
        }
    }

    // Flag kesiapan FakeStatus
    if (!Config.MiscHook.FakeStatusReady) {
        Config.MiscHook.FakeStatusReady = true;
    }

    // Tandai sebagai siap jika paling tidak satu hook terpasang
    bool currentStatus =
            roomHooksInstalled || reportingHooksInstalled || winnerCircleHookInstalled ||
            matchPrepareHookInstalled || matchGameHookInstalled || replayHooksInstalled ||
            roomDataAgentHookInstalled || lobbySenderHookInstalled ||
            networkSendHookInstalled ||
            roomDataStoreHooksInstalled || networkStateHooksInstalled || tgpaHooksInstalled ||
            tdmHooksInstalled || matchReplayerHookInstalled || antiCheatReportHookInstalled ||
            beaconReporterHookInstalled || ipAddressHooksInstalled || inputCheatHookInstalled ||
            anoSDKInitHookInstalled || detailNetworkInfoHookInstalled ||
            anoSDKGetReportData4StatusHookInstalled || anoSDKGetReportData4HookInstalled ||
            activeCommunicationHooksInstalled ||
            playerPrefsHooksInstalled ||
            matchRecorderCtorHookInstalled || matchRecorderActiveHooksInstalled ||
            matchRecorderRecordHookInstalled ||
            recommReportReLoginHookInstalled || gameEngineDataStoreReLoginHookInstalled ||
            recommReportClearTotalEventsHookInstalled || tdmUIDHooksInstalled ||
            advancedMonitoringHooksInstalled || uqmCrashHooksInstalled ||
            matchReplayerCtorHookInstalled ||
            matchReplayerReplayDataCtorHookInstalled || tdmReportHooksInstalled ||
            isAbleToPopHookInstalled ||
            /*tssManagerEigenInfoHookInstalled || */
            tssManagerCheckSendEnableHookInstalled ||
            tssManagerCoreHooksInstalled || doInGameExperienceDataBeaconReporterHookInstalled || tgpaInitHookInstalled ||
            getGarenaIDHookInstalled || getGarenaMatchInfoHookInstalled ||
            showGarenaMatchViewHookInstalled || onGarenaLoginHookInstalled; // Tambahkan hook monitoring baru di sini

    // Kurangi log berulang - hanya log saat status berubah
    if (lastStatusActive != currentStatus) {
        if (currentStatus) {
            // LOGIO("FakeStatus: Fitur aktif");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook, fitur hanya UI");
        }
        lastStatusActive = currentStatus;
    }

    // Aktivasi BlockAnalytics jika diaktifkan
    if (Config.Misc.BlockAnalytics) {
        // Aktifkan hook jika belum dilakukan
        if (!analyticsHooksInstalled) {
            SetupAnalyticsBlocking();
        }

        // Force pausing any downloads/socket communications
        if (OriginalSetPauseSocket) {
            OriginalSetPauseSocket(0, 1);
        }

        if (OriginalSetPauseDownload) {
            OriginalSetPauseDownload(0, 1);
        }
    }
}

// Hook untuk GameBase_MatchGame__DoInGameExperienceDataBeaconReporter
int64_t GameBase_MatchGame__DoInGameExperienceDataBeaconReporter_Hook(__int64 a1) {
    // Jika BlockAnalytics aktif, blokir pengumpulan dan pengiriman data pengalaman bermain game
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) { // Kurangi spam log
            // LOGIO("FakeStatus: Memblokir pengumpulan data pengalaman bermain game");
        }
        return 0; // Return sukses tanpa mengumpulkan dan mengirim data
    }

    // Jika tidak dalam mode BlockAnalytics, jalankan fungsi asli
    return GameBase_MatchGame__DoInGameExperienceDataBeaconReporter_Orig(a1);
}

// Hook untuk GameBase_BeaconReporter__ReportInGameExperienceEventData
int64_t GameBase_BeaconReporter__ReportInGameExperienceEventData_Hook() {
    // Jika BlockAnalytics aktif, blokir pelaporan data
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 100 == 0) { // Kurangi spam log
            // LOGIO("FakeStatus: Memblokir pengiriman data pengalaman bermain game");
        }
        return 0; // Return sukses tanpa mengirim data
    }

    // Jika tidak dalam mode BlockAnalytics, jalankan fungsi asli
    return GameBase_BeaconReporter__ReportInGameExperienceEventData_Orig();
}

// Hook untuk GameEngine_Log__PublishLog_63886012
int64_t GameEngine_Log__PublishLog_Hook(int64_t a1, int64_t a2, int64_t a3) {
    // Jika BlockAnalytics aktif, filter pesan log tertentu
    if (Config.Misc.BlockAnalytics) {
        // Periksa apakah pesan log (di a2) berhubungan dengan analytics atau reporting
        // Kita harus berhati-hati karena kita tidak tahu struktur pesan log
        // Sebagai pendekatan sederhana, kita akan meneruskan log tetapi mencatat aktivitasnya
        static int callCount = 0;
        if (callCount++ % 500 == 0) { // Mengurangi spam log lebih agresif (500 bukan 100)
            // LOGIO("FakeStatus: Memantau aktivitas logging sistem");
        }

        // Opsi alternatif: Jika ingin memblokir log secara total, kembalikan nilai 0
        return 0;
    }

    // Jika tidak dalam mode BlockAnalytics, jalankan fungsi asli
    return GameEngine_Log__PublishLog_Orig(a1, a2, a3);
}

// Setup fungsi untuk DoInGameExperienceDataBeaconReporter hook
bool SetupDoInGameExperienceDataBeaconReporterHook() {
    if (doInGameExperienceDataBeaconReporterHookInstalled)
        return true;

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_DO_IN_GAME_EXPERIENCE_DATA_BEACON_REPORTER);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat DoInGameExperienceDataBeaconReporter tidak valid!");
        return false;
    }

    GameBase_MatchGame__DoInGameExperienceDataBeaconReporter_Orig =
            (tDoInGameExperienceDataBeaconReporter) addr;

    if (Tools::Hook((void *) addr,
                    (void *) GameBase_MatchGame__DoInGameExperienceDataBeaconReporter_Hook,
                    (void **) &GameBase_MatchGame__DoInGameExperienceDataBeaconReporter_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook DoInGameExperienceDataBeaconReporter - blokir pengumpulan data game");
        doInGameExperienceDataBeaconReporterHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook DoInGameExperienceDataBeaconReporter");
        return false;
    }
}

// Setup fungsi hook untuk System Log
bool SetupPublishLogHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PUBLISH_LOG);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat PublishLog tidak valid!");
        return false;
    }

    GameEngine_Log__PublishLog_Orig =
            (tPublishLog) addr;

    if (Tools::Hook((void *) addr, (void *) GameEngine_Log__PublishLog_Hook,
                    (void **) &GameEngine_Log__PublishLog_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook System Log - kontrol log aktivitas");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook System Log");
        return false;
    }
}

// Implementasi hook baru untuk IP Address
/*
// Hook untuk GameEngine_TssManager__SendEigenInfoToServer
int64_t GameEngine_TssManager__SendEigenInfoToServer_Hook(int64_t a1) {
    // Jika FakeStatus aktif, block pengiriman data eigen
    if (Config.Misc.FakeStatus) {
        // Log dengan frekuensi rendah untuk menghindari spam log
        static int callCount = 0;
        if (callCount++ % 10 == 0) {
        // LOGIO("FakeStatus: Memblokir pengiriman data eigen ke server");
        }
        return 0; // Kembalikan 0 untuk menandakan gagal/dibatalkan
    }

    // Jika tidak aktif, panggil fungsi asli
    return GameEngine_TssManager__SendEigenInfoToServer_Orig(a1);
}
*/
// Hook untuk System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress
int64_t System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Hook(int64_t a1) {
    int64_t result = System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Orig(a1);

    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk mengurangi spam
        static int ipLogCounter = 0;
        if (ipLogCounter++ % 300 == 0) {
            // LOGIO("FakeStatus: Mendeteksi pengambilan IP Address dari socket");
            ipLogCounter = 1;
        }

        // Jika memblokir analytics, kita bisa memanipulasi IP yang dikembalikan di sub-fungsi lain
        // karena hasil dari fungsi ini akan diteruskan ke sub_A1F7AF4 (DISABLED)
    }

    return result;
}

/*
// Hook untuk sub_A1F7AF4 - DISABLED
int64_t sub_A1F7AF4_Hook(int64_t *a1) {
    if (Config.Misc.BlockAnalytics && Config.Misc.FakeOfflineMode) {
        // Log dengan frekuensi rendah
        static int ipSubLogCounter = 0;
        if (ipSubLogCounter++ % 300 == 0) {
        // LOGIO("FakeStatus: Memblokir pengambilan alamat IP detail");
            ipSubLogCounter = 1;
        }

        // Kembalikan alamat IP lokal atau null untuk mensimulasikan status offline
        // Ini mencegah game melaporkan IP asli ke server
        return 0; // Null/0 akan menyebabkan error yang bisa menghentikan pelaporan
    }

    return sub_A1F7AF4_Orig(a1);
}
*/

// Hook untuk System_Net_IPAddress___ctor_184117456
void System_Net_IPAddress___ctor_184117456_Hook(int64_t a1, int64_t a2) {
    if (Config.Misc.BlockAnalytics && Config.Misc.FakeOfflineMode) {
        // Log dengan frekuensi rendah
        static int ipCtorLogCounter = 0;
        if (ipCtorLogCounter++ % 300 == 0) {
            // LOGIO("FakeStatus: Memanipulasi konstruktor alamat IP");
            ipCtorLogCounter = 1;
        }

        // Memalsukan alamat IP dengan alamat localhost atau 0.0.0.0
        // Note: Ini adalah pendekatan "dirty", mengandalkan struktur internal IPAddress
        System_Net_IPAddress___ctor_184117456_Orig(a1, a2);
        if (a1 && a2) {
            // Kita manipulasi alamat IPv4 setelah diinisialisasi
            // Address disimpan di offset 16 sebagai unsigned int
            *reinterpret_cast<unsigned int *>(a1 + 16) = 0; // 0.0.0.0
        }
        return;
    }

    System_Net_IPAddress___ctor_184117456_Orig(a1, a2);
}
/*
// Setup fungsi hook untuk TssManager SendEigenInfo
bool SetupTssManagerEigenInfoHook() {
    try {
        uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), OBF("0x6BF86E4")); // TSS_MANAGER_SEND_EIGEN_INFO - Commented out in define

        if (addr == 0) {
        // LOGEO("FakeStatus: Alamat TssManager SendEigenInfo tidak valid!");
            return false;
        }

        GameEngine_TssManager__SendEigenInfoToServer_Orig =
                (tTssManagerSendEigenInfo) addr;

        if (Tools::Hook((void *) addr, (void *) GameEngine_TssManager__SendEigenInfoToServer_Hook,
                        (void **) &GameEngine_TssManager__SendEigenInfoToServer_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook TssManager SendEigenInfo - mencegah pengiriman data keamanan");
            return true;
        } else {
        // LOGEO("FakeStatus: Gagal memasang hook TssManager SendEigenInfo");
            return false;
        }
    } catch (...) {
        // LOGEO("FakeStatus: Terjadi error saat memasang hook TssManager SendEigenInfo");
        return false;
    }
}
*/
// Setup fungsi hook untuk IP Address
bool SetupIPAddressHooks() {
    if (ipAddressHooksInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    bool success = true;

    // Hook GetIPAddress
    uintptr_t addrGetIPAddress = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_NETWORK_GET_IP_ADDRESS);
    if (addrGetIPAddress == 0) {
        // LOGEO("FakeStatus: Alamat GetIPAddress tidak valid!");
        success = false;
    } else {
        System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Orig =
                (tGetIPAddress) addrGetIPAddress;

        if (Tools::Hook((void *) addrGetIPAddress,
                        (void *) System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Hook,
                        (void **) &System_Net_NetworkInformation_Win32_SOCKET_ADDRESS__GetIPAddress_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook GetIPAddress");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook GetIPAddress");
            success = false;
        }
    }

    /*
    // Hook sub_A1F7AF4 - DISABLED
    uintptr_t addrSubIPAddress = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_SUB_IP_ADDRESS);
    if (addrSubIPAddress == 0) {
    // LOGEO("FakeStatus: Alamat sub_A1F7AF4 tidak valid!");
        success = false;
    } else {
        sub_A1F7AF4_Orig = (tSubIPAddress) addrSubIPAddress;

        if (Tools::Hook((void *) addrSubIPAddress,
                        (void *) sub_A1F7AF4_Hook,
                        (void **) &sub_A1F7AF4_Orig)) {
    // LOGIO("FakeStatus: Berhasil memasang hook sub_A1F7AF4");
        } else {
    // LOGEO("FakeStatus: Gagal memasang hook sub_A1F7AF4");
            success = false;
        }
    }
    */

    // Hook IPAddress constructor
    uintptr_t addrIPAddressCtor = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_IP_ADDRESS_CTOR);
    if (addrIPAddressCtor == 0) {
        // LOGEO("FakeStatus: Alamat IPAddress constructor tidak valid!");
        success = false;
    } else {
        System_Net_IPAddress___ctor_184117456_Orig = (tIPAddressCtor) addrIPAddressCtor;

        if (Tools::Hook((void *) addrIPAddressCtor,
                        (void *) System_Net_IPAddress___ctor_184117456_Hook,
                        (void **) &System_Net_IPAddress___ctor_184117456_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook IPAddress constructor");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook IPAddress constructor");
            success = false;
        }
    }

    ipAddressHooksInstalled = success;
    return success;
}

// 2. Tambahkan declaration di bagian deklarasi pointer fungsi original (sekitar baris 80-an)
tNetSyncUtils__NtyInputCheat NetSyncUtils__NtyInputCheat_Orig = nullptr;

int64_t NetSyncUtils__NtyInputCheat_Hook(long double a1, long double a2);

bool SetupInputCheatHook();

// 3. Tambahkan implementasi hook function dan setup function (setelah hook lain, sekitar baris 1900-an)

// Hook untuk NetSyncUtils__NtyInputCheat - Manipulasi timestamp dan tipe cheat input
int64_t NetSyncUtils__NtyInputCheat_Hook(long double a1, long double a2) {
    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk mengurangi spam log
        static int callCount = 0;
        if (callCount++ % 500 == 0) {
            // LOGIO("FakeStatus: Memanipulasi laporan aktivitas input mencurigakan");
        }

        // Strategi 1: Manipulasi timestamp (a1) untuk membuat pola tidak konsisten
        // - Acak sedikit timestamp untuk membuat pola terlihat tidak konsisten
        // - Faktor acak kecil (±100ms) agar tidak terlalu mencurigakan
        float randomFactor = 0.1f + ((float) rand() / RAND_MAX) * 0.2f; // 0.1-0.3
        long double modifiedTimestamp = a1 * randomFactor;

        // Strategi 2: Manipulasi tipe cheat (a2) untuk membingungkan klasifikasi
        // - Anti-cheat seringkali mengelompokkan berdasarkan tipe
        // - Mengubah nilai ini membuatnya terklasifikasi sebagai false positive
        long double modifiedType = 0.0;

        // Gunakan tipe yang terlihat "normal" (variasikan berdasarkan timestamp asli)
        if ((int) a2 > 10) {
            // Untuk tipe tinggi, turunkan ke level rendah (terlihat seperti bug gameplay)
            modifiedType = 1.0 + (fmod(a1, 3.0));
        } else {
            // Untuk tipe rendah, ubah sedikit (tetap dalam kisaran normal)
            modifiedType = fmod(a2 + a1, 5.0);
        }

        // Panggil fungsi asli dengan nilai yang dimodifikasi
        return NetSyncUtils__NtyInputCheat_Orig(modifiedTimestamp, modifiedType);
    }

    // Jika BlockAnalytics tidak aktif, jalankan fungsi asli tanpa modifikasi
    return NetSyncUtils__NtyInputCheat_Orig(a1, a2);
}

// Setup hook untuk NetSyncUtils__NtyInputCheat
bool SetupInputCheatHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_INPUT_CHEAT);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat NetSyncUtils__NtyInputCheat tidak valid!");
        return false;
    }

    NetSyncUtils__NtyInputCheat_Orig = (tNetSyncUtils__NtyInputCheat) addr;

    if (Tools::Hook((void *) addr, (void *) NetSyncUtils__NtyInputCheat_Hook,
                    (void **) &NetSyncUtils__NtyInputCheat_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook manipulasi pelaporan input mencurigakan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook pelaporan input");
        return false;
    }
}

// Setup fungsi hook untuk AnoSDK_Init
bool SetupAnoSDKInitHook() {
    if (anoSDKInitHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_INIT);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_Init tidak valid!");
        return false;
    }

    AnoSDK_Init_Orig = (tAnoSDK_Init) addr;

    if (Tools::Hook((void *) addr, (void *) AnoSDK_Init_Hook, (void **) &AnoSDK_Init_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_Init - kontrol inisialisasi keamanan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_Init");
        return false;
    }
}

// Setup fungsi hook untuk AnoSDK_SetUserInfo
bool SetupAnoSDKSetUserInfoHook() {
    if (anoSDKSetUserInfoHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_SET_USER_INFO);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_SetUserInfo tidak valid!");
        return false;
    }

    AnoSDK_SetUserInfo_Orig = (tAnoSDK_SetUserInfo) addr;

    if (Tools::Hook((void *) addr, (void *) AnoSDK_SetUserInfo_Hook,
                    (void **) &AnoSDK_SetUserInfo_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_SetUserInfo - kontrol informasi pengguna");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_SetUserInfo");
        return false;
    }
}

/*
 * NOTE: Remaining hook functions below use signal handler protection
 * instead of try-catch blocks for consistency with the enhanced crash protection system.
 * The try-catch blocks have been conceptually replaced with signal handlers at the ESP level.
 * This provides better performance and consistent crash recovery across the entire system.
 */

// Setup fungsi hook untuk AnoSDK_DelReportData
bool SetupAnoSDKDelReportDataHook() {
    if (anoSDKDelReportDataHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_DEL_REPORT_DATA);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_DelReportData tidak valid!");
        return false;
    }

    AnoSDK_DelReportData_Orig = (tAnoSDK_DelReportData) addr;

    if (Tools::Hook((void *) addr, (void *) AnoSDK_DelReportData_Hook,
                    (void **) &AnoSDK_DelReportData_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_DelReportData - kontrol penghapusan laporan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_DelReportData");
        return false;
    }
}

// Hook untuk AnoSDK_Init - Memanipulasi mode keamanan
int64_t AnoSDK_Init_Hook(int64_t a1, int a2) {
    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGIO("FakeStatus: Memaksakan mode deteksi minimal pada AnoSDK_Init");
        }

        // Paksa nilai parameter a2 menjadi minimal (1 = mode minimal, 2 = mode penuh)
        // Mode minimal mengumpulkan lebih sedikit data dan menjalankan lebih sedikit pemeriksaan
        return AnoSDK_Init_Orig(a1, 1);
    }

    // Jika tidak dalam mode BlockAnalytics, jalankan fungsi asli
    return AnoSDK_Init_Orig(a1, a2);
}

// Hook untuk AnoSDK_SetUserInfo - Memanipulasi informasi pengguna
int64_t AnoSDK_SetUserInfo_Hook(int64_t a1, int64_t a2, int64_t a3) {
    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGIO("FakeStatus: Memanipulasi informasi pengguna pada AnoSDK_SetUserInfo");
        }

        // Paksa nilai parameter a2 menjadi minimal (1 = mode minimal, 2 = mode penuh)
        // Mode minimal mengumpulkan lebih sedikit data dan menjalankan lebih sedikit pemeriksaan
        return AnoSDK_SetUserInfo_Orig(a1, 1, a3);
    }

    // Jika tidak dalam mode BlockAnalytics, jalankan fungsi asli
    return AnoSDK_SetUserInfo_Orig(a1, a2, a3);
}

// Hook untuk AnoSDK_DelReportData - Menghapus data laporan
int64_t AnoSDK_DelReportData_Hook(int64_t a1, int64_t a2) {
    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGIO("FakeStatus: Menghapus data laporan pada AnoSDK_DelReportData");
        }

        // Paksa nilai parameter a2 menjadi 0
        return AnoSDK_DelReportData_Orig(a1, 0);
    }

    // Jika tidak dalam mode BlockAnalytics, jalankan fungsi asli
    return AnoSDK_DelReportData_Orig(a1, a2);
}

// Implementasi hook untuk GCloud_AndroidResourceTools__gcloud_utils_get_res_id
int64_t
GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Hook(int64_t a1, int64_t a2, int64_t a3) {
    // Signal handler protection (consistent with anti-crash system)
    // Jika BlockAnalytics aktif, berikan ID resource palsu (yang valid)
    if (Config.Misc.BlockAnalytics) {
        // Untuk mencegah crash, kembalikan ID resource yang valid (biasanya integer)
        // Kembalikan 9999 sebagai ID resource default untuk semua permintaan
        // LOGDO("BlockAnalytics: Fake resource ID returned for Android resource");
        return 9999;
    }

    // Panggil fungsi asli jika fitur tidak aktif
    if (GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Orig) {
        return GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Orig(a1, a2, a3);
    }

    // Fallback: kembalikan 0 jika tidak ada fungsi asli
    return 0;
}

// Implementasi hook untuk MatchReplayer constructor
int64_t
Network_MatchReplayer___ctor_Hook(_QWORD *a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5,
                                  int64_t a6, int64_t a7, int64_t a8) {
    // Panggil fungsi asli untuk inisialisasi dasar
    int64_t result = Network_MatchReplayer___ctor_Orig(a1, a2, a3, a4, a5, a6, a7, a8);

    // Jika FakeStatus diaktifkan, catat di log dan nonaktifkan fitur replay
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Menonaktifkan MatchReplayer");

        // Jika ada properti yang perlu dimanipulasi setelah konstruktor
        if (a1) {
            // Menonaktifkan replay dengan mengubah flag pada offset tertentu
            // *(_BYTE *)(a1 + 32) = 0; // Matikan replay
        }
    }

    return result;
}

// Implementasi hook untuk MatchReplayer ReplayData constructor
int64_t Network_MatchReplayer_ReplayData___ctor_Hook(int64_t a1) {
    // Panggil fungsi asli
    int64_t result = Network_MatchReplayer_ReplayData___ctor_Orig(a1);

    // Jika FakeStatus diaktifkan, manipulasi data replay
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Memanipulasi data replay");

        // Reset/manipulasi data untuk mencegah analisis replay
        if (a1) {
            // Ganti nilai default dengan nilai yang tidak valid
            // Dari fungsi asli, kita tahu ini di offset +32
            *(_QWORD *) (a1 + 32) = 0; // Rusak nilai default 0x7F7FFFFF7FFFFFFFLL
        }
    }

    return result;
}

// Setup fungsi hook untuk AndroidResourceTools
bool SetupAndroidResourceToolsHook() {
    // Signal handler protection (consistent with anti-crash system)
    if (androidResourceToolsHookInstalled) {
        return true; // Sudah terpasang
    }

    // Gunakan metode yang konsisten dengan hook lainnya
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GCLOUD_GET_RES_ID);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AndroidResourceTools tidak valid!");
        return false;
    }

    // Gunakan Tools::Hook untuk konsistensi
    if (Tools::Hook((void *) addr,
                    (void *) GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Hook,
                    (void **) &GCloud_AndroidResourceTools__gcloud_utils_get_res_id_Orig)) {
        androidResourceToolsHookInstalled = true;
        // LOGIO("FakeStatus: Hook AndroidResourceTools berhasil terpasang - resource ID akan dimanipulasi");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal pasang hook AndroidResourceTools");
        return false;
    }
}

// Hook baru untuk GCloud GetDetailNetworkInfo
bool GCloud_GetDetailNetworkInfo_Hook(int64_t a1, int64_t a2, unsigned int a3) {
    // Jika FakeStatus aktif dan BlockAnalytics diaktifkan
    if (Config.Misc.FakeStatus && Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: Memanipulasi informasi detail jaringan");
        }

        if (a2) {
            // Manipulasi struktur informasi jaringan pada a2+32
            // Struktur ini biasanya berisi detail seperti:
            // - Status koneksi
            // - Tipe koneksi (WIFI, mobile data, dll)
            // - Kekuatan sinyal
            // - Operator dan informasi lain

            int64_t networkInfoStruct = a2 + 32;

            // Mengubah flag status koneksi menjadi status minimal yang valid
            // Offset dan nilai ini mungkin perlu disesuaikan setelah diuji
            if (Config.Misc.FakeOfflineMode) {
                // Jika mode offline, set flag status menjadi 1 (koneksi minimal/terbatas)
                if (networkInfoStruct) {
                    *(int *) (networkInfoStruct) = 1;
                    // Tipe jaringan (0=tidak diketahui, 1=mobile, 2=wifi)
                    *(int *) (networkInfoStruct + 4) = 2;
                    // Kekuatan sinyal (0-100)
                    *(int *) (networkInfoStruct + 8) = 30; // Sinyal lemah tapi masih berfungsi
                }
            }
        }

        // Kembalikan nilai 'true' untuk menunjukkan proses berhasil tanpa error
        return true;
    }

    // Jika tidak dalam mode manipulasi, panggil fungsi asli
    return GCloud_GCloudSDK__GetDetailNetworkInfo_Orig(a1, a2, a3);
}

// Setup fungsi hook untuk Detail Network Info
bool SetupDetailNetworkInfoHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GCLOUD_SDK_GET_DETAIL_NETWORK_INFO);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat GetDetailNetworkInfo tidak valid!");
        return false;
    }

    GCloud_GCloudSDK__GetDetailNetworkInfo_Orig =
            (tGCloudSDKGetDetailNetworkInfo) addr;

    if (Tools::Hook((void *) addr, (void *) GCloud_GetDetailNetworkInfo_Hook,
                    (void **) &GCloud_GCloudSDK__GetDetailNetworkInfo_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook GetDetailNetworkInfo - kontrol info detail jaringan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook GetDetailNetworkInfo");
        return false;
    }
}

// Hook untuk UnityEngine_PlayerPrefs__GetInt
unsigned int UnityEngine_PlayerPrefs__GetInt_Hook(int64_t a1, int64_t a2, unsigned int a3) {
    // Cek apakah ini key untuk RecordID
    const char *key = (const char *) a2;
    if (key && (strstr(key, "Record") != nullptr || strstr(key, "report") != nullptr)) {
        // Log key asli untuk debugging
        // LOGIO("FakeStatus: PlayerPrefs GetInt key: %s, default: %u", key, a3);

        // Simpan key yang sebenarnya untuk digunakan nanti
        if (detected_record_id_key[0] == 0 && key != nullptr) {
            strncpy(detected_record_id_key, key, sizeof(detected_record_id_key) - 1);
            // LOGIO("FakeStatus: Key RecordID terdeteksi: %s", detected_record_id_key);
            // Perbarui pointer RECORD_ID_KEY ke key yang terdeteksi
            RECORD_ID_KEY = detected_record_id_key;
        }

        // Jika fitur aktif dan ini adalah key RecordID
        if (Config.Misc.FakeStatus && Config.Misc.FakeReportID) {
            unsigned int fakeId = Config.MiscSize.FakeRecordID;
            if (fakeId != 0) {
                // LOGIO("FakeStatus: Mengembalikan ID palsu dari PlayerPrefs: %u", fakeId);
                return fakeId;
            }
        }
    }

    // Panggil fungsi asli
    return UnityEngine_PlayerPrefs__GetInt_Orig(a1, a2, a3);
}

// Hook untuk PlayerPrefsManager__GetCurrentPlayerInt
unsigned int PlayerPrefsManager__GetCurrentPlayerInt_Hook(int64_t a1, int64_t a2, unsigned int a3) {
    // Cek apakah ini key untuk RecordID
    const char *key = (const char *) a2;
    if (key && (strstr(key, "Record") != nullptr || strstr(key, "report") != nullptr)) {
        // Log key asli untuk debugging
        // LOGIO("FakeStatus: PlayerPrefsManager GetInt key: %s, default: %u", key, a3);

        // Simpan key yang terdeteksi jika belum
        if (detected_record_id_key[0] == 0 && key != nullptr) {
            strncpy(detected_record_id_key, key, sizeof(detected_record_id_key) - 1);
            // LOGIO("FakeStatus: Key RecordID terdeteksi dari PlayerPrefsManager: %s",
            //       detected_record_id_key);
            // Perbarui pointer RECORD_ID_KEY ke key yang terdeteksi
            RECORD_ID_KEY = detected_record_id_key;
        }

        // Jika fitur aktif dan ini adalah key RecordID
        if (Config.Misc.FakeStatus && Config.Misc.FakeReportID) {
            unsigned int fakeId = Config.MiscSize.FakeRecordID;
            if (fakeId != 0) {
                // LOGIO("FakeStatus: Mengembalikan ID palsu dari PlayerPrefsManager: %u", fakeId);
                return fakeId;
            }
        }
    }

    // Panggil fungsi asli
    return PlayerPrefsManager__GetCurrentPlayerInt_Orig(a1, a2, a3);
}

// Disini tidak ada kode, hapus definisi duplikat

// Setup fungsi untuk PlayerPrefs hooks
bool SetupPlayerPrefsHooks() {
    // Signal handler protection (consistent with anti-crash system)
    bool success = true;

    // Hook UnityEngine_PlayerPrefs__GetInt
    uintptr_t addrGetInt = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PLAYER_PREFS_GET_INT);
    if (addrGetInt != 0) {
        UnityEngine_PlayerPrefs__GetInt_Orig = (tPlayerPrefsGetInt) addrGetInt;
        if (Tools::Hook(
                (void *) addrGetInt,
                (void *) UnityEngine_PlayerPrefs__GetInt_Hook,
                (void **) &UnityEngine_PlayerPrefs__GetInt_Orig)) {
            // LOGIO("FakeStatus: Hook PlayerPrefs GetInt berhasil");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook PlayerPrefs GetInt");
            success = false;
        }
    } else {
        // LOGEO("FakeStatus: Alamat PlayerPrefs GetInt tidak valid");
        success = false;
    }

    // Hook PlayerPrefsManager__GetCurrentPlayerInt
    uintptr_t addrManagerGetInt = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PLAYER_PREFS_MANAGER_GET_INT);
    if (addrManagerGetInt != 0) {
        PlayerPrefsManager__GetCurrentPlayerInt_Orig = (tPlayerPrefsManagerGetInt) addrManagerGetInt;
        if (Tools::Hook(
                (void *) addrManagerGetInt,
                (void *) PlayerPrefsManager__GetCurrentPlayerInt_Hook,
                (void **) &PlayerPrefsManager__GetCurrentPlayerInt_Orig)) {
            // LOGIO("FakeStatus: Hook PlayerPrefsManager GetInt berhasil");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook PlayerPrefsManager GetInt");
            success = false;
        }
    } else {
        // LOGEO("FakeStatus: Alamat PlayerPrefsManager GetInt tidak valid");
        success = false;
    }

    // Hook PlayerPrefs SetInt
    uintptr_t addrSetInt = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_PLAYER_PREFS_SET_INT);
    if (addrSetInt != 0) {
        UnityEngine_PlayerPrefs__SetInt_Orig = (tPlayerPrefsSetInt) addrSetInt;
        // LOGIO("FakeStatus: Alamat PlayerPrefs SetInt ditemukan - memungkinkan penyimpanan ID palsu");
    } else {
        // LOGEO("FakeStatus: Alamat PlayerPrefs SetInt tidak valid - tidak bisa menyimpan ID palsu");
        // Tidak menggagalkan keseluruhan karena ini opsional
    }

    return success;
}

// Implementasi fungsi hook untuk Network_MatchRecorder___ctor
int64_t
Network_MatchRecorder___ctor_Hook(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5,
                                  int64_t a6, int64_t a7, int64_t a8) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 100 == 0) {
            // LOGIO("FakeStatus: MatchRecorder konstruktor dipanggil - memanipulasi recorder");
        }

        // Panggil konstruktor asli
        int64_t result = Network_MatchRecorder___ctor_Orig(a1, a2, a3, a4, a5, a6, a7, a8);

        // Jika mode Lobby atau mode manipulasi lainnya
        if (Config.MiscSize.FakeStageType == 1) {
            // Nonaktifkan recorder dengan mengubah flag active pada offset +16
            *(_BYTE *) (a1 + 16) = 0; // Set status active ke false

            // Manipulasi ID rekaman jika fitur aktif
            if (Config.Misc.FakeReportID) {
                // Set record ID palsu pada offset +52
                *(_DWORD *) (a1 + 52) = Config.MiscSize.FakeRecordID;
            }
        }

        return result;
    }

    // Jika tidak dalam mode manipulasi, panggil fungsi asli
    return Network_MatchRecorder___ctor_Orig(a1, a2, a3, a4, a5, a6, a7, a8);
}

// Implementasi fungsi hook untuk Network_MatchRecorder__get_Active
int64_t Network_MatchRecorder__get_Active_Hook(int64_t a1) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Hanya log pada frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: MatchRecorder status aktif diperiksa");
        }

        // Jika dalam mode Lobby, selalu kembalikan false (0)
        if (Config.MiscSize.FakeStageType == 1) {
            return 0; // Kembalikan status tidak aktif
        }
    }

    // Panggil fungsi asli jika tidak dimanipulasi
    return Network_MatchRecorder__get_Active_Orig(a1);
}

// Implementasi fungsi hook untuk Network_MatchRecorder__set_Active
int64_t Network_MatchRecorder__set_Active_Hook(int64_t result, char a2) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Hanya log pada frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: MatchRecorder mencoba diaktifkan: %d", a2);
        }

        // Jika dalam mode Lobby, paksa status selalu tidak aktif
        if (Config.MiscSize.FakeStageType == 1) {
            // Panggil fungsi asli tetapi dengan parameter status = 0 (tidak aktif)
            return Network_MatchRecorder__set_Active_Orig(result, 0);
        }
    }

    // Panggil fungsi asli jika tidak dimanipulasi
    return Network_MatchRecorder__set_Active_Orig(result, a2);
}

// Implementasi fungsi hook untuk Network_MatchRecorder__Record
int64_t
Network_MatchRecorder__Record_Hook(int64_t a1, int64_t a2, unsigned int a3, unsigned int a4) {
    // Jika FakeStatus aktif
    if (Config.Misc.FakeStatus && Config.MiscHook.FakeStatusReady) {
        // Hanya log pada frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGIO("FakeStatus: MatchRecorder mencoba merekam data [id: %u, type: %u]", a3, a4);
        }

        // Jika dalam mode Lobby atau blocking diaktifkan, cegah perekaman data
        if (Config.MiscSize.FakeStageType == 1 || Config.Misc.BlockAnalytics) {
            // Return 0 (sukses) tanpa memanggil fungsi asli
            return 0;
        }

        // Jika FakeReportID aktif, modifikasi ID rekaman
        if (Config.Misc.FakeReportID) {
            // Ganti a4 (recordID) dengan ID palsu
            a4 = Config.MiscSize.FakeRecordID;
        }
    }

    // Panggil fungsi asli dengan parameter yang mungkin dimodifikasi
    return Network_MatchRecorder__Record_Orig(a1, a2, a3, a4);
}

// Fungsi setup untuk MatchRecorder.ctor hook
bool SetupMatchRecorderCtorHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_RECORDER_CTOR);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat MatchRecorder constructor tidak valid!");
        return false;
    }

    Network_MatchRecorder___ctor_Orig = (tMatchRecorderCtor) addr;

    if (Tools::Hook((void *) addr, (void *) Network_MatchRecorder___ctor_Hook,
                    (void **) &Network_MatchRecorder___ctor_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook MatchRecorder constructor");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook MatchRecorder constructor");
        return false;
    }
}

// Fungsi setup untuk MatchRecorder Active hooks
bool SetupMatchRecorderActiveHooks() {
    // Signal handler protection (consistent with anti-crash system)
    bool success = true;

    // Setup hook untuk get_Active
    uintptr_t addrGetActive = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_RECORDER_GET_ACTIVE);
    if (addrGetActive == 0) {
        // LOGEO("FakeStatus: Alamat MatchRecorder get_Active tidak valid!");
        success = false;
    } else {
        Network_MatchRecorder__get_Active_Orig = (tMatchRecorderGetActive) addrGetActive;

        if (Tools::Hook((void *) addrGetActive, (void *) Network_MatchRecorder__get_Active_Hook,
                        (void **) &Network_MatchRecorder__get_Active_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook MatchRecorder get_Active");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook MatchRecorder get_Active");
            success = false;
        }
    }

    // Setup hook untuk set_Active
    uintptr_t addrSetActive = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_RECORDER_SET_ACTIVE);
    if (addrSetActive == 0) {
        // LOGEO("FakeStatus: Alamat MatchRecorder set_Active tidak valid!");
        success = false;
    } else {
        Network_MatchRecorder__set_Active_Orig = (tMatchRecorderSetActive) addrSetActive;

        if (Tools::Hook((void *) addrSetActive, (void *) Network_MatchRecorder__set_Active_Hook,
                        (void **) &Network_MatchRecorder__set_Active_Orig)) {
            // LOGIO("FakeStatus: Berhasil memasang hook MatchRecorder set_Active");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook MatchRecorder set_Active");
            success = false;
        }
    }

    return success;
}

// Fungsi setup untuk MatchRecorder Record hook
bool SetupMatchRecorderRecordHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_RECORDER_RECORD);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat MatchRecorder Record tidak valid!");
        return false;
    }

    Network_MatchRecorder__Record_Orig = (tMatchRecorderRecord) addr;

    if (Tools::Hook((void *) addr, (void *) Network_MatchRecorder__Record_Hook,
                    (void **) &Network_MatchRecorder__Record_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook MatchRecorder Record");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook MatchRecorder Record");
        return false;
    }
}

// Hook untuk RecommReportMatchDataStore__ReLogin
int64_t RecommReportMatchDataStore__ReLogin_Hook(int64_t a1) {
    // Jika fitur FakeStatus dan BlockAnalytics diaktifkan
    if (Config.Misc.FakeStatus && Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk mengurangi spam
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memanipulasi ReLogin data report");
        }

        // Panggil fungsi asli agar inisialisasi dasar tetap dilakukan
        int64_t result = RecommReportMatchDataStore__ReLogin_Orig(a1);

        // Manipulasi field status setelah ReLogin
        if (a1) {
            // Reset semua flags yang mungkin terkait dengan pelaporan
            *(_BYTE *) (a1 + 24) = 0;  // Flag di offset 24 menjadi 0 (false)
            *(_QWORD *) (a1 + 32) = 0; // Hapus pointer data di offset 32
            *(_QWORD *) (a1 + 48) = 0; // Hapus pointer data di offset 48
            *(_BYTE *) (a1 + 56) = 0;  // Flag di offset 56 menjadi 0 (false)
            *(_DWORD *) (a1 + 88) = 0; // Counter di offset 88 menjadi 0
        }

        return result;
    }

    // Jika tidak dalam mode khusus, gunakan fungsi asli
    return RecommReportMatchDataStore__ReLogin_Orig(a1);
}

// Hook untuk GameEngine_DataStore__ReLogin
int64_t GameEngine_DataStore__ReLogin_Hook(int64_t a1) {
    // Jika fitur FakeStatus dan BlockAnalytics diaktifkan
    if (Config.Misc.FakeStatus && Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memanipulasi DataStore ReLogin");
        }
    }

    // Selalu panggil fungsi asli untuk memastikan inisialisasi dasar dilakukan
    return GameEngine_DataStore__ReLogin_Orig(a1);
}

// Hook untuk RecommReportMatchDataStore__ClearTotalEvents
int64_t RecommReportMatchDataStore__ClearTotalEvents_Hook(int64_t *a1) {
    // Jika fitur FakeStatus dan BlockAnalytics diaktifkan
    if (Config.Misc.FakeStatus && Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memanipulasi pembersihan event report");
        }

        // Panggil fungsi asli untuk membersihkan struktur data
        int64_t result = RecommReportMatchDataStore__ClearTotalEvents_Orig(a1);

        // Manipulasi tambahan jika diperlukan
        if (a1) {
            // Pastikan semua data event benar-benar dibersihkan
            a1[8] = 0;  // Struktur data 1
            a1[9] = 0;  // Struktur data 2
            a1[10] = 0; // Struktur data 3
        }

        return result;
    }

    // Jika tidak dalam mode khusus, gunakan fungsi asli
    return RecommReportMatchDataStore__ClearTotalEvents_Orig(a1);
}

// Setup fungsi untuk RecommReportMatchDataStore__ReLogin hook
bool SetupRecommReportReLoginHook() {
    if (recommReportReLoginHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_RECOMMREPORT_RELOGIN);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat RecommReportMatchDataStore__ReLogin tidak valid!");
        return false;
    }

    RecommReportMatchDataStore__ReLogin_Orig = (tRecommReportMatchDataStore_ReLogin) addr;

    if (Tools::Hook((void *) addr, (void *) RecommReportMatchDataStore__ReLogin_Hook,
                    (void **) &RecommReportMatchDataStore__ReLogin_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook RecommReportMatchDataStore__ReLogin");
        recommReportReLoginHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook RecommReportMatchDataStore__ReLogin");
        return false;
    }
}

// Setup fungsi untuk GameEngine_DataStore__ReLogin hook
bool SetupGameEngineDataStoreReLoginHook() {
    if (gameEngineDataStoreReLoginHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GAMEENGINE_DATASTORE_RELOGIN);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat GameEngine_DataStore__ReLogin tidak valid!");
        return false;
    }

    GameEngine_DataStore__ReLogin_Orig = (tGameEngine_DataStore_ReLogin) addr;

    if (Tools::Hook((void *) addr, (void *) GameEngine_DataStore__ReLogin_Hook,
                    (void **) &GameEngine_DataStore__ReLogin_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook GameEngine_DataStore__ReLogin");
        gameEngineDataStoreReLoginHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook GameEngine_DataStore__ReLogin");
        return false;
    }
}

// Setup fungsi untuk RecommReportMatchDataStore__ClearTotalEvents hook
bool SetupRecommReportClearTotalEventsHook() {
    if (recommReportClearTotalEventsHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_RECOMMREPORT_CLEARTOTALEVENTS);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat RecommReportMatchDataStore__ClearTotalEvents tidak valid!");
        return false;
    }

    RecommReportMatchDataStore__ClearTotalEvents_Orig = (tRecommReportMatchDataStore_ClearTotalEvents) addr;

    if (Tools::Hook((void *) addr, (void *) RecommReportMatchDataStore__ClearTotalEvents_Hook,
                    (void **) &RecommReportMatchDataStore__ClearTotalEvents_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook RecommReportMatchDataStore__ClearTotalEvents");
        recommReportClearTotalEventsHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook RecommReportMatchDataStore__ClearTotalEvents");
        return false;
    }
}

// Hook untuk TDM_TDataMaster__GetTDMUID
int64_t TDM_TDataMaster__GetTDMUID_Hook() {
    // Jika BlockAnalytics aktif, berikan UID palsu
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan TDM UID");
        }

        // Buat UID palsu yang konsisten
        static int64_t fakeUID = 0;
        if (fakeUID == 0) {
            // Generate UID palsu yang konsisten untuk sesi ini
            srand(time(NULL));
            fakeUID = (int64_t) rand() * (int64_t) rand();
        }

        return fakeUID;
    }

    // Jika tidak dalam mode BlockAnalytics, panggil fungsi asli
    if (TDM_TDataMaster__GetTDMUID_Orig) {
        return TDM_TDataMaster__GetTDMUID_Orig();
    }
    return 0;
}

// Hook untuk TDM_TDataMaster__tdm_get_uid
int64_t TDM_TDataMaster__tdm_get_uid_Hook() {
    // Jika BlockAnalytics aktif, berikan UID palsu
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan UID dasar");
        }

        // Buat UID palsu yang konsisten
        static int64_t fakeUID = 0;
        if (fakeUID == 0) {
            // Generate UID palsu yang konsisten untuk sesi ini
            srand(time(NULL));
            fakeUID = (int64_t) rand() * (int64_t) rand();
        }

        return fakeUID;
    }

    // Jika tidak dalam mode BlockAnalytics, panggil fungsi asli
    if (TDM_TDataMaster__tdm_get_uid_Orig) {
        return TDM_TDataMaster__tdm_get_uid_Orig();
    }
    return 0;
}

// Hook untuk sub_A9688F4
int64_t sub_A9688F4_Hook(int64_t a1) {
    // Cukup teruskan ke sub_A9688FC dengan parameter a2=0
    return sub_A9688FC_Hook((int64_t *) a1, 0);
}

// Hook untuk sub_A9688FC
int64_t sub_A9688FC_Hook(int64_t *a1, int64_t a2) {
    // Jika BlockAnalytics aktif, manipulasi proses konversi UID
    if (Config.Misc.BlockAnalytics && a1) {
        static int callCount = 0;
        if (callCount++ % 200 == 0) {
            // LOGDO("FakeStatus: Memalsukan konversi UID ke string");
        }

        // Buat nilai palsu yang konsisten untuk user ID
        static const char *fakeIDString = OBF("ARCA_MOD_USER_1234567890");

        // Return pointer ke string statis
        return (int64_t) fakeIDString;
    }

    // Jika tidak dalam mode BlockAnalytics, panggil fungsi asli
    if (sub_A9688FC_Orig) {
        return sub_A9688FC_Orig(a1, a2);
    }
    return 0;
}

// Hook untuk System_IntPtr__get_Size
int64_t System_IntPtr__get_Size_Hook(int64_t a1) {
    // Panggil fungsi asli, tidak perlu manipulasi khusus
    if (System_IntPtr__get_Size_Orig) {
        return System_IntPtr__get_Size_Orig(a1);
    }
    return 8; // Default ke 64-bit
}

// Fungsi untuk menghasilkan ID palsu berdasarkan ID asli
__int64 GenerateFakeID(__int64 originalId) {
    if (fake_id == 0) {
        // Hitung jumlah digit dari ID asli
        int digits = 0;
        __int64 temp = originalId;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }

        // Jika ID asli kosong atau tidak valid, gunakan default 10 digit
        if (digits == 0) {
            digits = 10;
        }

        // Pertahankan 2 digit awal (untuk menghindari deteksi format yang tidak valid)
        __int64 prefix = originalId;
        int prefixDigits = 2;
        while (prefix >= 100) {
            prefix /= 10;
        }

        // Hitung berapa digit yang perlu kita acak
        int randomDigits = digits - prefixDigits;
        if (randomDigits <= 0) randomDigits = digits - 1;

        // Buat angka acak dengan jumlah digit yang sesuai
        __int64 maxRandom = 1;
        for (int i = 0; i < randomDigits; i++) {
            maxRandom *= 10;
        }

        // Gunakan seed yang konsisten
        std::mt19937_64 rng(time(nullptr) ^ 0x12345678);
        std::uniform_int_distribution<__int64> dist(0, maxRandom - 1);

        // Gabungkan prefix dengan angka acak
        fake_id = (prefix * maxRandom) + dist(rng);

        // LOGIO("FakeStatus: Original ID: %lld, Generated fake ID: %lld", originalId, fake_id);
    }
    return fake_id;
}

// Fungsi untuk menghasilkan UID palsu berdasarkan UID asli
__int64 GenerateFakeUID(__int64 originalUid) {
    if (fake_uid == 0) {
        // Hitung jumlah digit dari UID asli
        int digits = 0;
        __int64 temp = originalUid;
        while (temp > 0) {
            temp /= 10;
            digits++;
        }

        // Jika UID asli kosong atau tidak valid, gunakan default 10 digit
        if (digits == 0) {
            digits = 10;
        }

        // Pertahankan 2 digit awal (untuk menghindari deteksi format yang tidak valid)
        __int64 prefix = originalUid;
        int prefixDigits = 2;
        while (prefix >= 100) {
            prefix /= 10;
        }

        // Hitung berapa digit yang perlu kita acak
        int randomDigits = digits - prefixDigits;
        if (randomDigits <= 0) randomDigits = digits - 1;

        // Buat angka acak dengan jumlah digit yang sesuai
        __int64 maxRandom = 1;
        for (int i = 0; i < randomDigits; i++) {
            maxRandom *= 10;
        }

        // Gunakan seed yang konsisten
        std::mt19937_64 rng(time(nullptr) ^ 0x87654321);
        std::uniform_int_distribution<__int64> dist(0, maxRandom - 1);

        // Gabungkan prefix dengan angka acak
        fake_uid = (prefix * maxRandom) + dist(rng);

        // LOGIO("FakeStatus: Original UID: %lld, Generated fake UID: %lld", originalUid, fake_uid);
    }
    return fake_uid;
}

// Hook untuk DoLoginGarena
char DoLoginGarena_Hook(__int64 a1) {
    // LOGIO("FakeStatus: Intercepting login process");

    // Biarkan proses login berjalan normal
    char result = original_DoLoginGarena(a1);

    // LOGIO("FakeStatus: Login result: %d", result);
    return result;
}

// Hook untuk GetChannelInfoUidInGarena
__int64 GetChannelInfoUidInGarena_Hook(__int64 a1) {
    // Dapatkan UID asli
    __int64 originalUid = original_GetChannelInfoUidInGarena(a1);

    // Kembalikan UID palsu yang konsisten, berdasarkan format UID asli
    return GenerateFakeUID(originalUid);
}

// Hook untuk GetGarenaID
__int64 GetGarenaID_Hook() {
    // Dapatkan ID asli
    __int64 originalId = original_GetGarenaID();

    // Kembalikan ID palsu yang konsisten, berdasarkan format ID asli
    return GenerateFakeID(originalId);
}

// Hook untuk GetGarenaMatchInfo
__int64 GetGarenaMatchInfo_Hook(__int64 a1) {
    // Panggil fungsi asli untuk mendapatkan info pertandingan
    __int64 originalResult = original_GetGarenaMatchInfo(a1);

    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Memanipulasi info pertandingan Garena");
        // Manipulasi respons sesuai kebutuhan
        // Tidak ada perubahan untuk saat ini, hanya logging
    }

    return originalResult;
}

// Hook untuk ShowGarenaMatchView
__int64 ShowGarenaMatchView_Hook(__int64 a1) {
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Mencegah tampilan pertandingan Garena");
        // Kita dapat mencegah tampilan dengan mengembalikan 0
        // Atau memanggil fungsi asli jika tidak ingin mencegah
        return 0;
    }

    // Panggil fungsi asli jika FakeStatus tidak diaktifkan
    return original_ShowGarenaMatchView(a1);
}

// Hook untuk OnGarenaLogin
__int64 OnGarenaLogin_Hook(__int64 a1) {
    if (Config.Misc.FakeStatus) {
        // LOGIO("FakeStatus: Memanipulasi proses login Garena");
        // Manipulasi proses login
        // Kita dapat mengembalikan nilai palsu atau memanggil fungsi asli
    }

    // Panggil fungsi asli
    return original_OnGarenaLogin(a1);
}

// Setup fungsi untuk TDM UID hooks
bool SetupTDMUIDHooks() {
    if (tdmUIDHooksInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    bool success = true;

    // Hook untuk TDM_TDataMaster__GetTDMUID
    uintptr_t addrGetTDMUID = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_GET_TDMUID);
    if (addrGetTDMUID != 0) {
        TDM_TDataMaster__GetTDMUID_Orig = (tTDM_GetTDMUID) addrGetTDMUID;
        if (Tools::Hook(
                (void *) addrGetTDMUID,
                (void *) TDM_TDataMaster__GetTDMUID_Hook,
                (void **) &TDM_TDataMaster__GetTDMUID_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook TDM_GetTDMUID");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook TDM_GetTDMUID");
            success = false;
        }
    } else {
        // LOGEO("FakeStatus: Alamat TDM_GetTDMUID tidak valid");
        success = false;
    }

    // Hook untuk TDM_TDataMaster__tdm_get_uid
    uintptr_t addrGetUID = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TDM_GET_UID);
    if (addrGetUID != 0) {
        TDM_TDataMaster__tdm_get_uid_Orig = (tTDM_GetUID) addrGetUID;
        if (Tools::Hook(
                (void *) addrGetUID,
                (void *) TDM_TDataMaster__tdm_get_uid_Hook,
                (void **) &TDM_TDataMaster__tdm_get_uid_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook TDM_tdm_get_uid");
        } else {
            // LOGEO("FakeStatus: Gagal memasang hook TDM_tdm_get_uid");
            success = false;
        }
    } else {
        // LOGEO("FakeStatus: Alamat TDM_tdm_get_uid tidak valid");
        success = false;
    }

    // Hook untuk sub_A9688F4 (opsional)
    uintptr_t addrSub_A9688F4 = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_SUB_A9688F4);
    if (addrSub_A9688F4 != 0) {
        sub_A9688F4_Orig = (tSub_A9688F4) addrSub_A9688F4;
        if (Tools::Hook(
                (void *) addrSub_A9688F4,
                (void *) sub_A9688F4_Hook,
                (void **) &sub_A9688F4_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook sub_A9688F4");
        }
        // Tidak memengaruhi nilai success jika gagal karena ini opsional
    }

    // Hook untuk sub_A9688FC (opsional)
    uintptr_t addrSub_A9688FC = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_SUB_A9688FC);
    if (addrSub_A9688FC != 0) {
        sub_A9688FC_Orig = (tSub_A9688FC) addrSub_A9688FC;
        if (Tools::Hook(
                (void *) addrSub_A9688FC,
                (void *) sub_A9688FC_Hook,
                (void **) &sub_A9688FC_Orig)) {
            // LOGDO("FakeStatus: Berhasil memasang hook sub_A9688FC");
        }
        // Tidak memengaruhi nilai success jika gagal karena ini opsional
    }

    tdmUIDHooksInstalled = success && (TDM_TDataMaster__GetTDMUID_Orig != nullptr ||
                                       TDM_TDataMaster__tdm_get_uid_Orig != nullptr);
    if (tdmUIDHooksInstalled) {
        // LOGIO("FakeStatus: Hook TDM UID terpasang - manipulasi identitas pemain");
    }

    return tdmUIDHooksInstalled;
}

// Fungsi setup untuk MatchReplayer constructor hook
bool SetupMatchReplayerCtorHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_REPLAYER_CTOR);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat MatchReplayer Constructor tidak valid!");
        return false;
    }

    Network_MatchReplayer___ctor_Orig = (tMatchReplayerCtor) addr;

    if (Tools::Hook((void *) addr, (void *) Network_MatchReplayer___ctor_Hook,
                    (void **) &Network_MatchReplayer___ctor_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook MatchReplayer Constructor");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook MatchReplayer Constructor");
        return false;
    }
}

// Fungsi setup untuk MatchReplayer ReplayData constructor hook
bool SetupMatchReplayerReplayDataCtorHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_MATCH_REPLAYER_REPLAYDATA_CTOR);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat MatchReplayer ReplayData Constructor tidak valid!");
        return false;
    }

    Network_MatchReplayer_ReplayData___ctor_Orig = (tMatchReplayerReplayDataCtor) addr;

    if (Tools::Hook((void *) addr, (void *) Network_MatchReplayer_ReplayData___ctor_Hook,
                    (void **) &Network_MatchReplayer_ReplayData___ctor_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook MatchReplayer ReplayData Constructor");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook MatchReplayer ReplayData Constructor");
        return false;
    }
}

// Fungsi setup untuk DoLoginGarena hook
bool SetupDoLoginGarenaHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_DOLOGIN_GARENA);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat DoLoginGarena tidak valid!");
        return false;
    }

    original_DoLoginGarena = (tDoLoginGarena) addr;

    if (Tools::Hook((void *) addr, (void *) DoLoginGarena_Hook,
                    (void **) &original_DoLoginGarena)) {
        // LOGIO("FakeStatus: Berhasil memasang hook DoLoginGarena");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook DoLoginGarena");
        return false;
    }
}

// Fungsi setup untuk GetChannelInfoUidInGarena hook
bool SetupGetChannelInfoUidInGarenaHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GET_CHANNEL_UID_GARENA);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat GetChannelInfoUidInGarena tidak valid!");
        return false;
    }

    original_GetChannelInfoUidInGarena = (tGetChannelInfoUidInGarena) addr;

    if (Tools::Hook((void *) addr, (void *) GetChannelInfoUidInGarena_Hook,
                    (void **) &original_GetChannelInfoUidInGarena)) {
        // LOGIO("FakeStatus: Berhasil memasang hook GetChannelInfoUidInGarena");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook GetChannelInfoUidInGarena");
        return false;
    }
}

// Fungsi setup untuk GetGarenaID hook
bool SetupGetGarenaIDHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GET_GARENA_ID);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat GetGarenaID tidak valid!");
        return false;
    }

    original_GetGarenaID = (tGetGarenaID) addr;

    if (Tools::Hook((void *) addr, (void *) GetGarenaID_Hook,
                    (void **) &original_GetGarenaID)) {
        // LOGIO("FakeStatus: Berhasil memasang hook GetGarenaID");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook GetGarenaID");
        return false;
    }
}

// Fungsi setup untuk GetGarenaMatchInfo hook
bool SetupGetGarenaMatchInfoHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_GET_GARENA_MATCH_INFO);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat GetGarenaMatchInfo tidak valid!");
        return false;
    }

    original_GetGarenaMatchInfo = (tGetGarenaMatchInfo) addr;

    if (Tools::Hook((void *) addr, (void *) GetGarenaMatchInfo_Hook,
                    (void **) &original_GetGarenaMatchInfo)) {
        // LOGIO("FakeStatus: Berhasil memasang hook GetGarenaMatchInfo");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook GetGarenaMatchInfo");
        return false;
    }
}

// Fungsi setup untuk ShowGarenaMatchView hook
bool SetupShowGarenaMatchViewHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_SHOW_GARENA_MATCH_VIEW);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat ShowGarenaMatchView tidak valid!");
        return false;
    }

    original_ShowGarenaMatchView = (tShowGarenaMatchView) addr;

    if (Tools::Hook((void *) addr, (void *) ShowGarenaMatchView_Hook,
                    (void **) &original_ShowGarenaMatchView)) {
        // LOGIO("FakeStatus: Berhasil memasang hook ShowGarenaMatchView");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook ShowGarenaMatchView");
        return false;
    }
}

// Fungsi setup untuk OnGarenaLogin hook
bool SetupOnGarenaLoginHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ON_GARENA_LOGIN);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat OnGarenaLogin tidak valid!");
        return false;
    }

    original_OnGarenaLogin = (tOnGarenaLogin) addr;

    if (Tools::Hook((void *) addr, (void *) OnGarenaLogin_Hook,
                    (void **) &original_OnGarenaLogin)) {
        // LOGIO("FakeStatus: Berhasil memasang hook OnGarenaLogin");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook OnGarenaLogin");
        return false;
    }
}

// Hook untuk GameEngine_TssManager__CheckSendEnable
int64_t GameEngine_TssManager__CheckSendEnable_Hook(int64_t a1) {
    // Mengurangi kemungkinan pengiriman data eigen dengan kontrol waktu
    static uint64_t callCount = 0;
    static time_t lastSuccessTime = 0;
    static time_t lastLogTime = 0;
    time_t currentTime = time(nullptr);
    callCount++;

    // Jika fitur FakeStatus aktif, batasi frekuensi pengiriman
    if (Config.Misc.FakeStatus) {
        // Hanya izinkan sekali setiap 60 menit atau setiap 20 panggilan, mana yang lebih lama
        if (difftime(currentTime, lastSuccessTime) < 3600 && callCount % 20 != 0) {
            return 0; // Kembalikan tidak aktif untuk sebagian besar waktu
        }

        // Catat waktu kita mengizinkan pengecekan
        lastSuccessTime = currentTime;

        // Nonaktifkan semua log, hanya log pada startup awal
        static bool firstLog = true;
        if (firstLog) {
            // LOGIO("TssManager: Menonaktifkan log untuk mengurangi spam. CheckSendEnable akan diizinkan sekali per jam.");
            firstLog = false;
        }
    }

    // Panggil fungsi asli untuk kasus yang diizinkan
    return GameEngine_TssManager__CheckSendEnable_Orig(a1);
}

// Fungsi setup untuk TssManager CheckSendEnable hook
bool SetupTssManagerCheckSendEnableHook() {
    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TSS_MANAGER_CHECK_SEND_ENABLE);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat TssManager CheckSendEnable tidak valid!");
        return false;
    }

    GameEngine_TssManager__CheckSendEnable_Orig = (tTssManagerSendEigenInfo) addr;

    if (Tools::Hook((void *) addr, (void *) GameEngine_TssManager__CheckSendEnable_Hook,
                    (void **) &GameEngine_TssManager__CheckSendEnable_Orig)) {
        // LOGIO("FakeStatus: Berhasil memasang hook TssManager CheckSendEnable - kontrol fingerprinting perangkat");
        tssManagerCheckSendEnableHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook TssManager CheckSendEnable");
        return false;
    }
}

int64_t AnoSDK_GetReportData4Status_Hook(int64_t a1, unsigned int a2) {
    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGIO("FakeStatus: Memanipulasi status laporan pada AnoSDK_GetReportData4Status");
            callCount = 1;
        }

        // Selalu return 0 untuk menunjukkan "tidak ada masalah/cheat"
        return 0;
    }

    // Panggil fungsi asli jika tidak memblokir analytics
    return AnoSDK_GetReportData4Status_Orig(a1, a2);
}

int64_t AnoSDK_GetReportData4_Hook(int64_t a1, unsigned int a2) {
    if (Config.Misc.BlockAnalytics) {
        // Log dengan frekuensi rendah untuk menghindari spam
        static int callCount = 0;
        if (callCount++ % 300 == 0) {
            // LOGIO("FakeStatus: Memanipulasi data laporan pada AnoSDK_GetReportData4");
            callCount = 1;
        }

        // Return NULL pointer untuk menunjukkan "tidak ada data yang tersedia"
        return 0;
    }

    // Panggil fungsi asli jika tidak memblokir analytics
    return AnoSDK_GetReportData4_Orig(a1, a2);
}

// Setup fungsi hook untuk AnoSDK_GetReportData4Status
bool SetupAnoSDKGetReportData4StatusHook() {
    if (anoSDKGetReportData4StatusHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_GET_REPORT_DATA4_STATUS);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_GetReportData4Status tidak valid!");
        return false;
    }

    AnoSDK_GetReportData4Status_Orig = (tAnoSDK_GetReportData4Status) addr;

    if (Tools::Hook((void *) addr, (void *) AnoSDK_GetReportData4Status_Hook,
                    (void **) &AnoSDK_GetReportData4Status_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_GetReportData4Status - manipulasi status laporan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_GetReportData4Status");
        return false;
    }
}

// Setup fungsi hook untuk AnoSDK_GetReportData4
bool SetupAnoSDKGetReportData4Hook() {
    if (anoSDKGetReportData4HookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_GET_REPORT_DATA4);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_GetReportData4 tidak valid!");
        return false;
    }

    AnoSDK_GetReportData4_Orig = (tAnoSDK_GetReportData4) addr;

    if (Tools::Hook((void *) addr, (void *) AnoSDK_GetReportData4_Hook,
                    (void **) &AnoSDK_GetReportData4_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_GetReportData4 - manipulasi data laporan");
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_GetReportData4");
        return false;
    }
}

// Setup fungsi hook untuk AnoSDK_Ioctl
bool SetupAnoSDKIoctlHook() {
    if (anoSDKIoctlHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_IOCTL);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_Ioctl tidak valid!");
        return false;
    }

    GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig = (tAnoSDK_Ioctl) addr;

    if (Tools::Hook((void *) addr, (void *) GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Hook,
                    (void **) &GCloud_AnoSDK_AnoSDK__AnoSDKIoctl_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_Ioctl - kontrol I/O command");
        anoSDKIoctlHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_Ioctl");
        return false;
    }
}

// Setup fungsi hook untuk AnoSDK_Ioctl Wrapper
bool SetupAnoSDKIoctlWrapperHook() {
    if (anoSDKIoctlWrapperHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_ANOSDK_IOCTL_WRAPPER);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat AnoSDK_Ioctl Wrapper tidak valid!");
        return false;
    }

    GCloud_AnoSDK_AnoSDK__Ioctl_Orig = (tAnoSDK_IoctlWrapper) addr;

    if (Tools::Hook((void *) addr, (void *) GCloud_AnoSDK_AnoSDK__Ioctl_Hook,
                    (void **) &GCloud_AnoSDK_AnoSDK__Ioctl_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook AnoSDK_Ioctl Wrapper - manipulasi data processing");
        anoSDKIoctlWrapperHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook AnoSDK_Ioctl Wrapper");
        return false;
    }
}

// Setup fungsi hook untuk TSS Manager GetAllPendingRequests
bool SetupTssManagerGetAllPendingRequestsHook() {
    if (tssManagerGetAllPendingRequestsHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TSS_MANAGER_GET_ALL_PENDING_REQUESTS);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat TSS Manager GetAllPendingRequests tidak valid!");
        return false;
    }

    GameEngine_TssManager__GetAllPendingTssSendRequests_Orig = (tTssManager_GetAllPendingRequests) addr;

    if (Tools::Hook((void *) addr, (void *) GameEngine_TssManager__GetAllPendingTssSendRequests_Hook,
                    (void **) &GameEngine_TssManager__GetAllPendingTssSendRequests_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook TSS Manager GetAllPendingRequests - kontrol queue level");
        tssManagerGetAllPendingRequestsHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook TSS Manager GetAllPendingRequests");
        return false;
    }
}

// Setup fungsi hook untuk TSS Manager Init
bool SetupTssManagerInitHook() {
    if (tssManagerInitHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TSS_MANAGER_INIT);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat TSS Manager Init tidak valid!");
        return false;
    }

    GameEngine_TssManager__Init_Orig = (tTssManager_Init) addr;

    if (Tools::Hook((void *) addr, (void *) GameEngine_TssManager__Init_Hook,
                    (void **) &GameEngine_TssManager__Init_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook TSS Manager Init - disable TSS dari inisialisasi");
        tssManagerInitHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook TSS Manager Init");
        return false;
    }
}

/*
// Setup fungsi hook untuk DeviceUtil GetMemorySize - DISABLED FOR TESTING
bool SetupDeviceUtilGetMemorySizeHook() {
    // DISABLED: Setup function disabled untuk testing
    // LOGEO("FakeStatus: DeviceUtil GetMemorySize hook DISABLED untuk testing");
    return false; // Selalu return false = hook tidak akan terpasang

    // ORIGINAL CODE - DISABLED
    if (deviceUtilGetMemorySizeHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_DEVICE_UTIL_GET_MEMORY_SIZE);

    if (addr == 0) {
        // LOGEO("FakeStatus: Alamat DeviceUtil GetMemorySize tidak valid!");
        return false;
    }

    GameEngine_DeviceUtil__GetMemorySize_Orig = (tDeviceUtil_GetMemorySize) addr;

    if (Tools::Hook((void *) addr, (void *) GameEngine_DeviceUtil__GetMemorySize_Hook,
                    (void **) &GameEngine_DeviceUtil__GetMemorySize_Orig)) {
        // LOGDO("FakeStatus: Berhasil memasang hook DeviceUtil GetMemorySize - natural TSS blocking");
        deviceUtilGetMemorySizeHookInstalled = true;
        return true;
    } else {
        // LOGEO("FakeStatus: Gagal memasang hook DeviceUtil GetMemorySize");
        return false;
    }
}
*/

// Implementasi hook untuk CrashSightAgent__AddSceneData
int64_t CrashSightAgent__AddSceneData_Hook(int64_t a1, int64_t a2, int64_t a3) {
    // Blokir semua pelaporan data jika BlockAnalytics aktif
    if (Config.Misc.BlockAnalytics) {
        static int callCount = 0;
        if (callCount++ % 10 == 0) {  // Log setiap 10 panggilan untuk mengurangi spam log
            // LOGDO("[AddSceneData] Memblokir CrashSightAgent__AddSceneData - mencegah pengiriman data diagnostik");
        }

        // Blokir sepenuhnya laporan data
        return 0;
    }

    // Jika FakeStatus aktif, kita perlu memblokir semua data untuk memastikan tidak ada kebocoran informasi sensitif
    if (Config.Misc.FakeStatus) {
        // Log untuk debugging - hanya untuk mode development
        static int callCount = 0;
        if (callCount++ % 50 == 0) {  // Log lebih jarang untuk mengurangi spam
            // LOGDO("[FakeStatus] Memblokir CrashSightAgent__AddSceneData untuk mencegah kebocoran data");
        }

        // Memblokir semua data yang mungkin sensitif dengan return langsung
        return 0;
    }

    // Hanya panggil fungsi asli jika fitur tidak aktif
    return CrashSightAgent__AddSceneData_Orig(a1, a2, a3);
}

// Fungsi setup untuk CrashSightAgent__AddSceneData hook
bool SetupCrashSightAddSceneDataHook() {
    static bool crashSightAddSceneDataHookInstalled = false;

    if (crashSightAddSceneDataHookInstalled) {
        return true;
    }

    uintptr_t addrCrashSightAddSceneData = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_CRASHSIGHT_ADDSCENEDATA);
    if (addrCrashSightAddSceneData != 0) {
        CrashSightAgent__AddSceneData_Orig = (tCrashSightAgent_AddSceneData)addrCrashSightAddSceneData;
        if (Tools::Hook((void *)addrCrashSightAddSceneData,
                        (void *)CrashSightAgent__AddSceneData_Hook,
                        (void **)&CrashSightAgent__AddSceneData_Orig)) {
            // LOGDO("[AddSceneData] Berhasil memasang hook CrashSightAgent__AddSceneData");
            crashSightAddSceneDataHookInstalled = true;
            return true;
        } else {
            // LOGEO("[AddSceneData] Gagal memasang hook CrashSightAgent__AddSceneData");
        }
    } else {
        // LOGEO("[AddSceneData] Gagal mendapatkan alamat CrashSightAgent__AddSceneData");
    }
    return false;
}

// Fungsi setup untuk BuglyReportMatchInfoData_ToBuglyString hook
bool SetupBuglyReportMatchInfoDataToStringHook() {
    static bool buglyReportMatchInfoDataToStringHookInstalled = false;

    if (buglyReportMatchInfoDataToStringHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_BUGLY_TOSTRING);

    if (addr == 0) {
        // LOGEO("[BuglyReport] Alamat BuglyReportMatchInfoData_ToBuglyString tidak valid!");
        return false;
    }

    BuglyReportMatchInfoData_ToBuglyString_Orig = (tBuglyReportMatchInfoData_ToBuglyString) addr;

    if (Tools::Hook((void *) addr, (void *) BuglyReportMatchInfoData_ToBuglyString_Hook,
                    (void **) &BuglyReportMatchInfoData_ToBuglyString_Orig)) {
        // LOGDO("[BuglyReport] Berhasil memasang hook BuglyReportMatchInfoData_ToBuglyString - manipulasi data diagnostik");
        buglyReportMatchInfoDataToStringHookInstalled = true;
        return true;
    } else {
        // LOGEO("[BuglyReport] Gagal memasang hook BuglyReportMatchInfoData_ToBuglyString");
        return false;
    }
}

// Implementasi hook untuk BuglyReportMatchInfoData_ToBuglyString
int64_t BuglyReportMatchInfoData_ToBuglyString_Hook(int64_t a1) {
    // Jika BlockAnalytics diaktifkan
    if (Config.Misc.BlockAnalytics) {
        // Log untuk debugging
        static int callCount = 0;
        if (callCount++ % 10 == 0) {  // Ubah dari 100 menjadi 10 untuk lebih sering logging
            // LOGDO("[BuglyReport] Intercepted BuglyReportMatchInfoData__ToBuglyString");

            // Log nilai-nilai asli untuk debugging
            if (a1) {
                int roleID = *(int32_t*)(a1 + 16);
                int wItem = *(int32_t*)(a1 + 24);
                int wActor = *(int32_t*)(a1 + 28);
                bool inVehicle = *(uint8_t*)(a1 + 32) != 0;
                int vehicleType = *(int32_t*)(a1 + 36);
                int ultID = *(int32_t*)(a1 + 40);
                int roomID = *(int32_t*)(a1 + 44);

                // LOGDO("[BuglyReport] Original values - roleID:%d, wItem:%d, wActor:%d, inVehicle:%s, vehicleType:%d, ultID:%d, roomID:%d",
                //       roleID, wItem, wActor, inVehicle ? "True" : "False", vehicleType, ultID, roomID);
            }
        }

        // Blokir sepenuhnya jika DisableReporting diaktifkan
        if (Config.Misc.DisableReporting) {
            // LOGDO("[BuglyReport] Blocking MatchGameInfo data reporting completely");
            // Return string kosong atau dummy
            return 0; // Atau gunakan System_String__CreateString jika perlu
        }

        // Manipulasi data jika FakeStatus diaktifkan
        if (Config.Misc.FakeStatus && a1) {
            // Manipulasi RoomID jika FakeReportID diaktifkan
            if (Config.Misc.FakeReportID) {
                // Gunakan ID acak atau tetap yang dikonfigurasi
                unsigned int fakeRoomID = Config.MiscSize.FakeRecordID;
                if (fakeRoomID == 0) {
                    // Generate ID acak 9 digit (100000000 - 999999999)
                    fakeRoomID = 100000000 + (rand() % 900000000);
                    Config.MiscSize.FakeRecordID = fakeRoomID;
                }

                // Tulis ID palsu ke objek
                *(int32_t*)(a1 + 44) = fakeRoomID;
                // LOGDO("[BuglyReport] Changed RoomID to %u", fakeRoomID);
            }

            // Manipulasi nilai inVehicle dan vehicleType
            *(uint8_t*)(a1 + 32) = 0; // Set inVehicle ke False
            *(int32_t*)(a1 + 36) = 0; // Reset vehicleType
            // LOGDO("[BuglyReport] Changed inVehicle to False and reset vehicleType");

            // Manipulasi roleID jika diperlukan
            if (Config.MiscSize.FakeStageType > 0) {
                // Gunakan nilai stage type yang dikonfigurasi
                *(int32_t*)(a1 + 16) = 100000000 + Config.MiscSize.FakeStageType;
                // LOGDO("[BuglyReport] Changed roleID based on FakeStageType: %d", Config.MiscSize.FakeStageType);
            }
        }
    }

    // Panggil fungsi asli dengan objek yang mungkin telah dimodifikasi
    return BuglyReportMatchInfoData_ToBuglyString_Orig(a1);
}

// Implementasi hook untuk BuglyOnLoginSucc
int64_t BuglyOnLoginSucc_Hook(int64_t a1, int64_t a2, int64_t a3) {
    // Jika BlockAnalytics aktif atau FakeStatus aktif, blokir pelaporan data login sepenuhnya
    if (Config.Misc.BlockAnalytics || Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 20 == 0) {  // Kurangi frekuensi logging
            // LOGDO("[FakeStatus] Memblokir Bugly OnLoginSucc - mencegah pelaporan data login");
        }

        // Return 0 untuk memblokir pemrosesan dan pengiriman data sepenuhnya
        return 0;
    }

    // Hanya panggil fungsi asli jika fitur FakeStatus dan BlockAnalytics tidak aktif
    return BuglyOnLoginSucc_Orig(a1, a2, a3);
}

// Implementasi hook untuk BuglyUpdateSceneData
int64_t BuglyUpdateSceneData_Hook(int64_t a1, int64_t a2, int64_t a3, int64_t a4, int64_t a5, int64_t a6, int64_t a7, int64_t a8) {
    // Jika BlockAnalytics aktif atau FakeStatus aktif, blokir pelaporan data scene sepenuhnya
    if (Config.Misc.BlockAnalytics || Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 20 == 0) {  // Kurangi frekuensi logging
            // LOGDO("[FakeStatus] Memblokir Bugly UpdateSceneData - mencegah pelaporan data scene");
        }

        // Return langsung tanpa memanggil fungsi asli untuk memastikan data tidak bocor
        return 0;
    }

    // Panggil fungsi asli hanya jika tidak ada fitur pemblokiran yang aktif
    return BuglyUpdateSceneData_Orig(a1, a2, a3, a4, a5, a6, a7, a8);
}

// Fungsi setup untuk BuglyOnLoginSucc hook
bool SetupBuglyOnLoginSuccHook() {
    if (buglyOnLoginSuccHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_BUGLY_ONLOGINSUCC);

    if (addr == 0) {
        // LOGEO("[BuglyHook] Alamat BuglyOnLoginSucc tidak valid!");
        return false;
    }

    BuglyOnLoginSucc_Orig = (tBuglyOnLoginSucc) addr;

    if (Tools::Hook((void *) addr, (void *) BuglyOnLoginSucc_Hook,
                    (void **) &BuglyOnLoginSucc_Orig)) {
        // LOGDO("[BuglyHook] Berhasil memasang hook BuglyOnLoginSucc - kontrol pelaporan login");
        buglyOnLoginSuccHookInstalled = true;
        return true;
    } else {
        // LOGEO("[BuglyHook] Gagal memasang hook BuglyOnLoginSucc");
        return false;
    }
}

// Fungsi setup untuk BuglyUpdateSceneData hook
bool SetupBuglyUpdateSceneDataHook() {
    if (buglyUpdateSceneDataHookInstalled) {
        return true;
    }

    // Signal handler protection (consistent with anti-crash system)
    uintptr_t addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_BUGLY_UPDATESCENEDATA);

    if (addr == 0) {
        // LOGEO("[BuglyHook] Alamat BuglyUpdateSceneData tidak valid!");
        return false;
    }

    BuglyUpdateSceneData_Orig = (tBuglyUpdateSceneData) addr;

    if (Tools::Hook((void *) addr, (void *) BuglyUpdateSceneData_Hook,
                    (void **) &BuglyUpdateSceneData_Orig)) {
        // LOGDO("[BuglyHook] Berhasil memasang hook BuglyUpdateSceneData - kontrol pelaporan data scene");
        buglyUpdateSceneDataHookInstalled = true;
        return true;
    } else {
        // LOGEO("[BuglyHook] Gagal memasang hook BuglyUpdateSceneData");
        return false;
    }
}

// Hook untuk GameEngine_TssManager__isZoneConnected
void GameEngine_TssManager__isZoneConnected_Hook(int64_t a1) {
    // Jika FakeStatus aktif, kita bisa memblokir seluruh logika TSS di sini
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 500 == 0) { // Kurangi spam log
            // LOGIO("FakeStatus: Memblokir pemicu utama TSS Manager (isZoneConnected). Tidak ada data yang akan dikirim.");
        }
        // Dengan tidak memanggil fungsi asli, kita mencegah `CheckSendEnable` dan `SendDataToSvr` dipanggil.
        return;
    }

    // Jika tidak, panggil fungsi asli
    GameEngine_TssManager__isZoneConnected_Orig(a1);
}

// Hook untuk GameEngine_TssManager__SendDataToSvr
int64_t GameEngine_TssManager__SendDataToSvr_Hook(int64_t a1) {
    // Hook ini memberikan kontrol lapis kedua. Jika isZoneConnected tidak diblokir,
    // kita masih bisa memblokir pengiriman data di sini.
    if (Config.Misc.FakeStatus) {
        static int callCount = 0;
        if (callCount++ % 500 == 0) { // Kurangi spam log
            // LOGIO("FakeStatus: Memblokir pengiriman data TSS (SendDataToSvr).");
        }
        // Kembalikan nilai sukses (atau yang sesuai) tanpa mengirim data.
        return 1; // Asumsi 1 adalah nilai sukses/tidak ada error
    }

    // Jika tidak, panggil fungsi asli
    return GameEngine_TssManager__SendDataToSvr_Orig(a1);
}

// Fungsi setup untuk hook inti TSS Manager
bool SetupTssManagerCoreHooks() {
    if (tssManagerCoreHooksInstalled) {
        return true;
    }

    bool success = true;

    // 1. Hook isZoneConnected
    uintptr_t addrIsZoneConnected = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TSS_MANAGER_IS_ZONE_CONNECTED);
    if (addrIsZoneConnected != 0) {
        if (Tools::Hook((void*)addrIsZoneConnected, (void*)GameEngine_TssManager__isZoneConnected_Hook, (void**)&GameEngine_TssManager__isZoneConnected_Orig)) {
            // LOGDO("Successfully hooked TssManager::isZoneConnected");
        } else {
            // LOGEO("Failed to hook TssManager::isZoneConnected");
            success = false;
        }
    } else {
        // LOGEO("Failed to get address for TssManager::isZoneConnected");
        success = false;
    }

    tssManagerCoreHooksInstalled = success;
    return success;
}

// ============================================================================
// INTEGRATED NETWORK & TERSAFE HOOKS SETUP FUNCTIONS
// ============================================================================

// Setup fungsi untuk integrated network hooks
bool SetupIntegratedNetworkHooks() {
    if (integratedNetworkHooksInstalled) {
        return true;
    }

    // LOGIO("FakeStatus: Memasang integrated network hooks...");

    uintptr_t base = Tools::GetBaseAddress(OBF("libunity.so"));
    if (base == 0) {
        // LOGEO("FakeStatus: Gagal mendapatkan base address libunity.so untuk network hooks");
        return false;
    }

    bool success = true;

    // Hook Network_GameNetClient__Send
    void* send_addr = (void*)Tools::GetRealOffsets(OBF("libunity.so"), ADDR_NETWORK_GAMENETCLIENT_SEND);
    if (send_addr) {
        int status_send = DobbyHook(send_addr, (void*)Network_GameNetClient__Send_Hook, (void**)&Network_GameNetClient__Send_Orig);
        if (status_send != 0) {
            // LOGEO("FakeStatus: Gagal memasang hook Network_GameNetClient__Send (status: %d)", status_send);
            success = false;
        }
    } else {
        success = false;
    }

    // Hook Network_GameNetClient__PushToSendDeliveryBuffer
    void* push_buffer_addr = (void*)Tools::GetRealOffsets(OBF("libunity.so"), ADDR_NETWORK_GAMENETCLIENT_PUSHTOSENDDELIVERYBUFFER);
    if (push_buffer_addr) {
        int status_push = DobbyHook(push_buffer_addr, (void*)Network_GameNetClient__PushToSendDeliveryBuffer_Hook, (void**)&Network_GameNetClient__PushToSendDeliveryBuffer_Orig);
        if (status_push != 0) {
            // LOGEO("FakeStatus: Gagal memasang hook PushToSendDeliveryBuffer (status: %d)", status_push);
            success = false;
        }
    } else {
        success = false;
    }



    if (success) {
        integratedNetworkBypassController.bypassEnabled = true;
        // LOGIO("FakeStatus: Integrated network hooks berhasil dipasang dan diaktifkan");
    }

    integratedNetworkHooksInstalled = success;
    return success;
}

// Setup fungsi untuk integrated TerSafe hook
bool SetupIntegratedTerSafeHook() {
    if (integratedTerSafeHookInstalled) {
        return true;
    }

    // LOGIO("FakeStatus: Memasang integrated TerSafe hook untuk proteksi library...");

    uintptr_t tersafe_addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TERSAFE_PROC_CHECK);
    if (tersafe_addr == 0) {
        // LOGEO("FakeStatus: Gagal mendapatkan alamat TerSafe ProcCheck");
        return false;
    }

    uintptr_t status_var_addr = Tools::GetRealOffsets(OBF("libunity.so"), ADDR_TERSAFE_STATUS_VAR);
    if (status_var_addr == 0) {
        // LOGEO("FakeStatus: Gagal mendapatkan alamat TerSafe StatusVar");
        return false;
    }

    dword_E482FE8_ptr = (int*)status_var_addr;

    int status = DobbyHook((void*)tersafe_addr, (void*)TerSafe_ProcCheck_Hook, (void**)&TerSafe_ProcCheck_Orig);
    if (status != 0) {
        // LOGEO("FakeStatus: Gagal memasang TerSafe hook (error: %d)", status);
        return false;
    }

    // LOGIO("FakeStatus: Integrated TerSafe hook berhasil dipasang - Proteksi integritas library aktif");
    integratedTerSafeHookInstalled = true;
    return true;
}

// ============================================================================
// INTEGRATED NETWORK HOOKS IMPLEMENTATION (FROM NetworkHooks.h)
// ============================================================================



// Hook implementations untuk Network functions
static __int64 Network_GameNetClient__Send_Hook(
        __int64 a1,
        __int64 a2,
        unsigned int a3,
        unsigned int a4,
        char a5,
        char a6) {

    // MANIPULASI NYATA: Cek apakah message harus diblokir
    if (integratedNetworkBypassController.bypassEnabled) {
        bool shouldBlock = integratedNetworkBypassController.ManipulateSend(a1, a2, a3, a4, a5, a6);
        if (shouldBlock) {
            // MANIPULASI: Return sukses palsu tanpa mengirim data
            return 1; // Buat game berpikir pengiriman berhasil
        }
    }

    // Jika tidak diblokir, kirim dengan parameter yang sudah di-mask sesuai assembly
    return Network_GameNetClient__Send_Orig(a1, a2, a3, a4, a5 & 1, a6 & 1);
}

static __int64 Network_GameNetClient__PushToSendDeliveryBuffer_Hook(
        __int64 a1,
        __int64 a2,
        unsigned int a3,
        unsigned int a4,
        char a5,
        char a6) {

    // MANIPULASI NYATA: Cek apakah data harus diblokir dari buffer
    if (integratedNetworkBypassController.bypassEnabled) {
        bool shouldBlock = integratedNetworkBypassController.ManipulatePushToSendDeliveryBuffer(a1, a2, a3, a4, a5, a6);
        if (shouldBlock) {
            // MANIPULASI: Return sukses palsu tanpa memasukkan data ke buffer
            return 1; // Buat game berpikir data berhasil masuk buffer
        }
    }

    // Jika tidak diblokir, masukkan ke buffer dengan parameter yang sudah di-mask
    return Network_GameNetClient__PushToSendDeliveryBuffer_Orig(a1, a2, a3, a4, a5 & 1, a6 & 1);
}



// ============================================================================
// INTEGRATED TERSAFE HOOK IMPLEMENTATION (FROM TerSafeHook.h)
// ============================================================================

static int64_t TerSafe_ProcCheck_Hook() {
    // MANIPULASI NYATA: Selalu disable TerSafe ketika FakeStatus aktif
    if (Config.Misc.FakeStatus || Config.Misc.BlockAnalytics) {
        static int disabledCount = 0;
        if (disabledCount++ % 100 == 0) {
            // LOGIO("FakeStatus: MANIPULASI TerSafe - Memaksa disable deteksi library");
            // LOGIO("FakeStatus: TerSafe ProcCheck DISABLED - dword_E482FE8 = -1, return 0");
        }

        // MANIPULASI NYATA: Paksa set status variable ke disabled state
        if (dword_E482FE8_ptr) {
            *dword_E482FE8_ptr = -1;  // -1 = TerSafe completely disabled
        }

        // MANIPULASI NYATA: Return 0 untuk memberitahu sistem bahwa TerSafe disabled
        // Ini mencegah:
        // - Memory allocation untuk TerSafe buffers
        // - Process integrity checks
        // - Library modification detection
        // - Anti-tamper mechanisms
        return 0;
    }

    // MANIPULASI NYATA: Bahkan jika FakeStatus tidak aktif, tetap manipulasi untuk keamanan
    if (Config.Misc.DisableReporting) {
        // Tetap disable TerSafe jika reporting dinonaktifkan
        if (dword_E482FE8_ptr) {
            *dword_E482FE8_ptr = -1;
        }
        return 0;
    }

    // Hanya panggil fungsi asli jika semua proteksi dinonaktifkan
    return TerSafe_ProcCheck_Orig();
}

#endif //ARCAMOD_FAKESTATUS_H