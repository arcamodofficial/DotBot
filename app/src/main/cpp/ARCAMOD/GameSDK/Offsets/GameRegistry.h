#ifndef ARCAMOD_GAME_REGISTRY_H
#define ARCAMOD_GAME_REGISTRY_H

#pragma once

#include <cstdint>
#include <cstring>

struct System$$StringStruct {
    void *klazz;
    void *instancezz;
    int32_t length;
    uint16_t start_char;

    char *get_string() {
        static char buffer[256];
        memset(buffer, 0, sizeof(buffer));

        if (length <= 0 || length > 100) return buffer;

        char *str = (char *) &start_char;
        for (int i = 0; i < length && i < 100; i++) {
            if (str[i * 2] >= 32 && str[i * 2] <= 126) {
                buffer[i] = str[i * 2];
            } else {
                buffer[i] = '*';
            }
        }

        return buffer;
    }
};

struct InventoryManagerStruct {
    void *klazz;
    void *instancezz;
    Il2CppList<void *> inventory_list;
    void *owner_pawn;
    void *m_LoadingWeapon;
    void *m_LoadingSubWeapon;
    void *m_FirstWeapon;
    void *m_SecondWeapon;
    void *m_CurrentSubWeapon;
    void *m_CurrentWeaponValue;
};
extern void *PlayerController;

void *Screen = nullptr;
int (*Screen$$get_height)();
int (*Screen$$get_width)();
float (*Screen$$get_dpi)();

void *Input = nullptr;
int (*Input$$get_touchCount)();
bool (*Input$$get_touchSupported)();

void *GamePlay = nullptr;
uintptr_t GamePlay$$get_Game;
void *(*GamePlay$$get_MatchGame)();
void *(*GamePlay$$get_LocalPawn)();

void *BaseGame = nullptr;

void *Pawn = nullptr;
void *(*Pawn$$GetRealPawnHeadPosition)(void *);

void *(*Pawn$$GetRootTransform)(void *);

void *(*Pawn$$GetHeadTransform)(void *);

System$$StringStruct *(*Pawn$$get_PlayerName)(void *);

unsigned int (*Pawn$$get_TeamId)(void *);

unsigned int (*Pawn$$get_RealTeamId)(void *);

unsigned int (*Pawn$$get_TeamSeatId)(void *);

void *(*Pawn$$get_CurrentWeapon)(void **);

void *(*Pawn$$get_CurrentWeaponAttachment)(void *);

void *(*Pawn$$get_InvManager)(void *);

void *(*Pawn$$get_RagdollComponent)(void *);

void *(*Pawn$$GetCurrentAnimator)(void *);





static inline void *GetPawnPlayerInfo(void *entity);
static inline const char *GetPlayerName(void *playerInfo);
template<typename T>
static inline bool isValidPtr(T *ptr) {
    return ptr != nullptr && reinterpret_cast<uintptr_t>(ptr) > 0x1000 && reinterpret_cast<uintptr_t>(ptr) < 0x7FFFFFFFFF;
}

static inline bool IsPawnAlive(void *entity) {
    if (!isValidPtr(entity)) return false;
    return *(bool *) ((uintptr_t) entity + Offsets::Pawn::IsAlive);
}

static inline bool IsPawnBot(void *entity) {
    if (!isValidPtr(entity)) return false;

    bool isDirectBot = *(bool *) ((uintptr_t) entity + Offsets::Pawn::IsBot);
    void *playerInfo = GetPawnPlayerInfo(entity);
    if (isValidPtr(playerInfo)) {
        int gamePlayerID_AI = *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID_AI);
        int gamePlayerID = *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID);

        if (gamePlayerID_AI > 0) {
            return true;
        }

        if (gamePlayerID == 0 && isDirectBot) {
            return true;
        }

        const char *name = GetPlayerName(playerInfo);
        if (name && (
                strstr(name, OBF("AI_")) == name ||
                strstr(name, OBF("Bot")) == name ||
                strstr(name, OBF("BOT_")) == name ||
                strstr(name, OBF("NPC")) == name)
                ) {
            return true;
        }
    }

    return isDirectBot;
}

static inline int GetBotID(void *entity) {
    if (!isValidPtr(entity)) return -1;
    void *playerInfo = GetPawnPlayerInfo(entity);
    if (isValidPtr(playerInfo)) {
        return *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID_AI);
    }
    return -1;
}

static inline int GetPlayerID(void *entity) {
    if (!isValidPtr(entity)) return -1;
    void *playerInfo = GetPawnPlayerInfo(entity);
    if (isValidPtr(playerInfo)) {
        return *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID);
    }
    return -1;
}

static inline void *GetPawnPlayerInfo(void *entity) {
    if (!isValidPtr(entity)) return nullptr;
    void *playerInfo = *(void **) ((uintptr_t) entity + Offsets::Pawn::PlayerInfo);
    if (!isValidPtr(playerInfo)) return nullptr;
    return playerInfo;
}

