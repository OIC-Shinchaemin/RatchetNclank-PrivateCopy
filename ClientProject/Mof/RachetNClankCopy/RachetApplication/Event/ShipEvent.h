#ifndef MY_SHIP_EVENT_H
#define MY_SHIP_EVENT_H


#include "Event.h"
#include "Base/Core/Observer.h"

#include <memory>

#include "BridgeEvent.h"
#include "../Stage/StageObject.h"
#include "../Camera/PointCameraController.h"


namespace my {
class ShipEvent : public my::Event,
    public my::Observer<const my::CameraController::CameraInfo&>,
    public my::Observer<const char*, const std::shared_ptr<StageObject>&> {
    using super = my::Event;
private:
    //! 通知用
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _ship_event_subject;
    //! カメラ
    std::shared_ptr<my::Camera> _ship_view_camera;
    //! カメラコントローラ
    my::PointCameraController _ship_view_camera_controller;
    //! 位置
    Mof::CVector3 _ideal_position;
    //! カメラ情報
    my::CameraController::CameraInfo _info;
    //! プレイヤービュー
    std::weak_ptr<my::Observer<const my::CameraController::CameraInfo&>> _camera_com;
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
    virtual void OnNotify(const my::CameraController::CameraInfo& info) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    my::Observable<const char*, const std::shared_ptr<my::Actor>&>* GetShipEventSubject(void);
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
#endif // !MY_SHIP_EVENT_H