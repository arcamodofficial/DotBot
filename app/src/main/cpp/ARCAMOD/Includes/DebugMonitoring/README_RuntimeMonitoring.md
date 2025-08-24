# LibAnogs Runtime Monitoring System

## Deskripsi
Sistem monitoring real-time untuk memantau aktivitas **libanogs.so** saat game berjalan. Berbeda dari sistem sebelumnya yang hanya memonitor fungsi bypass, sistem ini benar-benar memantau aktivitas library secara langsung.

## Fitur Utama

### 🔍 **Real-time Library Monitoring**
- **Memory Region Scanning** - Memantau semua region memory yang digunakan libanogs.so
- **Dynamic Loading Detection** - Mendeteksi saat library di-load/unload
- **Memory Access Tracking** - Melacak akses read/write/execute ke memory library
- **Permission Changes** - Mendeteksi perubahan permission memory (mprotect)

### 📊 **API Call Monitoring**
- **System Call Interception** - Hook system calls yang digunakan library
- **File Operations** - Monitor open/read/write file operations
- **Memory Operations** - Track mmap/munmap/mprotect calls
- **Dynamic Linking** - Monitor dlopen/dlsym/dlclose calls

### 🎯 **Function Call Tracing**
- **Function Discovery** - Scan dan identifikasi semua fungsi dalam library
- **Call Interception** - Hook function calls secara dinamis
- **Parameter Logging** - Log parameter dan return values
- **Call Flow Analysis** - Analisis alur pemanggilan fungsi

### 🚨 **Behavioral Analysis**
- **Suspicious Activity Detection** - Deteksi aktivitas mencurigakan
- **Pattern Recognition** - Identifikasi pola perilaku tidak normal
- **Performance Monitoring** - Monitor performa dan resource usage
- **Anti-debugging Detection** - Deteksi teknik anti-debugging

## Struktur File

```
ARCAMOD/Includes/DebugMonitoring/
├── LibanogsRuntimeMonitor.h        # Core runtime monitoring
├── LibanogsRuntimeMonitor.cpp      # Implementation
├── LibanogsFunctionTracer.h        # Advanced function tracing
└── README_RuntimeMonitoring.md     # Dokumentasi ini
```

## Integrasi dengan arcamod.cpp

Sistem telah diintegrasikan dengan minimal changes:

```cpp
__attribute__((constructor))
void lib_main_call() PASS_OBF PASS_OBF_STRING {
    initialize_security_systems();
    
    // Start LibAnogs runtime monitoring
    StartRuntimeMonitor();  // <-- ADDED
    
    pthread_t anogs_thread_id, unity_thread_id;
    create_worker_thread(&anogs_thread_id, anogs_thread, "anogs_thread");
    create_worker_thread(&unity_thread_id, unity_thread, "unity_thread");
}

static void cleanup_signal_handler(int signal) PASS_OBF PASS_OBF_STRING {
    StopRuntimeMonitor();  // <-- ADDED
    
    extern void CleanupResources();
    CleanupResources();
    exit(signal);
}
```

## Output Monitoring

### **Log File Location**
```
/sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Runtime.txt
```

### **Android Logcat**
```
Tag: ARCAMOD_RUNTIME
```

## Contoh Output Real-time

### **Memory Region Detection**
```
[2025-08-19 14:30:15] [RUNTIME] MEMORY_REGION found: 0x7f12345000-0x7f12567000 (2236416 bytes) r-xp
[2025-08-19 14:30:15] [RUNTIME] MEMORY_REGION found: 0x7f12567000-0x7f12568000 (4096 bytes) r--p
[2025-08-19 14:30:15] [RUNTIME] MEMORY_REGION found: 0x7f12568000-0x7f1256a000 (8192 bytes) rw-p
[2025-08-19 14:30:15] [RUNTIME] LibAnogs loaded: Base=0x7f12345000 Size=2248704 bytes, Regions=3
```

### **API Call Monitoring**
```
[2025-08-19 14:30:16] [RUNTIME] API_CALL dlopen Parameters: libanogs.so, 1
[2025-08-19 14:30:16] [RUNTIME] API_CALL dlsym(handle=0x7f12345000, symbol=JNI_OnLoad) -> 0x7f12346780
[2025-08-19 14:30:17] [RUNTIME] API_CALL mmap(addr=0x0, len=4096, prot=3, flags=34) -> 0x7f12569000
```

### **Function Activity**
```
[2025-08-19 14:30:18] [RUNTIME] FUNCTION_CALL JNI_OnLoad at 0x7f12346780
[2025-08-19 14:30:18] [RUNTIME] FUNCTION_CALL sub_12345 at 0x7f12357890
[2025-08-19 14:30:19] [RUNTIME] FUNCTION_CALL anti_debug_check at 0x7f12358000
```

### **Memory Access Tracking**
```
[2025-08-19 14:30:20] [RUNTIME] MEMORY_ACCESS [READ] Address: 0x7f12345100 Size: 8 bytes (LibAnogs region)
[2025-08-19 14:30:20] [RUNTIME] MEMORY_ACCESS [write] Address: 0x7f12568000 Size: 4 bytes (LibAnogs region)
[2025-08-19 14:30:21] [RUNTIME] MEMORY_ACCESS [execute] Address: 0x7f12346000 Size: 16 bytes (LibAnogs region)
```

