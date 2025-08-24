import java.util.zip.ZipFile
import java.io.File

plugins {
    id("com.android.application") version "8.12.1"
}

// Baca konfigurasi dari gradle.properties
val extractionFolderName = project.findProperty("extraction.folder")?.toString() ?: "extracted_libs"
val libName = project.findProperty("extraction.lib.name")?.toString() ?: "libarcamod.so"
val libPath = project.findProperty("extraction.lib.path")?.toString() ?: "lib/arm64-v8a/libarcamod.so"
val dexName = project.findProperty("extraction.dex.name")?.toString() ?: "classes.dex"
val dexPath = project.findProperty("extraction.dex.path")?.toString() ?: "classes.dex"

// Definisi folder ekstraksi di root proyek
val extractionFolder = File(rootProject.projectDir, extractionFolderName)

// Fungsi untuk mendeteksi build type dan menentukan NDK version
fun determineNdkVersion(): String {
    val taskNames = gradle.startParameter.taskNames
    val isDebugBuild = taskNames.any {
        it.contains("debug", ignoreCase = true) ||
        it.contains("Debug", ignoreCase = false)
    }
    val isReleaseBuild = taskNames.any {
        it.contains("release", ignoreCase = true) ||
        it.contains("Release", ignoreCase = false)
    }

    return when {
        isDebugBuild -> {
            println("🔧 ARCAMOD: Detected DEBUG build - Using NDK 25.2.9519653")
            "25.2.9519653"
        }
        isReleaseBuild -> {
            println("🚀 ARCAMOD: Detected RELEASE build - Using NDK 26.1.10909125")
            "26.1.10909125"
        }
        else -> {
            // Default ke release NDK jika tidak bisa mendeteksi
            println("⚠️ ARCAMOD: Could not detect build type - Defaulting to RELEASE NDK 26.1.10909125")
            "26.1.10909125"
        }
    }
}

// Tentukan NDK version berdasarkan build type
val selectedNdkVersion = determineNdkVersion()

// Force resolution strategy untuk memaksa versi dependency yang kompatibel dengan compileSdk 33
configurations.all {
    resolutionStrategy {
        force("androidx.activity:activity:1.7.2")
        force("androidx.core:core:1.9.0")
        force("androidx.core:core-ktx:1.9.0")
        force("androidx.annotation:annotation-experimental:1.3.0")
        force("androidx.profileinstaller:profileinstaller:1.3.0")
        force("androidx.transition:transition:1.2.0")
    }
}

android {
    namespace = "com.imgui.arcamod"
    compileSdk = 33

    defaultConfig {
        applicationId = "com.imgui.arcamod"
        minSdk = 24
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                cppFlags.add("-std=c++20") // Sinkronisasi standar C++ ke c++20
            }
        }
        ndk {
            abiFilters.add("arm64-v8a")
        }
    }

    buildTypes {
        debug {
            // Tambahkan definisi DEBUG untuk build debug
            externalNativeBuild {
                cmake {
                    arguments.add("-DANDROID_TOOLCHAIN=clang")
                    cppFlags.add("-DDEBUG") // Definisi makro DEBUG
                }
            }
        }

        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
            signingConfig = signingConfigs.getByName("debug")
            externalNativeBuild {
                cmake {
                    arguments.add("-DANDROID_TOOLCHAIN=clang") // Pastikan LLVM (Clang) digunakan
                    // RELIABLE BUILD: Hapus Ninja dan parallel untuk consistency
                    cppFlags.add("-DRELEASE") // Definisi makro RELEASE
                }
            }
        }
    }

    // Mengatur compiler args di Kotlin DSL
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    // Untuk menambahkan flag -Xlint:deprecation dalam kompilasi Java
    tasks.withType<JavaCompile> {
        options.compilerArgs.add("-Xlint:deprecation")
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }

    buildFeatures {
        viewBinding = true
    }

    // Konfigurasi resource untuk menghindari resource API 34+ saat menggunakan compileSdk 33
    androidResources {
        generateLocaleConfig = false
    }

    packaging {
        resources {
            excludes += "/META-INF/{AL2.0,LGPL2.1}"
        }
    }

    // Tambahan konfigurasi untuk menghindari resource API tinggi
    lint {
        disable += "NewApi"
        disable += "UnusedResources"
    }

    // NDK Version otomatis berdasarkan build type
    // Debug: 25.2.9519653, Release: 26.1.10909125
    ndkVersion = selectedNdkVersion
