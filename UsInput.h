#pragma once

#include "CoreMinimal.h"
#include "InputCoreTypes.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Components/InputComponent.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"

#pragma region KeyCodes
#define KEYCODE_NONE 0
#define KEYCODE_MOUSE_LEFT_KEY 0x1
#define KEYCODE_MOUSE_RIGHT_KEY 0x2
#define KEYCODE_MOUSE_MID_KEY 0x4
#define KEYCODE_BACKSPACE 8
#define KEYCODE_TAB 9
#define KEYCODE_CLEAR 12
#define KEYCODE_RETURN 13
#define KEYCODE_PAUSE 19
#define KEYCODE_ESCAPE 27
#define KEYCODE_SPACE 32
#define KEYCODE_EXCLAIM 33
#define KEYCODE_DOUBLEQUOTE 34
#define KEYCODE_HASH 35
#define KEYCODE_DOLLAR 36
#define KEYCODE_PERCENT 37
#define KEYCODE_AMPERSAND 38
#define KEYCODE_QUOTE 39
#define KEYCODE_LEFTPAREN 40
#define KEYCODE_RIGHTPAREN 41
#define KEYCODE_ASTERISK 42
#define KEYCODE_PLUS 43
#define KEYCODE_COMMA 44
#define KEYCODE_MINUS 45
#define KEYCODE_PERIOD 46
#define KEYCODE_SLASH 47
#define KEYCODE_ALPHA0 48
#define KEYCODE_ALPHA1 49
#define KEYCODE_ALPHA2 50
#define KEYCODE_ALPHA3 51
#define KEYCODE_ALPHA4 52
#define KEYCODE_ALPHA5 53
#define KEYCODE_ALPHA6 54
#define KEYCODE_ALPHA7 55
#define KEYCODE_ALPHA8 56
#define KEYCODE_ALPHA9 57
#define KEYCODE_COLON 58
#define KEYCODE_SEMICOLON 59
#define KEYCODE_LESS 60
#define KEYCODE_EQUALS 61
#define KEYCODE_GREATER 62
#define KEYCODE_QUESTION 63
#define KEYCODE_AT 64
#define KEYCODE_LEFTBRACKET 91
#define KEYCODE_BACKSLASH 92
#define KEYCODE_RIGHTBRACKET 93
#define KEYCODE_CARET 94
#define KEYCODE_UNDERSCORE 95
#define KEYCODE_BACKQUOTE 96
#define KEYCODE_A 65
#define KEYCODE_B 66
#define KEYCODE_C 67
#define KEYCODE_D 68
#define KEYCODE_E 69
#define KEYCODE_F 70
#define KEYCODE_G 71
#define KEYCODE_H 72
#define KEYCODE_I 73
#define KEYCODE_J 74
#define KEYCODE_K 75
#define KEYCODE_L 76
#define KEYCODE_M 77
#define KEYCODE_N 78
#define KEYCODE_O 79
#define KEYCODE_P 80
#define KEYCODE_Q 81
#define KEYCODE_R 82
#define KEYCODE_S 83
#define KEYCODE_T 84
#define KEYCODE_U 85
#define KEYCODE_V 86
#define KEYCODE_W 87
#define KEYCODE_X 88
#define KEYCODE_Y 89
#define KEYCODE_Z 90
#define KEYCODE_LEFTCURLYBRACKET 123
#define KEYCODE_PIPE 124
#define KEYCODE_RIGHTCURLYBRACKET 125
#define KEYCODE_TILDE 126
#define KEYCODE_DELETE 127
#define KEYCODE_KEYPAD0 256
#define KEYCODE_KEYPAD1 257
#define KEYCODE_KEYPAD2 258
#define KEYCODE_KEYPAD3 259
#define KEYCODE_KEYPAD4 260
#define KEYCODE_KEYPAD5 261
#define KEYCODE_KEYPAD6 262
#define KEYCODE_KEYPAD7 263
#define KEYCODE_KEYPAD8 264
#define KEYCODE_KEYPAD9 265
#define KEYCODE_KEYPADPERIOD 266
#define KEYCODE_KEYPADDIVIDE 267
#define KEYCODE_KEYPADMULTIPLY 268
#define KEYCODE_KEYPADMINUS 269
#define KEYCODE_KEYPADPLUS 270
#define KEYCODE_KEYPADENTER 271
#define KEYCODE_KEYPADEQUALS 272
#define KEYCODE_UPARROW 273
#define KEYCODE_DOWNARROW 274
#define KEYCODE_RIGHTARROW 275
#define KEYCODE_LEFTARROW 276
#define KEYCODE_INSERT 277
#define KEYCODE_HOME 278
#define KEYCODE_END 279
#define KEYCODE_PAGEUP 280
#define KEYCODE_PAGEDOWN 281
#define KEYCODE_F1 282
#define KEYCODE_F2 283
#define KEYCODE_F3 284
#define KEYCODE_F4 285
#define KEYCODE_F5 286
#define KEYCODE_F6 287
#define KEYCODE_F7 288
#define KEYCODE_F8 289
#define KEYCODE_F9 290
#define KEYCODE_F10 291
#define KEYCODE_F11 292
#define KEYCODE_F12 293
#define KEYCODE_F13 294
#define KEYCODE_F14 295
#define KEYCODE_F15 296
#define KEYCODE_NUMLOCK 300
#define KEYCODE_CAPSLOCK 301
#define KEYCODE_SCROLLLOCK 302
#define KEYCODE_RIGHTSHIFT 303
#define KEYCODE_LEFTSHIFT 304
#define KEYCODE_RIGHTCONTROL 305
#define KEYCODE_LEFTCONTROL 306
#define KEYCODE_RIGHTALT 307
#define KEYCODE_LEFTALT 308
#define KEYCODE_RIGHTMETA 309
#define KEYCODE_RIGHTCOMMAND 309
#define KEYCODE_RIGHTAPPLE 309
#define KEYCODE_LEFTMETA 310
#define KEYCODE_LEFTCOMMAND 310
#define KEYCODE_LEFTAPPLE 310
#define KEYCODE_LEFTWINDOWS 311
#define KEYCODE_RIGHTWINDOWS 312
#define KEYCODE_ALTGR 313
#define KEYCODE_HELP 315
#define KEYCODE_PRINT 316
#define KEYCODE_SYSREQ 317
#define KEYCODE_BREAK 318
#define KEYCODE_MENU 319
#pragma endregion

