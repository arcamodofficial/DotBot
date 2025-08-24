//
// Created by t.me/arcamod on 6/4/2025.
//

#ifndef ARCAMOD_H_SUB_1B0088_H
#define ARCAMOD_H_SUB_1B0088_H

#include <cstdint>
#include <cstring>

// Deklarasi fungsi asli untuk hook sub_1B0088
__int64 (*o_sub_1B0088)();

// Fungsi hook untuk sub_1B0088
__int64 h_sub_1B0088() {
    // Inisialisasi base_address jika belum diatur
    if (base_address == 0) {
        base_address = Tools::GetBaseAddress(OBF("libanogs.so"));
    }

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    // Daftar offset yang akan diblokir
    uintptr_t blocked_offsets[] = {
        // Offset dari log sebelumnya
        0x1cbdb0, 0x14a5bc, 0x14a60c, 0x1cb744, 0x1cb7f4, 
        0x10eaa0, 0x1cbf74, 0x1cfaec, 0x10c068, 0x4126e8, 
        0xfae20, 0x1219c0, 0xf3968, 0x11ab74, 0xf24f0, 
        0x1992ac, 0xf2658, 0xda2c0, 0xd37cc, 0x42e358,
        0xd7564, 0xdb9b0, 0xd7c00, 0x42de5c, 0xd6ad4,
        0xd55e4, 0xdb9b0, 0x1039e4, 0x42e244, 0x42e180,
        0x10531c, 0x42e1a0, 0x1407a0, 0x1b0c8c, 0x11b698,
        0x11b664, 0x11b47c, 0x1b01d4, 0x11b56c, 0x11af78,
        0x11b468, 0x11a0b8, 0x11ad10, 0x11b570, 0x11aa7c,
        0x1b01d8, 0x11b44c, 0x11b564, 0x11b568, 0x11b5a0,
        0x11b588, 0x11b58c, 0x11b590, 0x11b594, 0x11b598,
        0x11b59c, 0x11b5a4, 0x11b5a8, 0x11b5ac, 0x11b5b0,
        0x11b5b4, 0x11b5b8, 0x11b5bc, 0x1407a0, 0x1407a8,
        0x1407ac,
        
        // Offset dari log kedua
        0xd79a8, 0x1ba9a8, 0x19e688, 0x19e640, 0x121e98,
        0xd6cc4, 0xd6a00, 0x119e18, 0x119e78, 0x1cfa90, 
        0x118ed0, 0x1ccebc, 0x1cb09c, 0x1ce864, 0x1ce924, 
        0x1ced70, 0x1cc858, 0x122c68, 0x11a02c, 0x14ab40, 
        0x14620c, 0x1442b8, 0x108408, 0x1070b0, 0x107294, 
        0x10996c, 0x19b0ac, 0x1bbdc8, 0x199274, 0x199388, 
        0x1c08b0, 0xd32a0, 0x1250e0,
        
        // Offset baru dari log terakhir
        0x11bd50, 0x141ed4, 0xd82ac, 0x173a04, 0x140364,
        0x173dfc, 0x173e2c, 0x132f5c, 0xd50f8, 0x11bd70,
        0x179be8, 0x11a0d4, 0x11cc3c, 0x1538c8, 0x155f88,
        0x11ce64, 0x11abb4, 0x11deec, 0x124f3c, 0x11e2cc,
        0x125c84, 0x122b90, 0x11f6cc, 0x11e88c, 0x40e4e8,
        0x40a304, 0x4131e0, 0x11f8d0, 0x11fbb8, 0x11ed80,
        0x121758, 0x11a27c, 0x11a344, 0x11a3e4, 0x1c5944
    };

    // Nilai return yang konsisten dari log
    __int64 consistent_return_value = 0x73cf47e80e00;

    // Cek apakah offset ada dalam daftar blokir
    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
            // Offset diblokir, kembalikan nilai konsisten tanpa memanggil fungsi asli
            // LOGI("[SUB_1B0088] BLOCKED call from offset: 0x%lx", offset_call);
            return consistent_return_value;
        }
    }

    // Jika tidak diblokir, log dan panggil fungsi asli
    LOGI("[SUB_1B0088] ALLOWED call from new offset: 0x%lx", offset_call);
    
    // Panggil fungsi asli dan simpan hasilnya
    __int64 result = o_sub_1B0088();
    
    // Log nilai return
    LOGI("[SUB_1B0088] Return value: 0x%llx", result);
    
    return result;
}

#endif //ARCAMOD_H_SUB_1B0088_H 