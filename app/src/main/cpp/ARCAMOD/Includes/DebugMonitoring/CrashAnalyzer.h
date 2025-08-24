#ifndef ARCAMOD_CRASH_ANALYZER_H
#define ARCAMOD_CRASH_ANALYZER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <android/log.h>
// #include "CrashDetector.h" // REMOVED: Crash tracking system dihapus
#include "ThreadMonitor.h"

// Crash analysis configuration - Only enabled in Debug builds
#ifdef DEBUG
#define CRASH_ANALYSIS_ENABLED 1
#else
#define CRASH_ANALYSIS_ENABLED 0  // Disabled in Release builds
#endif
#define DETAILED_ANALYSIS_PATH OBF("/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Detailed_Analysis.txt")

// Crash pattern types
enum CrashPattern {
    PATTERN_ESP_NULL_POINTER = 0,
    PATTERN_ESP_INVALID_TRANSFORM = 1,
    PATTERN_ESP_MEMORY_CORRUPTION = 2,
    PATTERN_EGL_CONTEXT_LOST = 3,
    PATTERN_EGL_TEXTURE_ERROR = 4,
    PATTERN_EGL_RENDER_ERROR = 5,
    PATTERN_THREAD_DEADLOCK = 6,
    PATTERN_MEMORY_LEAK = 7,
    PATTERN_UNKNOWN = 99
};

// Crash statistics
struct CrashStats {
    int total_crashes;
    int esp_crashes;
    int egl_crashes;
    int sigsegv_crashes;
    int sigabrt_crashes;
    int thread_crashes[4]; // Main, EGL, ESP, Render
    std::vector<std::string> frequent_functions;
    std::vector<std::string> frequent_files;
};

// Function declarations
void InitializeCrashAnalyzer();
void AnalyzeCrashPattern(const CrashContext& context);
void GenerateDetailedReport();
CrashPattern IdentifyCrashPattern(const CrashContext& context);
std::string GetCrashPatternName(CrashPattern pattern);
std::string GetCrashSolution(CrashPattern pattern);
void UpdateCrashStatistics(const CrashContext& context);
CrashStats GetCrashStatistics();

// ESP-specific crash analysis
void AnalyzeESPCrash(const CrashContext& context);
std::string GetESPCrashSolution(const CrashContext& context);

// EGL-specific crash analysis
void AnalyzeEGLCrash(const CrashContext& context);
std::string GetEGLCrashSolution(const CrashContext& context);

// Implementation
inline void InitializeCrashAnalyzer() {
    if (!CRASH_ANALYSIS_ENABLED) return;
    
    __android_log_print(ANDROID_LOG_INFO, OBF("ARCAMOD"), OBF("Crash Analyzer initialized"));
}

inline CrashPattern IdentifyCrashPattern(const CrashContext& context) {
    // ESP-related crash patterns
    if (context.is_esp_related) {
        if (context.signal_number == SIGSEGV) {
            if (context.function_name) {
                std::string func_name = context.function_name;
                if (func_name.find(OBF("Transform")) != std::string::npos ||
                    func_name.find(OBF("GetHeadTransform")) != std::string::npos ||
                    func_name.find(OBF("GetRootTransform")) != std::string::npos) {
                    return PATTERN_ESP_INVALID_TRANSFORM;
                }
                if (func_name.find(OBF("IsBot")) != std::string::npos ||
                    func_name.find(OBF("IsAlive")) != std::string::npos) {
                    return PATTERN_ESP_NULL_POINTER;
                }
            }
            return PATTERN_ESP_MEMORY_CORRUPTION;
        }
    }
    
    // EGL-related crash patterns
    if (context.is_egl_related) {
        if (context.signal_number == SIGABRT) {
            return PATTERN_EGL_CONTEXT_LOST;
        }
        if (context.function_name) {
            std::string func_name = context.function_name;
            if (func_name.find(OBF("Texture")) != std::string::npos ||
                func_name.find(OBF("glTexture")) != std::string::npos) {
                return PATTERN_EGL_TEXTURE_ERROR;
            }
            if (func_name.find(OBF("Render")) != std::string::npos ||
                func_name.find(OBF("Draw")) != std::string::npos) {
                return PATTERN_EGL_RENDER_ERROR;
            }
        }
    }
    
    return PATTERN_UNKNOWN;
}

