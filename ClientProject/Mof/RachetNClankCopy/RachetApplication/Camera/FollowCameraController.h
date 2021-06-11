#ifndef RATCHET_FOLLOW_CAMERA_CONTROLLER_H
#define RATCHET_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
class FollowCameraController: public ratchet::CameraController {
    using super = ratchet::CameraController;
private:
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::Camera>& camera);
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
    virtual bool Update(float delta_time, const ratchet::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_FOLLOW_CAMERA_CONTROLLER_H