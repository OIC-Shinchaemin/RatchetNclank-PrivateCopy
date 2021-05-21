#ifndef MY_DEBUG_CAMERA_CONTROLLER_H
#define MY_DEBUG_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class DebugCameraController: public my::CameraController {
    using super = my::CameraController;
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
    virtual bool Update(float delta_time,const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_DEBUG_CAMERA_CONTROLLER_H