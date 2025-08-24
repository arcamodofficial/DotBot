#include "LibanogsDataAnalyzer.h"
#include <algorithm>
#include <cctype>
#include <cstring>
#include <iomanip>

// Global analyzer instance
LibanogsDataAnalyzer* g_data_analyzer = nullptr;

LibanogsDataAnalyzer::LibanogsDataAnalyzer() : is_active(false) {
    pthread_mutex_init(&analyzer_mutex, nullptr);
}

LibanogsDataAnalyzer::~LibanogsDataAnalyzer() {
    Shutdown();
    pthread_mutex_destroy(&analyzer_mutex);
}

bool LibanogsDataAnalyzer::Initialize() {
    if (!RUNTIME_MONITOR_ENABLED) return false;
    
    pthread_mutex_lock(&analyzer_mutex);
    
    // Clear previous data
    string_refs.clear();
    hex_patterns.clear();
    offset_activities.clear();
    runtime_constants.clear();
    memory_snapshots.clear();
    
    // Clear previous log
    std::ofstream log_file(DATA_LOG_PATH, std::ios::trunc);
    if (log_file.is_open()) {
        log_file.close();
    }
    
    DATA_LOG("LibAnogs Data Analyzer initialized");
    
    pthread_mutex_unlock(&analyzer_mutex);
    return true;
}

void LibanogsDataAnalyzer::StartAnalysis() {
    if (!RUNTIME_MONITOR_ENABLED) return;

    is_active = true;
    DATA_LOG("Data analysis started");

    // Initial scans
    ScanForStrings();
    ScanForHexPatterns();
    ScanForConstants();
    TakeMemorySnapshot();
    ScanForAntiCheatPatterns();
}

void LibanogsDataAnalyzer::Shutdown() {
    if (!RUNTIME_MONITOR_ENABLED) return;

    is_active = false;
    GenerateDataReport();
    DATA_LOG("Data analyzer shutdown");
}

void LibanogsDataAnalyzer::StopAnalysis() {
    if (!RUNTIME_MONITOR_ENABLED) return;

    is_active = false;
    DATA_LOG("Data analysis stopped");
}

void LibanogsDataAnalyzer::ScanForStrings() {
    if (!g_runtime_monitor.library_loaded) return;
    
    DATA_LOG("=== SCANNING FOR STRINGS ===");
    
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (!(region.permissions & PROT_READ)) continue;
        
        uintptr_t current = region.start_addr;
        uintptr_t end = region.end_addr;
        
        while (current < end - 4) {
            if (IsReadableMemory(current)) {
                const char* str_ptr = reinterpret_cast<const char*>(current);
                
                if (IsValidString(str_ptr)) {
                    std::string content = ExtractString(current);
                    if (content.length() >= 4) { // Minimum string length
                        LogStringFound(current, content);
                        
                        // Check for anti-cheat keywords
                        if (ContainsAntiCheatKeywords(content)) {
                            std::stringstream ss;
                            ss << "ANTICHEAT_STRING detected: \"" << content << "\" at " << FormatOffset(CalculateOffset(current));
                            DATA_LOG(ss.str().c_str());
                        }
                    }
                }
            }
            current += 4; // Scan every 4 bytes
        }
    }
    
    DATA_LOG("=== STRING SCAN COMPLETE ===");
}

