#ifndef ARCAMOD_LIBANOGS_DATA_ANALYZER_H
#define ARCAMOD_LIBANOGS_DATA_ANALYZER_H

#include "LibanogsRuntimeMonitor.h"
#include <regex>
#include <set>
#include <algorithm>
#include <iomanip>

#define DATA_LOG_PATH "/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Data.txt"

/*
 * LIBANOGS DATA ANALYZER
 * ======================
 * 
 * Sistem untuk menganalisis data mentah dari libanogs.so:
 * - HEX patterns yang aktif
 * - String references
 * - Offset calculations
 * - Runtime constants
 * - Memory changes
 * - Anti-cheat patterns
 */

struct StringReference {
    uintptr_t address;
    uintptr_t offset_from_base;
    std::string content;
    size_t length;
    bool is_ascii;
    bool is_wide;
    time_t first_seen;
    int access_count;
};

struct HexPattern {
    uintptr_t address;
    uintptr_t offset_from_base;
    std::vector<uint8_t> bytes;
    std::string hex_string;
    size_t size;
    std::string pattern_type;
    time_t first_seen;
    int match_count;
};

struct OffsetActivity {
    uintptr_t offset;
    uintptr_t absolute_address;
    std::string activity_type;
    std::vector<uint8_t> data_snapshot;
    time_t timestamp;
    std::string description;
};

struct RuntimeConstant {
    uintptr_t address;
    uintptr_t offset_from_base;
    uint64_t value;
    std::string value_type;
    std::string interpretation;
    bool is_pointer;
    bool is_string_ptr;
    time_t discovered;
};

class LibanogsDataAnalyzer {
private:
    std::vector<StringReference> string_refs;
    std::vector<HexPattern> hex_patterns;
    std::vector<OffsetActivity> offset_activities;
    std::vector<RuntimeConstant> runtime_constants;
    std::map<uintptr_t, std::vector<uint8_t>> memory_snapshots;
    pthread_mutex_t analyzer_mutex;
    bool is_active;
    
public:
    LibanogsDataAnalyzer();
    ~LibanogsDataAnalyzer();
    
    // Initialization
    bool Initialize();
    void Shutdown();
    void StartAnalysis();
    void StopAnalysis();
    
    // String Analysis
    void ScanForStrings();
    void AnalyzeStringReferences();
    void LogStringFound(uintptr_t address, const std::string& content);
    bool IsValidString(const char* ptr, size_t max_len = 1024);
    std::string ExtractString(uintptr_t address, bool is_wide = false);
    
    // HEX Pattern Analysis
    void ScanForHexPatterns();
    void AnalyzeKnownPatterns();
    void LogHexPatternFound(uintptr_t address, const uint8_t* data, size_t size, const std::string& type);
    bool MatchesAntiCheatPattern(const uint8_t* data, size_t size);
    std::string BytesToHexString(const uint8_t* data, size_t size);
    
    // Offset Analysis
    void AnalyzeOffsets();
    void LogOffsetActivity(uintptr_t offset, const std::string& activity, const uint8_t* data, size_t size);
    void ScanActiveOffsets();
    uintptr_t CalculateOffset(uintptr_t absolute_address);
    
    // Runtime Constants Analysis
    void ScanForConstants();
    void AnalyzeRuntimeValues();
    void LogConstantFound(uintptr_t address, uint64_t value, const std::string& type);
    std::string InterpretValue(uint64_t value);
    bool IsLikelyPointer(uint64_t value);
    
    // Memory Change Detection
    void TakeMemorySnapshot();
    void DetectMemoryChanges();
    void LogMemoryChange(uintptr_t address, const uint8_t* old_data, const uint8_t* new_data, size_t size);
    
    // Anti-cheat Pattern Detection
    void ScanForAntiCheatPatterns();
    void AnalyzeSecurityChecks();
    void DetectObfuscationPatterns();
    
    // Reporting
    void GenerateDataReport();
    void ExportStringsToFile();
    void ExportHexPatternsToFile();
    void ExportOffsetsToFile();
    void ExportConstantsToFile();
    
    // Getters
    const std::vector<StringReference>& GetStringReferences() const { return string_refs; }
    const std::vector<HexPattern>& GetHexPatterns() const { return hex_patterns; }
    const std::vector<OffsetActivity>& GetOffsetActivities() const { return offset_activities; }
    const std::vector<RuntimeConstant>& GetRuntimeConstants() const { return runtime_constants; }
};

// Global analyzer instance
extern LibanogsDataAnalyzer* g_data_analyzer;

// Known anti-cheat patterns (common signatures)
static const uint8_t ANTICHEAT_PATTERNS[][16] = {
    {0x48, 0x8B, 0x05, 0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC0, 0x74, 0x00, 0x48, 0x8B, 0x00, 0x00}, // Memory check
    {0xE8, 0x00, 0x00, 0x00, 0x00, 0x85, 0xC0, 0x0F, 0x84, 0x00, 0x00, 0x00, 0x00, 0xEB, 0x00, 0x00}, // Function call check
    {0x64, 0x48, 0x8B, 0x04, 0x25, 0x30, 0x00, 0x00, 0x00, 0x48, 0x8B, 0x40, 0x60, 0x48, 0x8B, 0x40}, // PEB access
    {0x0F, 0x31, 0x48, 0xC1, 0xE2, 0x20, 0x48, 0x09, 0xC2, 0x48, 0x89, 0xD0, 0xC3, 0x00, 0x00, 0x00}, // RDTSC timing
};

