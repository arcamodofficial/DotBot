#ifndef ARCAMOD_UNITY_OFFSETS_H
#define ARCAMOD_UNITY_OFFSETS_H

static inline const char* GetVulkanSetterOffset() {
    static char buffer[32];
    const char* encoded = OBF(UNITY_VulkanSetter);

    for (int i = 0; encoded[i]; i++) {
        buffer[i] = encoded[i];
    }

    return buffer;
}

#endif //ARCAMOD_UNITY_OFFSETS_H