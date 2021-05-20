#ifndef MY_AUTO_CAMERA_CONTROLLER_H
#define MY_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"
#include "My/Core/Observable.h"

#include "My/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace my {
class AutoCameraController : public my::CameraController,
    public my::Observable<const my::CameraController::CameraInfo&> {
    using super = my::CameraController;
    using Observable = my::Observable<const my::CameraController::CameraInfo&>;
private:
    //! 時間
    float _time;
    //! 時間
    my::Timer _timer;
    //! アニメーション
    my::BezierCurveAnimation _bezier_curve_animation_position;
    //! アニメーション
    my::BezierCurveAnimation _bezier_curve_animation_target;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AutoCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~AutoCameraController();
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    void AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_AUTO_CAMERA_CONTROLLER_H