static inline void *GetPawnAttackableTarget(void *entity) {
    if (!isValidPtr(entity)) return nullptr;

    static void *lastEntity = nullptr;
    static void *lastAttackableTarget = nullptr;

    if (lastEntity == entity && isValidPtr(lastAttackableTarget)) {
        return lastAttackableTarget;
    }

    void *matchGame = nullptr;
    if (isValidPtr(GamePlay$$get_MatchGame)) {
        matchGame = GamePlay$$get_MatchGame();
    }

    if (isValidPtr(matchGame)) {
        void *attackableTargetDict = *(void **) ((uintptr_t) matchGame +
                                                 Offsets::BaseGame::AttackableTargetDictionary);

        if (isValidPtr(attackableTargetDict)) {
            void *playerInfo = GetPawnPlayerInfo(entity);
            if (isValidPtr(playerInfo)) {
                lastEntity = entity;
                lastAttackableTarget = playerInfo;
                return playerInfo;
            }
        }
    }

    lastEntity = entity;
    lastAttackableTarget = entity;
    return entity;
}

static inline void *GetAttackableTargetInfo(void *attackableTarget) {
    if (!isValidPtr(attackableTarget)) return nullptr;

    void *playerInfo = GetPawnPlayerInfo(attackableTarget);
    if (isValidPtr(playerInfo) && playerInfo == attackableTarget) {
        return attackableTarget;
    }

    void *attackableInfo = *(void **) ((uintptr_t) attackableTarget +
                                       Offsets::AttackableTarget::AttackableInfo);
    if (isValidPtr(attackableInfo)) {
        return attackableInfo;
    }

    return attackableTarget;
}

static inline void *GetEntityAttackableTargetInfo(void *entity) {
    if (!isValidPtr(entity)) return nullptr;
    void *attackableTarget = GetPawnAttackableTarget(entity);
    if (!isValidPtr(attackableTarget)) return nullptr;
    return GetAttackableTargetInfo(attackableTarget);
}

static inline float GetEntityHealth(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 0.0f;

    float health = *(float *) ((uintptr_t) attackableTargetInfo +
                               Offsets::AttackableTargetInfo::Health);

    if (health >= 0.0f && health <= 10000.0f) {
        return health;
    }

    void *playerInfo = GetPawnPlayerInfo(attackableTargetInfo);
    if (isValidPtr(playerInfo)) {
        health = *(float *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::Health);
        if (health >= 0.0f && health <= 10000.0f) {
            return health;
        }
    }

    return 0.0f;
}

static inline float GetEntityMaxHealth(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 100.0f;

    float maxHealth = *(float *) ((uintptr_t) attackableTargetInfo +
                                  Offsets::AttackableTargetInfo::MaxHealth);

    if (maxHealth > 0.0f && maxHealth <= 10000.0f) {
        return maxHealth;
    }

    void *playerInfo = GetPawnPlayerInfo(attackableTargetInfo);
    if (isValidPtr(playerInfo)) {
        maxHealth = *(float *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::MaxHealth);
        if (maxHealth > 0.0f && maxHealth <= 10000.0f) {
            return maxHealth;
        }
    }

    return 100.0f;
}

static inline float GetEntityExtraHealth(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 0.0f;
    return *(float *) ((uintptr_t) attackableTargetInfo +
                       Offsets::AttackableTargetInfo::ExtraHealth);
}

static inline float GetEntityMaxExtraHealth(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 0.0f;
    return *(float *) ((uintptr_t) attackableTargetInfo +
                       Offsets::AttackableTargetInfo::MaxExtraHealth);
}

static inline float GetEntitySignal(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 0.0f;
    return *(float *) ((uintptr_t) attackableTargetInfo + Offsets::AttackableTargetInfo::Signal);
}

static inline float GetEntityMaxSignal(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 100.0f;
    return *(float *) ((uintptr_t) attackableTargetInfo + Offsets::AttackableTargetInfo::MaxSignal);
}

static inline float GetEntityTotalHealth(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 0.0f;
    float baseHealth = GetEntityHealth(attackableTargetInfo);
    float extraHealth = GetEntityExtraHealth(attackableTargetInfo);
    return baseHealth + extraHealth;
}

static inline float GetEntityTotalMaxHealth(void *attackableTargetInfo) {
    if (!isValidPtr(attackableTargetInfo)) return 100.0f;
    float maxHealth = GetEntityMaxHealth(attackableTargetInfo);
    float maxExtraHealth = GetEntityMaxExtraHealth(attackableTargetInfo);
    return maxHealth + maxExtraHealth;
}

static inline float GetPlayerHealth(void *playerInfo) {
    if (!isValidPtr(playerInfo)) return 0.0f;

    float health = *(float *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::Health);

    if (health >= 0.0f && health <= 10000.0f) {
        return health;
    }

    return GetEntityHealth(playerInfo);
}

static inline float GetPlayerMaxHealth(void *playerInfo) {
    if (!isValidPtr(playerInfo)) return 100.0f;

    float maxHealth = *(float *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::MaxHealth);

    if (maxHealth > 0.0f && maxHealth <= 10000.0f) {
        return maxHealth;
    }

    return GetEntityMaxHealth(playerInfo);
}

