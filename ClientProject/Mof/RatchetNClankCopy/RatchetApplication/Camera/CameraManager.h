#ifndef RATCHET_CAMERA_CAMERA_MANAGER_H
#define RATCHET_CAMERA_CAMERA_MANAGER_H


#include "Camera.h"


namespace ratchet {
namespace camera {
class CameraManager {
private:
    //! �J����
    std::shared_ptr<ratchet::camera::Camera> _global_camera;
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
    void RegisterGlobalCamera(const std::shared_ptr<ratchet::camera::Camera>& ptr);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
}
#endif // !RATCHET_CAMERA_CAMERA_MANAGER_H