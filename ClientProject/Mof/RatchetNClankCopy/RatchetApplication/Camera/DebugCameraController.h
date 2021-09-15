#ifndef RATCHET_CAMERA_DEBUG_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_DEBUG_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class DebugCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DebugCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~DebugCameraController();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time,const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_DEBUG_CAMERA_CONTROLLER_H