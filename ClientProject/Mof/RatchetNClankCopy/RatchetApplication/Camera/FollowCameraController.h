#ifndef RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
namespace camera {
class FollowCameraController: public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::camera::Camera>& camera);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FollowCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~FollowCameraController();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
}
#endif // !RATCHET_CAMERA_FOLLOW_CAMERA_CONTROLLER_H