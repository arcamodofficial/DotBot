//
// Created by ARCAMOD (optimized) on 10/04/2025.
//

#ifndef ARCAMOD_THREAD_POOL_H
#define ARCAMOD_THREAD_POOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>
#include <type_traits>
#include <memory>

namespace ARCAMOD {

/**
 * ThreadPool: Implementasi thread pool yang efisien untuk eksekusi task paralel
 * 
 * Fitur:
 * - Membagi beban kerja di antara beberapa worker thread
 * - Mengurangi overhead pembuatan dan penghancuran thread
 * - Mendukung pengembalian nilai dengan std::future
 * - Implementasi thread-safe untuk operasi concurrent
 */
class ThreadPool {
public:
    /**
     * Constructor: Membuat thread pool dengan jumlah thread tertentu
     * 
     * @param num_threads Jumlah thread pekerja (0 = jumlah yang tersedia pada hardware)
     */
    ThreadPool(size_t num_threads = 0) : 
        m_stop_requested(false),
        m_active_tasks(0) {
        // Tentukan jumlah thread berdasarkan hardware jika 0
        size_t thread_count = num_threads;
        if (thread_count == 0) {
            thread_count = std::thread::hardware_concurrency();
            // Fallback ke 2 thread jika hardware_concurrency() mengembalikan 0
            if (thread_count == 0) thread_count = 2;
        }

        try {
            // Buat worker threads
            for (size_t i = 0; i < thread_count; ++i) {
                m_threads.emplace_back(&ThreadPool::worker_thread, this);
            }
        } catch (...) {
            // Jika ada exception saat membuat threads, pastikan kita shutdown dengan bersih
            m_stop_requested = true;
            m_task_cv.notify_all();
            
            // Tunggu semua thread yang sudah dibuat
            for (auto& thread : m_threads) {
                if (thread.joinable()) {
                    thread.join();
                }
            }
            throw; // Re-throw exception
        }
    }

    /**
     * Destructor: Menghentikan semua thread dan membersihkan resource
     */
    ~ThreadPool() {
        // Minta semua thread berhenti
        {
            std::unique_lock<std::mutex> lock(m_task_mutex);
            m_stop_requested = true;
        }

        // Bangunkan semua thread
        m_task_cv.notify_all();

        // Tunggu semua thread selesai
        for (auto& thread : m_threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

    /**
     * Tambahkan task ke dalam queue
     * 
     * @param f Fungsi atau lambda yang akan dieksekusi
     * @param args Argumen untuk fungsi
     * @return std::future berisi hasil eksekusi fungsi
     */
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::invoke_result<F, Args...>::type> {
        using return_type = typename std::invoke_result<F, Args...>::type;

        // Buat shared_ptr ke packaged_task
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        // Dapatkan future dari task
        std::future<return_type> result = task->get_future();

        // Tambahkan task ke queue
        {
            std::unique_lock<std::mutex> lock(m_task_mutex);
            
            // Tolak penambahan task baru jika pool sedang shutdown
            if (m_stop_requested) {
                throw std::runtime_error(OBF("ThreadPool: enqueue pada thread pool yang sedang shutdown"));
            }

            m_tasks.emplace([task]() { 
                (*task)(); 
            });
            
            // Tambah counter task aktif
            ++m_active_tasks;
        }

        // Bangunkan salah satu thread untuk mengerjakan task
        m_task_cv.notify_one();
        
        return result;
    }
    
    /**
     * Tunggu semua task selesai
     * 
     * @note Thread pool masih tetap aktif dan dapat menerima task baru setelah wait
     */
    void wait_all() {
        std::unique_lock<std::mutex> lock(m_task_mutex);
        m_wait_cv.wait(lock, [this]() { 
            return m_active_tasks == 0 && m_tasks.empty(); 
        });
    }
    
    /**
     * Dapatkan jumlah thread dalam pool
     * 
     * @return Jumlah thread pekerja
     */
    size_t size() const {
        return m_threads.size();
    }
    
    /**
     * Dapatkan jumlah task yang sedang aktif
     * 
     * @return Jumlah task dalam proses
     */
    size_t active_tasks() const {
        return m_active_tasks;
    }
    
    /**
     * Dapatkan jumlah task yang masih dalam queue
     * 
     * @return Jumlah task dalam queue
     */
    size_t queued_tasks() const {
        std::unique_lock<std::mutex> lock(m_task_mutex);
        return m_tasks.size();
    }

private:
    // Vector dari worker threads
    std::vector<std::thread> m_threads;
    
    // Queue task dengan mutex protection
    std::queue<std::function<void()>> m_tasks;
    mutable std::mutex m_task_mutex;
    
    // Condition variables
    std::condition_variable m_task_cv;  // Untuk thread menunggu task baru
    std::condition_variable m_wait_cv;  // Untuk wait_all
    
    // Flag untuk meminta thread berhenti
    bool m_stop_requested;
    
    // Jumlah task yang aktif diproses
    std::atomic<size_t> m_active_tasks;
    
    /**
     * Fungsi untuk worker thread
     * Mengambil dan mengeksekusi task dari queue
     */
    void worker_thread() {
        while (true) {
            std::function<void()> task;
            
            // Ambil task dari queue
            {
                std::unique_lock<std::mutex> lock(m_task_mutex);
                
                // Tunggu sampai ada task atau diinstruksikan untuk berhenti
                m_task_cv.wait(lock, [this] { 
                    return m_stop_requested || !m_tasks.empty(); 
                });
                
                // Keluar dari loop jika diminta berhenti dan tidak ada task lagi
                if (m_stop_requested && m_tasks.empty()) {
                    break;
                }
                
                // Ambil task dari depan queue
                task = std::move(m_tasks.front());
                m_tasks.pop();
            }
            
            // Eksekusi task
            try {
                task();
            } catch (...) {
                // Log error jika diperlukan
            }
            
            // Kurangi counter task aktif
            {
                std::unique_lock<std::mutex> lock(m_task_mutex);
                --m_active_tasks;
                
                // Jika tidak ada task aktif dan queue kosong, notifikasi wait_all
                if (m_active_tasks == 0 && m_tasks.empty()) {
                    lock.unlock();
                    m_wait_cv.notify_all();
                }
            }
        }
    }
};

// Singleton ThreadPool untuk penggunaan global
inline ThreadPool& globalThreadPool() {
    static ThreadPool instance;
    return instance;
}

} // namespace ARCAMOD

#endif // ARCAMOD_THREAD_POOL_H 