void LibanogsDataAnalyzer::ScanForHexPatterns() {
    if (!g_runtime_monitor.library_loaded) return;
    
    DATA_LOG("=== SCANNING FOR HEX PATTERNS ===");
    
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (!(region.permissions & PROT_READ)) continue;
        
        uintptr_t current = region.start_addr;
        uintptr_t end = region.end_addr;
        
        while (current < end - 16) {
            if (IsReadableMemory(current)) {
                const uint8_t* data = reinterpret_cast<const uint8_t*>(current);
                
                // Check for known anti-cheat patterns
                for (size_t i = 0; i < sizeof(ANTICHEAT_PATTERNS) / sizeof(ANTICHEAT_PATTERNS[0]); i++) {
                    bool matches = true;
                    for (size_t j = 0; j < 16; j++) {
                        if (ANTICHEAT_PATTERNS[i][j] != 0x00 && ANTICHEAT_PATTERNS[i][j] != data[j]) {
                            matches = false;
                            break;
                        }
                    }
                    
                    if (matches) {
                        std::stringstream ss;
                        ss << "ANTICHEAT_PATTERN_" << i << " detected at " << FormatOffset(CalculateOffset(current));
                        DATA_LOG(ss.str().c_str());
                        LogHexPatternFound(current, data, 16, "ANTICHEAT");
                    }
                }
                
                // Look for interesting patterns
                if (data[0] == 0x48 && data[1] == 0x8B) { // MOV instruction
                    LogHexPatternFound(current, data, 8, "MOV_INSTRUCTION");
                }
                
                if (data[0] == 0xE8) { // CALL instruction
                    LogHexPatternFound(current, data, 5, "CALL_INSTRUCTION");
                }
                
                if (data[0] == 0x0F && data[1] == 0x31) { // RDTSC instruction
                    LogHexPatternFound(current, data, 2, "RDTSC_TIMING");
                    DATA_LOG("TIMING_CHECK detected - possible anti-debug");
                }
            }
            current += 1;
        }
    }
    
    DATA_LOG("=== HEX PATTERN SCAN COMPLETE ===");
}

void LibanogsDataAnalyzer::ScanForConstants() {
    if (!g_runtime_monitor.library_loaded) return;
    
    DATA_LOG("=== SCANNING FOR RUNTIME CONSTANTS ===");
    
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (!(region.permissions & PROT_READ)) continue;
        
        uintptr_t current = region.start_addr;
        uintptr_t end = region.end_addr;
        
        while (current < end - 8) {
            if (IsReadableMemory(current)) {
                uint64_t value = *reinterpret_cast<const uint64_t*>(current);
                
                // Look for interesting constants
                if (value > 0x1000 && value < 0x7FFFFFFFFFFF) {
                    std::string interpretation = InterpretValue(value);
                    LogConstantFound(current, value, interpretation);
                    
                    // Check if it's a pointer to string
                    if (IsLikelyPointer(value) && IsReadableMemory(value)) {
                        const char* str_ptr = reinterpret_cast<const char*>(value);
                        if (IsValidString(str_ptr)) {
                            std::string content = ExtractString(value);
                            std::stringstream ss;
                            ss << "STRING_POINTER at " << FormatOffset(CalculateOffset(current)) 
                               << " -> \"" << content << "\"";
                            DATA_LOG(ss.str().c_str());
                        }
                    }
                }
            }
            current += 8;
        }
    }
    
    DATA_LOG("=== CONSTANT SCAN COMPLETE ===");
}

void LibanogsDataAnalyzer::ScanForAntiCheatPatterns() {
    if (!g_runtime_monitor.library_loaded) return;
    
    DATA_LOG("=== SCANNING FOR ANTI-CHEAT PATTERNS ===");
    
    // Look for common anti-cheat signatures
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (!(region.permissions & PROT_EXEC)) continue; // Focus on executable regions
        
        uintptr_t current = region.start_addr;
        uintptr_t end = region.end_addr;
        
        while (current < end - 32) {
            if (IsReadableMemory(current)) {
                const uint8_t* data = reinterpret_cast<const uint8_t*>(current);
                
                // Check for debugger detection patterns
                if (data[0] == 0x64 && data[1] == 0x48 && data[2] == 0x8B) { // FS segment access
                    DATA_LOG("DEBUGGER_DETECTION pattern detected (FS segment access)");
                    LogHexPatternFound(current, data, 16, "DEBUGGER_DETECTION");
                }
                
                // Check for timing checks
                if (data[0] == 0x0F && data[1] == 0x31) { // RDTSC
                    DATA_LOG("TIMING_CHECK pattern detected (RDTSC)");
                    LogHexPatternFound(current, data, 8, "TIMING_CHECK");
                }
                
                // Check for memory protection checks
                if (data[0] == 0x48 && data[1] == 0x8B && data[2] == 0x05) { // MOV from memory
                    DATA_LOG("MEMORY_CHECK pattern detected");
                    LogHexPatternFound(current, data, 12, "MEMORY_CHECK");
                }
                
                // Check for hook detection
                if (data[0] == 0xE8 && data[5] == 0x85 && data[6] == 0xC0) { // CALL + TEST EAX, EAX
                    DATA_LOG("HOOK_DETECTION pattern detected");
                    LogHexPatternFound(current, data, 10, "HOOK_DETECTION");
                }
            }
            current += 4;
        }
    }
    
    DATA_LOG("=== ANTI-CHEAT PATTERN SCAN COMPLETE ===");
}

