#ifndef ARCAMOD_QUICK_BYPASS_ANALYZER_H
#define ARCAMOD_QUICK_BYPASS_ANALYZER_H

#include "BypassCodeGenerator.h"

/*
 * QUICK BYPASS ANALYZER
 * =====================
 * 
 * Tool cepat untuk menganalisis file ARCAMOD_LibAnogs_Data.txt
 * dan memberikan rekomendasi bypass yang siap implementasi.
 */

// Quick analysis functions
void QuickAnalyzeDataFile();
void ExtractTopPriorityTargets();
void GenerateQuickBypassCode();
void ShowImplementationSteps();

// Utility functions for manual analysis
void SearchForPattern(const std::string& pattern);
void ListAllOffsets();
void FilterByType(const std::string& type);
void ShowMemoryChanges();
void ShowAntiCheatStrings();

inline void QuickAnalyzeDataFile() {
    DATA_LOG("=== QUICK BYPASS ANALYSIS ===");
    
    std::ifstream file(DATA_LOG_PATH);
    if (!file.is_open()) {
        DATA_LOG("ERROR: Cannot open data file. Make sure monitoring has run.");
        return;
    }
    
    std::string line;
    std::vector<std::string> anticheat_patterns;
    std::vector<std::string> debugger_detections;
    std::vector<std::string> timing_checks;
    std::vector<std::string> hook_detections;
    std::vector<std::string> memory_changes;
    std::vector<std::string> anticheat_strings;
    
    // Parse file and categorize findings
    while (std::getline(file, line)) {
        if (line.find("ANTICHEAT_PATTERN") != std::string::npos) {
            anticheat_patterns.push_back(line);
        }
        else if (line.find("DEBUGGER_DETECTION") != std::string::npos) {
            debugger_detections.push_back(line);
        }
        else if (line.find("TIMING_CHECK") != std::string::npos) {
            timing_checks.push_back(line);
        }
        else if (line.find("HOOK_DETECTION") != std::string::npos) {
            hook_detections.push_back(line);
        }
        else if (line.find("MEMORY_CHANGE") != std::string::npos) {
            memory_changes.push_back(line);
        }
        else if (line.find("ANTICHEAT_STRING") != std::string::npos) {
            anticheat_strings.push_back(line);
        }
    }
    
    file.close();
    
    // Report findings
    DATA_LOG("=== ANALYSIS RESULTS ===");
    
    std::stringstream ss;
    ss << "Anti-cheat patterns found: " << anticheat_patterns.size();
    DATA_LOG(ss.str().c_str());
    
    ss.str("");
    ss << "Debugger detections found: " << debugger_detections.size();
    DATA_LOG(ss.str().c_str());
    
    ss.str("");
    ss << "Timing checks found: " << timing_checks.size();
    DATA_LOG(ss.str().c_str());
    
    ss.str("");
    ss << "Hook detections found: " << hook_detections.size();
    DATA_LOG(ss.str().c_str());
    
    ss.str("");
    ss << "Memory changes found: " << memory_changes.size();
    DATA_LOG(ss.str().c_str());
    
    ss.str("");
    ss << "Anti-cheat strings found: " << anticheat_strings.size();
    DATA_LOG(ss.str().c_str());
    
    // Show top priority targets
    DATA_LOG("=== TOP PRIORITY TARGETS ===");
    
    // Extract offsets from anti-cheat patterns (highest priority)
    std::regex offset_regex(R"(0x([0-9A-Fa-f]+))");
    std::smatch match;
    
    int count = 0;
    for (const auto& pattern : anticheat_patterns) {
        if (std::regex_search(pattern, match, offset_regex) && count < 5) {
            ss.str("");
            ss << "PRIORITY " << (count + 1) << ": Hook " << match[0].str() << " (Anti-cheat pattern)";
            DATA_LOG(ss.str().c_str());
            count++;
        }
    }
    
    // Add debugger detections
    for (const auto& detection : debugger_detections) {
        if (std::regex_search(detection, match, offset_regex) && count < 10) {
            ss.str("");
            ss << "PRIORITY " << (count + 1) << ": Patch " << match[0].str() << " (Debugger detection)";
            DATA_LOG(ss.str().c_str());
            count++;
        }
    }
    
    DATA_LOG("=== QUICK ANALYSIS COMPLETE ===");
}

