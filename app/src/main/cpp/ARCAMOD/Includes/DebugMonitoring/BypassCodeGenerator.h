#ifndef ARCAMOD_BYPASS_CODE_GENERATOR_H
#define ARCAMOD_BYPASS_CODE_GENERATOR_H

#include "LibanogsDataAnalyzer.h"
#include <fstream>
#include <regex>

/*
 * BYPASS CODE GENERATOR
 * =====================
 * 
 * Tool otomatis untuk menganalisis data dari ARCAMOD_LibAnogs_Data.txt
 * dan menghasilkan kode bypass yang siap digunakan.
 */

struct BypassTarget {
    std::string offset;
    std::string type;
    std::string description;
    std::string hex_data;
    int priority;
    bool is_hook;
    bool is_patch;
};

class BypassCodeGenerator {
private:
    std::vector<BypassTarget> targets;
    std::string data_file_path;
    std::string output_file_path;
    
public:
    BypassCodeGenerator();
    ~BypassCodeGenerator();
    
    // Analysis functions
    bool LoadDataFile(const std::string& file_path = DATA_LOG_PATH);
    void AnalyzeDataFile();
    void ExtractAntiCheatPatterns();
    void ExtractStringDetections();
    void ExtractMemoryChanges();
    void ExtractOffsetActivities();
    void PrioritizeTargets();
    
    // Code generation
    void GenerateBypassCode();
    void GenerateHookFunctions();
    void GeneratePatchCode();
    void GenerateIntegrationCode();
    
    // Output functions
    void SaveBypassCode(const std::string& output_path);
    void PrintAnalysisReport();
    void ExportTargetList();
    
    // Utility functions
    std::string ExtractOffset(const std::string& line);
    std::string ExtractHexData(const std::string& line);
    std::string GenerateFunctionName(const std::string& offset);
    int CalculatePriority(const std::string& type);
};

// Global generator instance
extern BypassCodeGenerator* g_bypass_generator;

// Inline implementations
inline BypassCodeGenerator::BypassCodeGenerator() {
    data_file_path = DATA_LOG_PATH;
    output_file_path = "/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Generated_Bypass.cpp";
}

inline bool BypassCodeGenerator::LoadDataFile(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        DATA_LOG("ERROR: Cannot open data file for analysis");
        return false;
    }
    
    data_file_path = file_path;
    file.close();
    
    std::stringstream ss;
    ss << "Loaded data file: " << file_path;
    DATA_LOG(ss.str().c_str());
    
    return true;
}

inline std::string BypassCodeGenerator::ExtractOffset(const std::string& line) {
    // Extract offset from patterns like "at 0x13243C" or "0x13243C:"
    std::regex offset_regex(R"(0x([0-9A-Fa-f]+))");
    std::smatch match;
    
    if (std::regex_search(line, match, offset_regex)) {
        return match[0].str(); // Return full "0x13243C"
    }
    
    return "";
}

inline std::string BypassCodeGenerator::GenerateFunctionName(const std::string& offset) {
    // Convert "0x13243C" to "h_sub_13243C"
    std::string clean_offset = offset.substr(2); // Remove "0x"
    return "h_sub_" + clean_offset;
}

inline int BypassCodeGenerator::CalculatePriority(const std::string& type) {
    if (type.find("ANTICHEAT_PATTERN") != std::string::npos) return 1;
    if (type.find("DEBUGGER_DETECTION") != std::string::npos) return 2;
    if (type.find("TIMING_CHECK") != std::string::npos) return 3;
    if (type.find("HOOK_DETECTION") != std::string::npos) return 4;
    if (type.find("MEMORY_CHECK") != std::string::npos) return 5;
    if (type.find("ANTICHEAT_STRING") != std::string::npos) return 6;
    if (type.find("MEMORY_CHANGE") != std::string::npos) return 7;
    if (type.find("OFFSET_ACTIVITY") != std::string::npos) return 8;
    return 9;
}

