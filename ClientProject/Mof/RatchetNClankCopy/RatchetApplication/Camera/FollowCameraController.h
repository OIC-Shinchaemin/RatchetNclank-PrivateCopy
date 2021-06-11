#ifndef RATCHET_FOLLOW_CAMERA_CONTROLLER_H
#define RATCHET_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
class FollowCameraController: public ratchet::CameraController {
    using super = ratchet::CameraController;
private:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<ratchet::Camera>& camera);
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
    virtual bool Update(float delta_time, const ratchet::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_FOLLOW_CAMERA_CONTROLLER_H