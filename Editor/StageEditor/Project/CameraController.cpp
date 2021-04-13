#include "CameraController.h"
#include "MofImGui/MofImGui.h"

// ********************************************************************************
/// <summary>
/// カメラのパン(左右)とティルト(上下)処理
/// </summary>
/// <param name="rotation">回転量</param>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void CameraController::PanTilt(const Controll<Vector3>& rotation) {
    // 回転トリガーが作動していないか移動量がゼロなら処理しない。
    if (!(rotation.trigger_flag) ||
        (CVector3Utilities::Length(rotation.move) == 0.0f)) {
        return;
    }

    // 簡易アクセス用
    const Vector3& move = rotation.move;

    // カメラのターゲットを取得する。
    const CVector3& target = _camera_pointer->GetTargetPosition();
    CVector3        view   = _camera_pointer->GetViewPosition();

    // 原点からのビュー座標を計算して移動量だけ回転する。
    CVector3 view_vector = view - target;
    view_vector.RotationY(move.x);

    // 移動量から各成分を計算する。
    const float distance  = std::sqrtf(view_vector.x * view_vector.x + view_vector.z * view_vector.z);
    const float sin_a     = std::sinf(-move.y);
    const float cos_a     = std::cosf(-move.y);
    const float tmp_y     = view_vector.y * cos_a + distance * -sin_a;
    const float tmp_xz    = view_vector.y * sin_a + distance * cos_a;

    // 座標を計算しなおす。
    view_vector.y = tmp_y;
    view_vector.x = (view_vector.x / distance) * tmp_xz;
    view_vector.z = (view_vector.z / distance) * tmp_xz;
    view = target + view_vector;
    
    // 再設定する。
    _camera_pointer->SetViewPosition(view);
    _camera_pointer->Update();
}

// ********************************************************************************
/// <summary>
/// カメラのズーム
/// </summary>
/// <param name="zoom">ズーム量</param>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void CameraController::Zoom(const Controll<float>& zoom) {
    // トリガーが作動していないか移動量がゼロなら処理しない
    if (!zoom.trigger_flag || zoom.move == 0.0f) {
        return;
    }

    // カメラのターゲットを取得する。
    const CVector3& target = _camera_pointer->GetTargetPosition();
    CVector3        view   = _camera_pointer->GetViewPosition();

    // 原点からのビュー座標を計算する。
    CVector3 view_vector = view - target;
    view_vector         *= 1.0f - zoom.move;
    view                 = target + view_vector;
    _zoom_ratio         -= zoom.move;

    // 再設定する。
    _camera_pointer->SetViewPosition(view);
    _camera_pointer->Update();
}

// ********************************************************************************
/// <summary>
/// カメラのトラック
/// </summary>
/// <param name="track">移動量</param>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void CameraController::Track(const Controll<Vector3>& track) {
    // トリガーが作動していないか移動量がゼロなら処理しない。
    if (!(track.trigger_flag) ||
        (CVector3Utilities::Length(track.move) == 0.0f)) {
        return;
    }

    // カメラのターゲットを取得する。
    CVector3 target = _camera_pointer->GetTargetPosition();
    CVector3 view   = _camera_pointer->GetViewPosition();

    // 原点からのビュー座標を計算する。
    CVector3 view_vector = target - view;

    // 簡易アクセス用
    const Vector3& move = track.move;

    // 移動量から各成分を計算する。
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

    // 再設定する。
    _camera_pointer->SetViewPosition(view);
    _camera_pointer->SetTargetPosition(target);
    _camera_pointer->Update();
}

// ********************************************************************************
/// <summary>
/// カメラの設定
/// </summary>
/// <param name="camera_pointer">制御するカメラポインタ</param>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void CameraController::SetCamera(CCamera* camera_pointer) {
    this->_camera_pointer = camera_pointer;
}

// ********************************************************************************
/// <summary>
/// 初期化
/// </summary>
/// <param name="camera_pointer">制御するカメラポインタ</param>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void CameraController::Initialize(CCamera* camera_pointer) {
    SetCamera(camera_pointer);
}

// ********************************************************************************
/// <summary>
/// 更新
/// </summary>
/// <param name="controller">制御データ</param>
/// <created>いのうえ,2021/03/17</created>
/// <changed>いのうえ,2021/03/17</changed>
// ********************************************************************************
void CameraController::Update(const Controller& controller) {
    // 操作するカメラがない場合更新しない
    if (_camera_pointer == nullptr) {
        return;
    }

    // 各制御
    Zoom(controller.zoom);
    Track(controller.track);
    PanTilt(controller.rotation);
}
