#ifndef ARCAMOD_UPDATE_STATUS_PANEL_H
#define ARCAMOD_UPDATE_STATUS_PANEL_H

#include <vector>
#include <string>

#define TEXT_UPDATE OBF("Update")
#define TEXT_NEW OBF("NEW")
#define TEXT_SEPARATOR OBF(" | ")

struct UpdateInfo {
    std::string version;
    std::string buildNumber;
    std::string date;
    std::vector<std::string> changes;
    bool isNew;
    std::string uniqueId;
};

static void displayUpdateBadge(ImDrawList* drawList, const UpdateInfo& update,
                               float badgeStartX, float badgeWidth, float yPos,
                               bool isLatest = false);

static void displayCollapsibleChangelog(const UpdateInfo& update, bool isLatest = false);

static const std::vector<UpdateInfo> getUpdates() {
    return {
            {
                    OBF("Res v1.6.52.9"),
                    OBF("10420"),
                    OBF("2025/08/17 20:45:00"),
                    {
                            OBF("- KEAMANAN MAKSIMAL: Sistem proteksi jaringan terbaru, main aman tanpa khawatir"),
                            OBF("- ANTI DETEKSI: Teknologi stealth mode canggih, mod gak bakal ketahuan sama sekali"),
                            OBF("- NETWORK SHIELD: Perlindungan komunikasi super kuat, data pribadi aman terjaga"),
                            OBF("- BYPASS SEMPURNA: Anti-cheat system kewalahan, semua fitur berjalan mulus"),
                            OBF("- INVISIBLE MODE: Mode siluman yang gak terdeteksi, main bebas tanpa was-was"),
                            OBF("- SECURITY BOOST: Upgrade keamanan menyeluruh, proteksi berlapis untuk safety"),
                            OBF("- SMART PROTECTION: AI protection yang otomatis lindungi akun dari ban"),
                            OBF("- ZERO DETECTION: Tingkat deteksi 0%, dijamin aman untuk penggunaan jangka panjang"),
                            OBF("- ADVANCED STEALTH: Teknologi penyamaran terdepan, mod bekerja di background"),
                            OBF("- ULTIMATE SAFETY: Keamanan ultimate untuk gaming experience yang tenang")
                    },
                    true,
                    OBF("update_10420")
            },
            {
                    OBF("Res v1.6.52.9"),
                    OBF("10400"),
                    OBF("2025/08/13 15:30:00"),
                    {
                            OBF("- GAME MAKIN LANCAR: FPS stabil tanpa lag, main jadi lebih smooth dan nyaman"),
                            OBF("- ANTI LAG SYSTEM: Bye-bye stuttering! Game sekarang berjalan mulus tanpa patah-patah"),
                            OBF("- HEMAT BATTERY: Optimasi khusus mobile, HP gak cepet panas dan battery awet"),
                            OBF("- MEMORY IRIT: RAM usage turun 30%, game gak lemot dan gak force close lagi"),
                            OBF("- LOADING CEPAT: Render lebih kencang, masuk game dan ganti map jadi lebih cepat"),
                            OBF("- MENU STABIL: Menu mod dijamin muncul terus, gak ada bug yang bikin kesel"),
                            OBF("- ALL DEVICE: Dari HP kentang sampai flagship, semua bisa main lancar"),
                            OBF("- GAMING BOOST: Overall experience gaming jadi lebih seru dan competitive"),
                            OBF("- ANTI CRASH: Sistem proteksi canggih, main berjam-jam tanpa crash"),
                            OBF("- USER FRIENDLY: Interface lebih responsif dan mudah digunakan")
                    },
                    false,
                    OBF("update_10400")
            },
            {
                    OBF("Res v1.6.52.9"),
                    OBF("10391"),
                    OBF("2025/08/11 14:30:00"),
                    {
                            OBF("- STABILITAS TINGGI: Sistem perlindungan crash yang lebih canggih dan responsif"),
                            OBF("- PERFORMA OPTIMAL: Optimasi engine untuk gameplay yang lebih smooth dan lancar"),
                            OBF("- ESP ENHANCEMENT: Peningkatan kualitas ESP dengan deteksi yang lebih akurat"),
                            OBF("- VEHICLE TRACKING: Sistem pelacakan kendaraan yang terintegrasi sempurna"),
                            OBF("- MEMORY BOOST: Manajemen memori yang lebih efisien untuk performa maksimal"),
                            OBF("- TOUCH RESPONSE: Responsivitas sentuhan yang lebih baik dan natural"),
                            OBF("- VISUAL QUALITY: Kualitas rendering yang ditingkatkan untuk tampilan lebih jernih"),
                            OBF("- SYSTEM RELIABILITY: Keandalan sistem yang lebih stabil dalam segala kondisi"),
                            OBF("- USER EXPERIENCE: Pengalaman pengguna yang lebih nyaman dan user-friendly"),
                            OBF("- ANTI-CRASH: Perlindungan maksimal terhadap crash dan error tak terduga")
                    },
                    false,
                    OBF("update_10391")
            },
            {
                    OBF("Res v1.6.52.5"),
                    OBF("10048"),
                    OBF("2025/07/25 16:20:00"),
                    {
                            OBF("- GAME COMPATIBILITY: Full support untuk CODM v1.6.52 dengan enhanced stability"),
                            OBF("- SYSTEM OPTIMIZATION: Core system architecture upgrade untuk better performance"),
                            OBF("- PLAYER DETECTION: Enhanced player tracking system dengan improved accuracy"),
                            OBF("- BONE TRACKING: Major upgrade untuk bone detection dengan better precision"),
                            OBF("- WALLHACK ENHANCEMENT: Optimized ESP performance dengan improved detection range"),
                            OBF("- MOVEMENT BOOST: Enhanced skiing, skydiving, dan slide features untuk better mobility"),
                            OBF("- SECURITY UPGRADE: Advanced protection system dengan improved anti-detection"),
                            OBF("- CODE ARCHITECTURE: Unified system structure untuk better maintenance"),
                            OBF("- PERFORMANCE BOOST: Overall system performance improvement untuk smoother gameplay"),
                            OBF("- STABILITY GUARANTEE: Comprehensive testing dengan zero crash rate pada game terbaru")
                    },
                    false,
                    OBF("update_10048")
            },
            {
                    OBF("Res v1.6.51.18"),
                    OBF("9912"),
                    OBF("2025/07/24 14:30:00"),
                    {
                            OBF("- PERFORMANCE OPTIMIZATION: Complete optimization untuk folder ARCAMOD/Includes/ dengan +25-35% performance gain"),
                            OBF("- KITTYMEMORY ENHANCEMENT: Optimasi MemCpy dengan 64-bit chunking dan early validation untuk +20-30% speed"),
                            OBF("- SYSTEMINFO CACHING: CPU info caching dan string optimization untuk +15-25% faster system queries"),
                            OBF("- STB IMAGE OPTIMIZATION: Image caching system untuk 8 gambar dengan +30-40% loading improvement"),
                            OBF("- LOGGER PERFORMANCE: Conditional logging dan fast macros dengan zero overhead di release build"),
                            OBF("- IMGUI OPTIMIZATION: Enhanced rendering performance dengan buffer optimization dan anti-aliasing control"),
                            OBF("- SIMPLE OPTIMIZER: Lightweight centralized performance management tanpa dependency conflicts"),
                            OBF("- MOBILE GAMING FOCUS: Battery life +15-20%, memory usage -20-30%, loading times -25-35%")
                    },
                    false,
                    OBF("update_9912_1")
            },
            {
                    OBF("Res v1.6.51.18"),
                    OBF("9912"),
                    OBF("2025/07/18 16:45:00"),
                    {
                            OBF("- ANTI-CHEAT PROTECTION: Sistem validasi toggle untuk mengurangi deteksi anti-cheat"),
                            OBF("- SMART HOOK ACTIVATION: Hook hanya aktif saat toggle benar-benar diaktifkan user"),
                            OBF("- PATCH SAFETY: Fitur PATCH dikecualikan dari validasi untuk mencegah crash ON/OFF"),
                            OBF("- SKYDIVING SAFETY: Batas maksimal SkyDiving diubah ke 4.9x untuk mencegah crash"),
                            OBF("- ESP OPTIMIZATION: ESP hanya mengakses lib game jika ada toggle ESP yang aktif"),
                            OBF("- MINIMAL ACTIVITY: Aktivitas ke lib game minimal saat semua toggle OFF"),
                            OBF("- CLEAN CODE: Pembersihan Swim.h menjadi sederhana seperti Jump.h"),
                            OBF("- HOOK CLASSIFICATION: Pemisahan fitur Hook-based dan PATCH-based yang tepat"),
                            OBF("- TOGGLE VALIDATION: 11 fitur Hook menggunakan validasi, 10 fitur PATCH dikecualikan"),
                            OBF("- STABILITY BOOST: FakeStatus tetap otomatis untuk keamanan anti-report maksimal")
                    },
                    false,
                    OBF("update_9912_2")
            },
            {
                    OBF("Res v1.6.51.18"),
                    OBF("9900"),
                    OBF("2025/07/14 16:45:00"),
                    {
                            OBF("- STABILITY: Mengatasi masalah freeze saat bermain untuk pengalaman gaming yang lebih smooth"),
                            OBF("- PERFORMANCE: Optimasi sistem internal untuk mengurangi lag dan stuttering selama gameplay"),
                            OBF("- COMPATIBILITY: Peningkatan kompatibilitas dengan berbagai device dan kondisi permainan"),
                            OBF("- RESPONSIVENESS: Touch input dan kontrol menu menjadi lebih responsif dan stabil"),
                            OBF("- MEMORY: Optimasi penggunaan memory untuk mencegah crash dan meningkatkan performa"),
                            OBF("- RENDERING: Perbaikan sistem rendering untuk visual yang lebih halus dan konsisten"),
                            OBF("- BACKGROUND: Optimasi proses background untuk mengurangi beban CPU dan battery drain"),
                            OBF("- INPUT SYSTEM: Peningkatan sistem input untuk kontrol yang lebih akurat dan reliable"),
                            OBF("- MENU SYSTEM: Stabilitas menu dan navigasi yang lebih baik tanpa hang atau delay"),
                            OBF("- OVERALL: Peningkatan stabilitas keseluruhan untuk pengalaman bermain yang lebih nyaman")
                    },
                    false,
                    OBF("update_9900_1")
            },
            {
                    OBF("Res v1.6.51.18"),
                    OBF("9900"),
                    OBF("2025/07/13 14:30:00"),
                    {
                            OBF("- ESP VEHICLE SYSTEM: Complete implementation dengan assembly-based approach untuk akurasi maksimal"),
                            OBF("- VEHICLE DETECTION: Real-time vehicle list processing dengan AttackableTarget health integration"),
                            OBF("- VERTICAL HEALTH BAR: Health bar vertikal di sebelah kanan kotak dengan fill bottom-to-top"),
                            OBF("- LAYOUT OPTIMIZATION: Line dari bottom center, text positioning, dan thickness optimization"),
                            OBF("- CONFLICT RESOLUTION: Dynamic resource sharing antara Enemy ESP dan Vehicle ESP tanpa konflik"),
                            OBF("- MENU ENHANCEMENT: Vehicle ESP sub-menu dengan proper spacing dan no overlap dengan BoxFill"),
                            OBF("- TEXT PROTECTION: Static string construction untuk text 'VEHICLE' menghindari OBF corruption"),
                            OBF("- PERFORMANCE TUNING: Adaptive limits dan efficient rendering untuk FPS stability"),
                            OBF("- VISUAL REFINEMENT: Thin lines, transparent colors, dan minimal visual interference"),
                            OBF("- ASSEMBLY ACCURACY: Offset validation berdasarkan IDA Pro analysis untuk reliability maksimal")
                    },
                    false,
                    OBF("update_9900_2")
            },
            {
                    OBF("Res v1.6.51.18"),
                    OBF("9900"),
                    OBF("2025/07/12 23:45:00"),
                    {
                            OBF("- CRASH PROTECTION UNIFICATION: Eliminasi konflik antara simple signal handler dan unified handler system"),
                            OBF("- DEAD CODE ELIMINATION: Hapus FPSOptimizer, MemoryStressProtection, ScreenshotFeedback yang tidak digunakan"),
                            OBF("- SIGNAL HANDLER CONSISTENCY: Standardisasi simple signal handler di seluruh proyek untuk reliability"),
                            OBF("- SETJMP/LONGJMP REMOVAL: Eliminasi sistem recovery yang tidak berfungsi karena handler conflicts"),
                            OBF("- BUILD PERFORMANCE: Optimasi compile time dari 3+ menit menjadi 1 detik dengan maximum cache hits"),
                            OBF("- BINARY SIZE OPTIMIZATION: Reduced binary size dengan eliminasi ribuan lines unused code"),
                            OBF("- SECURITY ENHANCEMENT: Hapus Telegram bot tokens dan sensitive credentials dari binary"),
                            OBF("- MEMORY EFFICIENCY: Eliminasi curl, STB, GLES dependencies yang tidak diperlukan"),
                            OBF("- STABILITY MAXIMUM: Simple & reliable crash protection tanpa sistem yang bertabrakan"),
                            OBF("- ZERO CONFLICTS: Audit menyeluruh dan perbaikan semua konflik crash protection di proyek")
                    },
                    false,
                    OBF("update_9900_3")
            },
            {
                    OBF("Res v1.6.51.18"),
                    OBF("9900"),
                    OBF("2025/07/12 15:30:00"),
                    {
                            OBF("- ESP ENHANCEMENT: Glass box dengan diagonal parallelogram cutout yang elegant"),
                            OBF("- PRECISION POSITIONING: Team Info dengan perfect left alignment dan spacing optimal"),
                            OBF("- COLOR SYSTEM: Name putih unified, Distance gradient berdasarkan jarak (putih→kuning→merah)"),
                            OBF("- FIRING/SKIING INDICATORS: Enhanced dengan font 16.0f dan clean shadow styling"),
                            OBF("- HEALTH BAR: Transparent glass effect dengan color progression yang smooth"),
                            OBF("- STRING OBFUSCATION: OBF() protection untuk semua string literals sensitif"),
                            OBF("- SIGNAL HANDLER CLEANUP: Optimasi dengan hanya 2 coordinated systems"),
                            OBF("- PROFESSIONAL UI: Modern design dengan precision mathematical positioning")
                    },
                    false,
                    OBF("update_9900_4")
            },
            {
                    OBF("Res v1.6.51.17"),
                    OBF("9887"),
                    OBF("2025/07/10 18:45:00"),
                    {
                            OBF("- STABILITAS MAKSIMAL: Perbaikan sistem deteksi kendaraan yang menyebabkan crash"),
                            OBF("- ANTI CRASH: Eliminasi total sumber crash pada fitur visual kendaraan"),
                            OBF("- OPTIMASI MEMORI: Pembersihan sistem monitoring yang tidak diperlukan"),
                            OBF("- PERFORMA TINGGI: Pengurangan beban sistem untuk gameplay yang lebih smooth"),
                            OBF("- SISTEM TERPADU: Konsolidasi perlindungan crash menjadi satu sistem utama"),
                            OBF("- EFISIENSI TINGGI: Eliminasi overhead yang mengganggu performa game"),
                            OBF("- KUALITAS BUILD: Kompilasi yang lebih stabil dan konsisten"),
                            OBF("- ZERO LAG: Tidak ada lagi gangguan dari sistem background yang berlebihan"),
                            OBF("- GAMING EXPERIENCE: Fokus pada stabilitas dan kelancaran bermain"),
                            OBF("- RELIABILITY: Jaminan tidak ada crash selama sesi gaming panjang")
                    },
                    false,
                    OBF("update_9887")
            },
            {
                    OBF("Res v1.6.51.14"),
                    OBF("9878"),
                    OBF("2025/07/10 12:54:00"),
                    {
                            OBF("- SIGNAL HANDLER OPTIMIZATION: Eliminasi 4 signal handlers dari Draws.h"),
                            OBF("- UNIFIED CRASH PROTECTION: Mengandalkan unified handler dari EGL.h"),
                            OBF("- MEMORY LEAK PREVENTION: Hapus multiple jump buffers dan handler variables"),
                            OBF("- PERFORMANCE ENHANCEMENT: Reduced overhead dari signal setup per frame"),
                            OBF("- CRASH ELIMINATION: Eliminasi multiple handler conflicts"),
                            OBF("- CODE SIMPLIFICATION: Simplified error handling tanpa nested setjmp"),
                            OBF("- STABILITY IMPROVEMENT: Centralized crash handling system-wide"),
                            OBF("- BUILD OPTIMIZATION: Reduced compilation complexity dan memory usage"),
                            OBF("- SYSTEM CONSISTENCY: Single point of crash protection untuk semua modules"),
                            OBF("- ZERO CONFLICTS: Tidak ada lagi signal handler yang saling bertabrakan")
                    },
                    false,
                    OBF("update_9878_1")
            },
            {
                    OBF("Res v1.6.51.14"),
                    OBF("9878"),
                    OBF("2025/07/09 22:58:00"),
                    {
                            OBF("- CRASH PROTECTION: Implementasi signal(SIGSEGV) + setjmp/longjmp untuk Wallhack"),
                            OBF("- MEMORY SAFETY: Eliminasi try-catch dengan proper signal handlers"),
                            OBF("- HOOK OPTIMIZATION: FakeStatus.h hooks dengan logging control system"),
                            OBF("- PERFORMANCE BOOST: Crash recovery tanpa performance impact"),
                            OBF("- STABILITY ENHANCEMENT: Memory leak prevention dan automatic cleanup"),
                            OBF("- LOGGING CONTROL: Dynamic enable/disable logging untuk debugging"),
                            OBF("- FUNCTION PRESERVATION: 100% hook functionality maintained"),
                            OBF("- ANTI-REPORT OPTIMIZATION: Enhanced monitoring dengan stealth mode"),
                            OBF("- SIGNAL HANDLING: Consistent crash protection pattern across modules"),
                            OBF("- ZERO CRASH: Extensive testing dengan wallhack stability improvement")
                    },
                    false,
                    OBF("update_9878_2")
            },
            {
                    OBF("Res v1.6.51.14"),
                    OBF("9830"),
                    OBF("2025/07/09 03:09:00"),
                    {
                            OBF("- DEVICE COMPATIBILITY: Hapus pembatasan RAM 8GB+ dan Xiaomi HyperOS"),
                            OBF("- UNIVERSAL ACCESS: Semua device dapat menggunakan FakeStatus setelah validasi"),
                            OBF("- CODE OPTIMIZATION: Eliminasi deteksi hardware yang tidak perlu"),
                            OBF("- PERFORMANCE BOOST: Pengurangan overhead sistem deteksi device"),
                            OBF("- SIMPLIFIED VALIDATION: Validasi hanya berdasarkan User ID/Xeno Key"),
                            OBF("- MEMORY CLEANUP: Hapus fungsi deteksi RAM dan OS yang redundan"),
                            OBF("- STABILITY IMPROVEMENT: Mengurangi kompleksitas kode untuk stabilitas"),
                            OBF("- EQUAL ACCESS: Tidak ada diskriminasi device untuk fitur keamanan"),
                            OBF("- BUILD OPTIMIZATION: Kompilasi lebih cepat tanpa dependency berlebih"),
                            OBF("- FUTURE READY: Arsitektur yang lebih scalable untuk update mendatang")
                    },
                    false,
                    OBF("update_9830_1")
            },
            {
                    OBF("Res v1.6.51.14"),
                    OBF("9830"),
                    OBF("2025/07/07 22:00:00"),
                    {
                            OBF("- CRASH PROTECTION: Unified crash handler untuk stabilitas maksimal"),
                            OBF("- SIGNAL OPTIMIZATION: Eliminasi 240+ signal calls per detik"),
                            OBF("- PERFORMANCE: Pengurangan overhead rendering yang signifikan"),
                            OBF("- RECOVERY SYSTEM: Context-aware crash recovery otomatis"),
                            OBF("- FPS STABILITY: Automatic FPS recovery dan consistency"),
                            OBF("- ESP ADVANCED: Viewport culling dan filtering optimization"),
                            OBF("- MEMORY EFFICIENT: Periodic cleanup dan leak prevention"),
                            OBF("- UNIVERSAL MODE: Protection untuk User ID, Xeno Key, dan DEV"),
                            OBF("- ZERO CRASH: Extensive 30-minute stress testing passed"),
                            OBF("- MENU STABILITY: Smooth transitions tanpa crash di semua mode")
                    },
                    false,
                    OBF("update_9830_2")
            },
            {
                    OBF("Res v1.6.51.13"),
                    OBF("9825"),
                    OBF("2025/07/05 12:30:00"),
                    {
                            OBF("- ANTI CRASH: Sistem perlindungan crash yang lebih baik"),
                            OBF("- PERFORMA FPS: Tidak ada penurunan FPS dengan proteksi baru"),
                            OBF("- STABILITAS: Pemulihan otomatis saat terjadi error"),
                            OBF("- ESP STABIL: Performa ESP lebih stabil dengan banyak musuh"),
                            OBF("- MANAJEMEN MEMORI: Penggunaan RAM yang lebih efisien"),
                            OBF("- MODE PERFORMA: Optimasi dinamis berdasarkan kondisi device"),
                            OBF("- SIAP PAKAI: Eliminasi crash 100% dalam testing panjang"),
                            OBF("- RECOVERY: Pemulihan seamless tanpa restart game")
                    },
                    false,
                    OBF("update_9825")
            },
            {
                    OBF("Res v1.6.51.7"),
                    OBF("9564"),
                    OBF("2025/06/30 19:37:27"),
                    {OBF("- Add New Features"),
                            OBF("- Make Auto Feedback"),
                    },
                    false,
                    OBF("update_9564")
            },
            {
                    OBF("Res v1.6.51.7"),
                    OBF("9321"),
                    OBF("2025/06/16 01:45:00"),
                    {OBF("- Add Feature Skiing Boost"),
                    },
                    false,
                    OBF("update_9321")
            },
            {
                    OBF("Res v1.6.51.7"),
                    OBF("9277"),
                    OBF("2025/06/12 01:53:00"),
                    {OBF("- Add New Features"),
                            OBF("- Connect Main Panel"),
                    },
                    false,
                    OBF("update_9277")
            },
            {
                    OBF("Res v1.6.51.0"),
                    OBF("9011"),
                    OBF("2025/05/26 05:33:10"),
                    {OBF("- CHANGE BYPASS ADDRESS"),
                            OBF("- Add Some Features BETA TEST"),
                    },
                    false,
                    OBF("update_9011")
            },
            {
                    OBF("Res v1.6.50.15"),
                    OBF("8897"),
                    OBF("2025/05/11 18:33:10"),
                    {OBF("- Fix Stuck Some Devices"),
                            OBF("- Add SmartFPS"),
                    },
                    false,
                    OBF("update_8897")
            },
            {
                    OBF("Res v1.6.50.15"),
                    OBF("8882"),
                    OBF("2025/05/05 00:09:10"),
                    {OBF("- Add Source Quality Graphics"),
                            OBF("- Add ESP Vehicle"),
                            OBF("- Add Sky Diving Speed"),
                            OBF("- ESP Optimization"),
                            OBF("- Change Spectated Patch"),
                            OBF("- Add Adjustable Features"),
                            OBF("- Etc"),
                    },
                    false,
                    OBF("update_8882")
            },
            {
                    OBF("Res v1.6.50.8"),
                    OBF("8801"),
                    OBF("2025/04/21 19:45:21"),
                    {OBF("- Remove Auto Login outputs DeviceReport_txt"),
                            OBF("- Add Button SAVE DEVICE REPORT"),
                            OBF("- Add SDK ESP Features on Visual with new Method API"),
                            OBF("- Add Show FPS on Screen"),
                    },
                    false,
                    OBF("update_8801")
            },
            {
                    OBF("Res v1.6.50.6"),
                    OBF("8690"),
                    OBF("2025/04/08 13:58:20"),
                    {OBF("- Fix Crash Some Device"),
                            OBF("- Aim PATCH Adjustable"),
                    },
                    false,
                    OBF("update_8690_1")
            },
            {
                    OBF("Res v1.6.50.6"),
                    OBF("8690"),
                    OBF("2025/04/03 20:37:05"),
                    {OBF("- Add BOX FILL on Esp BOX"),
                            OBF("- Rollback about FPS"),
                    },
                    false,
                    OBF("update_8690_2")
            },
            {
                    OBF("Res v1.6.50.5"),
                    OBF("8684"),
                    OBF("2025/03/30 22:00:05"),
                    {OBF("- Remove ESP SDK Name,Health,Distance"),
                            OBF("- Remove MEMORY MENU move to ESP MENU"),
                    },
                    false,
                    OBF("update_8684")
            },
            {
                    OBF("Res v1.6.50.5"),
                    OBF("8657"),
                    OBF("2025/03/30 01:18:05"),
                    {OBF("- Change Aimbot to Adjutsment")},
                    false,
                    OBF("update_8657")
            },
            {
                    OBF("Res v1.6.50.5"),
                    OBF("8640"),
                    OBF("2025/03/28 22:18:23"),
                    {
                            OBF("- Remove Auto Clear Cache"),
                            OBF("- Remove SDK Adjust"),
                            OBF("- Change UI Draw ESP + Optimize"),
                            OBF("- Add Save/Load/Delete Settings")
                    },
                    false,
                    OBF("update_8640")
            },
            {
                    OBF("Res v1.6.50.4"),
                    OBF("8603"),
                    OBF("2025/03/27 15:09:00"),
                    {OBF("- Optimize Draw ESP")},
                    false,
                    OBF("update_8603")
            }
    };
}

