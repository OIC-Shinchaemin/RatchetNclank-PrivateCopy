#ifndef MY_SHIP_EVENT_H
#define MY_SHIP_EVENT_H


#include "My/Core/Observer.h"

#include <memory>

#include "../Actor.h"
#include "BridgeEvent.h"
#include "../Stage/StageObject.h"
#include "../Camera/FirstPersonCameraController.h"


namespace my {
class ShipEvent :
    public std::enable_shared_from_this<my::ShipEvent>,
    public my::Observer<const char*, const std::shared_ptr<my::Actor>&>,
    public my::Observer<const my::CameraController::CameraInfo&>,
    //public my::Observer<const char*, const std::shared_ptr<my::BridgeEvent>&>,
    public my::Observer<const char*, const std::shared_ptr<StageObject>&>
{
private:
    //! 通知用
    my::Observable<const char*, const std::shared_ptr<my::Actor>& > _ship_event_subject;
    //! カメラ
    std::shared_ptr<my::Camera> _ship_view_camera;
    //! カメラコントローラ
    my::PointCameraController _ship_view_camera_controller;
    //my::FirstPersonCameraController _ship_view_camera_controller;
    //! 位置
    Mof::CVector3 _ideal_position;
    //! カメラ情報
    my::CameraController::CameraInfo _info;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Actor>& ptr) override;
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
    my::Observable<const char*, const std::shared_ptr<my::Actor>&>& GetShipEventSubject(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Initialize(void);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
};
}
#endif // !MY_SHIP_EVENT_H