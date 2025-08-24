//
// Created by @arcamod on 20/12/2024.
// Renamed to JavaBridge on 8/8/2025 for better organization
//
#include <jni.h>
#include <string>
extern "C" JNIEXPORT jstring JNICALL
Java_com_imgui_arcamod_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
        std::string hello = "Hello from C++";
        return env->NewStringUTF(hello.c_str());
}
