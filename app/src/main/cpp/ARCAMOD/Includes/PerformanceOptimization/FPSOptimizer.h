#ifndef ARCAMOD_FPS_OPTIMIZER_H
#define ARCAMOD_FPS_OPTIMIZER_H

#include <chrono>
#include <android/log.h>

// LOGIO is defined globally in eConfig.h (via ARCAMOD/Includes.h)

namespace FPSOptimizer {
    
    // FPS monitoring context
    struct FPSContext {
        std::chrono::high_resolution_clock::time_point last_fps_check;
        std::chrono::high_resolution_clock::time_point session_start;
        int frame_count_since_check = 0;
        int total_frames = 0;
        float current_fps = 0.0f;
        float average_fps = 0.0f;
        float min_fps = 999.0f;
        float max_fps = 0.0f;
        bool fps_drop_detected = false;
        int fps_drop_count = 0;
        bool performance_mode = false;
    };
    
    static FPSContext g_fps_context;
    static bool g_fps_optimizer_initialized = false;
    
    // Initialize FPS optimizer
    inline void Initialize() {
        if (g_fps_optimizer_initialized) return;
        
        auto now = std::chrono::high_resolution_clock::now();
        g_fps_context.last_fps_check = now;
        g_fps_context.session_start = now;
        g_fps_optimizer_initialized = true;
        
        // LOGIO("FPSOptimizer: Initialized FPS monitoring and optimization");
    }
    
    // Update FPS tracking
    inline void UpdateFPS() {
        if (!g_fps_optimizer_initialized) Initialize();
        
        g_fps_context.frame_count_since_check++;
        g_fps_context.total_frames++;
        
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - g_fps_context.last_fps_check).count();
        
