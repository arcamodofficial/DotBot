#ifndef ARCAMOD_CRASH_DETECTOR_H
#define ARCAMOD_CRASH_DETECTOR_H

#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <pthread.h>
#include <android/log.h>

// Crash detection configuration - Only enabled in Debug builds
#define CRASH_LOG_PATH OBF("/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Crash_Report.txt")
#define MAX_CRASH_REPORTS 50

// Crash detection only enabled in Debug builds
#ifdef DEBUG
#define CRASH_DETECTION_ENABLED 1
#else
#define CRASH_DETECTION_ENABLED 0  // Disabled in Release builds
#endif

// Thread identification
enum ThreadType {
    THREAD_MAIN = 0,
    THREAD_EGL = 1,
    THREAD_ESP = 2,
    THREAD_RENDER = 3,
    THREAD_UNKNOWN = 99
};

// Crash context information
struct CrashContext {
    int signal_number;
    void* crash_address;
    const char* function_name;
    const char* file_name;
    int line_number;
    ThreadType thread_type;
    time_t crash_time;
    pid_t process_id;
    pthread_t thread_id;
    bool is_esp_related;
    bool is_egl_related;
    std::string additional_info;
};

// Global crash context
extern CrashContext g_crash_context;
extern bool g_crash_detection_active;

// Function declarations
void InitializeCrashDetector();
void SetCurrentFunction(const char* function_name, const char* file_name, int line_number);
void SetThreadType(ThreadType type);
void WriteCrashReport(const CrashContext& context);
void HandleCrashSignal(int signal, siginfo_t* info, void* context);
std::string GetCurrentTimestamp();
std::string GetThreadTypeName(ThreadType type);
std::string GetSignalName(int signal);
void CleanupOldCrashReports();

// Macros for easy crash tracking
#define CRASH_TRACK_FUNCTION() SetCurrentFunction(__FUNCTION__, __FILE__, __LINE__)
#define CRASH_TRACK_EGL() SetThreadType(THREAD_EGL); SetCurrentFunction(__FUNCTION__, __FILE__, __LINE__)
#define CRASH_TRACK_ESP() SetThreadType(THREAD_ESP); SetCurrentFunction(__FUNCTION__, __FILE__, __LINE__)

// ESP-specific crash tracking
#define ESP_CRASH_GUARD_START() \
    do { \
        CRASH_TRACK_ESP(); \
        g_crash_context.is_esp_related = true; \
    } while(0)

#define ESP_CRASH_GUARD_END() \
    do { \
        g_crash_context.is_esp_related = false; \
    } while(0)

// EGL-specific crash tracking
#define EGL_CRASH_GUARD_START() \
    do { \
        CRASH_TRACK_EGL(); \
        g_crash_context.is_egl_related = true; \
    } while(0)

#define EGL_CRASH_GUARD_END() \
    do { \
        g_crash_context.is_egl_related = false; \
    } while(0)

// Implementation - Signal handlers disabled, mengandalkan EGL.h unified handler
inline void InitializeCrashDetector() {
    if (!CRASH_DETECTION_ENABLED) return;

    g_crash_detection_active = true;

    // Signal handlers dihapus - mengandalkan unified handler dari EGL.h
    // Hanya initialize crash context untuk logging

    // Initialize crash context
    memset(&g_crash_context, 0, sizeof(CrashContext));
    g_crash_context.process_id = getpid();
    g_crash_context.thread_type = THREAD_MAIN;

    // Cleanup old reports
    CleanupOldCrashReports();

    __android_log_print(ANDROID_LOG_INFO, OBF("ARCAMOD"), OBF("Crash Detector initialized (no signal handlers)"));
}

inline void SetCurrentFunction(const char* function_name, const char* file_name, int line_number) {
    if (!g_crash_detection_active) return;
    
    g_crash_context.function_name = function_name;
    g_crash_context.file_name = file_name;
    g_crash_context.line_number = line_number;
    g_crash_context.thread_id = pthread_self();
}

inline void SetThreadType(ThreadType type) {
    if (!g_crash_detection_active) return;
    g_crash_context.thread_type = type;
}

inline std::string GetCurrentTimestamp() {
    time_t now = time(0);
    char buffer[100];
    strftime(buffer, sizeof(buffer), OBF("%Y-%m-%d %H:%M:%S"), localtime(&now));
    return std::string(buffer);
}

inline std::string GetThreadTypeName(ThreadType type) {
    switch (type) {
        case THREAD_MAIN: return OBF("Main Thread");
        case THREAD_EGL: return OBF("EGL Thread");
        case THREAD_ESP: return OBF("ESP Thread");
        case THREAD_RENDER: return OBF("Render Thread");
        default: return OBF("Unknown Thread");
    }
}

inline std::string GetSignalName(int signal) {
    switch (signal) {
        case SIGSEGV: return OBF("Memory Access Fault");
        case SIGABRT: return OBF("System Abort");
        case SIGFPE: return OBF("Math Exception");
        case SIGILL: return OBF("Invalid Operation");
        case SIGBUS: return OBF("Memory Bus Error");
        default: return OBF("Unknown Signal");
    }
}