inline void ExtractTopPriorityTargets() {
    DATA_LOG("=== EXTRACTING TOP PRIORITY TARGETS ===");
    
    std::ifstream file(DATA_LOG_PATH);
    if (!file.is_open()) {
        DATA_LOG("ERROR: Cannot open data file");
        return;
    }
    
    std::string line;
    std::regex offset_regex(R"(0x([0-9A-Fa-f]+))");
    std::smatch match;
    
    DATA_LOG("=== IMMEDIATE ACTION REQUIRED ===");
    
    int priority = 1;
    while (std::getline(file, line) && priority <= 10) {
        if (line.find("ANTICHEAT_PATTERN") != std::string::npos) {
            if (std::regex_search(line, match, offset_regex)) {
                std::stringstream ss;
                ss << "URGENT " << priority << ": Add hook for " << match[0].str();
                DATA_LOG(ss.str().c_str());
                
                ss.str("");
                ss << "Code: WhileHook(HOOK2(arcamod, \"" << match[0].str() << "\", h_sub_" 
                   << match[1].str() << ", o_sub_" << match[1].str() << "));";
                DATA_LOG(ss.str().c_str());
                
                priority++;
            }
        }
    }
    
    file.close();
    DATA_LOG("=== TOP PRIORITY EXTRACTION COMPLETE ===");
}

inline void GenerateQuickBypassCode() {
    DATA_LOG("=== GENERATING QUICK BYPASS CODE ===");
    
    std::ifstream file(DATA_LOG_PATH);
    if (!file.is_open()) {
        DATA_LOG("ERROR: Cannot open data file");
        return;
    }
    
    std::ofstream output("/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Quick_Bypass.txt");
    if (!output.is_open()) {
        DATA_LOG("ERROR: Cannot create output file");
        return;
    }
    
    output << "// QUICK BYPASS CODE - COPY PASTE READY\n";
    output << "// Generated from ARCAMOD_LibAnogs_Data.txt\n\n";
    
    std::string line;
    std::regex offset_regex(R"(0x([0-9A-Fa-f]+))");
    std::smatch match;
    
    // Generate hook declarations
    output << "// 1. ADD THESE DECLARATIONS AT TOP OF FILE:\n";
    while (std::getline(file, line)) {
        if (line.find("ANTICHEAT_PATTERN") != std::string::npos || 
            line.find("TIMING_CHECK") != std::string::npos) {
            if (std::regex_search(line, match, offset_regex)) {
                std::string offset_clean = match[1].str();
                output << "static void (*o_sub_" << offset_clean << ")(void);\n";
                output << "static void h_sub_" << offset_clean << "(void) { return; }\n";
            }
        }
    }
    
    // Reset file position
    file.clear();
    file.seekg(0, std::ios::beg);
    
    output << "\n// 2. ADD THESE HOOKS TO initialize_anogs_hooks():\n";
    while (std::getline(file, line)) {
        if (line.find("ANTICHEAT_PATTERN") != std::string::npos || 
            line.find("TIMING_CHECK") != std::string::npos) {
            if (std::regex_search(line, match, offset_regex)) {
                std::string offset_full = match[0].str();
                std::string offset_clean = match[1].str();
                output << "WhileHook(HOOK2(arcamod, \"" << offset_full 
                       << "\", h_sub_" << offset_clean << ", o_sub_" << offset_clean << "));\n";
            }
        }
    }
    
    // Reset file position
    file.clear();
    file.seekg(0, std::ios::beg);
    
    output << "\n// 3. ADD THESE PATCHES TO apply_anogs_patches():\n";
    while (std::getline(file, line)) {
        if (line.find("DEBUGGER_DETECTION") != std::string::npos || 
            line.find("HOOK_DETECTION") != std::string::npos ||
            line.find("MEMORY_CHANGE") != std::string::npos) {
            if (std::regex_search(line, match, offset_regex)) {
                std::string offset_full = match[0].str();
                output << "WhilePatch(PATCH(arcamod, \"" << offset_full << "\", BYPASS_PATCH));\n";
            }
        }
    }
    
    file.close();
    output.close();
    
    DATA_LOG("Quick bypass code generated: /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Quick_Bypass.txt");
    DATA_LOG("=== QUICK BYPASS CODE GENERATION COMPLETE ===");
}

