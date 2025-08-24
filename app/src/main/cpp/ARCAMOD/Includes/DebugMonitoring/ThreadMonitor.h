#ifndef ARCAMOD_THREAD_MONITOR_H
#define ARCAMOD_THREAD_MONITOR_H

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <map>
#include <android/log.h>
// #include "CrashDetector.h" // REMOVED: Crash tracking system dihapus

// Thread monitoring configuration - Only enabled in Debug builds
#ifdef DEBUG
#define THREAD_MONITOR_ENABLED 1
#else
#define THREAD_MONITOR_ENABLED 0  // Disabled in Release builds
#endif
#define MAX_THREAD_HISTORY 100
#define THREAD_TIMEOUT_SECONDS 30

// Thread status
enum ThreadStatus {
    THREAD_STATUS_ACTIVE = 0,
    THREAD_STATUS_IDLE = 1,
    THREAD_STATUS_CRASHED = 2,
    THREAD_STATUS_TIMEOUT = 3,
    THREAD_STATUS_UNKNOWN = 99
};

// Thread information
struct ThreadInfo {
    pthread_t thread_id;
    ThreadType thread_type;
    ThreadStatus status;
    time_t last_activity;
    time_t start_time;
    std::string current_function;
    std::string current_file;
    int current_line;
    int crash_count;
    bool is_critical;
};

// Global thread registry
extern std::map<pthread_t, ThreadInfo> g_thread_registry;
extern pthread_mutex_t g_thread_mutex;

// Function declarations
void InitializeThreadMonitor();
void RegisterThread(ThreadType type, bool is_critical = false);
void UnregisterThread();
void UpdateThreadActivity(const char* function_name, const char* file_name, int line_number);
void CheckThreadHealth();
void LogThreadCrash(pthread_t thread_id);
void WriteThreadReport();
std::string GetThreadStatusName(ThreadStatus status);

// Macros for thread monitoring
#define THREAD_MONITOR_REGISTER(type) RegisterThread(type, false)
#define THREAD_MONITOR_REGISTER_CRITICAL(type) RegisterThread(type, true)
#define THREAD_MONITOR_UPDATE() UpdateThreadActivity(__FUNCTION__, __FILE__, __LINE__)
#define THREAD_MONITOR_UNREGISTER() UnregisterThread()

// ESP thread monitoring
#define ESP_THREAD_START() \
    do { \
        THREAD_MONITOR_REGISTER_CRITICAL(THREAD_ESP); \
        THREAD_MONITOR_UPDATE(); \
    } while(0)

#define ESP_THREAD_UPDATE() \
    do { \
        THREAD_MONITOR_UPDATE(); \
    } while(0)

#define ESP_THREAD_END() \
    do { \
        THREAD_MONITOR_UNREGISTER(); \
    } while(0)

// EGL thread monitoring
#define EGL_THREAD_START() \
    do { \
        THREAD_MONITOR_REGISTER_CRITICAL(THREAD_EGL); \
        THREAD_MONITOR_UPDATE(); \
    } while(0)

#define EGL_THREAD_UPDATE() \
    do { \
        THREAD_MONITOR_UPDATE(); \
    } while(0)

#define EGL_THREAD_END() \
    do { \
        THREAD_MONITOR_UNREGISTER(); \
    } while(0)

// Implementation
inline void InitializeThreadMonitor() {
    if (!THREAD_MONITOR_ENABLED) return;
    
    pthread_mutex_init(&g_thread_mutex, nullptr);
    g_thread_registry.clear();
    
    // Register main thread
    RegisterThread(THREAD_MAIN, true);
    
    __android_log_print(ANDROID_LOG_INFO, OBF("ARCAMOD"), OBF("Thread Monitor initialized"));
}

inline void RegisterThread(ThreadType type, bool is_critical) {
    if (!THREAD_MONITOR_ENABLED) return;
    
    pthread_mutex_lock(&g_thread_mutex);
    
    pthread_t current_thread = pthread_self();
    ThreadInfo info;
    info.thread_id = current_thread;
    info.thread_type = type;
    info.status = THREAD_STATUS_ACTIVE;
    info.last_activity = time(nullptr);
    info.start_time = info.last_activity;
    info.current_function = OBF("");
    info.current_file = OBF("");
    info.current_line = 0;
    info.crash_count = 0;
    info.is_critical = is_critical;
    
    g_thread_registry[current_thread] = info;
    
    pthread_mutex_unlock(&g_thread_mutex);
    
    __android_log_print(ANDROID_LOG_DEBUG, OBF("ARCAMOD"),
        OBF("Thread registered: %s (ID: %lu, Critical: %s)"),
        GetThreadTypeName(type).c_str(),
        (unsigned long)current_thread,
        is_critical ? OBF("YES") : OBF("NO"));
}

