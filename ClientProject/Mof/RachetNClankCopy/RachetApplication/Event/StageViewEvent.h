#ifndef RACHET_STAGE_VIEW_EVENT_H
#define RACHET_STAGE_VIEW_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Camera/Camera.h"
#include "../Camera/AutoCameraController.h"


namespace rachet {
class StageViewEvent : public rachet::Event {
    using super = rachet::Event;
    using CameraObservable = base::core::Observable<const rachet::CameraController::CameraInfo&>;
private:
    //! カメラ
    std::shared_ptr<rachet::Camera> _stage_view_camera;
    //! カメラコントローラ
    std::shared_ptr<rachet::AutoCameraController> _stage_view_camera_controller;
    //! 通知用
    rachet::StageViewEvent::CameraObservable _camera_subject;
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
    rachet::StageViewEvent::CameraObservable* GetCameraObservable(void);
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
#endif // !RACHET_BRIDGE_EVENT_H