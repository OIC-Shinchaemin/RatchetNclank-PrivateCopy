#ifndef RATCHET_CAMERA_POINT_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_POINT_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class PointCameraController : public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    //! �ʒu
    Mof::CVector3 _ideal_position;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PointCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~PointCameraController();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="info"></param>
    virtual void SetInfo(const ratchet::camera::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_POINT_CAMERA_CONTROLLER_H