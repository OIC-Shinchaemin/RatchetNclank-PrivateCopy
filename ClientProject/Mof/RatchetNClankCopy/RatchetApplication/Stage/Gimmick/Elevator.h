#pragma once
#include "GimmickBase.h"
#include "Base/Core/ServiceLocator.h"
#include "../../Actor/Actor.h"
#include "../../Camera/CameraController.h"
#include "../../Component/CameraComponent.h"
#include "../../Event/EventManager.h"


struct ElevatorArrivalMessage {
};
using ElevatorArrivalMessageSubject = base::core::Observable<const ElevatorArrivalMessage&>;
using ElevatorArrivalMessageListener = base::core::Observer<const ElevatorArrivalMessage&>;

class Elevator : public GimmickBase {
private:
    /// <summary>
    /// イベント開始
    /// </summary>
    /// <param name=""></param>
    void EnemyViewEventStart(void);
protected:
    //! 開始位置
    Vector3 _start_pos;
    //! 終了位置
    Vector3 _end_pos;
    //! 現在の時間
    float _now_timer;
    //! 所要時間
    float _request_time;
    //! 開始フラグ
    bool _start_flag;
    //! 終了フラグ
    bool _end_flag;
    //! 位置
    Mof::CVector3 _preview_position;
    //! 位置
    Mof::CVector3 _initial_position;
    //! フラグ
    bool _first_initialized;
    //! プレイヤーカメラ
    base::core::ServiceLocator<ratchet::camera::CameraController>* _camera_controller;
    //! プレイヤー通知用    
    ElevatorArrivalMessageSubject _elevator_arrival_message_subject;
    //! イベント
    std::weak_ptr<ratchet::event::EventManager> _event_manager;
    //! プレイヤーカメラ
    std::weak_ptr<ratchet::component::CameraComponent> _player_camera_component;
    //! 方位角,仰角
    Mof::CVector3 _camera_angle_start;
public:
    Elevator(Vector3 end, float request, bool enable = true, bool collision = true,
             StageObjectType type = StageObjectType::None, std::string name = "",
             int mesh_no = -1,
             Vector3 pos = Vector3(),
             Vector3 scale = Vector3(1, 1, 1),
             Vector3 rotate = Vector3());
    virtual ~Elevator(void);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCamera(base::core::ServiceLocator<ratchet::camera::CameraController>* ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetEventManager(const std::shared_ptr<ratchet::event::EventManager>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetPlayerCameraComponent(const std::shared_ptr<ratchet::component::CameraComponent>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetElevatorArrivalMessageSubject(void) {
        return &this->_elevator_arrival_message_subject;
    };
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetPreviewPosition(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetRequestTime(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CVector3 GetMoveValue(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetVolume(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual float GetHeight(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetStartPositionSphere(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual Mof::CSphere GetEndPositionSphere(void) const;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    virtual void Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta"></param>
    virtual void Update(float delta) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    virtual void ActionStart(void) override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsStart(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Vector3 GetEndPos(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRequest(void) const;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="pos"></param>
    virtual void SetPosition(const Vector3& pos) override;
    /// <summary>
    /// 再初期化
    /// </summary>
    /// <param name=""></param>
    virtual void ReInitialize(void) override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="enable"></param>
    /// <param name="collision"></param>
    /// <param name="type"></param>
    /// <param name="name"></param>
    /// <param name="mesh_no"></param>
    /// <param name="pos"></param>
    /// <param name="scale"></param>
    /// <param name="rotate"></param>
    virtual void SetStageObjectData(bool enable, bool collision, StageObjectType type, std::string name, int mesh_no,
                                    Vector3 pos, Vector3 scale, Vector3 rotate) override;

    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void DebugRender(void) override;
#ifdef STAGEEDITOR
    float* GetStartPosPointer(void);
    float* GetEndPosPointer(void);
    float* GetRequestPointer(void);
#endif//STAGEEDITOR
};