inline void ShowImplementationSteps() {
    DATA_LOG("=== IMPLEMENTATION STEPS ===");
    DATA_LOG("1. Copy declarations from ARCAMOD_Quick_Bypass.txt to top of arcamod.cpp");
    DATA_LOG("2. Copy hook lines to initialize_anogs_hooks() function");
    DATA_LOG("3. Copy patch lines to apply_anogs_patches() function");
    DATA_LOG("4. Compile and test");
    DATA_LOG("5. Monitor for new detections");
    DATA_LOG("=== IMPLEMENTATION STEPS COMPLETE ===");
}

inline void SearchForPattern(const std::string& pattern) {
    std::ifstream file(DATA_LOG_PATH);
    if (!file.is_open()) {
        DATA_LOG("ERROR: Cannot open data file");
        return;
    }
    
    std::stringstream ss;
    ss << "=== SEARCHING FOR PATTERN: " << pattern << " ===";
    DATA_LOG(ss.str().c_str());
    
    std::string line;
    int line_number = 0;
    int found_count = 0;
    
    while (std::getline(file, line)) {
        line_number++;
        if (line.find(pattern) != std::string::npos) {
            found_count++;
            ss.str("");
            ss << "Line " << line_number << ": " << line;
            DATA_LOG(ss.str().c_str());
        }
    }
    
    file.close();
    
    ss.str("");
    ss << "Found " << found_count << " occurrences of '" << pattern << "'";
    DATA_LOG(ss.str().c_str());
}

inline void ListAllOffsets() {
    std::ifstream file(DATA_LOG_PATH);
    if (!file.is_open()) {
        DATA_LOG("ERROR: Cannot open data file");
        return;
    }
    
    DATA_LOG("=== ALL DETECTED OFFSETS ===");
    
    std::string line;
    std::regex offset_regex(R"(0x([0-9A-Fa-f]+))");
    std::smatch match;
    std::set<std::string> unique_offsets;
    
    while (std::getline(file, line)) {
        if (std::regex_search(line, match, offset_regex)) {
            unique_offsets.insert(match[0].str());
        }
    }
    
    file.close();
    
    for (const auto& offset : unique_offsets) {
        DATA_LOG(offset.c_str());
    }
    
    std::stringstream ss;
    ss << "Total unique offsets: " << unique_offsets.size();
    DATA_LOG(ss.str().c_str());
}

inline void ShowMemoryChanges() {
    DATA_LOG("=== MEMORY CHANGES DETECTED ===");
    SearchForPattern("MEMORY_CHANGE");
}

inline void ShowAntiCheatStrings() {
    DATA_LOG("=== ANTI-CHEAT STRINGS DETECTED ===");
    SearchForPattern("ANTICHEAT_STRING");
}

// Main analysis function
inline void RunCompleteAnalysis() {
    DATA_LOG("========================================");
    DATA_LOG("RUNNING COMPLETE BYPASS ANALYSIS");
    DATA_LOG("========================================");
    
    QuickAnalyzeDataFile();
    ExtractTopPriorityTargets();
    GenerateQuickBypassCode();
    ShowImplementationSteps();
    
    DATA_LOG("========================================");
    DATA_LOG("COMPLETE ANALYSIS FINISHED");
    DATA_LOG("========================================");
    DATA_LOG("Next steps:");
    DATA_LOG("1. Check /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_Quick_Bypass.txt");
    DATA_LOG("2. Copy the generated code to your arcamod.cpp");
    DATA_LOG("3. Compile and test the bypass");
}

#endif // ARCAMOD_QUICK_BYPASS_ANALYZER_H
