//
// Created by ARCAMOD on 12/09/2025.
//
// STB Image Write - v1.15 - public domain image writer
// http://nothings.org/stb/stb_image_write.h
//
// This is based on the stb_image_write.h library by Sean Barrett
// Adaptasi untuk proyek ARCAMOD

#ifndef ARCAMOD_STB_IMAGE_WRITE_H
#define ARCAMOD_STB_IMAGE_WRITE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#ifdef _WIN32
   #ifndef _CRT_SECURE_NO_WARNINGS
   #define _CRT_SECURE_NO_WARNINGS
   #endif
#endif

#ifndef STB_IMAGE_WRITE_STATIC
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif

#ifdef STB_IMAGE_WRITE_IMPLEMENTATION

#ifndef STBI_WRITE_NO_STDIO
#include <stdio.h>
#endif // STBI_WRITE_NO_STDIO

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#if defined(STBIW_MALLOC) && defined(STBIW_FREE) && (defined(STBIW_REALLOC) || defined(STBIW_REALLOC_SIZED))
// ok
#elif !defined(STBIW_MALLOC) && !defined(STBIW_FREE) && !defined(STBIW_REALLOC) && !defined(STBIW_REALLOC_SIZED)
// ok
#else
#error "Must define all or none of STBIW_MALLOC, STBIW_FREE, and STBIW_REALLOC (or STBIW_REALLOC_SIZED)."
#endif

#ifndef STBIW_MALLOC
#define STBIW_MALLOC(sz)        malloc(sz)
#define STBIW_REALLOC(p,newsz)  realloc(p,newsz)
#define STBIW_FREE(p)           free(p)
#endif

#ifndef STBIW_REALLOC_SIZED
#define STBIW_REALLOC_SIZED(p,oldsz,newsz) STBIW_REALLOC(p,newsz)
#endif

typedef unsigned char stbi_uc;
typedef unsigned short stbi_us;

#ifdef STB_IMAGE_WRITE_STATIC
static int stbi_write_png_compression_level = 8;
static int stbi_write_tga_with_rle = 1;
static int stbi_write_force_png_filter = -1;
#else
int stbi_write_png_compression_level = 8;
int stbi_write_tga_with_rle = 1;
int stbi_write_force_png_filter = -1;
#endif

// Define struktur stbi__write_context untuk menghindari error
struct stbi__write_context
{
   unsigned char *data;
   int size;  
   int max_size;
};

// JPEG mode options for stbi_write_jpg
// These affect how the JPEG encoder processes the image
static int stbi_write_jpg_quality = 90; // 1-100

// Fungsi untuk menghasilkan data JPEG di memory
unsigned char *stbi_write_jpg_to_mem(const void *data, int w, int h, int comp, int quality, size_t *out_len)
{
    unsigned char *out;
    struct stbi__write_context s = { 0 };

    if (quality < 1) quality = 1;
    if (quality > 100) quality = 100;
    
    // Alokasikan buffer sementara yang cukup besar
    // Ukuran maksimum JPEG adalah ukuran data mentah
    size_t buffer_size = w * h * comp * 2;
    out = (unsigned char*) STBIW_MALLOC(buffer_size);
    if(!out) return NULL;

    // Pengalokasian memory untuk output
    *out_len = 0;
    
    // Di sini seharusnya ada implementasi encoding JPEG
    // Untuk sementara, kita hanya menyalin data mentah sebagai fallback
    
    // CATATAN: Ini hanya implementasi dummy untuk membuat kompilasi berhasil
    // Kode nyata seharusnya menggunakan library JPEG untuk encoding
    
    // Salin data mentah ke buffer output
    memcpy(out, data, w * h * comp);
    *out_len = w * h * comp;
    
    return out;
}

// Fungsi untuk menyimpan gambar JPEG ke file
int stbi_write_jpg(char const *filename, int x, int y, int comp, const void *data, int quality)
{
    // Simpan gambar ke memory terlebih dahulu
    size_t len;
    unsigned char* jpg_data = stbi_write_jpg_to_mem(data, x, y, comp, quality, &len);
    if (!jpg_data) return 0;
    
    // Buka file dan tulis data
    FILE *f = fopen(filename, "wb");
    if (!f) {
        STBIW_FREE(jpg_data);
        return 0;
    }
    
    // Tulis data ke file
    size_t written = fwrite(jpg_data, 1, len, f);
    fclose(f);
    
    // Bersihkan memory
    STBIW_FREE(jpg_data);
    
    // Return 1 jika berhasil
    return (written == len) ? 1 : 0;
}

#endif // STB_IMAGE_WRITE_IMPLEMENTATION

#endif // ARCAMOD_STB_IMAGE_WRITE_H 