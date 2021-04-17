#pragma once
#include "Mof.h"

// マウス中央ボタン
#define MOFMOUSE_CENTERBUTTON 2

// ********************************************************************************
/// <summary>
/// 
/// </summary>
// ********************************************************************************
class MouseUtilities {
private:
    MouseUtilities(void) = delete;
    ~MouseUtilities(void) = delete;

public:

    static Vector3 GetWorldPos(void);

    static Vector2 GetPos(void);

    static Vector3 GetMove(void);

    static float GetWheelMove(void);

    static bool IsKeyPush(MofU32 mouse_key);
    static bool IsKeyHold(MofU32 mouse_key);
    static bool IsKeyPull(MofU32 mouse_key);
};