class UsInput {

public:

    static UsInput* Instance() {

        if (sIsReleased) return nullptr;

        if (sInstance == nullptr) {
            sInstance = CreateInstance();
        }
        return sInstance;
    }

    static void ReleasedStateRestore() {
        sIsReleased = false;
    }

    static void Release() {
        if (sInstance != nullptr) {
            delete sInstance;
            sInstance = nullptr;
            sIsReleased = true;
        }
    }

private:
    static UsInput* CreateInstance() {
        UsInput* result = new UsInput();

        return result;
    }

private:
    static UsInput* sInstance;
    static bool sIsReleased;

private:
    TMap<FName, bool> mIsPressMap;
    TMap<FName, float> mAxisMap;
    UInputComponent* mInputComponent;

    void (*pfButtonEventDelegate)(const FKey&) = nullptr;
    void (*pfAxisEventDelegate)(const FKey&) = nullptr;

    void ButtonEventCallback(const FKey& key) const;
    void AxisEventCallback(const FKey& key) const;

public:

    void InitializeInput(const AActor* contextObject);
    void ReleaseInput();

    void SetButtonEventCallback(void (*pf)(const FKey&));
    void SetAxisEventCallback(void (*pf)(const FKey&));

    bool IsPress(const uint32 keyCode) const;
    bool IsPress(const FKey& key) const;
    float AxisValue(const FKey& key) const;
};

bool UsInput::sIsReleased = false;
UsInput* UsInput::sInstance = nullptr;
