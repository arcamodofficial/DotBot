#ifndef ARCAMOD_DEBUG_COMMANDS_H
#define ARCAMOD_DEBUG_COMMANDS_H

#include <string>
#include <fstream>
#include <android/log.h>
// #include "CrashDetector.h" // REMOVED: Crash tracking system dihapus
#include "ThreadMonitor.h"
#include "CrashAnalyzer.h"

// Debug commands configuration - Only enabled in Debug builds
#ifdef DEBUG
#define DEBUG_COMMANDS_ENABLED 1
#else
#define DEBUG_COMMANDS_ENABLED 0  // Disabled in Release builds
#endif
#define DEBUG_OUTPUT_PATH OBF("/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Debug_Output.txt")

// Debug command types
enum DebugCommand {
    CMD_CRASH_REPORT = 0,
    CMD_THREAD_STATUS = 1,
    CMD_CRASH_STATS = 2,
    CMD_SYSTEM_INFO = 3,
    CMD_CLEAR_LOGS = 4,
    CMD_FORCE_CRASH_TEST = 5
};

// Function declarations
void InitializeDebugCommands();
void ExecuteDebugCommand(DebugCommand cmd);
void GenerateCrashReport();
void GenerateThreadStatus();
void GenerateCrashStatistics();
void GenerateSystemInfo();
void ClearAllLogs();
void ForceCrashTest();
void WriteDebugOutput(const std::string& content);

// Macros for debug commands
#define DEBUG_CRASH_REPORT() ExecuteDebugCommand(CMD_CRASH_REPORT)
#define DEBUG_THREAD_STATUS() ExecuteDebugCommand(CMD_THREAD_STATUS)
#define DEBUG_CRASH_STATS() ExecuteDebugCommand(CMD_CRASH_STATS)
#define DEBUG_SYSTEM_INFO() ExecuteDebugCommand(CMD_SYSTEM_INFO)
#define DEBUG_CLEAR_LOGS() ExecuteDebugCommand(CMD_CLEAR_LOGS)

// Implementation
inline void InitializeDebugCommands() {
    if (!DEBUG_COMMANDS_ENABLED) return;
    
    __android_log_print(ANDROID_LOG_INFO, OBF("ARCAMOD"), OBF("Debug Commands initialized"));
}

inline void WriteDebugOutput(const std::string& content) {
    std::ofstream debug_file(DEBUG_OUTPUT_PATH, std::ios::app);
    if (debug_file.is_open()) {
        debug_file << content;
        debug_file.close();
    }
    
    // Also log to Android log
    __android_log_print(ANDROID_LOG_DEBUG, OBF("ARCAMOD"), OBF("%s"), content.c_str());
}

inline void ExecuteDebugCommand(DebugCommand cmd) {
    if (!DEBUG_COMMANDS_ENABLED) return;
    
    switch (cmd) {
        case CMD_CRASH_REPORT:
            GenerateCrashReport();
            break;
        case CMD_THREAD_STATUS:
            GenerateThreadStatus();
            break;
        case CMD_CRASH_STATS:
            GenerateCrashStatistics();
            break;
        case CMD_SYSTEM_INFO:
            GenerateSystemInfo();
            break;
        case CMD_CLEAR_LOGS:
            ClearAllLogs();
            break;
        case CMD_FORCE_CRASH_TEST:
            ForceCrashTest();
            break;
        default:
            WriteDebugOutput(OBF("Unknown debug command\n"));
            break;
    }
}