static inline const char *GetPlayerNameDirect(void *entity) {
    static char nameBuff[64] = "";

    if (!isValidPtr(entity)) return OBF("Unknown");

    void *playerInfo = *(void **) ((uintptr_t) entity + Offsets::Pawn::PlayerInfo);
    if (!isValidPtr(playerInfo)) return "Unknown";

    void *nickNamePtr = *(void **) ((uintptr_t) playerInfo + Offsets::PlayerInfo::NickName);
    if (!isValidPtr(nickNamePtr)) return OBF("Unknown");

    System$$StringStruct *strStruct = (System$$StringStruct *) nickNamePtr;
    if (isValidPtr(strStruct->instancezz) && strStruct->length > 0 && strStruct->length < 100) {
        char *name = strStruct->get_string();
        if (name && name[0] != '\0') {
            strncpy(nameBuff, name, sizeof(nameBuff) - 1);
            nameBuff[sizeof(nameBuff) - 1] = '\0';
            return nameBuff;
        }
    }

    if (strStruct->length > 0 && strStruct->length < 64) {
        const char *rawChars = (const char *) &strStruct->start_char;
        memset(nameBuff, 0, sizeof(nameBuff));

        for (int i = 0; i < strStruct->length && i < 32; i++) {
            char c = rawChars[i * 2];
            if (isprint(c)) {
                nameBuff[i] = c;
            } else {
                nameBuff[i] = '*';
            }
        }

        if (nameBuff[0] != '\0') {
            return nameBuff;
        }
    }

    const char *directStr = (const char *) nickNamePtr;
    if (isValidPtr(directStr) && directStr[0] != '\0') {
        size_t len = strnlen(directStr, sizeof(nameBuff) - 1);
        if (len > 0 && len < sizeof(nameBuff)) {
            memset(nameBuff, 0, sizeof(nameBuff));
            strncpy(nameBuff, directStr, len);
            return nameBuff;
        }
    }

    void *indirectStr = *(void **) nickNamePtr;
    if (isValidPtr(indirectStr)) {
        const char *str = (const char *) indirectStr;
        size_t len = strnlen(str, sizeof(nameBuff) - 1);
        if (len > 0 && len < sizeof(nameBuff)) {
            memset(nameBuff, 0, sizeof(nameBuff));
            strncpy(nameBuff, str, len);
            return nameBuff;
        }
    }

    int gamePlayerID = *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID);
    int botID = *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID_AI);
    int teamID = *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::TeamID);

    if (botID > 0) {
        snprintf(nameBuff, sizeof(nameBuff), OBF("Bot_%d"), botID);
    } else if (gamePlayerID > 0) {
        snprintf(nameBuff, sizeof(nameBuff), OBF("Player_%d"), gamePlayerID);
    } else {
        snprintf(nameBuff, sizeof(nameBuff), OBF("Team%d_Player"), teamID);
    }

    return nameBuff;
}

static inline const char *GetPlayerName(void *playerInfo) {
    static char nameBuff[64] = "";

    if (!isValidPtr(playerInfo)) {
        return OBF("Unknown");
    }

    void *klass = *(void **) playerInfo;

        if (!isValidPtr(klass)) {
            return OBF("Unknown");
        }
        System$$StringStruct *nameStruct = *(System$$StringStruct **) ((uintptr_t) playerInfo +
                                                                       Offsets::PlayerInfo::NickName);

        if (isValidPtr(nameStruct)) {
            if (isValidPtr(nameStruct->instancezz) && nameStruct->length > 0 &&
                nameStruct->length < 64) {
                char *name = nameStruct->get_string();

                if (isValidPtr(name) && name[0] != '\0') {
                    strncpy(nameBuff, name, sizeof(nameBuff) - 1);
                    nameBuff[sizeof(nameBuff) - 1] = '\0';

                    for (int i = 0; i < sizeof(nameBuff) && nameBuff[i]; i++) {
                        if (!isprint(nameBuff[i])) {
                            nameBuff[i] = '*';
                        }
                    }

                    return nameBuff;
                }
            }
        }

        const char *directName = *(const char **) ((uintptr_t) playerInfo +
                                                   Offsets::PlayerInfo::NickName);
        if (isValidPtr(directName)) {
            size_t nameLen = strnlen(directName, sizeof(nameBuff) - 1);
            if (nameLen > 0 && nameLen < sizeof(nameBuff)) {
                strncpy(nameBuff, directName, nameLen);
                nameBuff[nameLen] = '\0';

                for (int i = 0; i < nameLen; i++) {
                    if (!isprint(nameBuff[i])) {
                        nameBuff[i] = '*';
                    }
                }

                return nameBuff;
            }
        }

        if (*(bool *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GamePlayerID_AI)) {
            return OBF("BOT");
        }

        return OBF("Unknown");
}

static inline bool IsPawnSkiing(void *entity) {
    if (!isValidPtr(entity)) return false;
    int skiingValue = *(int *)((uintptr_t)entity + Offsets::Pawn::IsSkiing);
    return (skiingValue | 1) == 29;
}

static inline int GetPlayerTeamID(void *playerInfo) {
    if (!isValidPtr(playerInfo)) return -1;
    int teamID = *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::TeamID);
    if (teamID < 0) teamID = 6;
    if (teamID >= 7) teamID = teamID % 7;
    return teamID;
}

