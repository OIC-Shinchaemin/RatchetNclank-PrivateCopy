#ifndef RACHET_FOLLOW_CAMERA_CONTROLLER_H
#define RACHET_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace rachet {
class FollowCameraController: public rachet::CameraController {
    using super = rachet::CameraController;
private:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<rachet::Camera>& camera);
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
    virtual bool Update(float delta_time, const rachet::CameraController::CameraInfo& info) override;
};
}
#endif // !RACHET_FOLLOW_CAMERA_CONTROLLER_H