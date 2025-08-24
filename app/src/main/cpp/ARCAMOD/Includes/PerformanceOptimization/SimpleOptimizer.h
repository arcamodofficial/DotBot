//
// ARCAMOD Simple Performance Optimizer
// Optimasi sederhana yang tidak bergantung pada komponen yang di-disable
//

#ifndef ARCAMOD_SIMPLE_OPTIMIZER_H
#define ARCAMOD_SIMPLE_OPTIMIZER_H

#include <chrono>
#include <atomic>

// Include hanya komponen yang aktif
#include "../../CoreDefines/Config/ConfigManager.h"  // For // LOGIO macro
#include "../STB/stb_optimization.h"      // STB image optimization
#include "../Logger/backends/Logger.h"    // Optimized logging

namespace SimpleOptimizer {
    
    // Simple performance context (tanpa atomic yang kompleks)
    struct SimplePerformanceContext {
        bool optimization_enabled = true;
        int performance_level = 1;  // 0=disabled, 1=normal, 2=aggressive
        long total_memory_saved = 0;
        long total_time_saved = 0;
        int cache_hits = 0;
        int cache_misses = 0;
        bool image_cache_active = false;
        bool logging_optimized = false;
    };
    
    static SimplePerformanceContext g_simple_perf_context;
    static bool g_simple_optimizer_initialized = false;
    
    // Initialize simple optimizations
    inline void Initialize() {
        if (g_simple_optimizer_initialized) return;
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Initializing simple performance optimizations...");
        #endif
        
        // Preload common images
        ArcamodSTB::PreloadCommonImages();
        g_simple_perf_context.image_cache_active = true;
        
        // Mark logging as optimized
        g_simple_perf_context.logging_optimized = ARCAMOD_LOG_ENABLED;
        
        g_simple_optimizer_initialized = true;
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Initialization completed successfully");
        #endif
    }
    
    // Set performance level (0=disabled, 1=normal, 2=aggressive)
    inline void SetPerformanceLevel(int level) {
        if (level < 0 || level > 2) return;
        
        g_simple_perf_context.performance_level = level;
        g_simple_perf_context.optimization_enabled = (level > 0);
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Performance level set to %d", level);
        #endif
    }
    
    // Get current performance level
    inline int GetPerformanceLevel() {
        return g_simple_perf_context.performance_level;
    }
    
    // Check if optimizations should be applied
    inline bool ShouldOptimize() {
        return g_simple_perf_context.optimization_enabled;
    }
    
    // Simple memory optimization
    inline void OptimizeMemoryUsage() {
        if (!ShouldOptimize()) return;
        
        int level = GetPerformanceLevel();
        
        switch (level) {
            case 1: // Normal optimization
                // Clear image cache if it's getting full
                if (ArcamodSTB::GetCacheUsage() >= 6) {
                    ArcamodSTB::ClearImageCache();
                    g_simple_perf_context.total_memory_saved += 1024 * 1024; // Estimate 1MB saved
                    #ifdef DEBUG
                    // LOGIO("SimpleOptimizer: Cleared image cache (normal mode)");
                    #endif
                }
                break;
                
            case 2: // Aggressive optimization
                // More aggressive memory cleanup
                ArcamodSTB::ClearImageCache();
                g_simple_perf_context.total_memory_saved += 2 * 1024 * 1024; // Estimate 2MB saved
                #ifdef DEBUG
                // LOGIO("SimpleOptimizer: Cleared image cache (aggressive mode)");
                #endif
                break;
        }
    }
    
    // Frame-based optimization (call once per frame)
    inline void OptimizePerFrame() {
        if (!g_simple_optimizer_initialized) Initialize();
        if (!ShouldOptimize()) return;
        
        static int frame_count = 0;
        frame_count++;
        
        // Periodic memory optimization (every 5 seconds at 60fps)
        if (frame_count % 300 == 0) {
            OptimizeMemoryUsage();
        }
    }
    
    // Get simple performance statistics
    inline std::string GetPerformanceStats() {
        if (!g_simple_optimizer_initialized) return "Not initialized";
        
        char stats[256];
        snprintf(stats, sizeof(stats),
                "Simple Performance Stats:\n"
                "Level: %d | Enabled: %s\n"
                "Image Cache: %s | Logging: %s\n"
                "Memory Saved: %ld KB | Time Saved: %ld ms\n"
                "Cache Hits: %d | Cache Misses: %d",
                GetPerformanceLevel(),
                ShouldOptimize() ? "YES" : "NO",
                g_simple_perf_context.image_cache_active ? "ON" : "OFF",
                g_simple_perf_context.logging_optimized ? "ON" : "OFF",
                g_simple_perf_context.total_memory_saved / 1024,
                g_simple_perf_context.total_time_saved,
                g_simple_perf_context.cache_hits,
                g_simple_perf_context.cache_misses);
        
        return std::string(stats);
    }
    
