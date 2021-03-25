#ifndef MY_CAMERA_MANAGER_H
#define MY_CAMERA_MANAGER_H


#include "Camera.h"


namespace my {
class CameraManager {
private:
    //! �J����
    std::shared_ptr<my::Camera> _global_camera;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CameraManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~CameraManager();
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterGlobalCamera(const std::shared_ptr<my::Camera>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_CAMERA_MANAGER_H