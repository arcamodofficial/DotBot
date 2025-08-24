//
// Created by ARCAMOD (optimized) on 10/04/2025.
//

#ifndef ARCAMOD_MEMORY_POOL_H
#define ARCAMOD_MEMORY_POOL_H

#include <cstddef>
#include <cstdint>
#include <vector>
#include <mutex>
#include <new>
#include <memory>

/**
 * MemoryPool: Sistem alokasi memori yang efisien untuk objek kecil dan sering digunakan
 * 
 * Fitur:
 * - Mengurangi fragmentasi memori dengan alokasi blok
 * - Menghindari overhead alokasi berulang untuk objek kecil
 * - Thread-safe dengan mutex
 * - Mempertahankan blok memori terpisah untuk ukuran berbeda
 */
namespace ARCAMOD {

template <typename T, size_t BlockSize = 4096>
class MemoryPool {
public:
    // Tipe untuk pointer dan size
    using pointer = T*;
    using size_type = std::size_t;
    using value_type = T;

    /**
     * Constructor
     */
    MemoryPool() noexcept : 
        currentBlock_(nullptr),
        currentSlot_(nullptr),
        lastSlot_(nullptr),
        freeSlots_(nullptr) {
        // Alokasi blok pertama jika diperlukan dalam operasi allocate() pertama
    }

    /**
     * Destructor: Bebaskan semua blok memori yang dialokasikan
     */
    ~MemoryPool() noexcept {
        // Bebaskan memori dari setiap blok
        for (auto block : memoryBlocks_) {
            if (block) {
                std::free(block);
            }
        }
    }

    /**
     * Alokasi memori untuk satu objek T
     * @return Pointer ke objek yang dialokasikan
     */
    pointer allocate() {
        std::lock_guard<std::mutex> lock(mutex_);

        // Jika ada slot bebas, gunakan itu
        if (freeSlots_ != nullptr) {
            pointer result = reinterpret_cast<pointer>(freeSlots_);
            freeSlots_ = freeSlots_->next;
            return result;
        }

        // Jika tidak ada slot di blok saat ini, alokasi blok baru
        if (currentSlot_ >= lastSlot_) {
            allocateBlock();
        }

        // Gunakan slot saat ini dan pindahkan ke slot berikutnya
        pointer result = reinterpret_cast<pointer>(currentSlot_);
        currentSlot_ = reinterpret_cast<slot_pointer_>(
            reinterpret_cast<char*>(currentSlot_) + sizeof(value_type)
        );
        return result;
    }

    /**
     * Kembalikan memori ke pool
     * @param p Pointer ke objek yang ingin dibebaskan
     */
    void deallocate(pointer p) noexcept {
        if (p == nullptr) return;
        
        std::lock_guard<std::mutex> lock(mutex_);

        // Buat slot baru di awal linked list slot bebas
        auto slot = reinterpret_cast<slot_pointer_>(p);
        slot->next = freeSlots_;
        freeSlots_ = slot;
    }

    /**
     * Buat objek baru di lokasi tertentu
     * @param p Lokasi memori
     * @param args Argument untuk constructor
     * @return Pointer ke objek yang dibuat
     */
    template <typename... Args>
    pointer newElement(Args&&... args) {
        pointer result = allocate();
        new (result) value_type(std::forward<Args>(args)...);
        return result;
    }

    /**
     * Hancurkan objek dan bebaskan memorinya ke pool
     * @param p Pointer ke objek yang ingin dihancurkan
     */
    void deleteElement(pointer p) noexcept {
        if (p == nullptr) return;
        p->~value_type();
        deallocate(p);
    }

private:
    // Struktur Slot untuk linked list slot bebas
    union Slot {
        value_type element;
        Slot* next;
        
        // Constructor khusus untuk penanda tidak diinisialisasi
        Slot() noexcept : next(nullptr) {}
    };

    // Tipe untuk slot pointer internal
    using slot_pointer_ = Slot*;

