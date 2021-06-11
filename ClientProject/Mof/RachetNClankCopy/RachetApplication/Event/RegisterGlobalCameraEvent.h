#ifndef RACHET_REGISTER_GLOBAL_CAMERA_EVENT_H
#define RACHET_REGISTER_GLOBAL_CAMERA_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Camera/AutoCameraController.h"


namespace rachet {
class RegisterGlobalCameraEvent : public rachet::Event, public base::core::Observer<const rachet::CameraController::CameraInfo&> {
    using super = rachet::Event;
private:
    //! 通知用
    //rachet::RegisterGlobalCameraEvent::CameraObservable _camera_subject;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RegisterGlobalCameraEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~RegisterGlobalCameraEvent();
    /// <summary>
    /// イベント
    /// </summary>
    /// <param name="info"></param>
    virtual void OnNotify(const rachet::CameraController::CameraInfo& info) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //rachet::RegisterGlobalCameraEvent::CameraObservable* GetCameraObservable(void);
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
#endif // !RACHET_REGISTER_GLOBAL_CAMERA_EVENT_H