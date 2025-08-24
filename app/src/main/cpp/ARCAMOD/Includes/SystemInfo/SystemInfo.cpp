#include "SystemInfo.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <sys/utsname.h>
#include <vector>
#include <algorithm>
#include <cctype>

std::string GetRAMInfo() {
    std::ifstream memInfoFile("/proc/meminfo");
    std::string line;
    long totalRam = 0;
    long freeRam = 0;
    long buffers = 0;
    long cached = 0;
    long usedRam = 0;

    if (memInfoFile.is_open()) {
        while (std::getline(memInfoFile, line)) {
            if (line.find("MemTotal") != std::string::npos) {
                std::istringstream(line.substr(line.find(":") + 1)) >> totalRam;
            }
            if (line.find("MemFree") != std::string::npos) {
                std::istringstream(line.substr(line.find(":") + 1)) >> freeRam;
            }
            if (line.find("Buffers") != std::string::npos) {
                std::istringstream(line.substr(line.find(":") + 1)) >> buffers;
            }
            if (line.find("Cached") != std::string::npos) {
                std::istringstream(line.substr(line.find(":") + 1)) >> cached;
            }
            if (totalRam && freeRam && buffers && cached) {
                break;
            }
        }
        memInfoFile.close();
    }

    usedRam = totalRam - freeRam - buffers - cached;

    long forcedUsedRam = 8 * 1024;
    if (usedRam < forcedUsedRam) {
        usedRam = forcedUsedRam;
    }

    freeRam /= 1024;
    usedRam /= 1024;
    return std::to_string(usedRam) + " MB / " + std::to_string(freeRam) + " MB";
}

std::string GetCPUInfo() {
    static std::string cached_cpu_info;
    static bool cpu_info_cached = false;

    if (cpu_info_cached) {
        return cached_cpu_info;
    }

    std::ifstream cpuInfoFile("/proc/cpuinfo");
    if (!cpuInfoFile.is_open()) {
        cached_cpu_info = "Unknown CPU";
        cpu_info_cached = true;
        return cached_cpu_info;
    }

    std::string line;
    std::string modelName;
    int cores = 0;
    bool model_found = false;

    line.reserve(256);
    modelName.reserve(128);

    while (std::getline(cpuInfoFile, line)) {
        if (!model_found && line.find("model name") != std::string::npos) {
            size_t colon_pos = line.find(":");
            if (colon_pos != std::string::npos && colon_pos + 2 < line.length()) {
                modelName = line.substr(colon_pos + 2);
                model_found = true;
            }
        }
        if (line.find("processor") != std::string::npos) {
            cores++;
        }
        if (model_found && cores > 0) {
            break;
        }
    }
    cpuInfoFile.close();
    cached_cpu_info = modelName + " | Cores: " + std::to_string(cores);
    cpu_info_cached = true;

    return cached_cpu_info;
}

std::string GetCPUFrequency() {
    std::ifstream cpuFreqFile("/sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq");
    std::string line;
    int currentFreq = 0;

    if (cpuFreqFile.is_open()) {
        std::getline(cpuFreqFile, line);
        currentFreq = std::stoi(line);
        cpuFreqFile.close();
    }

    float currentFreqGHz = currentFreq / 1000.0f;
    return std::to_string(currentFreqGHz) + " GHz";
}

std::string GetCPUMaxFrequency() {
    std::ifstream cpuMaxFreqFile("/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq");
    std::string line;
    int maxFreq = 0;

    if (cpuMaxFreqFile.is_open()) {
        std::getline(cpuMaxFreqFile, line);
        maxFreq = std::stoi(line);
        cpuMaxFreqFile.close();
    }

    float maxFreqGHz = maxFreq / 1000.0f;
    return std::to_string(maxFreqGHz) + " GHz";
}

std::string GetCPUMinFrequency() {
    std::ifstream cpuMinFreqFile("/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq");
    std::string line;
    int minFreq = 0;

    if (cpuMinFreqFile.is_open()) {
        std::getline(cpuMinFreqFile, line);
        minFreq = std::stoi(line);
        cpuMinFreqFile.close();
    }

    float minFreqGHz = minFreq / 1000.0f;
    return std::to_string(minFreqGHz) + " GHz";
}

