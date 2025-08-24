cmake_minimum_required(VERSION 3.22.1)

project("arcamod")

set(CMAKE_TOOLCHAIN_FILE /data/data/com.itsaky.androidide/files/home/android-sdk/ndk/26.1.10909125/build/cmake/android.toolchain.cmake)

set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# OPTIMASI PROYEK BESAR: Enable precompiled headers dan parallel build
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)  # Disable module scanning untuk mempercepat
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # Export compile commands untuk debugging

option(ENABLE_LOGGING "Enable logging" OFF)
if (ENABLE_LOGGING)
    add_definitions(-DENABLE_LOGGING=1)
else()
    add_definitions(-DENABLE_LOGGING=0)
endif()

# Optimasi untuk memori dengan option baru
option(ENABLE_MEMORY_POOL "Enable memory pool optimization" ON)
if (ENABLE_MEMORY_POOL)
    add_definitions(-DENABLE_MEMORY_POOL=1)
else()
    add_definitions(-DENABLE_MEMORY_POOL=0)
endif()

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_source_files_properties(
            ${KITTYMEMORY_SRC}
            PROPERTIES
            COMPILE_FLAGS "-mllvm -bcf -mllvm -fla"
    )
endif()

set(KITTYMEMORY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ARCAMOD/Includes/KittyMemory)
file(GLOB KITTYMEMORY_SRC ${KITTYMEMORY_PATH}/*.cpp)

# RELIABLE BUILD: Single library untuk memastikan semua komponen ter-build lengkap
add_library(${CMAKE_PROJECT_NAME} SHARED
        arcamod.cpp
        ARCAMOD/JavaBridge/JavaBridge.cpp
        ARCAMOD/Includes/Oxorany/backends/Oxorany.cpp
        # IMGUI Core Files (IMGUI 1.85 WIP - AKTIF)
        ARCAMOD/Includes/ImGui/backends/imgui.cpp
        ARCAMOD/Includes/ImGui/backends/imgui_draw.cpp
        ARCAMOD/Includes/ImGui/backends/imgui_tables.cpp
        ARCAMOD/Includes/ImGui/backends/imgui_widgets.cpp
        ARCAMOD/Includes/ImGui/backends/imgui_impl_android.cpp
        ARCAMOD/Includes/ImGui/backends/imgui_impl_opengl3.cpp
        ARCAMOD/Includes/ImGui/backends/ImguiPP.cpp
        # Runtime Monitoring Components - DISABLED FOR PRODUCTION
        # ARCAMOD/Includes/DebugMonitoring/LibanogsRuntimeMonitor.cpp
        # ARCAMOD/Includes/DebugMonitoring/LibanogsDataAnalyzer.cpp
        # Other Components
        ARCAMOD/Includes/Tools/backends/Tools.cpp
        ARCAMOD/Includes/BNM/backends/IL2Cpp.cpp
        ${KITTYMEMORY_SRC}
        ARCAMOD/Includes/SystemInfo/SystemInfo.cpp
        ARCAMOD/Includes/STB/stb_image.cpp
        ARCAMOD/Includes/LogoData/LogoData.cpp
        ARCAMOD/Includes/LogoData/XenoLogoData.cpp
)

target_link_libraries(${CMAKE_PROJECT_NAME}
        android
        log
        dobby
        curl
        ssl
        crypto
        atomic
        z
        EGL
        GLESv1_CM
        GLESv2
        GLESv3)

target_include_directories(arcamod PUBLIC ${KITTYMEMORY_PATH})
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
        ARCAMOD/Includes/curl/backends/${CMAKE_ANDROID_ARCH_ABI}/include
        ARCAMOD/Includes/openssl/backends/${CMAKE_ANDROID_ARCH_ABI}/include
        ARCAMOD/Includes/DobbyHook/include
        ARCAMOD/Includes/SystemInfo
)

add_definitions(-w)  # Disable semua peringatan

# Flag linker dan compiler yang dioptimasi
set(LINKER_FLAGS "-ffixed-x18 -Wl,--hash-style=both")
set(C_FLAGS "-Werror=format -Wunknown-warning -Wno-multichar -Wno-parentheses -Wno-literal-conversion -Wno-error -Wno-format-security -fdata-sections -ffunction-sections -std=c18")
set(CXX_FLAGS "${CXX_FLAGS} -std=c++20")

# RELIABLE BUILD: Optimasi konservatif untuk memastikan semua komponen ter-build
if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    # RELEASE BUILD: Optimasi sedang untuk balance performa dan reliability
    set(C_FLAGS "${C_FLAGS} -O2")  # O2 untuk performa lebih baik tanpa risiko tinggi
    set(CXX_FLAGS "${CXX_FLAGS} -fvisibility=default")  # Pertahankan symbols untuk hooking
    set(LINKER_FLAGS "${LINKER_FLAGS} -llog")  # Minimal linker flags untuk stability

    # Optimasi tambahan yang aman
    set(C_FLAGS "${C_FLAGS} -ffast-math")  # Optimasi math yang aman
    set(CXX_FLAGS "${CXX_FLAGS} -ffast-math")  # Optimasi math yang aman

    message(STATUS "ARCAMOD: Release build dengan optimasi konservatif untuk reliability")
else()
    # DEBUG BUILD: No optimization
    set(C_FLAGS "${C_FLAGS} -O0 -g")
    set(LINKER_FLAGS "${LINKER_FLAGS} -llog")

    message(STATUS "ARCAMOD: Debug build tanpa optimasi")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${C_FLAGS} ${CXX_FLAGS}")

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${LINKER_FLAGS}")

# Optimasi cache CPU dengan prefetch hint
add_definitions(-DUSE_CPU_PREFETCH)

# Menambahkan pustaka curl
add_library(curl STATIC IMPORTED)
set_property(TARGET curl PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ARCAMOD/Includes/curl/backends/${CMAKE_ANDROID_ARCH_ABI}/lib/libcurl.a)

# Menambahkan pustaka ssl
add_library(ssl STATIC IMPORTED)
set_property(TARGET ssl PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ARCAMOD/Includes/openssl/backends/${CMAKE_ANDROID_ARCH_ABI}/lib/libssl.a)

# Menambahkan pustaka crypto
add_library(crypto STATIC IMPORTED)
set_property(TARGET crypto PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ARCAMOD/Includes/openssl/backends/${CMAKE_ANDROID_ARCH_ABI}/lib/libcrypto.a)

# Menambahkan pustaka dobby
add_library(dobby STATIC IMPORTED)
set_property(TARGET dobby PROPERTY IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/ARCAMOD/Includes/DobbyHook/include/${CMAKE_ANDROID_ARCH_ABI}/libdobby.a)