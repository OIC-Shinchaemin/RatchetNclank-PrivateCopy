#ifndef RATCHET_POINT_CAMERA_CONTROLLER_H
#define RATCHET_POINT_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
class PointCameraController : public ratchet::CameraController {
    using super = ratchet::CameraController;
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
    virtual void SetInfo(const ratchet::CameraController::CameraInfo& info) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_POINT_CAMERA_CONTROLLER_H