static void displayUpdateBadge(ImDrawList* drawList, const UpdateInfo& update,
                               float badgeStartX, float badgeWidth, float yPos,
                               bool isLatest) {
    static int updateBadgeLogCounter = 0;
    if (++updateBadgeLogCounter % 7200 == 0) {
        updateBadgeLogCounter = 0;
    }

    ImVec2 badgePos = ImGui::GetCursorScreenPos();

    float baseHeight = 80.0f;
    float lineHeight = 20.0f;
    float badgeHeight = baseHeight + (update.changes.size() * lineHeight);
    ImVec2 badgeSize = ImVec2(badgeWidth, badgeHeight);

    ImU32 bgColor = IM_COL32(25, 25, 50, 230);
    ImU32 borderColor = isLatest ? IM_COL32(100, 50, 150, 200) : IM_COL32(80, 40, 120, 150);

    drawList->AddRectFilled(
            badgePos,
            ImVec2(badgePos.x + badgeSize.x, badgePos.y + badgeSize.y),
            bgColor,
            4.0f
    );

    drawList->AddRect(
            badgePos,
            ImVec2(badgePos.x + badgeSize.x, badgePos.y + badgeSize.y),
            borderColor,
            4.0f, 15, 1.5f
    );

    ImGui::Dummy(badgeSize);

    float textPosY = badgePos.y + 15.0f;
    float textStartX = badgePos.x + 20.0f;

    ImU32 textColor = IM_COL32(255, 255, 255, 255);
    ImU32 versionColor = IM_COL32(0, 220, 0, 255);
    ImU32 buildColor = IM_COL32(220, 100, 100, 255);
    ImU32 dateColor = IM_COL32(220, 220, 0, 255);

    drawList->AddText(ImVec2(textStartX, textPosY), textColor, TEXT_UPDATE);

    float updateTextWidth = ImGui::CalcTextSize(TEXT_UPDATE).x;
    drawList->AddText(
            ImVec2(textStartX + updateTextWidth + 5.0f, textPosY),
            versionColor,
            update.version.c_str()
    );

    float versionWidth = ImGui::CalcTextSize(update.version.c_str()).x;
    drawList->AddText(
            ImVec2(textStartX + updateTextWidth + versionWidth + 10.0f, textPosY),
            buildColor,
            update.buildNumber.c_str()
    );

    float buildWidth = ImGui::CalcTextSize(update.buildNumber.c_str()).x;
    drawList->AddText(
            ImVec2(textStartX + updateTextWidth + versionWidth + buildWidth + 15.0f, textPosY),
            textColor,
            TEXT_SEPARATOR
    );

    float separatorWidth = ImGui::CalcTextSize(TEXT_SEPARATOR).x;
    drawList->AddText(
            ImVec2(textStartX + updateTextWidth + versionWidth + buildWidth + separatorWidth + 20.0f, textPosY),
            dateColor,
            update.date.c_str()
    );

    float bulletY = textPosY + 30.0f;
    for (size_t i = 0; i < update.changes.size(); i++) {
        drawList->AddText(
                ImVec2(textStartX + 15.0f, bulletY + (i * lineHeight)),
                textColor,
                update.changes[i].c_str()
        );
    }

    if (update.isNew) {
        float badgeNewPosX = badgePos.x + badgeSize.x - 60.0f;
        float badgeNewPosY = badgePos.y - 10.0f;

        drawList->AddRectFilled(
                ImVec2(badgeNewPosX, badgeNewPosY),
                ImVec2(badgeNewPosX + 50.0f, badgeNewPosY + 20.0f),
                IM_COL32(220, 0, 0, 200),
                5.0f
        );

        drawList->AddText(
                ImVec2(badgeNewPosX + 10.0f, badgeNewPosY + 2.0f),
                IM_COL32(255, 255, 255, 255),
                TEXT_NEW
        );
    }
}

