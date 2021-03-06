#ifndef RATCHET_CAMERA_DEBUG_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_DEBUG_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
namespace camera {
class DebugCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DebugCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~DebugCameraController();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time,const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
}
#endif // !RATCHET_CAMERA_DEBUG_CAMERA_CONTROLLER_H