inline void UnregisterThread() {
    if (!THREAD_MONITOR_ENABLED) return;
    
    pthread_mutex_lock(&g_thread_mutex);
    
    pthread_t current_thread = pthread_self();
    auto it = g_thread_registry.find(current_thread);
    if (it != g_thread_registry.end()) {
        __android_log_print(ANDROID_LOG_DEBUG, OBF("ARCAMOD"),
            OBF("Thread unregistered: %s (ID: %lu)"),
            GetThreadTypeName(it->second.thread_type).c_str(),
            (unsigned long)current_thread);
        g_thread_registry.erase(it);
    }
    
    pthread_mutex_unlock(&g_thread_mutex);
}

inline void UpdateThreadActivity(const char* function_name, const char* file_name, int line_number) {
    if (!THREAD_MONITOR_ENABLED) return;
    
    pthread_mutex_lock(&g_thread_mutex);
    
    pthread_t current_thread = pthread_self();
    auto it = g_thread_registry.find(current_thread);
    if (it != g_thread_registry.end()) {
        it->second.last_activity = time(nullptr);
        it->second.status = THREAD_STATUS_ACTIVE;
        it->second.current_function = function_name ? function_name : OBF("");
        it->second.current_file = file_name ? file_name : OBF("");
        it->second.current_line = line_number;
    }
    
    pthread_mutex_unlock(&g_thread_mutex);
}

inline std::string GetThreadStatusName(ThreadStatus status) {
    switch (status) {
        case THREAD_STATUS_ACTIVE: return OBF("Active");
        case THREAD_STATUS_IDLE: return OBF("Idle");
        case THREAD_STATUS_CRASHED: return OBF("Crashed");
        case THREAD_STATUS_TIMEOUT: return OBF("Timeout");
        default: return OBF("Unknown");
    }
}

inline void LogThreadCrash(pthread_t thread_id) {
    if (!THREAD_MONITOR_ENABLED) return;
    
    pthread_mutex_lock(&g_thread_mutex);
    
    auto it = g_thread_registry.find(thread_id);
    if (it != g_thread_registry.end()) {
        it->second.status = THREAD_STATUS_CRASHED;
        it->second.crash_count++;
        
        __android_log_print(ANDROID_LOG_ERROR, OBF("ARCAMOD"),
            OBF("Thread crash detected: %s (ID: %lu, Crashes: %d)"),
            GetThreadTypeName(it->second.thread_type).c_str(),
            (unsigned long)thread_id,
            it->second.crash_count);
    }
    
    pthread_mutex_unlock(&g_thread_mutex);
}

inline void CheckThreadHealth() {
    if (!THREAD_MONITOR_ENABLED) return;
    
    pthread_mutex_lock(&g_thread_mutex);
    
    time_t current_time = time(nullptr);
    
    for (auto& pair : g_thread_registry) {
        ThreadInfo& info = pair.second;
        
        if (current_time - info.last_activity > THREAD_TIMEOUT_SECONDS) {
            if (info.status != THREAD_STATUS_TIMEOUT) {
                info.status = THREAD_STATUS_TIMEOUT;
                
                __android_log_print(ANDROID_LOG_WARN, OBF("ARCAMOD"),
                    OBF("Thread timeout: %s (ID: %lu, Last activity: %ld seconds ago)"),
                    GetThreadTypeName(info.thread_type).c_str(),
                    (unsigned long)info.thread_id,
                    current_time - info.last_activity);
            }
        } else if (info.status == THREAD_STATUS_TIMEOUT) {
            info.status = THREAD_STATUS_ACTIVE;
        }
    }
    
    pthread_mutex_unlock(&g_thread_mutex);
}

// Global variables
std::map<pthread_t, ThreadInfo> g_thread_registry;
pthread_mutex_t g_thread_mutex;

#endif // ARCAMOD_THREAD_MONITOR_H