inline void GenerateCrashReport() {
    std::string report = OBF("\n=== ARCAMOD CRASH REPORT SUMMARY ===\n");
    report += OBF("Timestamp: ") + GetCurrentTimestamp() + OBF("\n");
    report += OBF("Process ID: ") + std::to_string(getpid()) + OBF("\n");

    // Current crash context
    report += OBF("\nCURRENT CRASH CONTEXT:\n");
    report += OBF("Function: ") + std::string(g_crash_context.function_name ? g_crash_context.function_name : OBF("None")) + OBF("\n");
    report += OBF("File: ") + std::string(g_crash_context.file_name ? g_crash_context.file_name : OBF("None")) + OBF("\n");
    report += OBF("Line: ") + std::to_string(g_crash_context.line_number) + OBF("\n");
    report += OBF("Thread Type: ") + GetThreadTypeName(g_crash_context.thread_type) + OBF("\n");
    report += OBF("ESP Related: ") + std::string(g_crash_context.is_esp_related ? OBF("YES") : OBF("NO")) + OBF("\n");
    report += OBF("EGL Related: ") + std::string(g_crash_context.is_egl_related ? OBF("YES") : OBF("NO")) + OBF("\n");
    
    // Crash statistics
    CrashStats stats = GetCrashStatistics();
    report += OBF("\nCRASH STATISTICS:\n");
    report += OBF("Total Crashes: ") + std::to_string(stats.total_crashes) + OBF("\n");
    report += OBF("ESP Crashes: ") + std::to_string(stats.esp_crashes) + OBF("\n");
    report += OBF("EGL Crashes: ") + std::to_string(stats.egl_crashes) + OBF("\n");
    report += OBF("SIGSEGV Crashes: ") + std::to_string(stats.sigsegv_crashes) + OBF("\n");
    report += OBF("SIGABRT Crashes: ") + std::to_string(stats.sigabrt_crashes) + OBF("\n");

    report += OBF("\nTHREAD CRASHES:\n");
    report += OBF("Main Thread: ") + std::to_string(stats.thread_crashes[THREAD_MAIN]) + OBF("\n");
    report += OBF("EGL Thread: ") + std::to_string(stats.thread_crashes[THREAD_EGL]) + OBF("\n");
    report += OBF("ESP Thread: ") + std::to_string(stats.thread_crashes[THREAD_ESP]) + OBF("\n");
    report += OBF("Render Thread: ") + std::to_string(stats.thread_crashes[THREAD_RENDER]) + OBF("\n");

    report += OBF("\n=====================================\n\n");
    
    WriteDebugOutput(report);
}

inline void GenerateThreadStatus() {
    std::string status = OBF("\n=== THREAD STATUS REPORT ===\n");
    status += OBF("Timestamp: ") + GetCurrentTimestamp() + OBF("\n");

    pthread_mutex_lock(&g_thread_mutex);

    status += OBF("Active Threads: ") + std::to_string(g_thread_registry.size()) + OBF("\n\n");
    
    for (const auto& pair : g_thread_registry) {
        const ThreadInfo& info = pair.second;
        
        status += OBF("Thread ID: ") + std::to_string((unsigned long)info.thread_id) + OBF("\n");
        status += OBF("Type: ") + GetThreadTypeName(info.thread_type) + OBF("\n");
        status += OBF("Status: ") + GetThreadStatusName(info.status) + OBF("\n");
        status += OBF("Critical: ") + std::string(info.is_critical ? OBF("YES") : OBF("NO")) + OBF("\n");
        status += OBF("Crash Count: ") + std::to_string(info.crash_count) + OBF("\n");
        status += OBF("Current Function: ") + info.current_function + OBF("\n");
        status += OBF("Current File: ") + info.current_file + OBF(":") + std::to_string(info.current_line) + OBF("\n");

        time_t current_time = time(nullptr);
        status += OBF("Last Activity: ") + std::to_string(current_time - info.last_activity) + OBF(" seconds ago\n");
        status += OBF("Running Time: ") + std::to_string(current_time - info.start_time) + OBF(" seconds\n");
        status += OBF("---\n");
    }
    
    pthread_mutex_unlock(&g_thread_mutex);

    status += OBF("\n============================\n\n");
    
    WriteDebugOutput(status);
}