### **Suspicious Activity Detection**
```
[2025-08-19 14:30:25] [RUNTIME] SUSPICIOUS_ACTIVITY [MEMORY_PROTECTION] Making LibAnogs memory writable
[2025-08-19 14:30:26] [RUNTIME] SUSPICIOUS_ACTIVITY [HIGH_ACTIVITY] Very high function call rate detected
[2025-08-19 14:30:27] [RUNTIME] SUSPICIOUS_ACTIVITY [FUNCTION_SPAM] Function at 0x7f12346780 called 150 times
```

### **Periodic Reports**
```
[2025-08-19 14:30:30] [RUNTIME] 
=== LIBANOGS RUNTIME REPORT ===
Monitor Active: YES
Library Loaded: YES
Base Address: 0x7f12345000
Library Size: 2248704 bytes
Memory Regions: 3
Total Function Calls: 1247
Memory Accesses: 3891
API Calls: 45
Unique Functions: 23
Runtime: 15 seconds
===============================
```

## Cara Monitoring Real-time

### **1. Monitor via ADB Logcat**
```bash
# Monitor semua aktivitas runtime
adb logcat | grep ARCAMOD_RUNTIME

# Filter hanya function calls
adb logcat | grep "FUNCTION_CALL"

# Filter hanya suspicious activity
adb logcat | grep "SUSPICIOUS_ACTIVITY"

# Filter hanya API calls
adb logcat | grep "API_CALL"
```

### **2. Monitor Log File**
```bash
# View real-time log file
adb shell tail -f /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Runtime.txt

# Search for specific patterns
adb shell grep "MEMORY_ACCESS" /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Runtime.txt

# Pull log file for analysis
adb pull /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Runtime.txt
```

### **3. Advanced Filtering**
```bash
# Monitor only memory operations
adb logcat | grep -E "(mmap|mprotect|MEMORY_ACCESS)"

# Monitor function calls with high frequency
adb logcat | grep -E "(FUNCTION_CALL|FUNCTION_SPAM)"

# Monitor library loading/unloading
adb logcat | grep -E "(dlopen|dlsym|LibAnogs loaded)"
```

## Konfigurasi Monitoring

### **Debug Build Only**
Monitoring hanya aktif dalam DEBUG build:
```cpp
#ifdef DEBUG
#define RUNTIME_MONITOR_ENABLED 1
#else
#define RUNTIME_MONITOR_ENABLED 0
#endif
```

### **Customizable Monitoring**
Anda dapat mengkustomisasi apa yang dimonitor dengan memodifikasi:
- `MonitorLibraryInteractions()` - Untuk monitoring interaksi library
- `AnalyzeRuntimeBehavior()` - Untuk analisis behavioral
- `DetectSuspiciousActivity()` - Untuk deteksi aktivitas mencurigakan

## Analisis Data

### **Pattern Recognition**
- **High Activity Patterns** - Deteksi aktivitas tinggi yang tidak normal
- **Memory Access Patterns** - Analisis pola akses memory
- **Function Call Patterns** - Identifikasi hot functions dan call chains
- **API Usage Patterns** - Monitor penggunaan system calls

### **Performance Analysis**
- **Function Call Rates** - Berapa sering fungsi dipanggil
- **Memory Access Rates** - Seberapa intensif akses memory
- **API Call Frequency** - Frekuensi penggunaan system calls
- **Resource Usage** - Monitor penggunaan resource system

### **Security Analysis**
- **Anti-debugging Detection** - Deteksi teknik anti-debugging
- **Code Injection Detection** - Deteksi injeksi kode
- **Memory Protection Changes** - Monitor perubahan permission memory
- **Suspicious API Usage** - Deteksi penggunaan API yang mencurigakan

## Troubleshooting

### **Monitor Tidak Berjalan**
1. Pastikan DEBUG flag enabled saat compile
2. Cek permission untuk menulis ke storage eksternal
3. Verify thread creation berhasil di logcat

### **Tidak Ada Activity Detected**
1. Pastikan libanogs.so benar-benar loaded
2. Cek apakah library menggunakan nama yang berbeda
3. Verify memory regions terdeteksi dengan benar

### **Performance Issues**
1. Reduce monitoring frequency di `runtime_monitor_thread()`
2. Disable detailed logging untuk production
3. Use conditional monitoring untuk specific events

## Keamanan dan Anti-Detection

### **Stealth Monitoring**
- Monitoring berjalan dalam thread terpisah
- Minimal footprint dalam memory
- No modification ke library target
- Log file tersembunyi di app directory

### **Anti-Detection Features**
- Thread name obfuscation
- Randomized monitoring intervals
- Encrypted log output (optional)
- Dynamic hook installation

## Kesimpulan

Sistem Runtime Monitoring ini memberikan visibilitas penuh terhadap aktivitas libanogs.so secara real-time, termasuk:

✅ **Memory operations** - Semua akses memory termonitor
✅ **Function calls** - Setiap pemanggilan fungsi tercatat
✅ **API usage** - Semua system calls terdeteksi
✅ **Behavioral analysis** - Pola perilaku dianalisis
✅ **Suspicious activity detection** - Aktivitas mencurigakan terdeteksi
✅ **Performance monitoring** - Resource usage dimonitor

Dengan sistem ini, Anda akan mendapatkan insight mendalam tentang apa yang sebenarnya dilakukan libanogs.so saat game berjalan!
