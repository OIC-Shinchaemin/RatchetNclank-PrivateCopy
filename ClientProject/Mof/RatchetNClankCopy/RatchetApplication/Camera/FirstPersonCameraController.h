#ifndef RATCHET_CAMERA_FIRST_PERSON_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_FIRST_PERSON_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class FirstPersonCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FirstPersonCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~FirstPersonCameraController();
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
#endif // !RATCHET_CAMERA_FIRST_PERSON_CAMERA_CONTROLLER_H