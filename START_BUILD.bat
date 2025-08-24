@echo off
setlocal enabledelayedexpansion

:input
echo ========================================
echo ARCAMOD Build System - Debug/Release
echo ========================================
echo.
echo Pilih jenis build yang ingin dijalankan:
echo [1] Debug Build   (NDK 25.2.9519653 + Debug flags)
echo [2] Release Build (NDK 26.1.10909125 + Release flags)
echo [3] Both (Debug + Release)
echo [4] Exit
echo.
set /p choice="Masukkan pilihan (1-4): "

if "%choice%"=="4" goto exit
if "%choice%" NEQ "1" if "%choice%" NEQ "2" if "%choice%" NEQ "3" (
    echo Invalid choice. Please try again.
    goto input
)

set /a round=1

:build_loop
if !round! gtr 2 goto end

echo.
echo === ROUND !round! / 2 ===

if "%choice%"=="1" goto debug_build
if "%choice%"=="2" goto release_build
if "%choice%"=="3" goto both_build
goto end

:debug_build
echo.
echo ========================================
echo DEBUG BUILD STARTED (Round !round!)
echo ========================================
echo [INFO] Stopping Gradle daemon...
call gradlew --stop

echo [INFO] Cleaning project...
call gradlew clean

echo [INFO] Removing extracted_libs folder...
if exist "extracted_libs" (
    rmdir /s /q "extracted_libs"
    echo ✅ extracted_libs folder removed
) else (
    echo ℹ️ extracted_libs folder not found
)

echo [INFO] Removing app\build folder...
if exist "app\build" (
    rmdir /s /q "app\build"
    echo ✅ app\build folder removed
) else (
    echo ℹ️ app\build folder not found
)

echo [INFO] Removing app\.cxx folder...
if exist "app\.cxx" (
    rmdir /s /q "app\.cxx"
    echo ✅ app\.cxx folder removed
) else (
    echo ℹ️ app\.cxx folder not found
)

echo [INFO] Building Debug with Auto Extract...
call gradlew assembleDebug

echo.
echo [INFO] Checking if debug extraction worked...
if exist "extracted_libs\debug\libarcamod.so" (
    echo ✅ SUCCESS: Debug lib extracted successfully!
    echo File location: extracted_libs\debug\libarcamod.so
) else (
    echo ❌ FAILED: Debug lib not found
    echo Checking APK location...
    dir /s "app\build\outputs\apk\debug" 2>nul
)
goto next_round

:release_build
echo.
echo ========================================
echo RELEASE BUILD STARTED (Round !round!)
echo ========================================
echo [INFO] Stopping Gradle daemon...
call gradlew --stop

echo [INFO] Cleaning project...
call gradlew clean

echo [INFO] Removing extracted_libs folder...
if exist "extracted_libs" (
    rmdir /s /q "extracted_libs"
    echo ✅ extracted_libs folder removed
) else (
    echo ℹ️ extracted_libs folder not found
)

echo [INFO] Removing app\build folder...
if exist "app\build" (
    rmdir /s /q "app\build"
    echo ✅ app\build folder removed
) else (
    echo ℹ️ app\build folder not found
)

echo [INFO] Removing app\.cxx folder...
if exist "app\.cxx" (
    rmdir /s /q "app\.cxx"
    echo ✅ app\.cxx folder removed
) else (
    echo ℹ️ app\.cxx folder not found
)

echo [INFO] Building Release with Auto Extract...
call gradlew assembleRelease

echo.
echo [INFO] Checking if release extraction worked...
if exist "extracted_libs\release\libarcamod.so" (
    echo ✅ SUCCESS: Release lib extracted successfully!
    echo File location: extracted_libs\release\libarcamod.so
) else (
    echo ❌ FAILED: Release lib not found
    echo Checking APK location...
    dir /s "app\build\outputs\apk\release" 2>nul
)
goto next_round

:both_build
echo.
echo ========================================
echo BUILDING BOTH DEBUG AND RELEASE (Round !round!)
echo ========================================
echo [INFO] Stopping Gradle daemon...
call gradlew --stop

echo [INFO] Cleaning project...
call gradlew clean

echo [INFO] Removing extracted_libs folder...
if exist "extracted_libs" (
    rmdir /s /q "extracted_libs"
    echo ✅ extracted_libs folder removed
) else (
    echo ℹ️ extracted_libs folder not found
)

echo [INFO] Removing app\build folder...
if exist "app\build" (
    rmdir /s /q "app\build"
    echo ✅ app\build folder removed
) else (
    echo ℹ️ app\build folder not found
)

echo [INFO] Removing app\.cxx folder...
if exist "app\.cxx" (
    rmdir /s /q "app\.cxx"
    echo ✅ app\.cxx folder removed
) else (
    echo ℹ️ app\.cxx folder not found
)

echo [INFO] Building Debug first...
call gradlew assembleDebug

echo [INFO] Building Release...
call gradlew assembleRelease

echo.
echo === DEBUG RESULTS ===
if exist "extracted_libs\debug\libarcamod.so" (
    echo ✅ SUCCESS: Debug lib extracted successfully!
    echo File location: extracted_libs\debug\libarcamod.so
) else (
    echo ❌ FAILED: Debug lib not found
)

echo.
echo === RELEASE RESULTS ===
if exist "extracted_libs\release\libarcamod.so" (
    echo ✅ SUCCESS: Release lib extracted successfully!
    echo File location: extracted_libs\release\libarcamod.so
) else (
    echo ❌ FAILED: Release lib not found
)
goto next_round

:next_round
set /a round+=1
goto build_loop

:end
echo.
echo ========================================
echo ✅ BUILD PROCESS COMPLETED (2 ROUNDS)
echo ========================================
pause
exit /b

:exit
echo.
echo Anda memilih keluar. Menutup program...
pause
exit /b