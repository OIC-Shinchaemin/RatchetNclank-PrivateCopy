#ifndef MY_FOLLOW_CAMERA_CONTROLLER_H
#define MY_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class FollowCameraController: public my::CameraController {
    using super = my::CameraController;
private:
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const std::shared_ptr<my::Camera>& camera);
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
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_FOLLOW_CAMERA_CONTROLLER_H