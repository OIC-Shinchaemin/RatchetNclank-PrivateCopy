#ifndef RACHET_FIRST_PERSON_CAMERA_CONTROLLER_H
#define RACHET_FIRST_PERSON_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace rachet {
class FirstPersonCameraController: public rachet::CameraController {
    using super = rachet::CameraController;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FirstPersonCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~FirstPersonCameraController();
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
#endif // !RACHET_FIRST_PERSON_CAMERA_CONTROLLER_H