static inline int GetPlayerLevel(void *playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::GameLevel);
}

void *AttackableTarget = nullptr;
Vector3 (*Transform$$get_position)(void *);
void *(*Camera$$get_main)();
Vector3 (*Camera$$WorldToScreenPoint)(void *, Vector3);
void *TutorialManager = nullptr;
void *Weapon = nullptr;
System$$StringStruct *(*Weapon$$get_WeaponNickName)(void *);
void *PlayerController = nullptr;
void *WeaponFireComponent_Instant = nullptr;
void *(*Component$$get_transform)(void *);
void *WeaponFireComponent = nullptr;



void *GameBase$$ObserverDelayManager = nullptr;
void *GameBase$$SkydivingPhysics = nullptr;
void *SlideTackleComponent = nullptr;
void *PlayerPawn = nullptr;

void (*PlayerPawn$$ShowFreeViewOcclustionEffect)(void *, bool);

void *(*PlayerPawn$$get_SpineBone)(void *);

void *(*PlayerPawn$$get_NeckBone)(void *);

void *(*PlayerPawn$$get_HipsBone)(void *);

void *(*PlayerPawn$$get_LeftAnkleBone)(void *);

void *(*PlayerPawn$$get_RightAnkleBone)(void *);


void *EffectInstance_SeeFrontGlow = nullptr;
void *WeaponAttachment = nullptr;

int (*WeaponAttachment$$get_WeaponName)(void *);

int (*WeaponAttachment$$get_WeaponID)(void *);

void *(*WeaponAttachment$$get_CurrentFireComponent)(void *);

void *(*WeaponAttachment$$get_InventoryInfo)(void *);

void *InventoryManager = nullptr;

void *(*InventoryManager$$get_CurrentWeapon)(void *);

void *(*InventoryManager$$GetPrimaryWeapon)(void *);

void *(*InventoryManager$$GetAWeapon)(void **, int);

void *(*InventoryManager$$CreateInventory)(void **, void *);

void *Inventory = nullptr;

System$$StringStruct *(*Inventory$$get_InventoryName)(void *);

int (*Inventory$$get_WeaponName)(void *);

System$$StringStruct *(*Inventory$$GetDefaultIconName)(void *, int, bool);

System$$StringStruct *(*Inventory$$GetInventoryName)(void *, int);



static inline std::string GetString(System$$StringStruct *str) {
    if (!str || !str->instancezz) return "";
    return std::string((char *) &str->start_char, str->length * 2);
}


enum TouchType {
    Direct = 0,
    Indirect = 1,
    Stylus = 2
};

enum TouchPhase {
    Began = 0,
    Moved = 1,
    Stationary = 2,
    Ended = 3,
    Canceled = 4
};

struct Touch {
    int m_FingerId;
    Vector2 m_Position;
    Vector2 m_RawPosition;
    Vector2 m_PositionDelta;
    float m_TimeDelta;
    int m_TapCount;
    TouchPhase m_Phase;
    TouchType m_Type;
    float m_Pressure;
    float m_maximumPossiblePressure;
    float m_Radius;
    float m_RadiusVariance;
    float m_AltitudeAngle;
    float m_AzimuthAngle;

    int get_fingerId();
    Vector2 get_position();
    Vector2 get_deltaPosition();
    float get_deltaTime();
    int get_tapCount();
    TouchPhase get_phase();
    TouchType get_type();
};

Touch (*Input$$GetTouch)(Touch, int);
void *PuppetMaster = nullptr;

void *(*PuppetMaster$$get_targetAnimator)(void *);

