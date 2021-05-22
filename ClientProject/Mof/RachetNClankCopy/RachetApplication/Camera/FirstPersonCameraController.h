#ifndef MY_FIRST_PERSON_CAMERA_CONTROLLER_H
#define MY_FIRST_PERSON_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class FirstPersonCameraController: public my::CameraController {
    using super = my::CameraController;
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
#endif // !MY_FIRST_PERSON_CAMERA_CONTROLLER_H