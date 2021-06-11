#ifndef RATCHET_FIRST_PERSON_CAMERA_CONTROLLER_H
#define RATCHET_FIRST_PERSON_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace ratchet {
class FirstPersonCameraController: public ratchet::CameraController {
    using super = ratchet::CameraController;
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
    virtual void SetInfo(const ratchet::CameraController::CameraInfo& info) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const ratchet::CameraController::CameraInfo& info) override;
};
}
#endif // !RATCHET_FIRST_PERSON_CAMERA_CONTROLLER_H