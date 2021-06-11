#ifndef MY_AUTO_CAMERA_CONTROLLER_H
#define MY_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"

#include "Base/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace my {
class AutoCameraController : public my::CameraController {
    using super = my::CameraController;
private:
    //! 時間
    float _time_max;
    //! 時間
    float _time;
    //! 時間
    base::core::Timer _timer;
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
    /// 追加
    /// </summary>
    /// <param name="ptr"></param>
    //void AddObserver(const std::shared_ptr<base::core::Observer<const my::CameraController::CameraInfo&>>& ptr);
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