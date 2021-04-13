#include "MouseMoveCameraController.h"
#include "Define.h"
#include "MouseUtilities.h"
#include "ParameterMap.h"

// ********************************************************************************
/// <summary>
/// �}�E�X�ł̑������Ԃ�
/// </summary>
/// <returns>�R���g���[�����</returns>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
CameraController::Controller MouseMoveCameraController::MouseMoveController(void) {
    // �J��������p
    CameraController::Controller controller;

    // �G�f�B�^�̃��[�h
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
    // �J��������p
    CameraController::Controller controller;

    // �}�E�X�ړ���
    Vector3 mouse_move = MouseUtilities::GetMove();

    // ��]
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_RBUTTON);
    controller.rotation.move = mouse_move * camera_move_rotation_ratio;

    // �Y�[��
    bool zoom_trigger = (mouse_move.z != 0.0f);
    float zoom_move = mouse_move.z * camera_move_zoom_ratio;
    if (MouseUtilities::IsKeyHold(MOFMOUSE_CENTERBUTTON)) {
        zoom_trigger = (mouse_move.y != 0.0f);
        zoom_move = -mouse_move.y * camera_move_zoom_hold_ratio;
    }
    controller.zoom.trigger_flag = zoom_trigger;
    controller.zoom.move = zoom_move;

    // �g���b�N
    bool track_trigger = MouseUtilities::IsKeyHold(MOFMOUSE_LBUTTON);
    controller.track.trigger_flag = track_trigger;
    controller.track.move = mouse_move * camera_move_track_ratio;

    return controller;
}

CameraController::Controller MouseMoveCameraController::ModeEye(void) {
    // �J��������p
    CameraController::Controller controller;

    // �}�E�X�ړ���
    Vector3 mouse_move = MouseUtilities::GetMove();

    // ��]
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_LBUTTON);
    controller.rotation.move         = mouse_move * camera_move_rotation_ratio;

    // �Y�[��
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
    // �J��������p
    CameraController::Controller controller;

    // �}�E�X�ړ���
    Vector3 mouse_move = MouseUtilities::GetMove();

    // ��]
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_RBUTTON);
    controller.rotation.move = mouse_move * camera_move_rotation_ratio;

    // �Y�[��
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
/// �X�V
/// </summary>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void MouseMoveCameraController::Update(void) {
    CameraController::Update(MouseMoveController());
}
