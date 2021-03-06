#ifndef RATCHET_CAMERA_AUTO_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"

#include "Base/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace ratchet {
namespace camera {
class AutoCameraController : public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    //! 時間
    float _time_max;
    //! 時間
    float _time;
    //! 時間
    base::core::Timer _timer;
    //! アニメーション
    ratchet::BezierCurveAnimation _bezier_curve_animation_position;
    //! アニメーション
    ratchet::BezierCurveAnimation _bezier_curve_animation_target;
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetTimeMax(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsCompleted(void) const;
    /// <summary>
    /// 強制的に進める
    /// </summary>
    /// <param name="time"></param>
    void ForceTick(float time);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
}
#endif // !RATCHET_CAMERA_AUTO_CAMERA_CONTROLLER_H