static const char* ANTICHEAT_STRINGS[] = {
    "debug",
    "hook",
    "inject",
    "cheat",
    "hack",
    "mod",
    "bypass",
    "patch",
    "memory",
    "process",
    "thread",
    "module",
    "library",
    "symbol",
    "breakpoint",
    "trace",
    "monitor",
    "detect",
    "protect",
    "security",
    "anti",
    "check",
    "verify",
    "validate",
    "integrity",
    "signature",
    "hash",
    "crc",
    "checksum"
};

// Utility functions
void WriteDataLog(const char* message);
std::string FormatHexDump(const uint8_t* data, size_t size, uintptr_t base_address = 0);
std::string FormatOffset(uintptr_t offset);
bool IsReadableMemory(uintptr_t address);
bool IsExecutableMemory(uintptr_t address);
size_t GetStringLength(const char* str, size_t max_len = 1024);
bool ContainsAntiCheatKeywords(const std::string& text);

// Inline implementations
inline void WriteDataLog(const char* message) {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    std::ofstream log_file(DATA_LOG_PATH, std::ios::app);
    if (log_file.is_open()) {
        log_file << "[" << timestamp << "] [DATA] " << message << std::endl;
        log_file.close();
    }
    
    __android_log_print(ANDROID_LOG_DEBUG, "ARCAMOD_DATA", "[%s] %s", timestamp, message);
}

inline std::string FormatHexDump(const uint8_t* data, size_t size, uintptr_t base_address) {
    std::stringstream ss;
    
    for (size_t i = 0; i < size; i += 16) {
        // Address
        ss << std::hex << std::setfill('0') << std::setw(8) << (base_address + i) << ": ";
        
        // Hex bytes
        for (size_t j = 0; j < 16 && (i + j) < size; j++) {
            ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(data[i + j]) << " ";
        }
        
        // Padding
        for (size_t j = size - i; j < 16; j++) {
            ss << "   ";
        }
        
        // ASCII representation
        ss << " |";
        for (size_t j = 0; j < 16 && (i + j) < size; j++) {
            char c = data[i + j];
            ss << (isprint(c) ? c : '.');
        }
        ss << "|\n";
    }
    
    return ss.str();
}

inline std::string FormatOffset(uintptr_t offset) {
    std::stringstream ss;
    ss << "0x" << std::hex << std::uppercase << offset;
    return ss.str();
}

inline bool IsReadableMemory(uintptr_t address) {
    // Simple check - try to read one byte
    try {
        volatile uint8_t test = *reinterpret_cast<uint8_t*>(address);
        (void)test; // Suppress unused variable warning
        return true;
    } catch (...) {
        return false;
    }
}

inline bool ContainsAntiCheatKeywords(const std::string& text) {
    std::string lower_text = text;
    std::transform(lower_text.begin(), lower_text.end(), lower_text.begin(), ::tolower);
    
    for (const char* keyword : ANTICHEAT_STRINGS) {
        if (lower_text.find(keyword) != std::string::npos) {
            return true;
        }
    }
    return false;
}

// Macros for easy data logging
#define DATA_LOG(message) WriteDataLog(message)

#define LOG_STRING_FOUND(addr, content) \
    do { \
        std::stringstream ss; \
        ss << "STRING_FOUND at " << FormatOffset(CalculateOffset(addr)) \
           << " (0x" << std::hex << addr << "): \"" << content << "\""; \
        DATA_LOG(ss.str().c_str()); \
    } while(0)

#define LOG_HEX_PATTERN(addr, data, size, type) \
    do { \
        std::stringstream ss; \
        ss << "HEX_PATTERN [" << type << "] at " << FormatOffset(CalculateOffset(addr)) \
           << " (0x" << std::hex << addr << "):\n" << FormatHexDump(data, size, addr); \
        DATA_LOG(ss.str().c_str()); \
    } while(0)

#define LOG_OFFSET_ACTIVITY(offset, activity, data, size) \
    do { \
        std::stringstream ss; \
        ss << "OFFSET_ACTIVITY [" << activity << "] at " << FormatOffset(offset) \
           << ":\n" << FormatHexDump(data, size, g_runtime_monitor.base_address + offset); \
        DATA_LOG(ss.str().c_str()); \
    } while(0)

#define LOG_CONSTANT_FOUND(addr, value, type) \
    do { \
        std::stringstream ss; \
        ss << "CONSTANT_FOUND [" << type << "] at " << FormatOffset(CalculateOffset(addr)) \
           << " (0x" << std::hex << addr << "): 0x" << value; \
        DATA_LOG(ss.str().c_str()); \
    } while(0)

// Initialization functions
void InitializeDataAnalyzer();
void StartDataAnalysis();
void StopDataAnalysis();

#endif // ARCAMOD_LIBANOGS_DATA_ANALYZER_H
