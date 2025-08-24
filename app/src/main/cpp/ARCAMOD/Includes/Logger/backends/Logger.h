#ifndef Logger_h
#define Logger_h

#include <jni.h>
#include <android/log.h>

#ifdef DEBUG
    #define ARCAMOD_LOG_ENABLED 1
    #define ARCAMOD_LOGD(tag, msg) \
        __android_log_write(ANDROID_LOG_DEBUG, tag, msg)

    #define ARCAMOD_LOGD_FMT(tag, fmt, ...) \
        __android_log_print(ANDROID_LOG_DEBUG, tag, fmt, ##__VA_ARGS__)

    #define ARCAMOD_LOGE(tag, msg) \
        __android_log_write(ANDROID_LOG_ERROR, tag, msg)

    #define ARCAMOD_LOGE_FMT(tag, fmt, ...) \
        __android_log_print(ANDROID_LOG_ERROR, tag, fmt, ##__VA_ARGS__)

    #define ARCAMOD_LOGI(tag, msg) \
        __android_log_write(ANDROID_LOG_INFO, tag, msg)

    #define ARCAMOD_LOGI_FMT(tag, fmt, ...) \
        __android_log_print(ANDROID_LOG_INFO, tag, fmt, ##__VA_ARGS__)

    #define ARCAMOD_LOGD_IF(condition, tag, msg) \
        do { if (condition) ARCAMOD_LOGD(tag, msg); } while(0)

    #define ARCAMOD_LOGE_IF(condition, tag, msg) \
        do { if (condition) ARCAMOD_LOGE(tag, msg); } while(0)

#else
    #define ARCAMOD_LOG_ENABLED 0
    #define ARCAMOD_LOGD(tag, msg) ((void)0)
    #define ARCAMOD_LOGD_FMT(tag, fmt, ...) ((void)0)
    #define ARCAMOD_LOGE(tag, msg) ((void)0)
    #define ARCAMOD_LOGE_FMT(tag, fmt, ...) ((void)0)
    #define ARCAMOD_LOGI(tag, msg) ((void)0)
    #define ARCAMOD_LOGI_FMT(tag, fmt, ...) ((void)0)
    #define ARCAMOD_LOGD_IF(condition, tag, msg) ((void)0)
    #define ARCAMOD_LOGE_IF(condition, tag, msg) ((void)0)
#endif

#ifdef DEBUG
    #include <chrono>
    #define ARCAMOD_TIME_BLOCK(name) \
        auto start_##name = std::chrono::high_resolution_clock::now(); \
        auto end_##name = std::chrono::high_resolution_clock::now(); \
        auto duration_##name = std::chrono::duration_cast<std::chrono::microseconds>(end_##name - start_##name); \
        ARCAMOD_LOGD_FMT("PERF", "%s took %ld microseconds", #name, duration_##name.count());

    #define ARCAMOD_TIME_START(name) \
        auto start_##name = std::chrono::high_resolution_clock::now();

    #define ARCAMOD_TIME_END(name) \
        auto end_##name = std::chrono::high_resolution_clock::now(); \
        auto duration_##name = std::chrono::duration_cast<std::chrono::microseconds>(end_##name - start_##name); \
        ARCAMOD_LOGD_FMT("PERF", "%s took %ld microseconds", #name, duration_##name.count());
#else
    #define ARCAMOD_TIME_BLOCK(name) ((void)0)
    #define ARCAMOD_TIME_START(name) ((void)0)
    #define ARCAMOD_TIME_END(name) ((void)0)
#endif

#endif /* Logger_h */