void LibanogsDataAnalyzer::TakeMemorySnapshot() {
    if (!g_runtime_monitor.library_loaded) return;
    
    pthread_mutex_lock(&analyzer_mutex);
    
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (region.permissions & PROT_READ) {
            std::vector<uint8_t> snapshot(region.size);
            memcpy(snapshot.data(), reinterpret_cast<void*>(region.start_addr), region.size);
            memory_snapshots[region.start_addr] = snapshot;
        }
    }
    
    DATA_LOG("Memory snapshot taken");
    pthread_mutex_unlock(&analyzer_mutex);
}

void LibanogsDataAnalyzer::DetectMemoryChanges() {
    if (!g_runtime_monitor.library_loaded) return;
    
    pthread_mutex_lock(&analyzer_mutex);
    
    for (const auto& region : g_runtime_monitor.memory_regions) {
        if (!(region.permissions & PROT_READ)) continue;
        
        auto snapshot_it = memory_snapshots.find(region.start_addr);
        if (snapshot_it != memory_snapshots.end()) {
            const std::vector<uint8_t>& old_data = snapshot_it->second;
            const uint8_t* current_data = reinterpret_cast<const uint8_t*>(region.start_addr);
            
            for (size_t i = 0; i < old_data.size() && i < region.size; i += 4) {
                if (memcmp(&old_data[i], &current_data[i], 4) != 0) {
                    uintptr_t change_addr = region.start_addr + i;
                    LogMemoryChange(change_addr, &old_data[i], &current_data[i], 4);
                    
                    std::stringstream ss;
                    ss << "MEMORY_CHANGE at " << FormatOffset(CalculateOffset(change_addr))
                       << " Old: " << BytesToHexString(&old_data[i], 4)
                       << " New: " << BytesToHexString(&current_data[i], 4);
                    DATA_LOG(ss.str().c_str());
                }
            }
        }
    }
    
    pthread_mutex_unlock(&analyzer_mutex);
}

bool LibanogsDataAnalyzer::IsValidString(const char* ptr, size_t max_len) {
    if (!ptr || !IsReadableMemory(reinterpret_cast<uintptr_t>(ptr))) return false;
    
    size_t len = 0;
    while (len < max_len && ptr[len] != '\0') {
        if (!isprint(ptr[len]) && ptr[len] != '\n' && ptr[len] != '\r' && ptr[len] != '\t') {
            return false;
        }
        len++;
    }
    
    return len >= 4 && len < max_len && ptr[len] == '\0';
}

std::string LibanogsDataAnalyzer::ExtractString(uintptr_t address, bool is_wide) {
    if (!IsReadableMemory(address)) return "";
    
    const char* str_ptr = reinterpret_cast<const char*>(address);
    std::string result;
    
    size_t max_len = 1024;
    for (size_t i = 0; i < max_len; i++) {
        if (str_ptr[i] == '\0') break;
        if (isprint(str_ptr[i]) || str_ptr[i] == '\n' || str_ptr[i] == '\r' || str_ptr[i] == '\t') {
            result += str_ptr[i];
        } else {
            break;
        }
    }
    
    return result;
}

std::string LibanogsDataAnalyzer::BytesToHexString(const uint8_t* data, size_t size) {
    std::stringstream ss;
    for (size_t i = 0; i < size; i++) {
        ss << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(data[i]);
        if (i < size - 1) ss << " ";
    }
    return ss.str();
}

uintptr_t LibanogsDataAnalyzer::CalculateOffset(uintptr_t absolute_address) {
    if (g_runtime_monitor.base_address == 0) return 0;
    return absolute_address - g_runtime_monitor.base_address;
}

