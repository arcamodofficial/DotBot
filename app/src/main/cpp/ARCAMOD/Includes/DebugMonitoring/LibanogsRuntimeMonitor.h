#ifndef ARCAMOD_LIBANOGS_RUNTIME_MONITOR_H
#define ARCAMOD_LIBANOGS_RUNTIME_MONITOR_H

#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string>
#include <fstream>
#include <sstream>
#include <dlfcn.h>
#include <android/log.h>
#include <sys/mman.h>
#include <sys/ptrace.h>
#include <signal.h>
#include <ucontext.h>
#include <link.h>
#include <elf.h>
#include <vector>
#include <map>

#define RUNTIME_LOG_PATH "/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Runtime.txt"
#define LIBANOGS_LIB "libanogs.so"

// Runtime monitoring configuration
#ifdef DEBUG
#define RUNTIME_MONITOR_ENABLED 1
#else
#define RUNTIME_MONITOR_ENABLED 0
#endif

struct LibanogsMemoryRegion {
    uintptr_t start_addr;
    uintptr_t end_addr;
    size_t size;
    int permissions;
    std::string name;
};

struct FunctionCallInfo {
    uintptr_t address;
    std::string name;
    time_t timestamp;
    uintptr_t caller_address;
    int call_count;
};

struct AddressActivity {
    uintptr_t address;
    std::string activity_type;
    time_t timestamp;
    uintptr_t caller_address;
    size_t data_size;
    std::string data_preview;
    int activity_count;
};

struct RealTimeActivityTracker {
    std::map<uintptr_t, AddressActivity> active_addresses;
    std::vector<AddressActivity> recent_activities;
    time_t last_report_time;
    int total_activities;
    pthread_mutex_t activity_mutex;
};

struct RuntimeMonitorInfo {
    bool is_active;
    bool library_loaded;
    uintptr_t base_address;
    size_t library_size;
    std::vector<LibanogsMemoryRegion> memory_regions;
    std::map<uintptr_t, FunctionCallInfo> function_calls;
    time_t start_time;
    time_t last_activity;
    int total_function_calls;
    int memory_accesses;
    int api_calls;
    pthread_mutex_t monitor_mutex;
    RealTimeActivityTracker activity_tracker;
};

// Global monitor instance
extern RuntimeMonitorInfo g_runtime_monitor;

// Function declarations
void InitializeRuntimeMonitor();
void StartRuntimeMonitor();
void StopRuntimeMonitor();
void* runtime_monitor_thread(void* arg);

// Memory monitoring
void ScanLibanogsMemoryRegions();
void MonitorMemoryAccess(uintptr_t address, size_t size, const char* operation);
void InstallMemoryAccessHooks();

// Function call monitoring
void InstallFunctionCallHooks();
void LogFunctionCall(uintptr_t function_addr, uintptr_t caller_addr);
void ScanLibanogsFunctions();

// API call monitoring
void InstallAPICallHooks();
void MonitorSystemCalls();

// Dynamic analysis
void AnalyzeRuntimeBehavior();
void DetectSuspiciousActivity();
void MonitorLibraryInteractions();

// Real-time address activity monitoring
void InitializeActivityTracker();
void TrackAddressActivity(uintptr_t address, const char* activity_type, uintptr_t caller, const void* data, size_t size);
void LogRealTimeActivity(const AddressActivity& activity);
void GenerateRealTimeReport();
void CleanupOldActivities();
std::string FormatDataPreview(const void* data, size_t size);
void MonitorAddressAccess(uintptr_t address, const char* operation, const void* data, size_t size);
void GenerateDemoActivities();
void GenerateAddressFrequencyReport();
void ReportHotAddresses(const std::map<uintptr_t, int>& address_frequency);
void ReportHotFunctions(const std::map<uintptr_t, int>& function_frequency);

// Logging functions
void WriteRuntimeLog(const char* message);
void LogMemoryAccess(uintptr_t address, size_t size, const char* operation);
void LogFunctionActivity(const char* function_name, uintptr_t address);
void LogAPICall(const char* api_name, const char* parameters);
void LogSuspiciousActivity(const char* activity_type, const char* details);

// Report generation
void GenerateRuntimeReport();
void GenerateMemoryMap();
void GenerateFunctionCallReport();
void GenerateAPICallReport();

// Utility functions
bool IsAddressInLibanogs(uintptr_t address);
std::string GetFunctionNameFromAddress(uintptr_t address);
uintptr_t GetLibanogsBaseAddress();
void DumpLibanogsELFHeader();
void AnalyzeLibanogsImports();
void AnalyzeLibanogsExports();