enum KeyCode {
    None = 0,
    Backspace = 8,
    Tabb = 9,
    Clear = 12,
    Return = 13,
    Pause = 19,
    Escape = 27,
    Space = 32,
    Keypad0 = 256,
    Keypad1 = 257,
    Keypad2 = 258,
    Keypad3 = 259,
    Keypad4 = 260,
    Keypad5 = 261,
    Keypad6 = 262,
    Keypad7 = 263,
    Keypad8 = 264,
    Keypad9 = 265,
    KeypadPeriod = 266,
    KeypadDivide = 267,
    KeypadMultiply = 268,
    KeypadMinus = 269,
    KeypadPlus = 270,
    KeypadEnter = 271,
    KeypadEquals = 272,
    UpArrow = 273,
    DownArrow = 274,
    RightArrow = 275,
    LeftArrow = 276,
    Insert = 277,
    Home = 278,
    End = 279,
    PageUp = 280,
    PageDown = 281,
    F1 = 282,
    F2 = 283,
    F3 = 284,
    F4 = 285,
    F5 = 286,
    F6 = 287,
    F7 = 288,
    F8 = 289,
    F9 = 290,
    F10 = 291,
    F11 = 292,
    F12 = 293,
    F13 = 294,
    F14 = 295,
    F15 = 296,
    Alpha0 = 48,
    Alpha1 = 49,
    Alpha2 = 50,
    Alpha3 = 51,
    Alpha4 = 52,
    Alpha5 = 53,
    Alpha6 = 54,
    Alpha7 = 55,
    Alpha8 = 56,
    Alpha9 = 57,
    Exclaim = 33,
    DoubleQuote = 34,
    Hash = 35,
    Dollar = 36,
    Percent = 37,
    Ampersand = 38,
    Quote = 39,
    LeftParen = 40,
    RightParen = 41,
    Asterisk = 42,
    Plus = 43,
    Comma = 44,
    Minus = 45,
    Period = 46,
    Slash = 47,
    Colon = 58,
    Semicolon = 59,
    Less = 60,
    Equals = 61,
    Greater = 62,
    Question = 63,
    At = 64,
    LeftBracket = 91,
    Backslash = 92,
    RightBracket = 93,
    Caret = 94,
    Underscore = 95,
    BackQuote = 96,
    A = 97,
    B = 98,
    C = 99,
    D = 100,
    E = 101,
    F = 102,
    G = 103,
    H = 104,
    I = 105,
    J = 106,
    K = 107,
    L = 108,
    M = 109,
    N = 110,
    O = 111,
    P = 112,
    Q = 113,
    R = 114,
    S = 115,
    T = 116,
    U = 117,
    V = 118,
    W = 119,
    X = 120,
    Y = 121,
    Z = 122,
    LeftCurlyBracket = 123,
    Pipe = 124,
    RightCurlyBracket = 125,
    Tilde = 126,
    Numlock = 300,
    CapsLock = 301,
    ScrollLock = 302,
    RightShift = 303,
    LeftShift = 304,
    RightControl = 305,
    LeftControl = 306,
    RightAlt = 307,
    LeftAlt = 308,
    RightCommand = 309,
    RightApple = 309,
    RightWindows = 309,
    LeftCommand = 310,
    LeftApple = 310,
    LeftWindows = 310,
    AltGr = 311,
    Help = 315,
    Print = 316,
    SysReq = 317,
    Break = 318,
    Menu = 319,
    Mouse0 = 323,
    Mouse1 = 324,
    Mouse2 = 325,
    Mouse3 = 326,
    Mouse4 = 327,
    Mouse5 = 328,
    Mouse6 = 329,
    JoystickButton0 = 330,
    JoystickButton1 = 331,
    JoystickButton2 = 332,
    JoystickButton3 = 333,
    JoystickButton4 = 334,
    JoystickButton5 = 335,
    JoystickButton6 = 336,
    JoystickButton7 = 337,
    JoystickButton8 = 338,
    JoystickButton9 = 339,
    JoystickButton10 = 340,
    JoystickButton11 = 341,
    JoystickButton12 = 342,
    JoystickButton13 = 343,
    JoystickButton14 = 344,
    JoystickButton15 = 345,
    JoystickButton16 = 346,
    JoystickButton17 = 347,
    JoystickButton18 = 348,
    JoystickButton19 = 349,
    MouseButton0 = 0,
    MouseButton1 = 1,
    MouseButton2 = 2,
    MouseButton3 = 3,
    MouseButton4 = 4,
    MouseButton5 = 5,
    MouseButton6 = 6,
    MouseButton7 = 7,
    MouseButton8 = 8,
    MouseButton9 = 9,
    MouseButton10 = 10,
    MouseButton11 = 11,
    MouseButton12 = 12,
    MouseButton13 = 13,
    MouseButton14 = 14,
    MouseButton15 = 15,
    Joystick1Button0 = 350,
    Joystick1Button1 = 351,
    Joystick1Button2 = 352,
    Joystick1Button3 = 353,
    Joystick1Button4 = 354,
    Joystick1Button5 = 355,
    Joystick1Button6 = 356,
    Joystick1Button7 = 357,
    Joystick1Button8 = 358,
    Joystick1Button9 = 359,
    Joystick1Button10 = 360,
    Joystick1Button11 = 361,
    Joystick1Button12 = 362,
    Joystick1Button13 = 363,
    Joystick1Button14 = 364,
    Joystick1Button15 = 365,
    Joystick1Button16 = 366,
    Joystick1Button17 = 367,
    Joystick1Button18 = 368,
    Joystick1Button19 = 369,
    Joystick2Button0 = 370,
    Joystick2Button1 = 371,
    Joystick2Button2 = 372,
    Joystick2Button3 = 373,
    Joystick2Button4 = 374,
    Joystick2Button5 = 375,
    Joystick2Button6 = 376,
    Joystick2Button7 = 377,
    Joystick2Button8 = 378,
    Joystick2Button9 = 379,
    Joystick2Button10 = 380,
    Joystick2Button11 = 381,
    Joystick2Button12 = 382,
    Joystick2Button13 = 383,
    Joystick2Button14 = 384,
    Joystick2Button15 = 385,
    Joystick2Button16 = 386,
    Joystick2Button17 = 387,
    Joystick2Button18 = 388,
    Joystick2Button19 = 389,
    Joystick3Button0 = 390,
    Joystick3Button1 = 391,
    Joystick3Button2 = 392,
    Joystick3Button3 = 393,
    Joystick3Button4 = 394,
    Joystick3Button5 = 395,
    Joystick3Button6 = 396,
    Joystick3Button7 = 397,
    Joystick3Button8 = 398,
    Joystick3Button9 = 399,
    Joystick3Button10 = 400,
    Joystick3Button11 = 401,
    Joystick3Button12 = 402,
    Joystick3Button13 = 403,
    Joystick3Button14 = 404,
    Joystick3Button15 = 405,
    Joystick3Button16 = 406,
    Joystick3Button17 = 407,
    Joystick3Button18 = 408,
    Joystick3Button19 = 409,
    Joystick4Button0 = 410,
    Joystick4Button1 = 411,
    Joystick4Button2 = 412,
    Joystick4Button3 = 413,
    Joystick4Button4 = 414,
    Joystick4Button5 = 415,
    Joystick4Button6 = 416,
    Joystick4Button7 = 417,
    Joystick4Button8 = 418,
    Joystick4Button9 = 419,
    Joystick4Button10 = 420,
    Joystick4Button11 = 421,
    Joystick4Button12 = 422,
    Joystick4Button13 = 423,
    Joystick4Button14 = 424,
    Joystick4Button15 = 425,
    Joystick4Button16 = 426,
    Joystick4Button17 = 427,
    Joystick4Button18 = 428,
    Joystick4Button19 = 429,
    Joystick5Button0 = 430,
    Joystick5Button1 = 431,
    Joystick5Button2 = 432,
    Joystick5Button3 = 433,
    Joystick5Button4 = 434,
    Joystick5Button5 = 435,
    Joystick5Button6 = 436,
    Joystick5Button7 = 437,
    Joystick5Button8 = 438,
    Joystick5Button9 = 439,
    Joystick5Button10 = 440,
    Joystick5Button11 = 441,
    Joystick5Button12 = 442,
    Joystick5Button13 = 443,
    Joystick5Button14 = 444,
    Joystick5Button15 = 445,
    Joystick5Button16 = 446,
    Joystick5Button17 = 447,
    Joystick5Button18 = 448,
    Joystick5Button19 = 449,
    Joystick6Button0 = 450,
    Joystick6Button1 = 451,
    Joystick6Button2 = 452,
    Joystick6Button3 = 453,
    Joystick6Button4 = 454,
    Joystick6Button5 = 455,
    Joystick6Button6 = 456,
    Joystick6Button7 = 457,
    Joystick6Button8 = 458,
    Joystick6Button9 = 459,
    Joystick6Button10 = 460,
    Joystick6Button11 = 461,
    Joystick6Button12 = 462,
    Joystick6Button13 = 463,
    Joystick6Button14 = 464,
    Joystick6Button15 = 465,
    Joystick6Button16 = 466,
    Joystick6Button17 = 467,
    Joystick6Button18 = 468,
    Joystick6Button19 = 469,
    Joystick7Button0 = 470,
    Joystick7Button1 = 471,
    Joystick7Button2 = 472,
    Joystick7Button3 = 473,
    Joystick7Button4 = 474,
    Joystick7Button5 = 475,
    Joystick7Button6 = 476,
    Joystick7Button7 = 477,
    Joystick7Button8 = 478,
    Joystick7Button9 = 479,
    Joystick7Button10 = 480,
    Joystick7Button11 = 481,
    Joystick7Button12 = 482,
    Joystick7Button13 = 483,
    Joystick7Button14 = 484,
    Joystick7Button15 = 485,
    Joystick7Button16 = 486,
    Joystick7Button17 = 487,
    Joystick7Button18 = 488,
    Joystick7Button19 = 489,
    Joystick8Button0 = 490,
    Joystick8Button1 = 491,
    Joystick8Button2 = 492,
    Joystick8Button3 = 493,
    Joystick8Button4 = 494,
    Joystick8Button5 = 495,
    Joystick8Button6 = 496,
    Joystick8Button7 = 497,
    Joystick8Button8 = 498,
    Joystick8Button9 = 499,
    Joystick8Button10 = 500,
    Joystick8Button11 = 501,
    Joystick8Button12 = 502,
    Joystick8Button13 = 503,
    Joystick8Button14 = 504,
    Joystick8Button15 = 505,
    Joystick8Button16 = 506,
    Joystick8Button17 = 507,
    Joystick8Button18 = 508,
    Joystick8Button19 = 509
};