void LibanogsDataAnalyzer::LogStringFound(uintptr_t address, const std::string& content) {
    LOG_STRING_FOUND(address, content);
    
    StringReference ref;
    ref.address = address;
    ref.offset_from_base = CalculateOffset(address);
    ref.content = content;
    ref.length = content.length();
    ref.is_ascii = true;
    ref.is_wide = false;
    ref.first_seen = time(nullptr);
    ref.access_count = 1;
    
    pthread_mutex_lock(&analyzer_mutex);
    string_refs.push_back(ref);
    pthread_mutex_unlock(&analyzer_mutex);
}

void LibanogsDataAnalyzer::LogHexPatternFound(uintptr_t address, const uint8_t* data, size_t size, const std::string& type) {
    LOG_HEX_PATTERN(address, data, size, type);
    
    HexPattern pattern;
    pattern.address = address;
    pattern.offset_from_base = CalculateOffset(address);
    pattern.bytes.assign(data, data + size);
    pattern.hex_string = BytesToHexString(data, size);
    pattern.size = size;
    pattern.pattern_type = type;
    pattern.first_seen = time(nullptr);
    pattern.match_count = 1;
    
    pthread_mutex_lock(&analyzer_mutex);
    hex_patterns.push_back(pattern);
    pthread_mutex_unlock(&analyzer_mutex);
}

void LibanogsDataAnalyzer::LogConstantFound(uintptr_t address, uint64_t value, const std::string& type) {
    LOG_CONSTANT_FOUND(address, value, type);
    
    RuntimeConstant constant;
    constant.address = address;
    constant.offset_from_base = CalculateOffset(address);
    constant.value = value;
    constant.value_type = type;
    constant.interpretation = InterpretValue(value);
    constant.is_pointer = IsLikelyPointer(value);
    constant.is_string_ptr = false;
    constant.discovered = time(nullptr);
    
    pthread_mutex_lock(&analyzer_mutex);
    runtime_constants.push_back(constant);
    pthread_mutex_unlock(&analyzer_mutex);
}

std::string LibanogsDataAnalyzer::InterpretValue(uint64_t value) {
    if (value == 0) return "NULL";
    if (value == 0xFFFFFFFFFFFFFFFF) return "INVALID";
    if (value < 0x1000) return "SMALL_INT";
    if (value > 0x7F0000000000 && value < 0x7FFFFFFFFFFF) return "LIKELY_POINTER";
    if (value > 1000000000 && value < 2000000000) return "TIMESTAMP";
    return "UNKNOWN";
}

bool LibanogsDataAnalyzer::IsLikelyPointer(uint64_t value) {
    return value > 0x7F0000000000 && value < 0x7FFFFFFFFFFF && (value % 8 == 0);
}

void LibanogsDataAnalyzer::LogMemoryChange(uintptr_t address, const uint8_t* old_data, const uint8_t* new_data, size_t size) {
    std::stringstream ss;
    ss << "MEMORY_CHANGE at " << FormatOffset(CalculateOffset(address))
       << " (0x" << std::hex << address << ")\n"
       << "Old: " << BytesToHexString(old_data, size) << "\n"
       << "New: " << BytesToHexString(new_data, size);
    DATA_LOG(ss.str().c_str());
}

void LibanogsDataAnalyzer::GenerateDataReport() {
    std::stringstream ss;
    ss << "\n=== LIBANOGS DATA ANALYSIS REPORT ===\n";
    ss << "Strings Found: " << string_refs.size() << "\n";
    ss << "Hex Patterns: " << hex_patterns.size() << "\n";
    ss << "Runtime Constants: " << runtime_constants.size() << "\n";
    ss << "Offset Activities: " << offset_activities.size() << "\n";
    ss << "=====================================";
    
    DATA_LOG(ss.str().c_str());
}

// Global functions
void InitializeDataAnalyzer() {
    if (!RUNTIME_MONITOR_ENABLED) return;
    
    if (!g_data_analyzer) {
        g_data_analyzer = new LibanogsDataAnalyzer();
        g_data_analyzer->Initialize();
    }
}

void StartDataAnalysis() {
    if (g_data_analyzer) {
        g_data_analyzer->StartAnalysis();
    }
}

void StopDataAnalysis() {
    if (g_data_analyzer) {
        g_data_analyzer->Shutdown();
        delete g_data_analyzer;
        g_data_analyzer = nullptr;
    }
}