inline void WriteCrashReport(const CrashContext& context) {
    std::ofstream crash_file(CRASH_LOG_PATH, std::ios::app);
    if (!crash_file.is_open()) {
        __android_log_print(ANDROID_LOG_ERROR, OBF("ARCAMOD"), OBF("Failed to open crash report file"));
        return;
    }

    crash_file << OBF("================== ARCAMOD CRASH REPORT ==================\n");
    crash_file << OBF("Timestamp: ") << GetCurrentTimestamp() << OBF("\n");
    crash_file << OBF("Signal: ") << GetSignalName(context.signal_number) << OBF(" (") << context.signal_number << OBF(")\n");
    crash_file << OBF("Process ID: ") << context.process_id << OBF("\n");
    crash_file << OBF("Thread ID: ") << context.thread_id << OBF("\n");
    crash_file << OBF("Thread Type: ") << GetThreadTypeName(context.thread_type) << OBF("\n");

    if (context.crash_address) {
        crash_file << OBF("Crash Address: 0x") << std::hex << context.crash_address << std::dec << OBF("\n");
    }

    if (context.function_name) {
        crash_file << OBF("Function: ") << context.function_name << OBF("\n");
    }

    if (context.file_name) {
        crash_file << OBF("File: ") << context.file_name;
        if (context.line_number > 0) {
            crash_file << OBF(":") << context.line_number;
        }
        crash_file << OBF("\n");
    }

    crash_file << OBF("ESP Related: ") << (context.is_esp_related ? OBF("YES") : OBF("NO")) << OBF("\n");
    crash_file << OBF("EGL Related: ") << (context.is_egl_related ? OBF("YES") : OBF("NO")) << OBF("\n");

    if (!context.additional_info.empty()) {
        crash_file << OBF("Additional Info: ") << context.additional_info << OBF("\n");
    }

    // Crash analysis
    crash_file << OBF("\n--- CRASH ANALYSIS ---\n");
    if (context.is_esp_related) {
        crash_file << OBF("ESP CRASH DETECTED:\n");
        crash_file << OBF("- Likely cause: Invalid memory access in ESP rendering\n");
        crash_file << OBF("- Check: Entity pointer validation, transform access\n");
        crash_file << OBF("- Location: Draws.h ESP functions\n");
    }

    if (context.is_egl_related) {
        crash_file << OBF("EGL CRASH DETECTED:\n");
        crash_file << OBF("- Likely cause: OpenGL context or rendering issue\n");
        crash_file << OBF("- Check: EGL context state, texture operations\n");
        crash_file << OBF("- Location: EGL.h rendering functions\n");
    }

    if (context.signal_number == SIGSEGV) {
        crash_file << OBF("MEMORY ACCESS FAULT ANALYSIS:\n");
        crash_file << OBF("- Null pointer dereference or invalid memory access\n");
        crash_file << OBF("- Check pointer validation before use\n");
        crash_file << OBF("- Verify memory alignment and bounds\n");
    }

    crash_file << OBF("\n========================================================\n\n");
    crash_file.close();

    __android_log_print(ANDROID_LOG_ERROR, OBF("ARCAMOD"), OBF("Crash report written to %s"), CRASH_LOG_PATH);
}

// DISABLED: HandleCrashSignal tidak akan dipanggil karena signal handler tidak di-install
/*
inline void HandleCrashSignal(int sig, siginfo_t* info, void* context) {
    if (!g_crash_detection_active) return;

    // Update crash context
    g_crash_context.signal_number = sig;
    g_crash_context.crash_time = time(nullptr);

    if (info) {
        g_crash_context.crash_address = info->si_addr;
    }

    // Write crash report
    WriteCrashReport(g_crash_context);

    // Log to Android log as well
    __android_log_print(ANDROID_LOG_FATAL, OBF("ARCAMOD"),
        OBF("CRASH DETECTED: %s in %s (%s:%d) - Thread: %s"),
        GetSignalName(sig).c_str(),
        g_crash_context.function_name ? g_crash_context.function_name : OBF("Unknown"),
        g_crash_context.file_name ? g_crash_context.file_name : OBF("Unknown"),
        g_crash_context.line_number,
        GetThreadTypeName(g_crash_context.thread_type).c_str());
*/

// SIMPLIFIED: Manual crash reporting function (dapat dipanggil manual jika diperlukan)
inline void ManualCrashReport(const char* function_name, const char* file_name, int line_number) {
    if (!CRASH_DETECTION_ENABLED) return;

    // Update crash context manually
    g_crash_context.signal_number = SIGSEGV; // Default
    g_crash_context.crash_time = time(nullptr);
    g_crash_context.function_name = function_name;
    g_crash_context.file_name = file_name;
    g_crash_context.line_number = line_number;

    // Write crash report
    WriteCrashReport(g_crash_context);

    __android_log_print(ANDROID_LOG_ERROR, OBF("ARCAMOD"),
        OBF("MANUAL CRASH REPORT: %s (%s:%d)"), function_name, file_name, line_number);

    // Call default handler to terminate
    signal(sig, SIG_DFL);
    raise(sig);
}

inline void CleanupOldCrashReports() {
    std::ifstream file(CRASH_LOG_PATH);
    if (!file.is_open()) return;

    std::string content((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
    file.close();

    // Count crash reports
    size_t report_count = 0;
    size_t pos = 0;
    while ((pos = content.find(OBF("================== ARCAMOD CRASH REPORT =================="), pos)) != std::string::npos) {
        report_count++;
        pos += 59;
    }

    // If too many reports, keep only the last MAX_CRASH_REPORTS
    if (report_count > MAX_CRASH_REPORTS) {
        size_t keep_from = 0;
        size_t current_count = 0;
        pos = 0;

        while ((pos = content.find(OBF("================== ARCAMOD CRASH REPORT =================="), pos)) != std::string::npos) {
            current_count++;
            if (current_count == report_count - MAX_CRASH_REPORTS + 1) {
                keep_from = pos;
                break;
            }
            pos += 59;
        }

        if (keep_from > 0) {
            std::ofstream out_file(CRASH_LOG_PATH);
            out_file << content.substr(keep_from);
            out_file.close();
        }
    }
}

// Global variables (defined in implementation)
CrashContext g_crash_context;
bool g_crash_detection_active = false;

#endif // ARCAMOD_CRASH_DETECTOR_H