//    ndkVersion = "26.3.11579264"
}

dependencies {
    // Versi yang kompatibel dengan compileSdk 33 dengan exclude untuk mencegah transitive dependency bermasalah
    implementation("androidx.appcompat:appcompat:1.6.1") {
        exclude(group = "androidx.activity", module = "activity")
        exclude(group = "androidx.core", module = "core")
        exclude(group = "androidx.core", module = "core-ktx")
    }
    implementation("com.google.android.material:material:1.10.0") {
        exclude(group = "androidx.activity", module = "activity")
        exclude(group = "androidx.core", module = "core")
        exclude(group = "androidx.core", module = "core-ktx")
    }
    implementation("androidx.constraintlayout:constraintlayout:2.1.4") {
        exclude(group = "androidx.activity", module = "activity")
        exclude(group = "androidx.core", module = "core")
        exclude(group = "androidx.core", module = "core-ktx")
    }

    // Explicit implementation dengan versi yang kompatibel dengan compileSdk 33
    implementation("androidx.activity:activity:1.7.2")
    implementation("androidx.core:core:1.9.0")
    implementation("androidx.core:core-ktx:1.9.0")
    implementation("androidx.annotation:annotation-experimental:1.3.0")
    implementation("androidx.profileinstaller:profileinstaller:1.3.0")
    implementation("androidx.transition:transition:1.2.0")

    testImplementation("junit:junit:4.13.2")
    androidTestImplementation("androidx.test.ext:junit:1.1.5")
    androidTestImplementation("androidx.test.espresso:espresso-core:3.5.1")
}

android.applicationVariants.all {
    val variant = this
    variant.outputs.all {
        tasks.register("extractLib${variant.name.replaceFirstChar { it.uppercase() }}") {
            doLast {
                // Gunakan path relatif berdasarkan lokasi proyek
                val buildDir = project.layout.buildDirectory.asFile.get()
                val outputDir = File(buildDir, "outputs/apk/${variant.name}")

                // Buat folder ekstraksi khusus berdasarkan variant (debug/release)
                val extractDir = File(extractionFolder, variant.name)
                extractDir.mkdirs()

                val apkFile = if (variant.name == "release") {
                    File(outputDir, "app-release.apk")
                } else {
                    File(outputDir, "app-debug.apk")
                }

                println("Checking APK file: ${apkFile.absolutePath}")
                println("Output directory: ${outputDir.absolutePath}")
                println("Extraction directory: ${extractDir.absolutePath}")

                if (apkFile.exists()) {
                    println("APK file exists, starting extraction...")
                    try {
                        val zip = ZipFile(apkFile)
                        val entries = zip.entries()

                        while (entries.hasMoreElements()) {
                            val entry = entries.nextElement()
                            if (entry.name == libPath) {
                                println("Found $libName, extracting...")
                                val targetFile = File(extractDir, libName)
                                zip.getInputStream(entry).use { input ->
                                    targetFile.outputStream().use { output ->
                                        input.copyTo(output)
                                    }
                                }
                                println("Successfully extracted $libName to: ${targetFile.absolutePath}")

                                // Salin juga ke folder output APK untuk kompatibilitas
                                val legacyFile = File(outputDir, libName)
                                targetFile.copyTo(legacyFile, overwrite = true)
                                println("Also copied to: ${legacyFile.absolutePath}")
                            } else if (entry.name == dexPath) {
                                println("Found $dexName, extracting...")
                                val targetFile = File(extractDir, dexName)
                                zip.getInputStream(entry).use { input ->
                                    targetFile.outputStream().use { output ->
                                        input.copyTo(output)
                                    }
                                }
                                println("Successfully extracted $dexName to: ${targetFile.absolutePath}")

                                // Salin juga ke folder output APK untuk kompatibilitas
                                val legacyFile = File(outputDir, dexName)
                                targetFile.copyTo(legacyFile, overwrite = true)
                                println("Also copied to: ${legacyFile.absolutePath}")
                            }
                        }

                        zip.close()
                        println("Extraction process completed")
                    } catch (e: Exception) {
                        println("ERROR during extraction: ${e.message}")
                        e.printStackTrace()
                    }
                } else {
                    println("APK file not found at: ${apkFile.absolutePath}")
                }
            }
        }

        tasks.named("package${variant.name.replaceFirstChar { it.uppercase() }}") {
            finalizedBy("extractLib${variant.name.replaceFirstChar { it.uppercase() }}")
        }
    }
}