enum HumanBodyBones {
    Hips = 0,
    Spine = 1,
    Chest = 2,
    UpperChest = 3,
    Neck = 4,
    Head = 5,
    LeftEye = 6,
    RightEye = 7,
    LeftShoulder = 8,
    RightShoulder = 9,
    LeftUpperArm = 10,
    RightUpperArm = 11,
    LeftLowerArm = 12,
    RightLowerArm = 13,
    LeftHand = 14,
    RightHand = 15,
    LeftToes = 16,
    RightToes = 17,
    Jaw = 20,
    LeftThumbProximal = 21,
    LeftThumbIntermediate = 22,
    LeftThumbDistal = 23,
    LeftIndexProximal = 24,
    LeftIndexIntermediate = 25,
    LeftIndexDistal = 26,
    LeftMiddleProximal = 27,
    LeftMiddleIntermediate = 28,
    LeftMiddleDistal = 29,
    LeftRingProximal = 30,
    LeftRingIntermediate = 31,
    LeftRingDistal = 32,
    LeftLittleProximal = 33,
    LeftLittleIntermediate = 34,
    LeftLittleDistal = 35,
    RightThumbProximal = 36,
    RightThumbIntermediate = 37,
    RightThumbDistal = 38,
    RightIndexProximal = 39,
    RightIndexIntermediate = 40,
    RightIndexDistal = 41,
    RightMiddleProximal = 42,
    RightMiddleIntermediate = 43,
    RightMiddleDistal = 44,
    RightRingProximal = 45,
    RightRingIntermediate = 46,
    RightRingDistal = 47,
    RightLittleProximal = 48,
    RightLittleIntermediate = 49,
    RightLittleDistal = 50
};

