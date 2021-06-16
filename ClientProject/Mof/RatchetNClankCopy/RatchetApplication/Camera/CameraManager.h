#ifndef RATCHET_CAMERA_CAMERA_MANAGER_H
#define RATCHET_CAMERA_CAMERA_MANAGER_H


#include "Camera.h"


namespace ratchet {
namespace camera {
class CameraManager {
private:
    //! カメラ
    std::shared_ptr<ratchet::camera::Camera> _global_camera;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CameraManager();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~CameraManager();
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterGlobalCamera(const std::shared_ptr<ratchet::camera::Camera>& ptr);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
}
#endif // !RATCHET_CAMERA_CAMERA_MANAGER_H