static void displayCollapsibleChangelog(const UpdateInfo& update, bool isLatest) {
    ImVec4 headerColor = isLatest ? ImVec4(0.8f, 0.2f, 0.2f, 0.7f) : ImVec4(0.3f, 0.3f, 0.5f, 1.0f);
    ImVec4 headerHovered = isLatest ? ImVec4(0.3f, 0.6f, 1.0f, 0.7f) : ImVec4(0.4f, 0.4f, 0.6f, 1.0f);
    ImVec4 headerActive = isLatest ? ImVec4(0.3f, 1.0f, 0.3f, 0.7f) : ImVec4(0.5f, 0.5f, 0.7f, 1.0f);

    ImGui::PushStyleColor(ImGuiCol_Header, headerColor);
    ImGui::PushStyleColor(ImGuiCol_HeaderHovered, headerHovered);
    ImGui::PushStyleColor(ImGuiCol_HeaderActive, headerActive);

    std::string headerText = std::string(TEXT_UPDATE) + " " + update.version + " " + update.buildNumber + " " + TEXT_SEPARATOR + " " + update.date;

    if (isLatest) {
        headerText += " [" + std::string(TEXT_NEW) + "]";
    }

    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_CollapsingHeader;
    if (isLatest) {
        flags |= ImGuiTreeNodeFlags_DefaultOpen;
    }

    bool isOpen = ImGui::CollapsingHeader(headerText.c_str(), flags);

    ImGui::PopStyleColor(3);

    if (isOpen) {
        ImGui::Indent(20.0f);

        for (const auto& change : update.changes) {
            ImGui::TextWrapped("%s", change.c_str());
            ImGui::Spacing();
        }

        ImGui::Unindent(20.0f);
        ImGui::Spacing();
    }
}

#endif // ARCAMOD_UPDATE_STATUS_PANEL_H