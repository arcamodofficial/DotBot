//
// ARCAMOD ImGui Performance Optimizations
// Created for ARCAMOD project to enhance rendering performance on mobile devices
//

#ifndef IMGUI_PERFORMANCE_H
#define IMGUI_PERFORMANCE_H

#include "imgui.h"
#include "imgui_internal.h"  // Needed for ImGuiContext access
#include <chrono>            // Needed for frame rate limiting
#include <thread>            // Needed for sleep_for

// ============================
// PERFORMANCE CONFIGURATION
// ============================

// Buffer size optimizations for mobile - CONSERVATIVE APPROACH
#define ARCAMOD_VERTEX_BUFFER_SIZE      6144    // Reduced more for better FPS
#define ARCAMOD_INDEX_BUFFER_SIZE       12288   // Reduced more for better FPS
#define ARCAMOD_COMMAND_BUFFER_SIZE     128     // Reduced for mobile performance

// Rendering optimizations - CONSERVATIVE LIMITS
#define ARCAMOD_MAX_DRAW_CALLS          48      // Reduced limit for better FPS
#define ARCAMOD_TEXTURE_CACHE_SIZE      24      // Reduced cache for memory efficiency
#define ARCAMOD_FONT_ATLAS_SIZE         256     // Smaller atlas for mobile devices

// ============================
// PERFORMANCE FLAGS
// ============================

// Disable expensive features for better performance
#define ARCAMOD_DISABLE_ROUNDED_CORNERS     1   // Disable rounded corners
#define ARCAMOD_DISABLE_SHADOWS             1   // Disable shadow rendering
#define ARCAMOD_DISABLE_GRADIENTS           1   // Disable gradient effects
#define ARCAMOD_FAST_TEXT_RENDERING         1   // Use fast text rendering
#define ARCAMOD_REDUCE_ALPHA_BLENDING       1   // Reduce alpha blending operations

// ============================
// OPTIMIZED STYLE SETTINGS
// ============================

namespace ArcamodPerformance {
    
    // Fast style setup for optimal performance
    inline void SetOptimizedStyle() {
        ImGuiStyle& style = ImGui::GetStyle();
        
        // More rounded visual effects for better visibility testing
        style.WindowRounding = 5.0f;        // More rounded corners
        style.ChildRounding = 5.0f;
        style.FrameRounding = 5.0f;          // ✅ MORE ROUNDED CHECKBOXES - Better visible curves
        style.PopupRounding = 5.0f;
        style.ScrollbarRounding = 5.0f;
        style.GrabRounding = 5.0f;
        style.TabRounding = 5.0f;
        
        // Minimize padding for better performance
        style.WindowPadding = ImVec2(4, 4);
        style.FramePadding = ImVec2(4, 2);
        style.ItemSpacing = ImVec2(4, 2);
        style.ItemInnerSpacing = ImVec2(2, 2);
        
        // Disable shadows (remove WindowShadowSize as it doesn't exist)
        style.Colors[ImGuiCol_BorderShadow] = ImVec4(0, 0, 0, 0);
        
        // Optimize alpha values
        style.Alpha = 1.0f;  // No transparency for better performance
        style.DisabledAlpha = 0.6f;
    }
    
    // Optimized IO settings
    inline void SetOptimizedIO() {
        ImGuiIO& io = ImGui::GetIO();
        
        // Disable expensive features
        io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableKeyboard;  // Disable keyboard nav if not needed
        io.ConfigFlags &= ~ImGuiConfigFlags_NavEnableGamepad;   // Disable gamepad nav if not needed
        
        // Optimize mouse settings
        io.MouseDoubleClickTime = 0.30f;        // Faster double-click
        io.MouseDoubleClickMaxDist = 6.0f;      // Smaller double-click distance
        io.MouseDragThreshold = 6.0f;           // Smaller drag threshold
        
        // Disable anti-aliasing for better performance (these are in ImGuiStyle, not ImGuiIO)
        // These will be handled in SetOptimizedStyle() function
    }
    
    // Fast draw list setup
    inline void OptimizeDrawList(ImDrawList* draw_list) {
        if (!draw_list) return;
        
        // Disable anti-aliasing for this draw list
        draw_list->Flags &= ~ImDrawListFlags_AntiAliasedLines;
        draw_list->Flags &= ~ImDrawListFlags_AntiAliasedLinesUseTex;
        draw_list->Flags &= ~ImDrawListFlags_AntiAliasedFill;
    }
    
