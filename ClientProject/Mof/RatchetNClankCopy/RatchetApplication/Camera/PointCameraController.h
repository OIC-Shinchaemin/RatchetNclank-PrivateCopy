#ifndef RATCHET_CAMERA_POINT_CAMERA_CONTROLLER_H
#define RATCHET_CAMERA_POINT_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet::camera {
class PointCameraController : public ratchet::camera::CameraController {
    using super = ratchet::camera::CameraController;
private:
    //! 位置
    Mof::CVector3 _ideal_position;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PointCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~PointCameraController();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="info"></param>
    virtual void SetInfo(const ratchet::camera::CameraController::CameraInfo& info) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::camera::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_CAMERA_POINT_CAMERA_CONTROLLER_H