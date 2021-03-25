#ifndef MY_CAMERA_INTERFACE_H
#define MY_CAMERA_INTERFACE_H


#include "My/Core/ServiceLocator.h"

#include <memory>
#include <string>


namespace my {
class CameraLocator: public my::ServiceLocator<class CameraManager> {
    using super = my::ServiceLocator<class CameraManager>;
private:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<class CameraManager> GetService(void) const = delete;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CameraLocator();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CameraLocator();
    /// <summary>
    /// �o�^
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterGlobalCamera(const std::shared_ptr<class Camera>& ptr);
};
}
#endif // !MY_CAMERA_INTERFACE_H