    // Data MemoryPool
    std::vector<void*> memoryBlocks_;  // Simpan semua blok untuk pembebasan
    slot_pointer_ currentBlock_;       // Blok saat ini
    slot_pointer_ currentSlot_;        // Slot berikutnya yang tersedia
    slot_pointer_ lastSlot_;           // Batas akhir blok saat ini
    slot_pointer_ freeSlots_;          // Linked list slot bebas
    std::mutex mutex_;                 // Mutex untuk thread safety

    /**
     * Alokasikan blok memori baru
     */
    void allocateBlock() {
        // Alokasi blok memori baru
        auto newBlock = reinterpret_cast<slot_pointer_>(std::malloc(BlockSize));
        if (newBlock == nullptr) {
            throw std::bad_alloc();
        }
        
        // Simpan blok untuk dibebaskan kemudian
        memoryBlocks_.push_back(newBlock);
        
        // Siapkan pointer blok
        currentBlock_ = newBlock;
        currentSlot_ = newBlock;
        
        // Hitung slot terakhir di blok ini
        lastSlot_ = reinterpret_cast<slot_pointer_>(
            reinterpret_cast<char*>(currentBlock_) + BlockSize
        );
    }
};

/**
 * Template spesialisasi untuk void
 */
template <size_t BlockSize>
class MemoryPool<void, BlockSize> {
public:
    using pointer = void*;
    using size_type = std::size_t;
    using value_type = void;
};

/**
 * PoolAllocator: Custom allocator kompatibel dengan STL yang menggunakan MemoryPool
 */
template <typename T, size_t BlockSize = 4096>
class PoolAllocator {
public:
    // Tipe yang diperlukan untuk kompatibilitas STL
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    
    // Rebind untuk mendukung container yang mengalokasikan tipe internal
    template <typename U>
    struct rebind {
        using other = PoolAllocator<U, BlockSize>;
    };

    /**
     * Constructor default
     */
    PoolAllocator() noexcept = default;

    /**
     * Constructor copy
     */
    PoolAllocator(const PoolAllocator& other) noexcept = default;
    
    /**
     * Rebind constructor
     */
    template <typename U>
    PoolAllocator(const PoolAllocator<U, BlockSize>& other) noexcept {}

    /**
     * Destructor
     */
    ~PoolAllocator() noexcept = default;

    /**
     * Alokasi memori untuk n objek
     */
    pointer allocate(size_type n = 1, const_pointer hint = nullptr) {
        if (n != 1 || hint != nullptr) {
            // Untuk alokasi besar atau dengan hint, gunakan allocator default
            return reinterpret_cast<pointer>(::operator new(n * sizeof(value_type)));
        }
        
        // Untuk alokasi tunggal, gunakan memory pool
        return memoryPool_.allocate();
    }

    /**
     * Bebaskan memori yang dialokasikan
     */
    void deallocate(pointer p, size_type n = 1) noexcept {
        if (n != 1) {
            // Untuk alokasi besar, gunakan operator delete standar
            ::operator delete(p);
            return;
        }
        
        // Untuk alokasi tunggal, gunakan memory pool
        memoryPool_.deallocate(p);
    }
    
    /**
     * Konstruksi objek di lokasi tertentu
     */
    template<typename U, typename... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }
    
    /**
     * Hancurkan objek
     */
    template<typename U>
    void destroy(U* p) {
        p->~U();
    }

private:
    // Memory pool untuk tipe ini
    static MemoryPool<T, BlockSize> memoryPool_;
};

// Inisialisasi memory pool statis untuk setiap tipe PoolAllocator
template <typename T, size_t BlockSize>
MemoryPool<T, BlockSize> PoolAllocator<T, BlockSize>::memoryPool_;

// Operator perbandingan untuk kompatibilitas STL
template <typename T1, size_t BS1, typename T2, size_t BS2>
inline bool operator==(const PoolAllocator<T1, BS1>&, const PoolAllocator<T2, BS2>&) noexcept {
    return BS1 == BS2;
}

template <typename T1, size_t BS1, typename T2, size_t BS2>
inline bool operator!=(const PoolAllocator<T1, BS1>& a, const PoolAllocator<T2, BS2>& b) noexcept {
    return !(a == b);
}

} // namespace ARCAMOD

#endif // ARCAMOD_MEMORY_POOL_H 