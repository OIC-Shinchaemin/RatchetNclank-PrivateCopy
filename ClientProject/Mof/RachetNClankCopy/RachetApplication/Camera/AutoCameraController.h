#ifndef MY_AUTO_CAMERA_CONTROLLER_H
#define MY_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"

#include "My/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace my {
class AutoCameraController : public my::CameraController {
    using super = my::CameraController;
private:
    //! ����
    float _time;
    //! ����
    my::Timer _timer;
    //! �A�j���[�V����
    my::BezierCurveAnimation _bezier_curve_animation_position;
    //! �A�j���[�V����
    my::BezierCurveAnimation _bezier_curve_animation_target;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AutoCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~AutoCameraController();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !MY_AUTO_CAMERA_CONTROLLER_H