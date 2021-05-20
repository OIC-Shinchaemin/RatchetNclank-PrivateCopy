#ifndef MY_FIRST_PERSON_CAMERA_CONTROLLER_H
#define MY_FIRST_PERSON_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class FirstPersonCameraController: public my::CameraController {
    using super = my::CameraController;
private:
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    void UpdateCameraPosition(float delta_time, const my::CameraController::CameraInfo& info, const std::shared_ptr<my::Camera>& camera);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    FirstPersonCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~FirstPersonCameraController();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="info"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time, const my::CameraController::CameraInfo& info) override;
};
}
#endif // !MY_FIRST_PERSON_CAMERA_CONTROLLER_H