bool (*Input$$GetKeyDownInt)(void *, int);



void *PawnTopNameHUD = nullptr;

void (*PawnTopNameHUD$$Add)(void *, void *);

void *SystemInfo = nullptr;



struct Color {
    float r;
    float g;
    float b;
    float a;
};



static inline int GetVehicleTypeId(void *vehicle);
static inline bool IsVehicleHelicopter(int typeId);
static inline bool IsVehicleBoat(int typeId);
static inline bool IsVehicleHover(int typeId);
static inline bool IsVehicleTankType(int typeId);
static inline bool IsVehicleFast(void *vehicle);
static inline const char *GetVehicleTypeName(int typeId);
static inline bool GetAvailableVehicles(void *vehicle);

static inline void* GetAllVehicles(void* baseGame) {
    if (!isValidPtr(baseGame)) return nullptr;
    void* vehicleListPtr = *(void**)((uintptr_t)baseGame + Offsets::Vehicle::AllVehicles);
    if (!isValidPtr(vehicleListPtr)) return nullptr;
    return vehicleListPtr;
}

static inline Vector3 GetVehicleChassisPosition(void* vehicle) {
    Vector3 position = {0, 0, 0};
    if (!isValidPtr(vehicle)) return position;
    position.x = *(float*)((uintptr_t)vehicle + Offsets::Vehicle::ChassisCenter);
    position.y = *(float*)((uintptr_t)vehicle + Offsets::Vehicle::ChassisCenterY);
    position.z = *(float*)((uintptr_t)vehicle + Offsets::Vehicle::ChassisCenterZ);
    return position;
}

static inline void* GetVehicleTransform(void* vehicle) {
    if (!isValidPtr(vehicle)) return nullptr;
    void* transform = Component$$get_transform(vehicle);
    if (isValidPtr(transform)) {
        return transform;
    }
    return nullptr;
}

static inline float GetVehicleHealth(void* vehicle) {
    if (!isValidPtr(vehicle)) return 0.0f;
    void* attackableInfo = *(void**)((uintptr_t)vehicle + Offsets::AttackableTarget::AttackableInfo);
    if (isValidPtr(attackableInfo)) {
        float health = *(float*)((uintptr_t)attackableInfo + Offsets::AttackableTargetInfo::Health);
        if (health >= 0.0f && health <= 10000.0f) {
            return health;
        }
    }
    return 100.0f;
}

static inline float GetVehicleMaxHealth(void* vehicle) {
    if (!isValidPtr(vehicle)) return 100.0f;
    void* attackableInfo = *(void**)((uintptr_t)vehicle + Offsets::AttackableTarget::AttackableInfo);
    if (isValidPtr(attackableInfo)) {
        float maxHealth = *(float*)((uintptr_t)attackableInfo + Offsets::AttackableTargetInfo::MaxHealth);
        if (maxHealth > 0.0f && maxHealth <= 10000.0f) {
            return maxHealth;
        }
    }
    return 100.0f;
}

static inline bool IsVehicleAlive(void* vehicle) {
    if (!isValidPtr(vehicle)) return false;
    return GetVehicleHealth(vehicle) > 0.0f;
}

static inline bool IsVehicleBroken(void* vehicle) {
    if (!isValidPtr(vehicle)) return true;
    return GetVehicleHealth(vehicle) <= 0.0f;
}

static inline bool IsPawnOnVehicle(void *entity) {
    if (!isValidPtr(entity)) return false;
    int vehicleStatus = *(int *) ((uintptr_t) entity + Offsets::Pawn::IsOnVehicle);
    return vehicleStatus == 3;
}

static inline bool IsVehicleFast(void *vehicle) {
    if (!isValidPtr(vehicle)) return false;
    uint32_t speedTypeValue = *(uint32_t *) ((uintptr_t) vehicle +
                                             Offsets::Vehicle::FastVehicleCheck);
    return speedTypeValue == Offsets::Vehicle::FastVehicleIdentifier;
}

static inline bool HasVehicleSkiFeature(void *vehicle) {
    if (!isValidPtr(vehicle)) return false;
    void *skiingComponent = *(void **) ((uintptr_t) vehicle +
                                        Offsets::Vehicle::VehicleSkisData);
        if (!isValidPtr(skiingComponent)) {
            return false;
        }

        void *physVehicleSkis = *(void **) ((uintptr_t) skiingComponent +
                                            Offsets::Vehicle::PhysVehicleSkisOffset);

        return isValidPtr(physVehicleSkis);
}