inline void GenerateCrashStatistics() {
    CrashStats stats = GetCrashStatistics();
    
    std::string crash_stats = OBF("\n=== CRASH STATISTICS ===\n");
    crash_stats += OBF("Timestamp: ") + GetCurrentTimestamp() + OBF("\n\n");

    crash_stats += OBF("OVERALL STATISTICS:\n");
    crash_stats += OBF("Total Crashes: ") + std::to_string(stats.total_crashes) + OBF("\n");
    
    if (stats.total_crashes > 0) {
        crash_stats += OBF("ESP Crash Rate: ") + std::to_string((stats.esp_crashes * 100) / stats.total_crashes) + OBF("%\n");
        crash_stats += OBF("EGL Crash Rate: ") + std::to_string((stats.egl_crashes * 100) / stats.total_crashes) + OBF("%\n");
        crash_stats += OBF("SIGSEGV Rate: ") + std::to_string((stats.sigsegv_crashes * 100) / stats.total_crashes) + OBF("%\n");
        crash_stats += OBF("SIGABRT Rate: ") + std::to_string((stats.sigabrt_crashes * 100) / stats.total_crashes) + OBF("%\n");
    }
    
    crash_stats += OBF("\nTHREAD BREAKDOWN:\n");
    crash_stats += OBF("Main Thread Crashes: ") + std::to_string(stats.thread_crashes[THREAD_MAIN]) + OBF("\n");
    crash_stats += OBF("EGL Thread Crashes: ") + std::to_string(stats.thread_crashes[THREAD_EGL]) + OBF("\n");
    crash_stats += OBF("ESP Thread Crashes: ") + std::to_string(stats.thread_crashes[THREAD_ESP]) + OBF("\n");
    crash_stats += OBF("Render Thread Crashes: ") + std::to_string(stats.thread_crashes[THREAD_RENDER]) + OBF("\n");
    
    crash_stats += OBF("\nRECOMMENDATIONS:\n");
    if (stats.esp_crashes > stats.egl_crashes) {
        crash_stats += OBF("- Focus on ESP stability (Draws.h)\n");
        crash_stats += OBF("- Add more entity validation\n");
        crash_stats += OBF("- Check SIGSEGV handler effectiveness\n");
    } else if (stats.egl_crashes > stats.esp_crashes) {
        crash_stats += OBF("- Focus on EGL stability (EGL.h)\n");
        crash_stats += OBF("- Check OpenGL context management\n");
        crash_stats += OBF("- Verify texture operations\n");
    }
    
    if (stats.sigsegv_crashes > stats.total_crashes / 2) {
        crash_stats += OBF("- High SIGSEGV rate indicates memory access issues\n");
        crash_stats += OBF("- Add more pointer validation\n");
        crash_stats += OBF("- Check memory alignment\n");
    }

    crash_stats += OBF("\n========================\n\n");
    
    WriteDebugOutput(crash_stats);
}

inline void GenerateSystemInfo() {
    std::string sys_info = OBF("\n=== SYSTEM INFORMATION ===\n");
    sys_info += OBF("Timestamp: ") + GetCurrentTimestamp() + OBF("\n");
    sys_info += OBF("Process ID: ") + std::to_string(getpid()) + OBF("\n");
    sys_info += OBF("Thread ID: ") + std::to_string((unsigned long)pthread_self()) + OBF("\n");

    sys_info += OBF("\nCRASH DETECTION STATUS:\n");
    sys_info += OBF("Crash Detection: ") + std::string(g_crash_detection_active ? OBF("ACTIVE") : OBF("INACTIVE")) + OBF("\n");
    sys_info += OBF("Thread Monitor: ") + std::string(THREAD_MONITOR_ENABLED ? OBF("ENABLED") : OBF("DISABLED")) + OBF("\n");
    sys_info += OBF("Crash Analysis: ") + std::string(CRASH_ANALYSIS_ENABLED ? OBF("ENABLED") : OBF("DISABLED")) + OBF("\n");
    sys_info += OBF("Debug Commands: ") + std::string(DEBUG_COMMANDS_ENABLED ? OBF("ENABLED") : OBF("DISABLED")) + OBF("\n");
    
    sys_info += OBF("\nFILE PATHS:\n");
    sys_info += OBF("Crash Reports: ") + std::string(CRASH_LOG_PATH) + OBF("\n");
    sys_info += OBF("Detailed Analysis: ") + std::string(DETAILED_ANALYSIS_PATH) + OBF("\n");
    sys_info += OBF("Debug Output: ") + std::string(DEBUG_OUTPUT_PATH) + OBF("\n");

    sys_info += OBF("\n==========================\n\n");
    
    WriteDebugOutput(sys_info);
}

inline void ClearAllLogs() {
    // Clear crash reports
    std::ofstream crash_file(CRASH_LOG_PATH, std::ios::trunc);
    crash_file.close();
    
    // Clear detailed analysis
    std::ofstream analysis_file(DETAILED_ANALYSIS_PATH, std::ios::trunc);
    analysis_file.close();
    
    // Clear debug output
    std::ofstream debug_file(DEBUG_OUTPUT_PATH, std::ios::trunc);
    debug_file.close();
    
    WriteDebugOutput(OBF("All log files cleared at ") + GetCurrentTimestamp() + OBF("\n"));
}

inline void ForceCrashTest() {
    WriteDebugOutput(OBF("WARNING: Force crash test initiated at ") + GetCurrentTimestamp() + OBF("\n"));
    
    // Simulate different types of crashes for testing
    static int crash_type = 0;
    crash_type = (crash_type + 1) % 3;
    
    switch (crash_type) {
        case 0:
            // Null pointer dereference
            *(int*)nullptr = 42;
            break;
        case 1:
            // Abort
            abort();
            break;
        case 2:
            // Division by zero
            volatile int zero = 0;
            volatile int result = 1 / zero;
            (void)result;
            break;
    }
}

#endif // ARCAMOD_DEBUG_COMMANDS_H
