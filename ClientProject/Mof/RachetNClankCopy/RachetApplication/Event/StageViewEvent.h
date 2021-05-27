#ifndef MY_STAGE_VIEW_EVENT_H
#define MY_STAGE_VIEW_EVENT_H


#include "Event.h"
#include "My/Core/Observer.h"
#include "My/Core/Observable.h"

#include <memory>
#include <vector>

#include "My/Core/ServiceLocator.h"
#include "My/UI/UICanvas.h"
#include "../Actor.h"
#include "../Camera/Camera.h"
#include "../Camera/CameraController.h"
#include "../Camera/AutoCameraController.h"


namespace my {
class StageViewEvent : public my::Event,
    public my::Observable<const char*, const std::shared_ptr<my::StageViewEvent>&> {
    using super = my::Event;
    using Observable = my::Observable<const char*, const std::shared_ptr<my::StageViewEvent>&>;
private:
    //! カメラ
    std::shared_ptr<my::Camera> _stage_view_camera;
    //! カメラコントローラ
    my::ServiceLocator<my::CameraController> _stage_view_camera_controller;
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
    std::shared_ptr<my::Observable<const my::CameraController::CameraInfo&>> GetSubject(void) const;
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
#endif // !MY_BRIDGE_EVENT_H