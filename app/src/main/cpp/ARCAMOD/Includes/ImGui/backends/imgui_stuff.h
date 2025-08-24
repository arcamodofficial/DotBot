#pragma once
#include <jni.h>

extern JavaVM *jvm;


std::string getClipboard() {
    std::string result;
    JNIEnv *env;

    jvm->AttachCurrentThread(&env, NULL);

    auto looperClass = env->FindClass(OBF("android/os/Looper"));
    auto prepareMethod = env->GetStaticMethodID(looperClass, OBF("prepare"), OBF("()V"));
    env->CallStaticVoidMethod(looperClass, prepareMethod);

    jclass activityThreadClass = env->FindClass(OBF("android/app/ActivityThread"));
    jfieldID sCurrentActivityThreadField = env->GetStaticFieldID(activityThreadClass, OBF("sCurrentActivityThread"), OBF("Landroid/app/ActivityThread;"));
    jobject sCurrentActivityThread = env->GetStaticObjectField(activityThreadClass, sCurrentActivityThreadField);

    jfieldID mInitialApplicationField = env->GetFieldID(activityThreadClass, OBF("mInitialApplication"), OBF("Landroid/app/Application;"));
    jobject mInitialApplication = env->GetObjectField(sCurrentActivityThread, mInitialApplicationField);

    auto contextClass = env->FindClass(OBF("android/content/Context"));
    auto getSystemServiceMethod = env->GetMethodID(contextClass, OBF("getSystemService"), OBF("(Ljava/lang/String;)Ljava/lang/Object;"));

    auto str = env->NewStringUTF(OBF("clipboard"));
    auto clipboardManager = env->CallObjectMethod(mInitialApplication, getSystemServiceMethod, str);
    env->DeleteLocalRef(str);

    auto ClipboardManagerClass = env->FindClass(OBF("android/content/ClipboardManager"));
    auto getText = env->GetMethodID(ClipboardManagerClass, OBF("getText"), OBF("()Ljava/lang/CharSequence;"));

    auto CharSequenceClass = env->FindClass(OBF("java/lang/CharSequence"));
    auto toStringMethod = env->GetMethodID(CharSequenceClass, OBF("toString"), OBF("()Ljava/lang/String;"));

    auto text = env->CallObjectMethod(clipboardManager, getText);
    if (text) {
        str = (jstring) env->CallObjectMethod(text, toStringMethod);
        result = env->GetStringUTFChars(str, 0);
        env->DeleteLocalRef(str);
        env->DeleteLocalRef(text);
    }
    env->DeleteLocalRef(CharSequenceClass);
    env->DeleteLocalRef(ClipboardManagerClass);
    env->DeleteLocalRef(clipboardManager);
    env->DeleteLocalRef(contextClass);
    env->DeleteLocalRef(mInitialApplication);
    env->DeleteLocalRef(activityThreadClass);
    jvm->DetachCurrentThread();
    return result.c_str();
}