#ifndef RACHET_DEBUG_CAMERA_CONTROLLER_H
#define RACHET_DEBUG_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace rachet {
class DebugCameraController: public rachet::CameraController {
    using super = rachet::CameraController;
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
    virtual bool Update(float delta_time,const rachet::CameraController::CameraInfo& info) override;
};
}
#endif // !RACHET_DEBUG_CAMERA_CONTROLLER_H