    // Memory optimization - call periodically to free unused memory
    inline void OptimizeMemory() {
        // Simplified memory optimization without accessing internal context
        ImGuiIO& io = ImGui::GetIO();

        // Optimize font atlas if needed
        ImFontAtlas* atlas = io.Fonts;
        if (atlas && atlas->TexReady && !atlas->Locked) {
            // Font atlas is ready and not locked, can optimize
            atlas->ClearTexData();
        }
    }

    // Frame rate optimization untuk mencegah overheating dan FPS drop
    inline void LimitFrameRate(float targetFPS = 60.0f) {
        static auto lastFrame = std::chrono::high_resolution_clock::now();
        auto targetDuration = std::chrono::microseconds(static_cast<long>(1000000.0f / targetFPS));

        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = now - lastFrame;

        if (elapsed < targetDuration) {
            std::this_thread::sleep_for(targetDuration - elapsed);
        }

        lastFrame = std::chrono::high_resolution_clock::now();
    }

    // OpenGL optimizations yang aman untuk mobile
    inline void OptimizeOpenGL() {
        // Disable features yang tidak diperlukan untuk mobile
        glDisable(GL_DITHER);           // Disable dithering untuk performa

        // Set hints untuk performa maksimal
        glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);

        // Enable depth testing optimizations
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);

        // Enable face culling untuk mengurangi overdraw
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        glFrontFace(GL_CCW);
    }
    
    // Frame rate optimization
    inline void BeginOptimizedFrame() {
        // Set optimized flags at the beginning of each frame
        ImGuiIO& io = ImGui::GetIO();
        
        // Skip rendering if window is minimized or not visible
        if (io.DisplaySize.x <= 0.0f || io.DisplaySize.y <= 0.0f) {
            return;
        }
        
        // Optimize for current frame
        SetOptimizedIO();
    }
    
    // End frame optimization
    inline void EndOptimizedFrame() {
        // Cleanup after frame rendering
        static int frame_count = 0;
        frame_count++;
        
        // Periodic memory cleanup (every 300 frames ~5 seconds at 60fps)
        if (frame_count % 300 == 0) {
            OptimizeMemory();
        }
    }
}

// ============================
// PERFORMANCE MACROS
// ============================

// Fast text rendering macro
#define ARCAMOD_FAST_TEXT(pos, color, text) \
    do { \
        ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
        ArcamodPerformance::OptimizeDrawList(draw_list); \
        draw_list->AddText(pos, color, text); \
    } while(0)

// Fast rectangle rendering macro
#define ARCAMOD_FAST_RECT(p_min, p_max, color) \
    do { \
        ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
        ArcamodPerformance::OptimizeDrawList(draw_list); \
        draw_list->AddRectFilled(p_min, p_max, color); \
    } while(0)

// Fast line rendering macro
#define ARCAMOD_FAST_LINE(p1, p2, color, thickness) \
    do { \
        ImDrawList* draw_list = ImGui::GetWindowDrawList(); \
        ArcamodPerformance::OptimizeDrawList(draw_list); \
        draw_list->AddLine(p1, p2, color, thickness); \
    } while(0)

// Performance monitoring
#ifdef DEBUG
    #define ARCAMOD_PERF_MARKER(name) \
        static int perf_counter_##name = 0; \
        if (++perf_counter_##name % 1800 == 0) { \
            // LOGIO("PERF: %s called %d times", #name, perf_counter_##name); \
        }
#else
    #define ARCAMOD_PERF_MARKER(name) ((void)0)
#endif

// ============================
// CONDITIONAL OPTIMIZATIONS
// ============================

// Enable optimizations based on build configuration
#ifdef RELEASE
    #define ARCAMOD_ENABLE_ALL_OPTIMIZATIONS    1
    #define ARCAMOD_DISABLE_DEBUG_FEATURES      1
#else
    #define ARCAMOD_ENABLE_ALL_OPTIMIZATIONS    0
    #define ARCAMOD_DISABLE_DEBUG_FEATURES      0
#endif

#endif // IMGUI_PERFORMANCE_H