#ifndef RATCHET_CAMERA_COMPONENT_H
#define RATCHET_CAMERA_COMPONENT_H


#include "UpdateComponent.h"

#include "Base/Core/Observable.h"
#include "Base/Core/ServiceLocator.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"


namespace ratchet {
class CameraComponent : public ratchet::UpdateComponent, public base::core::Observer<const ratchet::CameraController::CameraInfo&> {
    using super = ratchet::UpdateComponent;
private:
    //! 対象
    Mof::CVector3 _target;
    //! カメラ
    std::shared_ptr<ratchet::Camera> _camera;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::CameraController> _camera_controller;
    //! モード
    ratchet::CameraController::CameraMode _current_mode;
    //! コントローラ
    std::unordered_map<ratchet::CameraController::CameraMode, std::shared_ptr<ratchet::CameraController>> _controller_map;
    
    
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
    std::weak_ptr<class PlayerStateComponent> _state_com;
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
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="controller"></param>
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
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
    virtual void OnNotify(const ratchet::CameraController::CameraInfo& info) override;
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
    Mof::CVector3 GetPreviewPosition(void) const;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
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
#endif // !RATCHET_CAMERA_COMPONENT_H