static std::string GetGPUFrequencyMin() {
    const char* path = "/sys/class/kgsl/kgsl-3d0/devfreq/min_freq";
    
    std::ifstream file(path);
    if (!file.is_open()) {
        return "Error: Unable to read GPU frequency file.";
    }
    
    std::string line;
    std::getline(file, line);
    file.close();

    std::istringstream iss(line);
    long long freqHz;
    if (iss >> freqHz) {
        float freqMHz = static_cast<float>(freqHz) / 1000000.0f;
        std::ostringstream oss;
        oss.precision(2);
        oss << std::fixed << freqMHz;
        return oss.str() + " MHz";
    }
    
    return "Error: Invalid data from GPU frequency file.";
}

long GetTotalRAMInGB() {
    std::ifstream memInfoFile("/proc/meminfo");
    std::string line;
    long totalRam = 0;

    if (memInfoFile.is_open()) {
        while (std::getline(memInfoFile, line)) {
            if (line.find("MemTotal") != std::string::npos) {
                std::istringstream(line.substr(line.find(":") + 1)) >> totalRam;
                break;
            }
        }
        memInfoFile.close();
    }

    long totalRamGB = totalRam / (1024 * 1024);
    return totalRamGB;
}

bool IsRAM8GBOrHigher() {
    long totalRAM = GetTotalRAMInGB();
    return totalRAM >= 8;
}

std::string GetOSInfo() {
    std::string osInfo = "";
    std::vector<std::pair<std::string, std::string>> propPaths = {
        {"/system/build.prop", "ro.build.display.id"},
        {"/system/build.prop", "ro.miui.ui.version.name"},
        {"/system/build.prop", "ro.build.version.incremental"},
        {"/system/build.prop", "ro.product.manufacturer"},
        {"/vendor/build.prop", "ro.build.display.id"},
        {"/product/build.prop", "ro.build.display.id"}
    };

    for (const auto& propPath : propPaths) {
        std::ifstream buildPropFile(propPath.first);
        if (buildPropFile.is_open()) {
            std::string line;
            while (std::getline(buildPropFile, line)) {
                if (line.find(propPath.second) != std::string::npos) {
                    size_t equalPos = line.find("=");
                    if (equalPos != std::string::npos) {
                        std::string value = line.substr(equalPos + 1);
                        if (!value.empty()) {
                            osInfo = value;
                            buildPropFile.close();
                            return osInfo;
                        }
                    }
                }
            }
            buildPropFile.close();
        }
    }

    std::ifstream manufacturerFile("/sys/class/dmi/id/sys_vendor");
    if (manufacturerFile.is_open()) {
        std::getline(manufacturerFile, osInfo);
        manufacturerFile.close();
        if (!osInfo.empty()) {
            return osInfo;
        }
    }

    std::ifstream versionFile("/proc/version");
    if (versionFile.is_open()) {
        std::getline(versionFile, osInfo);
        versionFile.close();
    }

    return osInfo;
}

bool IsXiaomiHyperOS() {
    std::vector<std::string> buildPropPaths = {
        "/system/build.prop",
        "/vendor/build.prop",
        "/product/build.prop"
    };

    for (const std::string& path : buildPropPaths) {
        std::ifstream buildPropFile(path);
        if (buildPropFile.is_open()) {
            std::string line;
            while (std::getline(buildPropFile, line)) {
                std::string lineLower = line;
                std::transform(lineLower.begin(), lineLower.end(), lineLower.begin(), ::tolower);

                if (lineLower.find("xiaomi") != std::string::npos ||
                    lineLower.find("miui") != std::string::npos ||
                    lineLower.find("hyperos") != std::string::npos ||
                    lineLower.find("redmi") != std::string::npos ||
                    lineLower.find("poco") != std::string::npos) {
                    buildPropFile.close();
                    return true;
                }
            }
            buildPropFile.close();
        }
    }

    std::vector<std::string> androidPaths = {
        "/sys/devices/soc0/machine",
        "/sys/devices/system/cpu/cpu0/cpufreq/scaling_governor",
        "/proc/cmdline"
    };

    for (const std::string& path : androidPaths) {
        std::ifstream file(path);
        if (file.is_open()) {
            std::string content;
            std::getline(file, content);
            file.close();

            std::transform(content.begin(), content.end(), content.begin(), ::tolower);
            if (content.find("xiaomi") != std::string::npos ||
                content.find("miui") != std::string::npos ||
                content.find("redmi") != std::string::npos) {
                return true;
            }
        }
    }

    return true;
}

bool IsFakeStatusEligible() {
    return true;
}