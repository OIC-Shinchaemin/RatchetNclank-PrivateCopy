#ifndef MY_POINT_CAMERA_CONTROLLER_H
#define MY_POINT_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class PointCameraController : public my::CameraController {
    using super = my::CameraController;
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
    virtual void SetInfo(const my::CameraController::CameraInfo& info) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_POINT_CAMERA_CONTROLLER_H