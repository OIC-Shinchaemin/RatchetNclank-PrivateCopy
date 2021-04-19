#ifndef MY_DEBUG_CAMERA_CONTROLLER_H
#define MY_DEBUG_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class DebugCameraController: public my::CameraController {
    using super = my::CameraController;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DebugCameraController();
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ~DebugCameraController();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(void) override;
};
}
#endif // !MY_DEBUG_CAMERA_CONTROLLER_H