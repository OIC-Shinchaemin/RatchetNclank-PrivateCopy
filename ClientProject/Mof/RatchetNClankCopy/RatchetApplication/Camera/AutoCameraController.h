#ifndef RATCHET_CAMERA_AUTO_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"

#include "Base/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace ratchet::camera {
class AutoCameraController : public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    //! ����
    float _time_max;
    //! ����
    float _time;
    //! ����
    base::core::Timer _timer;
    //! �A�j���[�V����
    ratchet::BezierCurveAnimation _bezier_curve_animation_position;
    //! �A�j���[�V����
    ratchet::BezierCurveAnimation _bezier_curve_animation_target;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AutoCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AutoCameraController(float time);
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~AutoCameraController();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetTimeMax(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsCompleted(void) const;
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="point"></param>
    void RegisterCameraPositionControllPoint(std::vector<Mof::CVector3>& points);
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="point"></param>
    void RegisterCameraTargetControllPoint(std::vector<Mof::CVector3>& points);
    /// <summary>
    /// ���Z�b�g
    /// </summary>
    /// <param name="time_set"></param>
    void TimerReset(float time_set);
    /// <summary>
    /// �����I�ɐi�߂�
    /// </summary>
    /// <param name="time"></param>
    void ForceTick(float time);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_AUTO_CAMERA_CONTROLLER_H