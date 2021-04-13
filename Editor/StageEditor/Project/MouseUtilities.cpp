#include "MouseUtilities.h"

Vector3 MouseUtilities::GetWorldPos(void) {

    Vector2 mouse_pos = MouseUtilities::GetPos();

    LPCamera camera = CGraphicsUtilities::GetCamera();
    Vector3 cv;
    camera->ScreenToWorld(mouse_pos, cv);

    Vector3 camera_pos = camera->GetViewPosition();

    cv *= camera_pos.y / -cv.y;

    return camera_pos + cv;
}

Vector2 MouseUtilities::GetPos(void) {
    Vector2 mouse_pos;
    g_pInput->GetMousePos(mouse_pos);
    return mouse_pos;
}

Vector3 MouseUtilities::GetMove(void) {
    Vector3 move;
    g_pInput->GetMouseMove(move);
    return move;
}

float MouseUtilities::GetWheelMove(void) {
    return g_pInput->GetMouseWheelMove();
}

bool MouseUtilities::IsKeyPush(MofU32 mouse_key) {
    return g_pInput->IsMouseKeyPush(mouse_key);
}

bool MouseUtilities::IsKeyHold(MofU32 mouse_key) {
    return g_pInput->IsMouseKeyHold(mouse_key);
}

bool MouseUtilities::IsKeyPull(MofU32 mouse_key) {
    return g_pInput->IsMouseKeyPull(mouse_key);
}