// HEX/String/Offset Analysis Functions
void ScanLibanogsForStrings();
void ScanLibanogsForHexPatterns();
void DumpActiveMemoryRegions();
void AnalyzeRuntimeOffsets();
void CaptureRuntimeHexData();
void LogStringReferences(uintptr_t address, const char* string_data);
void LogHexPattern(uintptr_t address, const uint8_t* hex_data, size_t size);
void LogOffsetActivity(uintptr_t base_offset, uintptr_t actual_address, const char* activity_type);
void ScanForAntiCheatPatterns();
void DumpFunctionBytecode(uintptr_t function_address, size_t size);
void AnalyzeRuntimeConstants();
void CaptureMemoryChanges();
void LogMemoryDiff(uintptr_t address, const uint8_t* old_data, const uint8_t* new_data, size_t size);

// Signal handlers for memory access detection
void sigsegv_handler(int sig, siginfo_t* info, void* context);
void setup_signal_handlers();

// Implementation
inline void WriteRuntimeLog(const char* message) {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    pthread_mutex_lock(&g_runtime_monitor.monitor_mutex);
    
    time_t now = time(nullptr);
    struct tm* timeinfo = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);
    
    std::ofstream log_file(RUNTIME_LOG_PATH, std::ios::app);
    if (log_file.is_open()) {
        log_file << "[" << timestamp << "] [RUNTIME] " << message << std::endl;
        log_file.close();
    }
    
    __android_log_print(ANDROID_LOG_DEBUG, "ARCAMOD_RUNTIME", "[%s] %s", timestamp, message);
    
    g_runtime_monitor.last_activity = now;
    pthread_mutex_unlock(&g_runtime_monitor.monitor_mutex);
}

inline void LogMemoryAccess(uintptr_t address, size_t size, const char* operation) {
    if (!RUNTIME_MONITOR_ENABLED) return;

    if (IsAddressInLibanogs(address)) {
        g_runtime_monitor.memory_accesses++;

        // Real-time activity logging with address frequency tracking
        static std::map<uintptr_t, int> address_frequency;
        address_frequency[address]++;

        std::stringstream ss;
        ss << "REALTIME_ACTIVITY [" << operation << "] Addr: 0x" << std::hex << address
           << " (+0x" << (address - g_runtime_monitor.base_address) << ") "
           << "Size: " << std::dec << size << " Count: " << address_frequency[address];
        WriteRuntimeLog(ss.str().c_str());

        // Report hot addresses every 20 accesses
        static int total_accesses = 0;
        total_accesses++;
        if (total_accesses % 20 == 0) {
            ReportHotAddresses(address_frequency);
        }
    }
}

inline void LogFunctionActivity(const char* function_name, uintptr_t address) {
    if (!RUNTIME_MONITOR_ENABLED) return;

    if (IsAddressInLibanogs(address)) {
        g_runtime_monitor.total_function_calls++;

        // Real-time function call logging with frequency tracking
        static std::map<uintptr_t, int> function_frequency;
        function_frequency[address]++;

        std::stringstream ss;
        ss << "REALTIME_ACTIVITY [FUNCTION_CALL:" << function_name << "] Addr: 0x" << std::hex << address
           << " (+0x" << (address - g_runtime_monitor.base_address) << ") "
           << "Count: " << std::dec << function_frequency[address];
        WriteRuntimeLog(ss.str().c_str());

        // Report hot function addresses every 10 calls
        static int total_function_calls = 0;
        total_function_calls++;
        if (total_function_calls % 10 == 0) {
            ReportHotFunctions(function_frequency);
        }
    }
}

inline void LogAPICall(const char* api_name, const char* parameters) {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    g_runtime_monitor.api_calls++;
    
    std::stringstream ss;
    ss << "API_CALL " << api_name;
    if (parameters && strlen(parameters) > 0) {
        ss << " Parameters: " << parameters;
    }
    WriteRuntimeLog(ss.str().c_str());
}

inline void LogSuspiciousActivity(const char* activity_type, const char* details) {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    std::stringstream ss;
    ss << "SUSPICIOUS_ACTIVITY [" << activity_type << "] " << details;
    WriteRuntimeLog(ss.str().c_str());
}

inline bool IsAddressInLibanogs(uintptr_t address) {
    if (!g_runtime_monitor.library_loaded) return false;
    
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (address >= region.start_addr && address < region.end_addr) {
            return true;
        }
    }
    return false;
}

