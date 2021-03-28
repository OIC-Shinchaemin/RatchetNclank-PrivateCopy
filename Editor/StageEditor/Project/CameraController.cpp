#include "CameraController.h"
#include "MofImGui/MofImGui.h"

// ********************************************************************************
/// <summary>
/// �J�����̃p��(���E)�ƃe�B���g(�㉺)����
/// </summary>
/// <param name="rotation">��]��</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void CameraController::PanTilt(const Controll<Vector3>& rotation) {
    // ��]�g���K�[���쓮���Ă��Ȃ����ړ��ʂ��[���Ȃ珈�����Ȃ��B
    if (!(rotation.trigger_flag) ||
        (CVector3Utilities::Length(rotation.move) == 0.0f)) {
        return;
    }

    // �ȈՃA�N�Z�X�p
    const Vector3& move = rotation.move;

    // �J�����̃^�[�Q�b�g���擾����B
    const CVector3& target = _camera_pointer->GetTargetPosition();
    CVector3        view   = _camera_pointer->GetViewPosition();

    // ���_����̃r���[���W���v�Z���Ĉړ��ʂ�����]����B
    CVector3 view_vector = view - target;
    view_vector.RotationY(move.x);

    // �ړ��ʂ���e�������v�Z����B
    const float distance  = std::sqrtf(view_vector.x * view_vector.x + view_vector.z * view_vector.z);
    const float sin_a     = std::sinf(-move.y);
    const float cos_a     = std::cosf(-move.y);
    const float tmp_y     = view_vector.y * cos_a + distance * -sin_a;
    const float tmp_xz    = view_vector.y * sin_a + distance * cos_a;

    // ���W���v�Z���Ȃ����B
    view_vector.y = tmp_y;
    view_vector.x = (view_vector.x / distance) * tmp_xz;
    view_vector.z = (view_vector.z / distance) * tmp_xz;
    view = target + view_vector;
    
    // �Đݒ肷��B
    _camera_pointer->SetViewPosition(view);
    _camera_pointer->Update();
}

// ********************************************************************************
/// <summary>
/// �J�����̃Y�[��
/// </summary>
/// <param name="zoom">�Y�[����</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void CameraController::Zoom(const Controll<float>& zoom) {
    // �g���K�[���쓮���Ă��Ȃ����ړ��ʂ��[���Ȃ珈�����Ȃ�
    if (!zoom.trigger_flag || zoom.move == 0.0f) {
        return;
    }

    // �J�����̃^�[�Q�b�g���擾����B
    const CVector3& target = _camera_pointer->GetTargetPosition();
    CVector3        view   = _camera_pointer->GetViewPosition();

    // ���_����̃r���[���W���v�Z����B
    CVector3 view_vector = view - target;
    view_vector         *= 1.0f - zoom.move;
    view                 = target + view_vector;
    _zoom_ratio         -= zoom.move;

    // �Đݒ肷��B
    _camera_pointer->SetViewPosition(view);
    _camera_pointer->Update();
}

// ********************************************************************************
/// <summary>
/// �J�����̃g���b�N
/// </summary>
/// <param name="track">�ړ���</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void CameraController::Track(const Controll<Vector3>& track) {
    // �g���K�[���쓮���Ă��Ȃ����ړ��ʂ��[���Ȃ珈�����Ȃ��B
    if (!(track.trigger_flag) ||
        (CVector3Utilities::Length(track.move) == 0.0f)) {
        return;
    }

    // �J�����̃^�[�Q�b�g���擾����B
    CVector3 target = _camera_pointer->GetTargetPosition();
    CVector3 view   = _camera_pointer->GetViewPosition();

    // ���_����̃r���[���W���v�Z����B
    CVector3 view_vector = target - view;

    // �ȈՃA�N�Z�X�p
    const Vector3& move = track.move;

    // �ړ��ʂ���e�������v�Z����B
    CVector3 sv, uv;
    view_vector.Normal(view_vector);
    view_vector.Cross(Vector3(0, 1, 0), sv);
    sv.Normal(sv);
    view   += sv * move.x * _zoom_ratio;
    target += sv * move.x * _zoom_ratio;
    sv.Cross(view_vector, uv);
    uv.Normal(uv);
    view   += uv * move.y * _zoom_ratio;
    target += uv * move.y * _zoom_ratio;

    // �Đݒ肷��B
    _camera_pointer->SetViewPosition(view);
    _camera_pointer->SetTargetPosition(target);
    _camera_pointer->Update();
}

// ********************************************************************************
/// <summary>
/// �J�����̐ݒ�
/// </summary>
/// <param name="camera_pointer">���䂷��J�����|�C���^</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void CameraController::SetCamera(CCamera* camera_pointer) {
    this->_camera_pointer = camera_pointer;
}

// ********************************************************************************
/// <summary>
/// ������
/// </summary>
/// <param name="camera_pointer">���䂷��J�����|�C���^</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void CameraController::Initialize(CCamera* camera_pointer) {
    SetCamera(camera_pointer);
}

// ********************************************************************************
/// <summary>
/// �X�V
/// </summary>
/// <param name="controller">����f�[�^</param>
/// <created>���̂���,2021/03/17</created>
/// <changed>���̂���,2021/03/17</changed>
// ********************************************************************************
void CameraController::Update(const Controller& controller) {
    // ���삷��J�������Ȃ��ꍇ�X�V���Ȃ�
    if (_camera_pointer == nullptr) {
        return;
    }

    // �e����
    Zoom(controller.zoom);
    Track(controller.track);
    PanTilt(controller.rotation);
}
