# ProGuard rules for your project

# Suppress warnings for javax.lang.model.element.Modifier
-dontwarn javax.lang.model.element.Modifier

# If your project uses WebView with JS, uncomment the following
# and specify the fully qualified class name to the JavaScript interface class:
# -keepclassmembers class fqcn.of.javascript.interface.for.webview {
#    public *;
#}

# If your project uses native methods, you need to preserve them:
# Jaga semua metode native agar tidak terubah
-keepclassmembers class * {
    native <methods>;
}

# Suppress log method warnings (removes log methods)
-assumenosideeffects class android.util.Log {
    public static *** d(...);
    public static *** v(...);
    public static *** i(...);
    public static *** w(...);
    public static *** e(...);
}

# Uncomment this to preserve the line number information for debugging stack traces
-keepattributes SourceFile,LineNumberTable

# If you keep the line number information, uncomment this to hide the original source file name
# -renamesourcefileattribute SourceFile

# Add more custom rules as necessary, for example:
# -keep class com.example.yourpackage.** { *; }
# -keep class com.imgui.arcamod.** { *; }

# Keep specific libraries from being obfuscated or minified (Optional)
# -keep class com.some.library.** { *; }

# If using reflection, you should preserve specific classes or methods that might be accessed via reflection
-keepclassmembers class * {
    public <methods>;
}

# If you use Kotlin, you might need to keep these classes for reflection:
-keep class kotlin.** { *; }
-dontwarn kotlin.**

# Keep native classes for JNI (Native interfaces)
-keepclasseswithmembers class * {
    native <methods>;
}

# Protect methods or classes used by reflection
-keepclassmembers class * {
    @android.webkit.JavascriptInterface <methods>;
}

# Keep serializable classes from being obfuscated (Optional)
-keepclassmembers class * implements java.io.Serializable {
    static final long serialVersionUID;
}

# If you have any third-party libraries, check their documentation for ProGuard rules and add them here
# For example, if you're using Firebase or other libraries, they might have specific keep rules.