inline uintptr_t GetLibanogsBaseAddress() {
    void* handle = dlopen(LIBANOGS_LIB, RTLD_NOLOAD);
    if (handle) {
        uintptr_t base = reinterpret_cast<uintptr_t>(handle);
        dlclose(handle);
        return base;
    }
    return 0;
}

inline void InitializeRuntimeMonitor() {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    // Initialize monitor structure
    g_runtime_monitor.is_active = false;
    g_runtime_monitor.library_loaded = false;
    g_runtime_monitor.base_address = 0;
    g_runtime_monitor.library_size = 0;
    g_runtime_monitor.start_time = time(nullptr);
    g_runtime_monitor.last_activity = g_runtime_monitor.start_time;
    g_runtime_monitor.total_function_calls = 0;
    g_runtime_monitor.memory_accesses = 0;
    g_runtime_monitor.api_calls = 0;
    pthread_mutex_init(&g_runtime_monitor.monitor_mutex, nullptr);
    
    // Clear previous log
    std::ofstream log_file(RUNTIME_LOG_PATH, std::ios::trunc);
    if (log_file.is_open()) {
        log_file.close();
    }
    
    WriteRuntimeLog("LibAnogs Runtime Monitor initialized");
}

inline void ScanLibanogsMemoryRegions() {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    g_runtime_monitor.memory_regions.clear();
    
    std::ifstream maps("/proc/self/maps");
    std::string line;
    
    while (std::getline(maps, line)) {
        if (line.find(LIBANOGS_LIB) != std::string::npos) {
            // Parse memory region
            size_t dash_pos = line.find('-');
            size_t space_pos = line.find(' ');
            
            if (dash_pos != std::string::npos && space_pos != std::string::npos) {
                std::string start_addr = line.substr(0, dash_pos);
                std::string end_addr = line.substr(dash_pos + 1, space_pos - dash_pos - 1);
                std::string perms = line.substr(space_pos + 1, 4);
                
                LibanogsMemoryRegion region;
                region.start_addr = std::stoull(start_addr, nullptr, 16);
                region.end_addr = std::stoull(end_addr, nullptr, 16);
                region.size = region.end_addr - region.start_addr;
                region.permissions = 0;
                region.name = line;
                
                // Parse permissions
                if (perms[0] == 'r') region.permissions |= PROT_READ;
                if (perms[1] == 'w') region.permissions |= PROT_WRITE;
                if (perms[2] == 'x') region.permissions |= PROT_EXEC;
                
                g_runtime_monitor.memory_regions.push_back(region);
                
                std::stringstream ss;
                ss << "MEMORY_REGION found: 0x" << std::hex << region.start_addr 
                   << "-0x" << region.end_addr << " (" << std::dec << region.size 
                   << " bytes) " << perms;
                WriteRuntimeLog(ss.str().c_str());
            }
        }
    }
    
    if (!g_runtime_monitor.memory_regions.empty()) {
        g_runtime_monitor.library_loaded = true;
        g_runtime_monitor.base_address = g_runtime_monitor.memory_regions[0].start_addr;
        
        size_t total_size = 0;
        for (const auto& region : g_runtime_monitor.memory_regions) {
            total_size += region.size;
        }
        g_runtime_monitor.library_size = total_size;
        
        std::stringstream ss;
        ss << "LibAnogs loaded: Base=0x" << std::hex << g_runtime_monitor.base_address 
           << " Size=" << std::dec << total_size << " bytes, Regions=" 
           << g_runtime_monitor.memory_regions.size();
        WriteRuntimeLog(ss.str().c_str());
    }
}

// Macros for easy runtime monitoring
#define RUNTIME_LOG(message) WriteRuntimeLog(message)
#define RUNTIME_LOG_MEMORY(addr, size, op) LogMemoryAccess(addr, size, op)
#define RUNTIME_LOG_FUNCTION(name, addr) LogFunctionActivity(name, addr)
#define RUNTIME_LOG_API(name, params) LogAPICall(name, params)
#define RUNTIME_LOG_SUSPICIOUS(type, details) LogSuspiciousActivity(type, details)
#define RUNTIME_LOG_ADDRESS_ACTIVITY(addr, type, caller, data, size) TrackAddressActivity(addr, type, caller, data, size)

#endif // ARCAMOD_LIBANOGS_RUNTIME_MONITOR_H
