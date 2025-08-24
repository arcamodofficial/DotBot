//
// ARCAMOD STB Image Loading Optimizations
// Created for ARCAMOD project to enhance image loading performance
//

#ifndef STB_OPTIMIZATION_H
#define STB_OPTIMIZATION_H

#include "stb_image.h"
#include <cstring>
#include <memory>

// ============================
// STB PERFORMANCE CONFIGURATION
// ============================

// Optimize STB for mobile performance
#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_PSD              // Disable PSD support (not needed for game)
#define STBI_NO_TGA              // Disable TGA support (not needed for game)
#define STBI_NO_GIF              // Disable GIF support (not needed for game)
#define STBI_NO_HDR              // Disable HDR support (not needed for game)
#define STBI_NO_PIC              // Disable PIC support (not needed for game)
#define STBI_NO_PNM              // Disable PNM support (not needed for game)

// Enable only essential formats for ARCAMOD
#define STBI_ONLY_JPEG           // Enable JPEG (common for textures)
#define STBI_ONLY_PNG            // Enable PNG (common for UI)
#define STBI_ONLY_BMP            // Enable BMP (simple format)

// Performance optimizations
#define STBI_MAX_DIMENSIONS      4096    // Limit max image size for mobile
#define STBI_MALLOC(sz)          malloc(sz)
#define STBI_REALLOC(p,newsz)    realloc(p,newsz)
#define STBI_FREE(p)             free(p)

namespace ArcamodSTB {
    
    // Image cache for frequently loaded images
    struct ImageCache {
        std::string filename;
        unsigned char* data;
        int width;
        int height;
        int channels;
        size_t data_size;
        bool is_valid;
        
        ImageCache() : data(nullptr), width(0), height(0), channels(0), 
                      data_size(0), is_valid(false) {}
        
        ~ImageCache() {
            if (data) {
                stbi_image_free(data);
                data = nullptr;
            }
        }
    };
    
    // Simple cache for up to 8 images (logos, UI elements)
    static ImageCache g_image_cache[8];
    static int g_cache_index = 0;
    
    // Fast image loading with caching
    inline unsigned char* LoadImageOptimized(const char* filename, int* x, int* y, int* comp, int req_comp) {
        if (!filename || !x || !y || !comp) return nullptr;
        
        // Check cache first
        for (int i = 0; i < 8; ++i) {
            if (g_image_cache[i].is_valid && g_image_cache[i].filename == filename) {
                *x = g_image_cache[i].width;
                *y = g_image_cache[i].height;
                *comp = g_image_cache[i].channels;
                
                // Return a copy of cached data
                size_t data_size = g_image_cache[i].data_size;
                unsigned char* copy = (unsigned char*)malloc(data_size);
                if (copy) {
                    memcpy(copy, g_image_cache[i].data, data_size);
                }
                return copy;
            }
        }
        
        // Load image if not in cache
        unsigned char* data = stbi_load(filename, x, y, comp, req_comp);
        if (!data) return nullptr;
        
        // Cache the image (replace oldest)
        ImageCache& cache_entry = g_image_cache[g_cache_index];
        
        // Clean up old cache entry
        if (cache_entry.data) {
            stbi_image_free(cache_entry.data);
        }
        
        // Store in cache
        cache_entry.filename = filename;
        cache_entry.width = *x;
        cache_entry.height = *y;
        cache_entry.channels = *comp;
        cache_entry.data_size = (*x) * (*y) * (*comp);
        cache_entry.data = (unsigned char*)malloc(cache_entry.data_size);
        cache_entry.is_valid = true;
        
        if (cache_entry.data) {
            memcpy(cache_entry.data, data, cache_entry.data_size);
        }
        
        // Move to next cache slot
        g_cache_index = (g_cache_index + 1) % 8;
        
        return data;
    }
    
