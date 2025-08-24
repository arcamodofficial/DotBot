// Top-level build file where you can add configuration options common to all sub-projects/modules.
plugins {
    id("com.android.application") version "8.12.1" apply false
    id("com.android.library") version "8.12.1" apply false
    id("org.jetbrains.kotlin.android") version "2.0.20" apply false
}

// Global resolution strategy untuk memaksa versi dependency yang kompatibel dengan compileSdk 33
allprojects {
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
}

tasks.register<Delete>("clean") {
    delete(file("$rootDir/build")) // Menggunakan $rootDir untuk akses direktori build
}
