#ifndef ARCAMOD_H_SUB_11B300_H
#define ARCAMOD_H_SUB_11B300_H

#include <cstdint>
#include <cstring>

__int64 (__fastcall *o_sub_11B300)(__int64 a1, char *a2, int a3, __int64 a4) = nullptr;

static __int64 __fastcall h_sub_11B300(__int64 a1, char *a2, int a3, __int64 a4) {
    const char* blocked_strings[] = {
    };

    uintptr_t blocked_offsets[] = {
            0x11bdcc,
            0x11bfb4,
//            0x11cf74//Auto 10y
//            0x11d098
    };

    uintptr_t pointer_call = reinterpret_cast<uintptr_t>(__builtin_return_address(0));
    uintptr_t offset_call = pointer_call - base_address;

    // LOGIO("[DEBUG] Checking memory map before processing sub_11B300:");
    // read_proc_maps();

    for (size_t i = 0; i < sizeof(blocked_offsets) / sizeof(blocked_offsets[0]); ++i) {
        if (offset_call == blocked_offsets[i]) {
//             LOGIO("sub_11B300 [BLOCK OFFSET] | Offset: 0x%lx", offset_call);
            return 0LL;
        }
    }

    for (size_t i = 0; i < sizeof(blocked_strings) / sizeof(blocked_strings[0]); ++i) {
        if (strcmp(reinterpret_cast<const char*>(a1), blocked_strings[i]) == 0) {
            // LOGIO("sub_11B300 [BLOCK STRING] | Offset: 0x%lx", offset_call);
            return 0LL;
        }
    }

//    LOGIO("sub_11B300 [ALLOW] | Offset: 0x%lx", offset_call);

    return o_sub_11B300(a1, a2, a3, a4);
}

#endif // ARCAMOD_H_SUB_11B300_H