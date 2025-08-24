#include "ARCAMOD/GlobalIncludes.h"
#include "LIBANOGS/Monitoring.h"
#include <signal.h>

#define arcamod "libanogs.so"
#define UNITY_LIBRARY "libunity.so"
#define BYPASS_PATCH "000080D2C0035FD6"

static void (*old_il2cpp_init)(const char *, const char *);

static __int64 h_GameEngine_SystemSetting__set_EnableVulkan(__int64 a1) {
    static bool startupHandled = false;
    if (!startupHandled) {
        startupHandled = true;
        return 0;
    }
    return o_GameEngine_SystemSetting__set_EnableVulkan(a1);
}

static void hook_il2cpp_init(const char *domain_name, const char *version) PASS_OBF PASS_OBF_STRING {
    old_il2cpp_init(domain_name, version);
    CALL(&init_unity);
}

static bool initialize_anogs_hooks() PASS_OBF PASS_OBF_STRING {
    WhileHook(HOOK2(arcamod, "0x13243C", h_sub_13243C, o_sub_13243C));
    WhileHook(HOOK2(arcamod, "0x11B300", h_sub_11B300, o_sub_11B300));
    WhileHook(HOOK2(arcamod, "0x1EF62C", h_sub_1EF62C, o_sub_1EF62C));
    
    return initialize_monitoring_hooks(); // === MONITORING HOOKS - Managed by Monitoring.h ===
}

static bool apply_anogs_patches() PASS_OBF PASS_OBF_STRING {
    WhilePatch(PATCH(arcamod, "0x2DAB74", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x2080EC", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x26DE88", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x10D330", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x10CC84", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x12129C", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x24D1E4", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x1008AC", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x1423A8", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x1B4808", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x2B28E4", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x1F1028", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x24A458", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x1B434C", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x205DA8", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x205644", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x287724", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x26E244", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x2D8394", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x2491D8", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x218D88", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x208F38", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x110FFC", BYPASS_PATCH));
    WhilePatch(PATCH(arcamod, "0x13CBE8", BYPASS_PATCH));
    return true;
}

static void *anogs_thread(void *) PASS_OBF PASS_OBF_STRING {
    do {} while (!IsLoaded(arcamod));
    read_proc_maps(OBF(arcamod));
    Config.Init.Ready = false;
    do {} while (!initialize_anogs_hooks());
    do {} while (!apply_anogs_patches());
    Config.Init.Ready = true;
    CALL(&pthread_exit, nullptr);
}

static bool initialize_unity_hooks() PASS_OBF PASS_OBF_STRING {
    if (!HOOK_BATCH(UNITY_LIBRARY,
                    il2cpp_init, hook_il2cpp_init, old_il2cpp_init,
                    GameEngine_SystemSetting__set_EnableVulkan, h_GameEngine_SystemSetting__set_EnableVulkan, o_GameEngine_SystemSetting__set_EnableVulkan)) return false;
    if (!HOOKSYM_LIB(UNITY_LIBRARY, "eglSwapBuffers", h_fake_eglSwapBuffers, o_eglSwapBuffers)) return false;
    return true;
}

static bool setup_lobby_detection() PASS_OBF PASS_OBF_STRING {
    const int MAX_ATTEMPTS = 3;
    for (int attempt = 0; attempt < MAX_ATTEMPTS; attempt++) {
        if (SetupLobbyDetectionHook()) {
            init_lobby_detection();
            return true;
        }
    }
    return false;
}

static void *unity_thread(void *) PASS_OBF PASS_OBF_STRING {
    do {} while (!IsLoaded(UNITY_LIBRARY));
    do {} while (!initialize_unity_hooks());
    setup_lobby_detection();
    Config.Init.EGLReady = true;
    CALL(&pthread_exit, nullptr);
}

static void cleanup_signal_handler(int signal) PASS_OBF PASS_OBF_STRING {
    // StopRuntimeMonitor();

    extern void CleanupResources();
    CleanupResources();
    exit(signal);
}

static bool create_worker_thread(pthread_t *thread, void *(*start_routine)(void *), const char *thread_name) PASS_OBF PASS_OBF_STRING {
    if (CALL(&pthread_create, thread, nullptr, start_routine, nullptr) != 0) {
        fprintf(stderr, OBF("Error: Cannot create %s!\n"), thread_name);
        kill(getppid(), -1);
        abort();
        return false;
    }
    CALL(&pthread_detach, *thread);
    return true;
}

static void initialize_security_systems() PASS_OBF PASS_OBF_STRING {
    CALL(&RemapTools::RemapLibrary, OBF("libarcamod.so"));
    set_expiration_date();
}

__attribute__((constructor))
void lib_main_call() PASS_OBF PASS_OBF_STRING {
    initialize_security_systems();

    // Start LibAnogs runtime monitoring
    // StartRuntimeMonitor();

    pthread_t anogs_thread_id, unity_thread_id;
    create_worker_thread(&anogs_thread_id, anogs_thread, "anogs_thread");
    create_worker_thread(&unity_thread_id, unity_thread, "unity_thread");
}