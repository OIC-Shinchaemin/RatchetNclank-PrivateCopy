#ifndef RACHET_POINT_CAMERA_CONTROLLER_H
#define RACHET_POINT_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace rachet {
class PointCameraController : public rachet::CameraController {
    using super = rachet::CameraController;
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
    virtual void SetInfo(const rachet::CameraController::CameraInfo& info) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const rachet::CameraController::CameraInfo& info) override;
};
}
#endif // !RACHET_POINT_CAMERA_CONTROLLER_H