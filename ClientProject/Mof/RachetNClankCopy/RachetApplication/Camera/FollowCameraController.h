#ifndef MY_FOLLOW_CAMERA_CONTROLLER_H
#define MY_FOLLOW_CAMERA_CONTROLLER_H


#include "CameraController.h"


namespace my {
class FollowCameraController: public my::CameraController {
    using super = my::CameraController;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    FollowCameraController();
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ~FollowCameraController();
};
}
#endif // !MY_FOLLOW_CAMERA_CONTROLLER_H