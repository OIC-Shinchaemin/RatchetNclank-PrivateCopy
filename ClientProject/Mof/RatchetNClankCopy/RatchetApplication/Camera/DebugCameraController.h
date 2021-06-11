#ifndef RATCHET_DEBUG_CAMERA_CONTROLLER_H
#define RATCHET_DEBUG_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
class DebugCameraController: public ratchet::CameraController {
    using super = ratchet::CameraController;
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
    virtual bool Update(float delta_time,const ratchet::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_DEBUG_CAMERA_CONTROLLER_H