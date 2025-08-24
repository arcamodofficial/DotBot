#ifndef ARCAMOD_MEMORY_STRESS_PROTECTION_H
#define ARCAMOD_MEMORY_STRESS_PROTECTION_H

#include <chrono>
#include <signal.h>
#include <setjmp.h>
#include <android/log.h>

// LOGIO is defined globally in ConfigManager.h (via ARCAMOD/Includes.h)

namespace MemoryStressProtection {
    
    // Memory stress tracking
    struct MemoryStressContext {
        int total_frames = 0;
        int high_load_frames = 0;
        int consecutive_high_load = 0;
        int max_enemies_seen = 0;
        int max_vehicles_seen = 0;
        std::chrono::high_resolution_clock::time_point start_time;
        std::chrono::high_resolution_clock::time_point last_cleanup;
        bool extended_gameplay_mode = false;
        bool memory_stress_detected = false;
    };
    
    static MemoryStressContext g_memory_context;
    static bool g_memory_protection_initialized = false;
    
    // Initialize memory stress protection
    inline void Initialize() {
        if (g_memory_protection_initialized) return;
        
        g_memory_context.start_time = std::chrono::high_resolution_clock::now();
        g_memory_context.last_cleanup = g_memory_context.start_time;
        g_memory_protection_initialized = true;
        
        // LOGIO("MemoryStressProtection: Initialized memory stress monitoring");
    }
    
    // Update memory stress tracking
    inline void UpdateStressTracking(int frame_count, int enemy_count, int vehicle_count) {
        if (!g_memory_protection_initialized) Initialize();
        
        g_memory_context.total_frames = frame_count;
        g_memory_context.max_enemies_seen = std::max(g_memory_context.max_enemies_seen, enemy_count);
        g_memory_context.max_vehicles_seen = std::max(g_memory_context.max_vehicles_seen, vehicle_count);
        
        // Detect high load scenarios
        bool high_load = (enemy_count >= 10) || (vehicle_count >= 3) || (frame_count > 15000);
        
        if (high_load) {
            g_memory_context.high_load_frames++;
            g_memory_context.consecutive_high_load++;
        } else {
            g_memory_context.consecutive_high_load = 0;
        }
        
        // Detect extended gameplay (30+ minutes or 54000+ frames at 30fps)
        auto current_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(
            current_time - g_memory_context.start_time).count();
        
        if (duration >= 30 || frame_count >= 54000) {
            if (!g_memory_context.extended_gameplay_mode) {
                g_memory_context.extended_gameplay_mode = true;
                // LOGIO("MemoryStressProtection: Extended gameplay detected - duration=%ld min, frames=%d",
                      // duration, frame_count);
            }
        }
        
        // Detect memory stress conditions
        bool memory_stress = g_memory_context.extended_gameplay_mode && 
                           (g_memory_context.consecutive_high_load > 300); // 10 seconds of high load
        
        if (memory_stress && !g_memory_context.memory_stress_detected) {
            g_memory_context.memory_stress_detected = true;
            // LOGIO("MemoryStressProtection: Memory stress detected - triggering protective measures");
        } else if (!memory_stress && g_memory_context.memory_stress_detected) {
            g_memory_context.memory_stress_detected = false;
            // LOGIO("MemoryStressProtection: Memory stress resolved");
        }
    }
    
    // Check if memory cleanup is needed
    inline bool ShouldPerformCleanup() {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto cleanup_interval = std::chrono::duration_cast<std::chrono::minutes>(
            current_time - g_memory_context.last_cleanup).count();
        
        // Cleanup every 10 minutes or when memory stress is detected
        if (cleanup_interval >= 10 || g_memory_context.memory_stress_detected) {
            g_memory_context.last_cleanup = current_time;
            return true;
        }
        
        return false;
    }
    
