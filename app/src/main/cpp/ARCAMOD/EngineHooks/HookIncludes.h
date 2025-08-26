#ifndef ARCAMOD_HOOK_INCLUDES_H
#define ARCAMOD_HOOK_INCLUDES_H

#include "libanogs/definitions.h"
#include "libanogs/h_sub_13243C.h"
#include "libanogs/h_sub_11B300.h"
#include "libanogs/h_sub_1EF62C.h"
// #include "libanogs/h_sub_2DAB74.h"  // MONITORING: Data validation dengan checksum
#include "libanogs/h_monitoring_hooks.h"  // MONITORING: 7 Hook functions untuk aktivitas monitoring
#include "libanogs/h_monitoring_hooks_1.h"  // MONITORING: 10 Hook functions tambahan untuk monitoring
#include "libanogs/h_monitoring_hooks_2.h"  // MONITORING: 10 Hook functions series 1,2,3 untuk monitoring
#include "libanogs/h_monitoring_hooks_3.h"  // MONITORING: 10 Hook functions series 4 (void, QWORD, __int64) untuk monitoring
#include "libanogs/h_monitoring_hooks_4.h"  // MONITORING: 10 Hook functions series 13,2A,22 untuk monitoring
#include "libanogs/h_monitoring_hooks_5.h"  // MONITORING: 10 Hook functions series 14,17,2A untuk monitoring
#include "libanogs/h_monitoring_hooks_6.h"  // MONITORING: 10 Hook functions series 12,1D,26 untuk monitoring
#include "libanogs/h_monitoring_hooks_7.h"  // MONITORING: 10 Hook functions series 15,1DA,21,28,2D untuk monitoring
#include "libanogs/h_monitoring_hooks_8.h"  // MONITORING: 10 Hook functions series 2EF,2BE,291,290,241 untuk monitoring
#include "libanogs/h_monitoring_hooks_9.h"  // MONITORING: 10 Hook functions series 3A,3E,3F untuk monitoring
#include "libanogs/h_monitoring_hooks_10.h" // MONITORING: 10 Hook functions series 19F,161,13D,1D6,2A2 untuk monitoring
#include "libanogs/h_monitoring_hooks_11.h" // MONITORING: 10 Hook functions series 12F,17,1B,1A,20 untuk monitoring
#include "libanogs/h_monitoring_hooks_12.h" // MONITORING: 10 Hook functions series 11,18,10,1B,22 untuk monitoring
#include "libanogs/h_monitoring_hooks_13.h" // MONITORING: 10 Hook functions series 14C,12A,1DB,231,269 untuk monitoring
#include "libanogs/h_monitoring_hooks_14.h" // MONITORING: 10 Hook functions series 1D9,1C5,205,22B,25E untuk monitoring
#include "libanogs/h_monitoring_hooks_15.h" // MONITORING: 10 Hook functions series 108,10E,114,11B untuk monitoring
#include "libanogs/h_monitoring_hooks_16.h" // MONITORING: 10 Hook functions series 124,12C,133,141,157 untuk monitoring
#include "libanogs/h_monitoring_hooks_17.h" // MONITORING: 10 Hook functions series 157,10E,1B5,298,1FE untuk monitoring
#include "libanogs/h_monitoring_hooks_18.h" // MONITORING: 10 Hook functions series 1xxxx,2xxxx untuk monitoring
#include "libanogs/h_monitoring_hooks_19.h" // MONITORING: 10 Hook functions series 190,305,310,32A,340 untuk monitoring
#include "libanogs/h_monitoring_hooks_20.h" // MONITORING: 10 Hook functions series 102,103,104,105,106 untuk monitoring
#include "libanogs/h_monitoring_hooks_21.h" // MONITORING: 10 Hook functions series 121,122 untuk monitoring
#include "libanogs/h_monitoring_hooks_22.h" // MONITORING: 10 Hook functions series 123,13C,140,15B,222 untuk monitoring
#include "libanogs/h_monitoring_hooks_23.h" // MONITORING: 10 Hook functions series 201,205,250,252,2C4,2C5 untuk monitoring
#include "libanogs/h_monitoring_hooks_24.h" // MONITORING: 10 Hook functions series 21,24,2B,2C,1C untuk monitoring
#include "libanogs/h_monitoring_hooks_25.h" // MONITORING: 10 Hook functions series 139,13A,13B,152,155 untuk monitoring
#include "libanogs/h_monitoring_hooks_26.h" // MONITORING: 10 Hook functions series 198 untuk monitoring
#include "libanogs/h_monitoring_hooks_27.h" // MONITORING: 10 Hook functions series 1C6,1C7 untuk monitoring
#include "libanogs/h_monitoring_hooks_28.h" // MONITORING: 10 Hook functions series 16,191,1D,1F,227 untuk monitoring
#include "libanogs/h_monitoring_hooks_29.h" // MONITORING: 10 Hook functions series 228,24E(210),293,1C5(138),28B untuk monitoring
#include "libanogs/h_monitoring_hooks_30.h" // MONITORING: 10 Hook functions series 1E3,1E4,22E,26E,200 untuk monitoring
#include "libanogs/h_monitoring_hooks_31.h" // MONITORING: 10 Hook functions series 100 untuk monitoring
#include "libanogs/h_monitoring_hooks_32.h" // MONITORING: 10 Hook functions series 100A7C,100B08,100D88,101210,101348 untuk monitoring
#include "libanogs/h_monitoring_hooks_33.h" // MONITORING: 10 Hook functions series 101AA0,101B00,101F2C,101F74,101FB0 untuk monitoring
#include "libanogs/h_monitoring_hooks_34.h" // MONITORING: 10 Hook functions series 10240C,102448,102504,102564,102910 untuk monitoring
#include "libanogs/h_monitoring_hooks_35.h" // MONITORING: 10 Hook functions series 102EB8,102F78,102FD8,1032A4,103304 untuk monitoring
#include "libanogs/h_monitoring_hooks_36.h" // MONITORING: 10 Hook functions series 200D74,200E4C,200ED8,200F30,200FDC untuk monitoring
#include "libanogs/h_monitoring_hooks_37.h" // MONITORING: 10 Hook functions series 1083C4,106EF0,119CCC,1E2910,200054,10B130,200178,2002E4,200234,2003CC untuk monitoring
#include "libanogs/h_monitoring_hooks_38.h" // MONITORING: 10 Hook functions series 1069D4,1287C4,10E808,1543B0,200D1C,201DF8,20AF4C,151B14,300034,3000DC untuk monitoring
#include "libanogs/h_monitoring_hooks_39.h" // MONITORING: 10 Hook functions series 10355C,200084,1039B8,103A28,103A8C,2000A8,30000C,300090,2000CC,2000E0 untuk monitoring
#include "libanogs/h_monitoring_hooks_40.h" // MONITORING: 10 Hook functions series 103F28,103F88,1040F4,104154,2000F4,200118,200144,2001B0,3000B0,30022C untuk monitoring
#include "libanogs/h_monitoring_hooks_41.h" // MONITORING: 10 Hook functions series 1042CC,10432C,10458C,1045EC,2002BC,20030C,200330,200354,30027C,3002B0 untuk monitoring
#include "libanogs/h_monitoring_hooks_42.h" // MONITORING: 10 Hook functions series 1048D4,10518C,1051E4,105330,200368,2003E8,2003FC,200474,300374,3003C8 untuk monitoring
#include "libanogs/h_monitoring_hooks_43.h" // MONITORING: 10 Hook functions series 105390,1054B4,105514,105638,200488,2004C4,2004D8,20052C,3009CC,300A2C untuk monitoring
#include "libanogs/h_monitoring_hooks_44.h" // MONITORING: 10 Hook functions series 10AC20,10ADD8,10AE34,10B098,200554,200580,2005A8,2005D4,300B04,300B38 untuk monitoring
#include "libanogs/h_monitoring_hooks_45.h" // MONITORING: 10 Hook functions series 104A18,106DA8,107E0C,108A38,200B8C,200CE4,2006F0,200728,300494,300A88 untuk monitoring
#include "libanogs/h_monitoring_hooks_46.h" // MONITORING: 10 Hook functions series 1FF7C4,1FF7D8,1FF804,1FF828,2FFBE0,2FFC10,2FFC2C,2FFC54,3FFA00,3FFB28 untuk monitoring
#include "libanogs/h_monitoring_hooks_47.h" // MONITORING: 10 Hook functions series 150140,1501A8,150600,151160,2A02E0,2ADD80,2A0848,2ADD90,353C40,354060 untuk monitoring
#include "libanogs/h_monitoring_hooks_48.h" // MONITORING: 10 Hook functions series 1500C8,1501C0,1503A4,150444,250118,2502B4,2503E0,250940,353838,353AA0 untuk monitoring
#include "libanogs/h_monitoring_hooks_49.h" // MONITORING: 10 Hook functions series 15BE14,15BF2C,15C034,15C178,152004,152178,25A144,25A234,35F144,35F234 untuk monitoring
#include "libanogs/h_monitoring_hooks_50.h" // MONITORING: 10 Hook functions series 1A000C,1A003C,1A0094,1A0108,2A04D8,2A0560,2A05B4,2A05FC,3A00A4,3A0214 untuk monitoring
#include "libanogs/h_monitoring_hooks_51.h" // MONITORING: 10 Hook functions series 113A50,114710,114788,114D08,115FE8,116134,200724,200770,300CE8,3AB2A0 untuk monitoring
#include "libanogs/h_monitoring_hooks_52.h" // MONITORING: 10 Hook functions series 1E0040,1E008C,1E0184,1E0258,2E01A4,2E04D8,2E0148,2E04B8,3E0614,3E0674 untuk monitoring
#include "libanogs/h_monitoring_hooks_53.h" // MONITORING: 10 Hook functions series 1D0020,1D0028,1D00A4,1D0178,2F0004,2F0100,2F0134,2F0310,3F01E8,3F0214 untuk monitoring
// #include "libanogs/h_sub_131CD4.h"
// #include "libanogs/h_sub_12BE38.h"
//#include "libanogs/h_sub_24A3FC.h"

//#include "libunity/h_GameEngine_SystemSetting__set_EnableVulkan.h"
// REMOVED: TerSafeHook.h and NetworkHooks.h - These have been integrated into FakeStatus.h
// #include "libunity/TerSafeHook.h"
// #include "libunity/NetworkHooks.h"
//#include "libunity/unity_offsets.h"
//#include "libunity/EmulatorHooks.h"

#endif