        // Calculate FPS every 1000ms (1 second)
        if (duration >= 1000) {
            g_fps_context.current_fps = (float)g_fps_context.frame_count_since_check / (duration / 1000.0f);
            
            // Update min/max FPS
            if (g_fps_context.current_fps < g_fps_context.min_fps) {
                g_fps_context.min_fps = g_fps_context.current_fps;
            }
            if (g_fps_context.current_fps > g_fps_context.max_fps) {
                g_fps_context.max_fps = g_fps_context.current_fps;
            }
            
            // Calculate average FPS
            auto session_duration = std::chrono::duration_cast<std::chrono::seconds>(
                now - g_fps_context.session_start).count();
            if (session_duration > 0) {
                g_fps_context.average_fps = (float)g_fps_context.total_frames / session_duration;
            }
            
            // Detect FPS drops
            bool fps_drop = g_fps_context.current_fps < 25.0f; // Below 25 FPS considered drop
            if (fps_drop && !g_fps_context.fps_drop_detected) {
                g_fps_context.fps_drop_detected = true;
                g_fps_context.fps_drop_count++;
                // LOGIO("FPSOptimizer: FPS DROP DETECTED - Current: %.1f, Average: %.1f, Drop Count: %d",
                      // g_fps_context.current_fps, g_fps_context.average_fps, g_fps_context.fps_drop_count);
            } else if (!fps_drop && g_fps_context.fps_drop_detected) {
                g_fps_context.fps_drop_detected = false;
                // LOGIO("FPSOptimizer: FPS RECOVERED - Current: %.1f, Average: %.1f",
                      // g_fps_context.current_fps, g_fps_context.average_fps);
            }
            
            // Reset counters
            g_fps_context.frame_count_since_check = 0;
            g_fps_context.last_fps_check = now;
        }
    }
    
    // Check if performance mode should be enabled
    inline bool ShouldEnablePerformanceMode() {
        if (!g_fps_optimizer_initialized) return false;
        
        // Enable performance mode if:
        // 1. Current FPS < 25
        // 2. Average FPS < 28
        // 3. Multiple FPS drops detected
        bool should_enable = (g_fps_context.current_fps < 25.0f) || 
                           (g_fps_context.average_fps < 28.0f) || 
                           (g_fps_context.fps_drop_count >= 3);
        
        if (should_enable && !g_fps_context.performance_mode) {
            g_fps_context.performance_mode = true;
            // LOGIO("FPSOptimizer: PERFORMANCE MODE ENABLED - FPS: %.1f, Avg: %.1f, Drops: %d",
                  // g_fps_context.current_fps, g_fps_context.average_fps, g_fps_context.fps_drop_count);
        } else if (!should_enable && g_fps_context.performance_mode) {
            g_fps_context.performance_mode = false;
            // LOGIO("FPSOptimizer: PERFORMANCE MODE DISABLED - FPS: %.1f, Avg: %.1f",
                  // g_fps_context.current_fps, g_fps_context.average_fps);
        }
        
        return g_fps_context.performance_mode;
    }
    
    // Get optimized render limits based on FPS
    inline void GetOptimizedLimits(int& max_enemies, int& max_vehicles, bool& skip_effects) {
        if (!g_fps_optimizer_initialized) {
            max_enemies = 20;
            max_vehicles = 5;
            skip_effects = false;
            return;
        }
        
        if (g_fps_context.performance_mode) {
            // Aggressive optimization for low FPS
            if (g_fps_context.current_fps < 20.0f) {
                max_enemies = 6;
                max_vehicles = 2;
                skip_effects = true;
            } else if (g_fps_context.current_fps < 25.0f) {
                max_enemies = 8;
                max_vehicles = 3;
                skip_effects = true;
            } else {
                max_enemies = 10;
                max_vehicles = 4;
                skip_effects = false;
            }
        } else {
            // Normal limits for good FPS
            max_enemies = 20;
            max_vehicles = 5;
            skip_effects = false;
        }
    }
    
    // Check if crash protection should be reduced for FPS
    inline bool ShouldReduceCrashProtection() {
        return g_fps_context.performance_mode && g_fps_context.current_fps < 22.0f;
    }
    
    // Get FPS statistics
    inline std::string GetFPSStats() {
        if (!g_fps_optimizer_initialized) return "FPS: Not initialized";
        
        char stats[256];
        snprintf(stats, sizeof(stats),
                "FPS: Current=%.1f, Avg=%.1f, Min=%.1f, Max=%.1f, Drops=%d, PerfMode=%s",
                g_fps_context.current_fps, g_fps_context.average_fps,
                g_fps_context.min_fps, g_fps_context.max_fps,
                g_fps_context.fps_drop_count,
                g_fps_context.performance_mode ? "ON" : "OFF");
        
        return std::string(stats);
    }
    
    // Log FPS status (call periodically)
    inline void LogFPSStatus() {
        static int log_counter = 0;
        if (++log_counter % 1800 == 0) { // Every 60 seconds at 30fps
            // LOGIO("FPSOptimizer: %s", GetFPSStats().c_str());
            log_counter = 0;
        }
    }
    
    // Reset FPS drop counter (call when entering new match)
    inline void ResetFPSDropCounter() {
        g_fps_context.fps_drop_count = 0;
        g_fps_context.fps_drop_detected = false;
        // LOGIO("FPSOptimizer: FPS drop counter reset for new session");
    }
    
    // Get current FPS
    inline float GetCurrentFPS() {
        return g_fps_context.current_fps;
    }
    
    // Get average FPS
    inline float GetAverageFPS() {
        return g_fps_context.average_fps;
    }
    
    // Check if FPS is stable
    inline bool IsFPSStable() {
        return g_fps_context.current_fps >= 28.0f && !g_fps_context.fps_drop_detected;
    }
    
    // Get performance recommendations
    inline std::string GetPerformanceRecommendations() {
        if (!g_fps_optimizer_initialized) return "Initialize FPS monitoring first";
        
        std::string recommendations;
        
        if (g_fps_context.current_fps < 20.0f) {
            recommendations += "CRITICAL: Reduce ESP features, limit enemies to 6, disable effects";
        } else if (g_fps_context.current_fps < 25.0f) {
            recommendations += "WARNING: Reduce enemy limit to 8, limit vehicles to 3";
        } else if (g_fps_context.current_fps < 28.0f) {
            recommendations += "CAUTION: Monitor performance, consider reducing limits";
        } else {
            recommendations += "GOOD: Performance is stable, normal limits OK";
        }
        
        if (g_fps_context.fps_drop_count >= 5) {
            recommendations += " | Consider enabling permanent performance mode";
        }
        
        return recommendations;
    }
}

#endif // ARCAMOD_FPS_OPTIMIZER_H