inline void BypassCodeGenerator::AnalyzeDataFile() {
    std::ifstream file(data_file_path);
    if (!file.is_open()) return;
    
    std::string line;
    targets.clear();
    
    DATA_LOG("=== ANALYZING DATA FILE FOR BYPASS TARGETS ===");
    
    while (std::getline(file, line)) {
        BypassTarget target;
        
        // Check for anti-cheat patterns
        if (line.find("ANTICHEAT_PATTERN") != std::string::npos) {
            target.offset = ExtractOffset(line);
            target.type = "ANTICHEAT_PATTERN";
            target.description = "Anti-cheat pattern detection";
            target.priority = CalculatePriority(target.type);
            target.is_hook = true;
            target.is_patch = false;
            
            if (!target.offset.empty()) {
                targets.push_back(target);
                
                std::stringstream ss;
                ss << "Found ANTICHEAT target: " << target.offset;
                DATA_LOG(ss.str().c_str());
            }
        }
        
        // Check for debugger detection
        else if (line.find("DEBUGGER_DETECTION") != std::string::npos) {
            target.offset = ExtractOffset(line);
            target.type = "DEBUGGER_DETECTION";
            target.description = "Debugger detection bypass";
            target.priority = CalculatePriority(target.type);
            target.is_hook = false;
            target.is_patch = true;
            
            if (!target.offset.empty()) {
                targets.push_back(target);
                
                std::stringstream ss;
                ss << "Found DEBUGGER_DETECTION target: " << target.offset;
                DATA_LOG(ss.str().c_str());
            }
        }
        
        // Check for timing checks
        else if (line.find("TIMING_CHECK") != std::string::npos) {
            target.offset = ExtractOffset(line);
            target.type = "TIMING_CHECK";
            target.description = "Timing check bypass";
            target.priority = CalculatePriority(target.type);
            target.is_hook = true;
            target.is_patch = false;
            
            if (!target.offset.empty()) {
                targets.push_back(target);
                
                std::stringstream ss;
                ss << "Found TIMING_CHECK target: " << target.offset;
                DATA_LOG(ss.str().c_str());
            }
        }
        
        // Check for hook detection
        else if (line.find("HOOK_DETECTION") != std::string::npos) {
            target.offset = ExtractOffset(line);
            target.type = "HOOK_DETECTION";
            target.description = "Hook detection bypass";
            target.priority = CalculatePriority(target.type);
            target.is_hook = false;
            target.is_patch = true;
            
            if (!target.offset.empty()) {
                targets.push_back(target);
                
                std::stringstream ss;
                ss << "Found HOOK_DETECTION target: " << target.offset;
                DATA_LOG(ss.str().c_str());
            }
        }
        
        // Check for memory changes
        else if (line.find("MEMORY_CHANGE") != std::string::npos) {
            target.offset = ExtractOffset(line);
            target.type = "MEMORY_CHANGE";
            target.description = "Memory change patch";
            target.priority = CalculatePriority(target.type);
            target.is_hook = false;
            target.is_patch = true;
            
            if (!target.offset.empty()) {
                targets.push_back(target);
                
                std::stringstream ss;
                ss << "Found MEMORY_CHANGE target: " << target.offset;
                DATA_LOG(ss.str().c_str());
            }
        }
        
        // Check for anti-cheat strings
        else if (line.find("ANTICHEAT_STRING") != std::string::npos) {
            target.offset = ExtractOffset(line);
            target.type = "ANTICHEAT_STRING";
            target.description = "Anti-cheat string bypass";
            target.priority = CalculatePriority(target.type);
            target.is_hook = true;
            target.is_patch = false;
            
            if (!target.offset.empty()) {
                targets.push_back(target);
                
                std::stringstream ss;
                ss << "Found ANTICHEAT_STRING target: " << target.offset;
                DATA_LOG(ss.str().c_str());
            }
        }
    }
    
    file.close();
    
    // Sort by priority
    std::sort(targets.begin(), targets.end(), 
              [](const BypassTarget& a, const BypassTarget& b) {
                  return a.priority < b.priority;
              });
    
    std::stringstream ss;
    ss << "Analysis complete. Found " << targets.size() << " bypass targets";
    DATA_LOG(ss.str().c_str());
    
    DATA_LOG("=== DATA FILE ANALYSIS COMPLETE ===");
}

