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
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    void AddObserver(const std::shared_ptr<my::Observer<const my::CameraController::CameraInfo&>>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_AUTO_CAMERA_CONTROLLER_H