    // Emergency performance mode (simplified)
    inline void EnableEmergencyMode() {
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: EMERGENCY PERFORMANCE MODE ACTIVATED");
        #endif
        
        SetPerformanceLevel(2);
        
        // Aggressive cleanup
        ArcamodSTB::ClearImageCache();
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Emergency mode activated - aggressive optimizations enabled");
        #endif
    }
    
    // Disable emergency mode
    inline void DisableEmergencyMode() {
        SetPerformanceLevel(1);
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Emergency mode disabled - normal performance restored");
        #endif
    }
    
    // Cleanup all optimizations
    inline void Cleanup() {
        if (!g_simple_optimizer_initialized) return;
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Cleaning up simple performance optimizer...");
        #endif
        
        // Clear caches
        ArcamodSTB::ClearImageCache();
        
        // Reset context
        g_simple_perf_context = SimplePerformanceContext{};
        g_simple_optimizer_initialized = false;
        
        #ifdef DEBUG
        // LOGIO("SimpleOptimizer: Cleanup completed");
        #endif
    }
    
    // Simple performance monitoring macros
    #ifdef DEBUG
        #define SIMPLE_PERF_MONITOR_START() \
            auto simple_perf_start = std::chrono::high_resolution_clock::now();
        
        #define SIMPLE_PERF_MONITOR_END(operation_name) \
            auto simple_perf_end = std::chrono::high_resolution_clock::now(); \
            auto simple_perf_duration = std::chrono::duration_cast<std::chrono::microseconds>(simple_perf_end - simple_perf_start); \
            SimpleOptimizer::g_simple_perf_context.total_time_saved += simple_perf_duration.count(); \
            // LOGIO("PERF: %s took %ld microseconds", operation_name, simple_perf_duration.count());
        
        // Cache hit/miss tracking
        #define SIMPLE_CACHE_HIT() \
            SimpleOptimizer::g_simple_perf_context.cache_hits++;
        
        #define SIMPLE_CACHE_MISS() \
            SimpleOptimizer::g_simple_perf_context.cache_misses++;
    #else
        #define SIMPLE_PERF_MONITOR_START() ((void)0)
        #define SIMPLE_PERF_MONITOR_END(operation_name) ((void)0)
        #define SIMPLE_CACHE_HIT() ((void)0)
        #define SIMPLE_CACHE_MISS() ((void)0)
    #endif
    
    // Simple image loading with optimization
    inline unsigned char* LoadImageOptimized(const char* filename, int* x, int* y, int* comp, int req_comp) {
        SIMPLE_PERF_MONITOR_START();
        
        unsigned char* result = ArcamodSTB::LoadImageOptimized(filename, x, y, comp, req_comp);
        
        if (result) {
            SIMPLE_CACHE_HIT();
        } else {
            SIMPLE_CACHE_MISS();
        }
        
        SIMPLE_PERF_MONITOR_END("LoadImageOptimized");
        return result;
    }
    
    // Simple memory copy optimization (untuk KittyMemory yang sudah dioptimasi)
    inline void* OptimizedMemCpy(void* dest, const void* src, size_t len) {
        SIMPLE_PERF_MONITOR_START();
        
        // KittyMemory::MemCpy sudah dioptimasi, gunakan langsung
        void* result = dest;
        if (dest && src && len > 0) {
            if (len >= 64) {
                result = memcpy(dest, src, len);
            } else {
                // Untuk copy kecil, gunakan implementasi yang sudah ada
                char *d = reinterpret_cast<char *>(dest);
                const char *s = reinterpret_cast<const char *>(src);
                while (len--) {
                    *d++ = *s++;
                }
            }
        }
        
        SIMPLE_PERF_MONITOR_END("OptimizedMemCpy");
        return result;
    }
}

// Global convenience macros untuk simple optimizer
#define SIMPLE_INIT_PERFORMANCE() \
    SimpleOptimizer::Initialize()

#define SIMPLE_OPTIMIZE_FRAME() \
    SimpleOptimizer::OptimizePerFrame()

#define SIMPLE_SET_PERFORMANCE_LEVEL(level) \
    SimpleOptimizer::SetPerformanceLevel(level)

#define SIMPLE_EMERGENCY_MODE() \
    SimpleOptimizer::EnableEmergencyMode()

#define SIMPLE_CLEANUP_PERFORMANCE() \
    SimpleOptimizer::Cleanup()

#define SIMPLE_LOAD_IMAGE(filename, x, y, comp, req_comp) \
    SimpleOptimizer::LoadImageOptimized(filename, x, y, comp, req_comp)

#endif // ARCAMOD_SIMPLE_OPTIMIZER_H