inline void BypassCodeGenerator::GenerateBypassCode() {
    if (targets.empty()) {
        DATA_LOG("No targets found. Run AnalyzeDataFile() first.");
        return;
    }
    
    DATA_LOG("=== GENERATING BYPASS CODE ===");
    
    std::ofstream output(output_file_path);
    if (!output.is_open()) {
        DATA_LOG("ERROR: Cannot create output file");
        return;
    }
    
    // Generate header
    output << "/*\n";
    output << " * AUTO-GENERATED BYPASS CODE\n";
    output << " * Generated from: " << data_file_path << "\n";
    output << " * Targets found: " << targets.size() << "\n";
    output << " * Generation time: " << time(nullptr) << "\n";
    output << " */\n\n";
    
    // Generate hook function declarations
    output << "// Hook function declarations\n";
    for (const auto& target : targets) {
        if (target.is_hook) {
            std::string func_name = GenerateFunctionName(target.offset);
            std::string orig_name = "o_sub_" + target.offset.substr(2);
            
            output << "static void (*" << orig_name << ")(void);\n";
            output << "static void " << func_name << "(void) {\n";
            output << "    // " << target.description << "\n";
            output << "    return; // Bypass - do nothing\n";
            output << "}\n\n";
        }
    }
    
    // Generate hook integration code
    output << "// Add these hooks to initialize_anogs_hooks():\n";
    for (const auto& target : targets) {
        if (target.is_hook) {
            std::string func_name = GenerateFunctionName(target.offset);
            std::string orig_name = "o_sub_" + target.offset.substr(2);
            
            output << "WhileHook(HOOK2(arcamod, \"" << target.offset << "\", " 
                   << func_name << ", " << orig_name << ")); // " << target.description << "\n";
        }
    }
    
    output << "\n";
    
    // Generate patch integration code
    output << "// Add these patches to apply_anogs_patches():\n";
    for (const auto& target : targets) {
        if (target.is_patch) {
            output << "WhilePatch(PATCH(arcamod, \"" << target.offset 
                   << "\", BYPASS_PATCH)); // " << target.description << "\n";
        }
    }
    
    output << "\n";
    
    // Generate summary
    output << "/*\n";
    output << " * BYPASS SUMMARY:\n";
    output << " * Total targets: " << targets.size() << "\n";
    
    int hook_count = 0, patch_count = 0;
    for (const auto& target : targets) {
        if (target.is_hook) hook_count++;
        if (target.is_patch) patch_count++;
    }
    
    output << " * Hooks: " << hook_count << "\n";
    output << " * Patches: " << patch_count << "\n";
    output << " *\n";
    output << " * PRIORITY ORDER:\n";
    
    for (size_t i = 0; i < targets.size(); i++) {
        output << " * " << (i+1) << ". " << targets[i].offset 
               << " - " << targets[i].type << "\n";
    }
    
    output << " */\n";
    
    output.close();
    
    std::stringstream ss;
    ss << "Bypass code generated: " << output_file_path;
    DATA_LOG(ss.str().c_str());
    
    DATA_LOG("=== BYPASS CODE GENERATION COMPLETE ===");
}

inline void BypassCodeGenerator::PrintAnalysisReport() {
    DATA_LOG("=== BYPASS ANALYSIS REPORT ===");
    
    std::stringstream ss;
    ss << "Total targets found: " << targets.size();
    DATA_LOG(ss.str().c_str());
    
    int hook_count = 0, patch_count = 0;
    for (const auto& target : targets) {
        if (target.is_hook) hook_count++;
        if (target.is_patch) patch_count++;
    }
    
    ss.str("");
    ss << "Hooks needed: " << hook_count;
    DATA_LOG(ss.str().c_str());
    
    ss.str("");
    ss << "Patches needed: " << patch_count;
    DATA_LOG(ss.str().c_str());
    
    DATA_LOG("Priority order:");
    for (size_t i = 0; i < targets.size() && i < 10; i++) {
        ss.str("");
        ss << (i+1) << ". " << targets[i].offset << " - " << targets[i].type;
        DATA_LOG(ss.str().c_str());
    }
    
    DATA_LOG("=== ANALYSIS REPORT COMPLETE ===");
}

// Global functions
void InitializeBypassGenerator();
void GenerateBypassFromData();
void AnalyzeAndGenerateBypass();

inline void InitializeBypassGenerator() {
    if (!g_bypass_generator) {
        g_bypass_generator = new BypassCodeGenerator();
        DATA_LOG("Bypass code generator initialized");
    }
}

inline void GenerateBypassFromData() {
    if (!g_bypass_generator) {
        InitializeBypassGenerator();
    }
    
    if (g_bypass_generator->LoadDataFile()) {
        g_bypass_generator->AnalyzeDataFile();
        g_bypass_generator->GenerateBypassCode();
        g_bypass_generator->PrintAnalysisReport();
    }
}

inline void AnalyzeAndGenerateBypass() {
    DATA_LOG("=== STARTING AUTOMATIC BYPASS GENERATION ===");
    GenerateBypassFromData();
    DATA_LOG("=== AUTOMATIC BYPASS GENERATION COMPLETE ===");
    DATA_LOG("Check output file: /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Generated_Bypass.cpp");
}

#endif // ARCAMOD_BYPASS_CODE_GENERATOR_H
