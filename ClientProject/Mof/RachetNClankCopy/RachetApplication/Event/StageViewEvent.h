#ifndef RATCHET_STAGE_VIEW_EVENT_H
#define RATCHET_STAGE_VIEW_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"


namespace ratchet {
class StageViewEvent : public ratchet::Event {
    using super = ratchet::Event;
    using CameraObservable = base::core::Observable<const ratchet::CameraController::CameraInfo&>;
private:
    //! カメラ
    std::shared_ptr<ratchet::Camera> _stage_view_camera;
    //! カメラコントローラ
    std::shared_ptr<ratchet::AutoCameraController> _stage_view_camera_controller;
    //! 通知用
    ratchet::StageViewEvent::CameraObservable _camera_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    StageViewEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~StageViewEvent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::StageViewEvent::CameraObservable* GetCameraObservable(void);
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
#endif // !RATCHET_BRIDGE_EVENT_H