#include "MouseMoveCameraController.h"
#include "Define.h"
#include "MouseUtilities.h"

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

    // �}�E�X�ړ���
    Vector3 mouse_move = MouseUtilities::GetMove();
    g_pInput->GetMouseMove(mouse_move);
    // ��]
    controller.rotation.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_RBUTTON);
    controller.rotation.move         = mouse_move * camera_move_rotation_ratio;

    // �Y�[��
    bool zoom_trigger = (mouse_move.z != 0.0f);
    float zoom_move   = mouse_move.z * camera_move_zoom_ratio;
    if (MouseUtilities::IsKeyHold(MOFMOUSE_CENTERBUTTON)) {
        zoom_trigger  = (mouse_move.y != 0.0f);
        zoom_move     = -mouse_move.y * camera_move_zoom_hold_ratio;
    }
    controller.zoom.trigger_flag = zoom_trigger;
    controller.zoom.move         = zoom_move;

    // �g���b�N
    controller.track.trigger_flag = MouseUtilities::IsKeyHold(MOFMOUSE_LBUTTON);
    controller.track.move         = mouse_move * camera_move_track_ratio;

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
