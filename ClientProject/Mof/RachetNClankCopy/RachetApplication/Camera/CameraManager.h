#ifndef RACHET_CAMERA_MANAGER_H
#define RACHET_CAMERA_MANAGER_H


#include "Camera.h"


namespace rachet {
class CameraManager {
private:
    //! �J����
    std::shared_ptr<rachet::Camera> _global_camera;
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
    void RegisterGlobalCamera(const std::shared_ptr<rachet::Camera>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !RACHET_CAMERA_MANAGER_H