static inline uint32_t GetBRVehicleID(void *vehicle) {
    if (!isValidPtr(vehicle)) return 0;
    int typeId = GetVehicleTypeId(vehicle);
    if (IsVehicleHelicopter(typeId)) {
        return Offsets::Vehicle::BRVehicleID::Helicopter;
    } else if (IsVehicleBoat(typeId) || IsVehicleHover(typeId) || HasVehicleSkiFeature(vehicle)) {
        return Offsets::Vehicle::BRVehicleID::AmphibiousVehicle;
    } else if (IsVehicleFast(vehicle)) {
        return Offsets::Vehicle::BRVehicleID::FastVehicle;
    } else if (IsVehicleTankType(typeId)) {
        return Offsets::Vehicle::BRVehicleID::SpecialVehicle;
    } else {
        return Offsets::Vehicle::BRVehicleID::BasicLandVehicle;
    }
}

static inline const char *GetBRVehicleName(void *vehicle) {
    if (!isValidPtr(vehicle)) return OBF("Unknown");

    uint32_t brVehicleID = GetBRVehicleID(vehicle);

    switch (brVehicleID) {
        case Offsets::Vehicle::BRVehicleID::Helicopter:
            return OBF("Helicopter");
        case Offsets::Vehicle::BRVehicleID::AmphibiousVehicle:
            return OBF("Amphibious");
        case Offsets::Vehicle::BRVehicleID::FastVehicle:
            return OBF("Sports");
        case Offsets::Vehicle::BRVehicleID::SpecialVehicle:
            return OBF("Tank");
        case Offsets::Vehicle::BRVehicleID::CustomVehicle:
            return OBF("Special");
        case Offsets::Vehicle::BRVehicleID::SecondaryVehicle:
            return OBF("Secondary");
        case Offsets::Vehicle::BRVehicleID::BasicLandVehicle:
        default:
            return GetVehicleTypeName(GetVehicleTypeId(vehicle));
    }
}



static inline bool GetAvailableVehicles(void *vehicle) {
    if (!isValidPtr(vehicle)) return false;
    bool isAvailable = *(bool *) ((uintptr_t) vehicle + Offsets::Vehicle::AvailableVehicles);
    return isAvailable;
}

static inline uint32_t GetBRVehicleAssetId(void *vehicle) {
    if (!isValidPtr(vehicle)) return 0;

    uint32_t brVehicleID = GetBRVehicleID(vehicle);

    switch (brVehicleID) {
        case Offsets::Vehicle::BRVehicleID::BasicLandVehicle:
            return Offsets::Vehicle::BRVehicleAssetID::BasicLandVehicle;

        case Offsets::Vehicle::BRVehicleID::SecondaryVehicle:
            return Offsets::Vehicle::BRVehicleAssetID::SecondaryVehicle;

        case Offsets::Vehicle::BRVehicleID::Helicopter:
            return Offsets::Vehicle::BRVehicleAssetID::Helicopter;

        case Offsets::Vehicle::BRVehicleID::AmphibiousVehicle:
            return Offsets::Vehicle::BRVehicleAssetID::AmphibiousVehicle;

        case Offsets::Vehicle::BRVehicleID::FastVehicle:
            return Offsets::Vehicle::BRVehicleAssetID::FastVehicle;

        case Offsets::Vehicle::BRVehicleID::SpecialVehicle:
            return Offsets::Vehicle::BRVehicleAssetID::SpecialVehicle;

        case Offsets::Vehicle::BRVehicleID::CustomVehicle:
            return Offsets::Vehicle::BRVehicleAssetID::CustomVehicle;

        default:
            return 0;
    }
}







static inline int GetTeamKillCount(void *playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::TeamKillCount);
}

static inline int GetPlayerKillCount(void *playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int *) ((uintptr_t) playerInfo + Offsets::PlayerInfo::KillEnemyCount);
}

static inline int GetPlayerDeathCount(void* playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int*)((uintptr_t)playerInfo + Offsets::PlayerInfo::DeathCount);
}

static inline int GetPlayerAssistCount(void* playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int*)((uintptr_t)playerInfo + Offsets::PlayerInfo::AssistCount);
}

static inline int GetPlayerHeadshotCount(void* playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int*)((uintptr_t)playerInfo + Offsets::PlayerInfo::HeadShotCount);
}

static inline int GetPlayerKillStreak(void* playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int*)((uintptr_t)playerInfo + Offsets::PlayerInfo::KillStreak);
}

static inline int GetPlayerTotalDamage(void* playerInfo) {
    if (!isValidPtr(playerInfo)) return 0;
    return *(int*)((uintptr_t)playerInfo + Offsets::PlayerInfo::TotalDamage);
}

static inline bool IsPlayerFiring(void* playerInfo) {
    if (!isValidPtr(playerInfo)) return false;
    return *(bool*)((uintptr_t)playerInfo + Offsets::PlayerInfo::IsFiringForUIShow);
}

extern Quaternion (*UnityEngine_Transform__get_rotation)(void *);

#endif // ARCAMOD_GAME_REGISTRY_H
