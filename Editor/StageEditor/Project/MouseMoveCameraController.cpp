#include "MouseMoveCameraController.h"
#include "Define.h"
#include "MouseUtilities.h"
#include "ParameterMap.h"

// ********************************************************************************
/// <summary>
/// マウスでの操作情報を返す
/// </summary>
/// <returns>コントロール情報</returns>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
CameraController::Controller MouseMoveCameraController::MouseMoveController(void) {
    // カメラ制御用
    CameraController::Controller controller;

    // エディタのモード
    int edit_mode = *ParameterMap<int>::GetInstance().Get("edit_mode");

    if (edit_mode & EditHand) {
        controller = ModeHand();
    }
    else if (edit_mode & EditEye) {
        controller = ModeEye();
    }
    else if (edit_mode & InstObject) {
        controller = ModeInstObject();
    }

    return controller;
}

CameraController::Controller MouseMoveCameraController::ModeHand(void) {
    // カメラ制御用
    CameraController::Controller controller;

    // マウス移動量
    Vector3 mouse_move = MouseUtilities::GetMove();

    // 回転
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_RBUTTON);
    controller.rotation.move = mouse_move * camera_move_rotation_ratio;

    // ズーム
    bool zoom_trigger = (mouse_move.z != 0.0f);
    float zoom_move = mouse_move.z * camera_move_zoom_ratio;
    if (MouseUtilities::IsKeyHold(MOFMOUSE_CENTERBUTTON)) {
        zoom_trigger = (mouse_move.y != 0.0f);
        zoom_move = -mouse_move.y * camera_move_zoom_hold_ratio;
    }
    controller.zoom.trigger_flag = zoom_trigger;
    controller.zoom.move = zoom_move;

    // トラック
    bool track_trigger = MouseUtilities::IsKeyHold(MOFMOUSE_LBUTTON);
    controller.track.trigger_flag = track_trigger;
    controller.track.move = mouse_move * camera_move_track_ratio;

    return controller;
}

CameraController::Controller MouseMoveCameraController::ModeEye(void) {
    // カメラ制御用
    CameraController::Controller controller;

    // マウス移動量
    Vector3 mouse_move = MouseUtilities::GetMove();

    // 回転
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_LBUTTON);
    controller.rotation.move         = mouse_move * camera_move_rotation_ratio;

    // ズーム
    bool zoom_trigger = (mouse_move.z != 0.0f);
    float zoom_move   = mouse_move.z * camera_move_zoom_ratio;
    if (MouseUtilities::IsKeyHold(MOFMOUSE_CENTERBUTTON)) {
        zoom_trigger = (mouse_move.y != 0.0f);
        zoom_move    = -mouse_move.y * camera_move_zoom_hold_ratio;
    }
    controller.zoom.trigger_flag = zoom_trigger;
    controller.zoom.move         = zoom_move;

    return controller;
}

CameraController::Controller MouseMoveCameraController::ModeInstObject(void) {
    // カメラ制御用
    CameraController::Controller controller;

    // マウス移動量
    Vector3 mouse_move = MouseUtilities::GetMove();

    // 回転
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_RBUTTON);
    controller.rotation.move = mouse_move * camera_move_rotation_ratio;

    // ズーム
    bool zoom_trigger = (mouse_move.z != 0.0f);
    float zoom_move   = mouse_move.z * camera_move_zoom_ratio;
    if (MouseUtilities::IsKeyHold(MOFMOUSE_CENTERBUTTON)) {
        zoom_trigger = (mouse_move.y != 0.0f);
        zoom_move    = -mouse_move.y * camera_move_zoom_hold_ratio;
    }
    controller.zoom.trigger_flag = zoom_trigger;
    controller.zoom.move         = zoom_move;

    return controller;
}

// ********************************************************************************
/// <summary>
/// 更新
/// </summary>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void MouseMoveCameraController::Update(void) {
    CameraController::Update(MouseMoveController());
}
