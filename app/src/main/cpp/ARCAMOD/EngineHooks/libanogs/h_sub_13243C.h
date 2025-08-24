#ifndef ARCAMOD_H_SUB_13243C_H
#define ARCAMOD_H_SUB_13243C_H

int __fastcall (*o_sub_13243C)(int *a1, const char *a2, int *a3);

static int __fastcall h_sub_13243C(int *a1, const char *a2, int *a3) {
    const char* blocked_strings[] = {
            OBF("antiemulator"),
            OBF("cert3"),
    };

    uintptr_t blocked_offsets[] = {
            /*
            0x174958,//allow_xbl
            // 0x156654,//auto 3days
//            0x12af98,//Hilang
//            0x12b1e8,//Hilang
            0x169498,//sc_report //hilang
            0x417648,//property_get
//            0x11bff4,//Hilang
            0x1cf8e8,//cs_pkg_init
            0x106fa8,//port_80
            0x109894,//test_cs_ip_ext
            0x18b56c,//chk_elf_header2
            0x1b51b0,//CSReconnect
//            0x18113c,//Hilang
            0x1b2ffc,//device_info
            0x174e38,//x86_sys_scan
            0x18b548,//filter_by_uid
            0x17ff6c,//DexScan
//            0x15f40c,//cps_light_scan //hilang
            0x14fa88,//gp5_9992
            0x18c5e0,//zygisk_module
            0x10848c,//cs_ipv6
//            0x172a98,//switch_cs3 //hilang
            0x14b22c,//ten_origin_fd
            0x1d08d0,//anti_blackmodule
//            0x422a80,//gcloud_log //Hilang
//            0x3dd09c,//Hilang
            0x1b1028,//force_apk_collect
            0x16fcbc,//str
            0x170494,//seccp
            0x155e94,//gp4_nonblock
            0x11ed64,//comm_first
            0x121ec0,//rcv_by_main
            0x12d100,//tcj
            0x109c5c,//force_built_in_ip
            0x40ae14,//tdm_report
            0x106a3c,//cs3
            0x140348,//sec_path
//            0x119a04,//local_cache //Hilang
            0x1d5490,//emu_tp
            0x17321c,//9005.hi2
            0x16da00,//opcode_crash
            0x198930,//att_dev_flash
            0x16907c,//da_vap
            0x125c9c,//req_cf2
            0x1cb0c4,//mt_sar
//            0x1a38b8,//Hilang
//            0x1a24a4,//Hilang
            0x11c13c,//report_bk
            0x15c23c,//random_trap
            0x128678,//scan1
            0x11bee0,//anti_ts2
            0x1cf8e8,//cs_pkg_init
            0x11a040,//force_apk_collect
            0x146234,//force_apk_collect
            0x421f54,//cal_cert_md5
            0x40a320,//tdm_dev_info
//            0x1578c4,//fast_mm //Hilang
             */
            0x15bc30,
            0x11bee0,
            0x1b51b0,
            0x11c13c,
            0x124f94,
            0x121ec0,
            0x1cf8e8,
            0x40a320,
            0x421f54,
            0x146234,
            0x173e50,
            0x15c23c,
            0x1cb0c4,
            0x125c9c,
            0x140348,
            0x106a3c,
            0x106fa8,
            0x417648,
            0x40ae14,
            0x109894
    };

    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
//            LOGIO("sub_13243C [BLOCK OFFSET] | Offset: 0x%lx", offset_call);
            return 0;
        }
    }

    for (size_t i = 0; i < sizeof(blocked_strings) / sizeof(blocked_strings[0]); ++i) {
        if (strcmp(a2, blocked_strings[i]) == 0) {
//            LOGIO("sub_13243C [BLOCK STRING] | Thread: %s | Offset: 0x%lx", a2, offset_call);
            return 0;
        }
    }

//     LOGIO("sub_13243C [ALLOW] | Thread: %s | Offset: 0x%lx", a2, offset_call);

    return o_sub_13243C(a1, a2, a3);
}
#endif //ARCAMOD_H_SUB_13243C_H