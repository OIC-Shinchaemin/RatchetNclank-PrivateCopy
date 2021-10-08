#ifndef RATCHET_COMPONENT_CAMERA_COMPONENT_H
#define RATCHET_COMPONENT_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Observable.h"
#include "Base/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace ratchet::component::player { class PlayerStateComponent; }
namespace ratchet::component::player { class PlayerComponent; }
namespace ratchet::component {
class CameraComponent : public ratchet::component::UpdateComponent,
    public base::core::Observer<const ratchet::camera::CameraController::CameraInfo&> {
    using super = ratchet::component::UpdateComponent;
private:
    //! 対象
    Mof::CVector3 _target;
    //! カメラ
    std::shared_ptr<ratchet::camera::Camera> _camera;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::camera::CameraController> _camera_controller;
    //! モード
    ratchet::camera::CameraController::CameraMode _current_mode;
    //! コントローラ
    std::unordered_map<ratchet::camera::CameraController::CameraMode, std::shared_ptr<ratchet::camera::CameraController>> _controller_map;
    //! FPSカメラ方向
    float _ideal_fps_camera_angle;
    //! 距離
    float _default_distance;
    //! 対象
    Mof::CVector3 _preview_position;
    //! x方位角y仰角
    Mof::CVector2 _preview_angle;
    //! 衝突中
    bool _collisioned_stage;
    //! 状態
    std::weak_ptr<ratchet::component::player::PlayerComponent> _player_com;
    //! 状態
    std::weak_ptr<ratchet::component::player::PlayerStateComponent> _state_com;
    //! メッシュ
    std::weak_ptr<class AnimationMeshComponent> _mesh_com;
    //! 追従カメラを少しずつ前の位置で更新をかける
    bool _follow_camera_prev_position_update;
public:
    //! 対象
    base::accessor::Setter<decltype(_preview_position)> preview_position = _preview_position;
    /// <summary>
    /// キーを押した時のカメラ処理
    /// </summary>
    /// <param name=""></param>
    void OnPush(void);
    /// <summary>
    /// キーを押している時のカメラ処理
    /// </summary>
    /// <param name=""></param>
    void OnHold(void);
    /// <summary>
    /// キーを離した時のカメラ処理
    /// </summary>
    /// <param name=""></param>
    void OnPull(void);
    /// <summary>
    /// 角度設定
    /// </summary>
    /// <param name=""></param>
    void TurnLeft(void);
    /// <summary>
    /// 角度設定
    /// </summary>
    /// <param name=""></param>
    void TurnRight(void);
    /// <summary>
    /// 角度設定
    /// </summary>
    /// <param name=""></param>
    void LookUp(void);
    /// <summary>
    /// 角度設定
    /// </summary>
    /// <param name=""></param>
    void LookDown(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateFPSMode(void);
    /// <summary>
    /// 操作
    /// </summary>
    /// <param name=""></param>
    void ControlByKeyboardFollow(void);
    /// <summary>
    /// 操作
    /// </summary>
    /// <param name=""></param>
    void ControlByKeyboardFirstPerson(void);
    /// <summary>
    /// 操作
    /// </summary>
    /// <param name=""></param>
    void ControlByKeyboard(void);
    /// <summary>
    /// 操作
    /// </summary>
    /// <param name=""></param>
    void ControlByGamepad(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateThirdPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    CameraComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    CameraComponent(const CameraComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CameraComponent();
    /// <summary>
    /// イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const ratchet::camera::CameraController::CameraInfo& info) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="flag"></param>
    void SetFollowCameraPrevPositionUpdateFlag(bool flag);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetCameraController(void) {
        return &this->_camera_controller;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetViewFront(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPosition(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetVelocity(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetPreviousPosition(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name=""></param>
    void CollisionStage(void);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !RATCHET_COMPONENT_CAMERA_COMPONENT_H