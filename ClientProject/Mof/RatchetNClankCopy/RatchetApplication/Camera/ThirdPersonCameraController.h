#ifndef RATCHET_CAMERA_THIRD_PERSON_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_THIRD_PERSON_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class ThirdPersonCameraController: public ratchet::camera::CameraController {
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
    ThirdPersonCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~ThirdPersonCameraController();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_THIRD_PERSON_CAMERA_CONTROLLER_H