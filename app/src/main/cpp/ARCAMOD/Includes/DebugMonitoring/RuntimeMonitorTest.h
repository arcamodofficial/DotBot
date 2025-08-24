#ifndef ARCAMOD_RUNTIME_MONITOR_TEST_H
#define ARCAMOD_RUNTIME_MONITOR_TEST_H

#include "LibanogsRuntimeMonitor.h"

/*
 * TEST FUNCTIONS UNTUK RUNTIME MONITOR
 * ====================================
 * 
 * File ini berisi fungsi-fungsi test untuk memastikan
 * Runtime Monitor berfungsi dengan baik dan dapat
 * mendeteksi aktivitas libanogs.so.
 */

// Test basic monitoring functionality
static void test_basic_monitoring() {
    RUNTIME_LOG("=== TESTING BASIC MONITORING ===");
    RUNTIME_LOG("Testing basic logging functionality");
    RUNTIME_LOG("Monitor should be active and logging");
    RUNTIME_LOG("=== BASIC MONITORING TEST COMPLETE ===");
}

// Test memory access logging
static void test_memory_access_logging() {
    RUNTIME_LOG("=== TESTING MEMORY ACCESS LOGGING ===");
    
    // Test with various memory addresses
    RUNTIME_LOG_MEMORY(0x7f12345000, 8, "READ");
    RUNTIME_LOG_MEMORY(0x7f12345008, 4, "WRITE");
    RUNTIME_LOG_MEMORY(0x7f12345010, 16, "EXECUTE");
    
    // Test with non-libanogs addresses (should not log)
    RUNTIME_LOG_MEMORY(0x12345678, 8, "READ");
    
    RUNTIME_LOG("=== MEMORY ACCESS LOGGING TEST COMPLETE ===");
}

// Test function activity logging
static void test_function_activity_logging() {
    RUNTIME_LOG("=== TESTING FUNCTION ACTIVITY LOGGING ===");
    
    // Test function calls
    RUNTIME_LOG_FUNCTION("test_function_1", 0x7f12346000);
    RUNTIME_LOG_FUNCTION("test_function_2", 0x7f12346100);
    RUNTIME_LOG_FUNCTION("JNI_OnLoad", 0x7f12346200);
    
    RUNTIME_LOG("=== FUNCTION ACTIVITY LOGGING TEST COMPLETE ===");
}

// Test API call logging
static void test_api_call_logging() {
    RUNTIME_LOG("=== TESTING API CALL LOGGING ===");
    
    RUNTIME_LOG_API("dlopen", "libanogs.so, RTLD_LAZY");
    RUNTIME_LOG_API("dlsym", "handle=0x7f12345000, symbol=JNI_OnLoad");
    RUNTIME_LOG_API("mmap", "addr=0x0, len=4096, prot=PROT_READ|PROT_WRITE");
    RUNTIME_LOG_API("mprotect", "addr=0x7f12345000, len=4096, prot=PROT_READ|PROT_EXEC");
    
    RUNTIME_LOG("=== API CALL LOGGING TEST COMPLETE ===");
}

// Test suspicious activity detection
static void test_suspicious_activity_detection() {
    RUNTIME_LOG("=== TESTING SUSPICIOUS ACTIVITY DETECTION ===");
    
    RUNTIME_LOG_SUSPICIOUS("MEMORY_PROTECTION", "Making LibAnogs memory writable");
    RUNTIME_LOG_SUSPICIOUS("HIGH_ACTIVITY", "Very high function call rate detected");
    RUNTIME_LOG_SUSPICIOUS("FUNCTION_SPAM", "Function called 1000+ times");
    RUNTIME_LOG_SUSPICIOUS("ANTI_DEBUG", "Anti-debugging technique detected");
    
    RUNTIME_LOG("=== SUSPICIOUS ACTIVITY DETECTION TEST COMPLETE ===");
}

