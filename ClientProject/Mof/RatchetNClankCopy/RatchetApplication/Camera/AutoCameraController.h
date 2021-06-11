#ifndef RATCHET_AUTO_CAMERA_CONTROLLER_H
#define RATCHET_AUTO_CAMERA_CONTROLLER_H


#include "CameraController.h"

#include "Base/Core/Timer.h"
#include "../BezierCurveAnimation.h"


namespace ratchet {
class AutoCameraController : public ratchet::CameraController {
    using super = ratchet::CameraController;
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
    /// �����I�ɐi�߂�
    /// </summary>
    /// <param name="time"></param>
    void ForceTick(float time);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    //void AddObserver(const std::shared_ptr<base::core::Observer<const ratchet::CameraController::CameraInfo&>>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_AUTO_CAMERA_CONTROLLER_H