#ifndef MY_AUTO_CAMERA_CONTROLLER_H
#define MY_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"

#include "My/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace my {
class AutoCameraController : public my::CameraController {
    using super = my::CameraController;
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
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !MY_AUTO_CAMERA_CONTROLLER_H