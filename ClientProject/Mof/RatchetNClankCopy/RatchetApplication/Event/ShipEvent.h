#ifndef RATCHET_SHIP_EVENT_H
#define RATCHET_SHIP_EVENT_H


#include "Event.h"
#include "Base/Core/Observer.h"

#include <memory>

#include "BridgeEvent.h"
#include "../Stage/StageObject.h"
#include "../Camera/PointCameraController.h"


namespace ratchet ::event {
struct ShipEventEndMessage {
};
using ShipEventEndMessageSubject = base::core::Observable<const ShipEventEndMessage&>;
using ShipEventEndMessageListener = base::core::Observer<const  ShipEventEndMessage&>;
class ShipEvent : public ratchet::event::Event,
    public base::core::Observer<const ratchet::camera::CameraController::CameraInfo&>,
    public base::core::Observer<const char*, const std::shared_ptr<StageObject>&> {
    using super = ratchet::event::Event;
private:
    //! 開始
    bool _start;
    //! 通知用
    base::core::Observable<const char*, const std::shared_ptr<ratchet::actor::Actor>& > _ship_event_subject;
    //! カメラ
    std::shared_ptr<ratchet::camera::Camera> _ship_view_camera;
    //! カメラコントローラ
    ratchet::camera::PointCameraController _ship_view_camera_controller;
    //! 位置
    Mof::CVector3 _ideal_position;
    //! カメラ情報
    ratchet::camera::CameraController::CameraInfo _info;
    //! プレイヤービュー
    std::weak_ptr<base::core::Observer<const ratchet::camera::CameraController::CameraInfo&>> _camera_com;
    //! 実行時間
    base::core::Timer _timer;
    //! 実行時間
    const float _time;
    //! 通知
    ShipEventEndMessageSubject _ship_event_end_message_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShipEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~ShipEvent();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<StageObject>& ptr) override;
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const ratchet::camera::CameraController::CameraInfo& info) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const char*, const std::shared_ptr<ratchet::actor::Actor>&>* GetShipEventSubject(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto ShipEventEndMessageSubject(void) {
        return &this->_ship_event_end_message_subject;
    }
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_SHIP_EVENT_H