    // Get memory stress level (0-3)
    inline int GetMemoryStressLevel() {
        if (!g_memory_protection_initialized) return 0;
        
        int stress_level = 0;
        
        // Level 1: High enemy/vehicle count
        if (g_memory_context.max_enemies_seen >= 10 || g_memory_context.max_vehicles_seen >= 3) {
            stress_level = 1;
        }
        
        // Level 2: Extended gameplay
        if (g_memory_context.extended_gameplay_mode) {
            stress_level = 2;
        }
        
        // Level 3: Active memory stress
        if (g_memory_context.memory_stress_detected) {
            stress_level = 3;
        }
        
        return stress_level;
    }
    
    // Get recommended render limits based on stress level
    inline void GetRecommendedLimits(int& max_enemies, int& max_vehicles, float& max_distance) {
        int stress_level = GetMemoryStressLevel();
        
        switch (stress_level) {
            case 0: // Normal
                max_enemies = 20;
                max_vehicles = 5;
                max_distance = 350.0f;
                break;
                
            case 1: // High load
                max_enemies = 15;
                max_vehicles = 4;
                max_distance = 300.0f;
                break;
                
            case 2: // Extended gameplay
                max_enemies = 12;
                max_vehicles = 3;
                max_distance = 250.0f;
                break;
                
            case 3: // Memory stress
                max_enemies = 8;
                max_vehicles = 2;
                max_distance = 200.0f;
                break;
        }
    }
    
    // DISABLED: Memory stress crash handler system dinonaktifkan
    // Sistem setjmp/longjmp tidak berfungsi karena signal handler tidak di-install
    // Mengandalkan simple signal handler protection dari ESP level

    /*
    // Memory stress crash handler - DISABLED
    static jmp_buf memory_stress_jump_buf;
    static bool memory_stress_handler_active = false;

    static void memory_stress_crash_handler(int sig) {
        if (memory_stress_handler_active && (sig == SIGSEGV || sig == SIGABRT)) {
            // LOGIO("MEMORY STRESS CRASH: signal=%d, stress_level=%d, frames=%d",
                  // sig, GetMemoryStressLevel(), g_memory_context.total_frames);
            longjmp(memory_stress_jump_buf, 1);
        }
    }
    */

    // Setup memory stress protection - SIMPLIFIED
    inline bool SetupMemoryStressProtection() {
        // DISABLED: Tidak ada crash protection khusus, mengandalkan ESP level protection
        return (GetMemoryStressLevel() >= 2);
    }

    // Cleanup memory stress protection - SIMPLIFIED
    inline void CleanupMemoryStressProtection(sighandler_t old_sigsegv, sighandler_t old_sigabrt) {
        // DISABLED: Tidak ada cleanup yang diperlukan
    }

    // Check if memory stress jump should be used - DISABLED
    inline bool ShouldUseMemoryStressJump() {
        return false; // DISABLED: setjmp/longjmp system tidak aktif
    }
    
    // Get memory stress statistics
    inline std::string GetMemoryStressStats() {
        auto current_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::minutes>(
            current_time - g_memory_context.start_time).count();
        
        char stats[512];
        snprintf(stats, sizeof(stats),
                "MemoryStress Stats: Duration=%ldmin, Frames=%d, MaxEnemies=%d, MaxVehicles=%d, "
                "HighLoadFrames=%d, StressLevel=%d, ExtendedMode=%s, MemoryStress=%s",
                duration, g_memory_context.total_frames,
                g_memory_context.max_enemies_seen, g_memory_context.max_vehicles_seen,
                g_memory_context.high_load_frames, GetMemoryStressLevel(),
                g_memory_context.extended_gameplay_mode ? "YES" : "NO",
                g_memory_context.memory_stress_detected ? "YES" : "NO");
        
        return std::string(stats);
    }
    
    // Log memory stress status (call periodically)
    inline void LogMemoryStressStatus() {
        static int log_counter = 0;
        if (++log_counter % 1800 == 0) { // Every 60 seconds at 30fps
            // LOGIO("MemoryStressProtection: %s", GetMemoryStressStats().c_str());
            log_counter = 0;
        }
    }
}

#endif // ARCAMOD_MEMORY_STRESS_PROTECTION_H