inline std::string GetCrashPatternName(CrashPattern pattern) {
    switch (pattern) {
        case PATTERN_ESP_NULL_POINTER: return OBF("ESP Null Pointer Access");
        case PATTERN_ESP_INVALID_TRANSFORM: return OBF("ESP Invalid Transform Access");
        case PATTERN_ESP_MEMORY_CORRUPTION: return OBF("ESP Memory Corruption");
        case PATTERN_EGL_CONTEXT_LOST: return OBF("EGL Context Lost");
        case PATTERN_EGL_TEXTURE_ERROR: return OBF("EGL Texture Error");
        case PATTERN_EGL_RENDER_ERROR: return OBF("EGL Render Error");
        case PATTERN_THREAD_DEADLOCK: return OBF("Thread Deadlock");
        case PATTERN_MEMORY_LEAK: return OBF("Memory Leak");
        default: return OBF("Unknown Pattern");
    }
}

inline std::string GetCrashSolution(CrashPattern pattern) {
    switch (pattern) {
        case PATTERN_ESP_NULL_POINTER:
            return OBF("Add null pointer validation before accessing entity data. "
                   "Check FORCE_CHECK() macro usage and entity validity.");

        case PATTERN_ESP_INVALID_TRANSFORM:
            return OBF("Validate transform pointers before calling Transform functions. "
                   "Ensure GetHeadTransform/GetRootTransform return valid pointers.");

        case PATTERN_ESP_MEMORY_CORRUPTION:
            return OBF("Check memory bounds and alignment. Verify entity offsets are correct. "
                   "Consider adding memory protection around critical ESP operations.");

        case PATTERN_EGL_CONTEXT_LOST:
            return OBF("Implement EGL context recovery. Check for context loss before rendering. "
                   "Add proper cleanup and recreation of OpenGL resources.");

        case PATTERN_EGL_TEXTURE_ERROR:
            return OBF("Validate texture operations and memory allocation. "
                   "Check texture format compatibility and size limits.");

        case PATTERN_EGL_RENDER_ERROR:
            return OBF("Verify render state and OpenGL context validity. "
                   "Add error checking after OpenGL calls.");

        default:
            return OBF("General debugging recommended. Check logs and add more validation.");
    }
}

inline void AnalyzeESPCrash(const CrashContext& context) {
    std::ofstream analysis_file(DETAILED_ANALYSIS_PATH, std::ios::app);
    if (!analysis_file.is_open()) return;
    
    analysis_file << OBF("\n=== ESP CRASH ANALYSIS ===\n");
    analysis_file << OBF("Function: ") << (context.function_name ? context.function_name : OBF("Unknown")) << OBF("\n");
    analysis_file << OBF("File: ") << (context.file_name ? context.file_name : OBF("Unknown")) << OBF("\n");
    analysis_file << OBF("Line: ") << context.line_number << OBF("\n");

    CrashPattern pattern = IdentifyCrashPattern(context);
    analysis_file << OBF("Pattern: ") << GetCrashPatternName(pattern) << OBF("\n");
    analysis_file << OBF("Solution: ") << GetCrashSolution(pattern) << OBF("\n");

    // ESP-specific recommendations
    analysis_file << OBF("\nESP DEBUGGING STEPS:\n");
    analysis_file << OBF("1. Check entity pointer validation in Draws.h\n");
    analysis_file << OBF("2. Verify SIGSEGV handler setup is correct\n");
    analysis_file << OBF("3. Add logging to identify problematic entities\n");
    analysis_file << OBF("4. Check Unity engine memory layout changes\n");
    analysis_file << OBF("5. Verify offset values in Offsets namespace\n");
    
    if (context.signal_number == SIGSEGV) {
        analysis_file << OBF("\nMemory fault in ESP suggests:\n");
        analysis_file << OBF("- Invalid entity pointer access\n");
        analysis_file << OBF("- Corrupted transform data\n");
        analysis_file << OBF("- Memory protection violation\n");
        analysis_file << OBF("- Incorrect offset calculations\n");
    }

    analysis_file << OBF("\n========================\n");
    analysis_file.close();
}