// Test library detection simulation
static void test_library_detection_simulation() {
    RUNTIME_LOG("=== TESTING LIBRARY DETECTION SIMULATION ===");
    
    // Simulate library loading
    RUNTIME_LOG("Simulating library loading...");
    RUNTIME_LOG("LibAnogs library loading detected via dlopen");
    
    // Simulate memory regions
    RUNTIME_LOG("MEMORY_REGION found: 0x7f12345000-0x7f12567000 (2236416 bytes) r-xp");
    RUNTIME_LOG("MEMORY_REGION found: 0x7f12567000-0x7f12568000 (4096 bytes) r--p");
    RUNTIME_LOG("MEMORY_REGION found: 0x7f12568000-0x7f1256a000 (8192 bytes) rw-p");
    RUNTIME_LOG("LibAnogs loaded: Base=0x7f12345000 Size=2248704 bytes, Regions=3");
    
    RUNTIME_LOG("=== LIBRARY DETECTION SIMULATION TEST COMPLETE ===");
}

// Test performance monitoring
static void test_performance_monitoring() {
    RUNTIME_LOG("=== TESTING PERFORMANCE MONITORING ===");
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Simulate some work
    for (int i = 0; i < 1000; i++) {
        RUNTIME_LOG_FUNCTION("performance_test_function", 0x7f12346000 + i);
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::stringstream ss;
    ss << "Performance test completed: 1000 function calls in " << duration.count() << "ms";
    RUNTIME_LOG(ss.str().c_str());
    
    RUNTIME_LOG("=== PERFORMANCE MONITORING TEST COMPLETE ===");
}

// Test concurrent monitoring
static void* test_concurrent_thread(void* arg) {
    RUNTIME_LOG("=== CONCURRENT THREAD STARTED ===");
    
    for (int i = 0; i < 10; i++) {
        std::stringstream ss;
        ss << "Concurrent thread iteration " << (i + 1);
        RUNTIME_LOG(ss.str().c_str());
        
        RUNTIME_LOG_FUNCTION("concurrent_function", 0x7f12347000 + i * 0x100);
        RUNTIME_LOG_MEMORY(0x7f12345000 + i * 8, 8, "READ");
        
        sleep(1);
    }
    
    RUNTIME_LOG("=== CONCURRENT THREAD FINISHED ===");
    return nullptr;
}

static void test_concurrent_monitoring() {
    RUNTIME_LOG("=== TESTING CONCURRENT MONITORING ===");
    
    pthread_t test_thread;
    int result = pthread_create(&test_thread, nullptr, test_concurrent_thread, nullptr);
    
    if (result == 0) {
        pthread_detach(test_thread);
        RUNTIME_LOG("Concurrent test thread created successfully");
        
        // Continue logging from main thread
        for (int i = 0; i < 5; i++) {
            std::stringstream ss;
            ss << "Main thread iteration " << (i + 1);
            RUNTIME_LOG(ss.str().c_str());
            
            RUNTIME_LOG_API("main_thread_api", "test_parameter");
            sleep(2);
        }
    } else {
        RUNTIME_LOG("Failed to create concurrent test thread");
    }
    
    RUNTIME_LOG("=== CONCURRENT MONITORING TEST COMPLETE ===");
}

// Test stress monitoring
static void test_stress_monitoring() {
    RUNTIME_LOG("=== TESTING STRESS MONITORING ===");
    
    // Rapid fire logging
    for (int i = 0; i < 100; i++) {
        RUNTIME_LOG_FUNCTION("stress_function", 0x7f12348000 + i);
        RUNTIME_LOG_MEMORY(0x7f12345000 + i * 4, 4, "WRITE");
        RUNTIME_LOG_API("stress_api", "rapid_call");
        
        if (i % 10 == 0) {
            RUNTIME_LOG_SUSPICIOUS("STRESS_TEST", "High frequency activity detected");
        }
    }
    
    RUNTIME_LOG("=== STRESS MONITORING TEST COMPLETE ===");
}

// Test monitor status and reporting
static void test_monitor_status() {
    RUNTIME_LOG("=== TESTING MONITOR STATUS ===");
    
    // Check if monitor is active
    if (g_runtime_monitor.is_active) {
        RUNTIME_LOG("Runtime monitor is ACTIVE");
    } else {
        RUNTIME_LOG("Runtime monitor is INACTIVE");
    }
    
    // Check library status
    if (g_runtime_monitor.library_loaded) {
        std::stringstream ss;
        ss << "Library status: LOADED at 0x" << std::hex << g_runtime_monitor.base_address;
        RUNTIME_LOG(ss.str().c_str());
    } else {
        RUNTIME_LOG("Library status: NOT LOADED");
    }
    
    // Display statistics
    std::stringstream stats;
    stats << "Statistics: Functions=" << g_runtime_monitor.total_function_calls
          << ", Memory=" << g_runtime_monitor.memory_accesses
          << ", API=" << g_runtime_monitor.api_calls;
    RUNTIME_LOG(stats.str().c_str());
    
    RUNTIME_LOG("=== MONITOR STATUS TEST COMPLETE ===");
}

// Run all tests
static void run_all_runtime_monitor_tests() {
    RUNTIME_LOG("========================================");
    RUNTIME_LOG("STARTING RUNTIME MONITOR TEST SUITE");
    RUNTIME_LOG("========================================");
    
    test_basic_monitoring();
    sleep(1);
    
    test_memory_access_logging();
    sleep(1);
    
    test_function_activity_logging();
    sleep(1);
    
    test_api_call_logging();
    sleep(1);
    
    test_suspicious_activity_detection();
    sleep(1);
    
    test_library_detection_simulation();
    sleep(1);
    
    test_performance_monitoring();
    sleep(1);
    
    test_concurrent_monitoring();
    sleep(5); // Wait for concurrent thread
    
    test_stress_monitoring();
    sleep(1);
    
    test_monitor_status();
    
    RUNTIME_LOG("========================================");
    RUNTIME_LOG("RUNTIME MONITOR TEST SUITE COMPLETED");
    RUNTIME_LOG("========================================");
}

// Quick test for immediate verification
static void run_quick_test() {
    RUNTIME_LOG("=== QUICK RUNTIME MONITOR TEST ===");
    
    test_basic_monitoring();
    test_memory_access_logging();
    test_function_activity_logging();
    test_api_call_logging();
    test_monitor_status();
    
    RUNTIME_LOG("=== QUICK TEST COMPLETED ===");
}

/*
 * CARA MENGGUNAKAN TEST:
 * =====================
 * 
 * 1. Include file ini di tempat yang ingin Anda test:
 *    #include "ARCAMOD/Includes/DebugMonitoring/RuntimeMonitorTest.h"
 * 
 * 2. Panggil fungsi test yang diinginkan:
 *    run_quick_test();                    // Test cepat
 *    run_all_runtime_monitor_tests();     // Test lengkap
 * 
 * 3. Monitor output di:
 *    - File: /sdcard/Android/data/com.garena.game.codm/files/ARCAMOD_LibAnogs_Runtime.txt
 *    - Logcat: adb logcat | grep ARCAMOD_RUNTIME
 * 
 * 4. Contoh penggunaan di arcamod.cpp:
 *    
 *    #ifdef DEBUG
 *    #include "ARCAMOD/Includes/DebugMonitoring/RuntimeMonitorTest.h"
 *    #endif
 *    
 *    void lib_main_call() {
 *        initialize_security_systems();
 *        StartRuntimeMonitor();
 *        
 *        #ifdef DEBUG
 *        // Run tests only in debug build
 *        run_quick_test();
 *        #endif
 *        
 *        // ... rest of initialization
 *    }
 */

#endif // ARCAMOD_RUNTIME_MONITOR_TEST_H
