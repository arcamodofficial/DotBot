#ifndef SYSTEMINFO_H
#define SYSTEMINFO_H

#include <string>

std::string GetRAMInfo();
std::string GetRAMInfoInGB();
std::string GetCPUInfo();
std::string GetCPUFrequency();
std::string GetCPUMaxFrequency();
std::string GetCPUMinFrequency();
long GetTotalRAMInGB();
bool IsRAM8GBOrHigher();
std::string GetOSInfo();
bool IsXiaomiHyperOS();
bool IsFakeStatusEligible();

#endif // SYSTEMINFO_H