inline void AnalyzeEGLCrash(const CrashContext& context) {
    std::ofstream analysis_file(DETAILED_ANALYSIS_PATH, std::ios::app);
    if (!analysis_file.is_open()) return;
    
    analysis_file << OBF("\n=== EGL CRASH ANALYSIS ===\n");
    analysis_file << OBF("Function: ") << (context.function_name ? context.function_name : OBF("Unknown")) << OBF("\n");
    analysis_file << OBF("File: ") << (context.file_name ? context.file_name : OBF("Unknown")) << OBF("\n");
    analysis_file << OBF("Line: ") << context.line_number << OBF("\n");

    CrashPattern pattern = IdentifyCrashPattern(context);
    analysis_file << OBF("Pattern: ") << GetCrashPatternName(pattern) << OBF("\n");
    analysis_file << OBF("Solution: ") << GetCrashSolution(pattern) << OBF("\n");

    // EGL-specific recommendations
    analysis_file << OBF("\nEGL DEBUGGING STEPS:\n");
    analysis_file << OBF("1. Check OpenGL context validity\n");
    analysis_file << OBF("2. Verify texture memory management\n");
    analysis_file << OBF("3. Add glGetError() calls after operations\n");
    analysis_file << OBF("4. Check render surface state\n");
    analysis_file << OBF("5. Verify thread context binding\n");
    
    if (context.signal_number == SIGABRT) {
        analysis_file << OBF("\nSystem abort in EGL suggests:\n");
        analysis_file << OBF("- OpenGL context corruption\n");
        analysis_file << OBF("- Invalid OpenGL state\n");
        analysis_file << OBF("- Resource cleanup failure\n");
        analysis_file << OBF("- Thread synchronization issue\n");
    }

    analysis_file << OBF("\n========================\n");
    analysis_file.close();
}

inline void AnalyzeCrashPattern(const CrashContext& context) {
    if (!CRASH_ANALYSIS_ENABLED) return;
    
    if (context.is_esp_related) {
        AnalyzeESPCrash(context);
    }
    
    if (context.is_egl_related) {
        AnalyzeEGLCrash(context);
    }
    
    // Update statistics
    UpdateCrashStatistics(context);
    
    __android_log_print(ANDROID_LOG_INFO, OBF("ARCAMOD"),
        OBF("Crash pattern analyzed: %s"),
        GetCrashPatternName(IdentifyCrashPattern(context)).c_str());
}

// Global crash statistics
static CrashStats g_crash_stats = {0};

inline void UpdateCrashStatistics(const CrashContext& context) {
    g_crash_stats.total_crashes++;
    
    if (context.is_esp_related) g_crash_stats.esp_crashes++;
    if (context.is_egl_related) g_crash_stats.egl_crashes++;
    if (context.signal_number == SIGSEGV) g_crash_stats.sigsegv_crashes++;
    if (context.signal_number == SIGABRT) g_crash_stats.sigabrt_crashes++;
    
    // Update thread-specific crashes
    if (context.thread_type < 4) {
        g_crash_stats.thread_crashes[context.thread_type]++;
    }
}

inline CrashStats GetCrashStatistics() {
    return g_crash_stats;
}

#endif // ARCAMOD_CRASH_ANALYZER_H
