#ifndef RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
namespace camera {
class FollowCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FollowCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~FollowCameraController();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
}
#endif // !RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H