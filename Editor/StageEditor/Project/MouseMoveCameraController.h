#pragma once
#include "CameraController.h"

// ********************************************************************************
/// <summary>
/// �J��������N���X�̃}�E�X�ő��삷��N���X
/// </summary>
// ********************************************************************************
class MouseMoveCameraController : public CameraController {
private:

    // ********************************************************************************
    /// <summary>
    /// �}�E�X�ł̑������Ԃ�
    /// </summary>
    /// <returns>�R���g���[�����</returns>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    Controller MouseMoveController(void);

    Controller ModeHand(void);
    Controller ModeEye(void);
    Controller ModeInstObject(void);


public:
    // ********************************************************************************
    /// <summary>
    /// �X�V
    /// </summary>
    /// <created>���̂���,2021/03/17</created>
    /// <changed>���̂���,2021/03/17</changed>
    // ********************************************************************************
    void Update(void);
};