    // Fast image loading from memory with size validation
    inline unsigned char* LoadImageFromMemoryOptimized(const unsigned char* buffer, int len, 
                                                       int* x, int* y, int* comp, int req_comp) {
        if (!buffer || len <= 0 || !x || !y || !comp) return nullptr;
        
        // Validate buffer size to prevent crashes
        if (len > 50 * 1024 * 1024) {  // 50MB limit for mobile
            return nullptr;
        }
        
        return stbi_load_from_memory(buffer, len, x, y, comp, req_comp);
    }
    
    // Optimized image info without loading full image
    inline bool GetImageInfoOptimized(const char* filename, int* x, int* y, int* comp) {
        if (!filename || !x || !y || !comp) return false;
        
        // Check cache first
        for (int i = 0; i < 8; ++i) {
            if (g_image_cache[i].is_valid && g_image_cache[i].filename == filename) {
                *x = g_image_cache[i].width;
                *y = g_image_cache[i].height;
                *comp = g_image_cache[i].channels;
                return true;
            }
        }
        
        // Use STB info function (faster than full load)
        return stbi_info(filename, x, y, comp) != 0;
    }
    
    // Clear image cache to free memory
    inline void ClearImageCache() {
        for (int i = 0; i < 8; ++i) {
            if (g_image_cache[i].data) {
                stbi_image_free(g_image_cache[i].data);
                g_image_cache[i].data = nullptr;
            }
            g_image_cache[i].is_valid = false;
            g_image_cache[i].filename.clear();
        }
        g_cache_index = 0;
    }
    
    // Get cache statistics
    inline int GetCacheUsage() {
        int used = 0;
        for (int i = 0; i < 8; ++i) {
            if (g_image_cache[i].is_valid) {
                used++;
            }
        }
        return used;
    }
    
    // Preload commonly used images
    inline void PreloadCommonImages() {
        // Preload logo images that are used frequently
        const char* common_images[] = {
            "logo.png",
            "icon.png",
            "background.jpg"
        };
        
        for (const char* img : common_images) {
            int x, y, comp;
            unsigned char* data = LoadImageOptimized(img, &x, &y, &comp, 0);
            if (data) {
                stbi_image_free(data);  // We just want it cached
            }
        }
    }
    
    // Memory-efficient image resizing (simple nearest neighbor)
    inline unsigned char* ResizeImageSimple(unsigned char* input, int input_w, int input_h, 
                                           int output_w, int output_h, int channels) {
        if (!input || input_w <= 0 || input_h <= 0 || output_w <= 0 || output_h <= 0 || channels <= 0) {
            return nullptr;
        }
        
        unsigned char* output = (unsigned char*)malloc(output_w * output_h * channels);
        if (!output) return nullptr;
        
        float x_ratio = (float)input_w / output_w;
        float y_ratio = (float)input_h / output_h;
        
        for (int y = 0; y < output_h; ++y) {
            for (int x = 0; x < output_w; ++x) {
                int src_x = (int)(x * x_ratio);
                int src_y = (int)(y * y_ratio);
                
                // Clamp to bounds
                src_x = (src_x >= input_w) ? input_w - 1 : src_x;
                src_y = (src_y >= input_h) ? input_h - 1 : src_y;
                
                int src_idx = (src_y * input_w + src_x) * channels;
                int dst_idx = (y * output_w + x) * channels;
                
                for (int c = 0; c < channels; ++c) {
                    output[dst_idx + c] = input[src_idx + c];
                }
            }
        }
        
        return output;
    }
}

// Convenience macros for optimized STB usage
#define ARCAMOD_LOAD_IMAGE(filename, x, y, comp, req_comp) \
    ArcamodSTB::LoadImageOptimized(filename, x, y, comp, req_comp)

#define ARCAMOD_LOAD_IMAGE_MEMORY(buffer, len, x, y, comp, req_comp) \
    ArcamodSTB::LoadImageFromMemoryOptimized(buffer, len, x, y, comp, req_comp)

#define ARCAMOD_GET_IMAGE_INFO(filename, x, y, comp) \
    ArcamodSTB::GetImageInfoOptimized(filename, x, y, comp)

#define ARCAMOD_CLEAR_IMAGE_CACHE() \
    ArcamodSTB::ClearImageCache()

#endif // STB_OPTIMIZATION_H
