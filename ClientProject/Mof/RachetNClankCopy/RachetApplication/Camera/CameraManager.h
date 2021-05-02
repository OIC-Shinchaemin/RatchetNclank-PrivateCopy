#ifndef MY_CAMERA_MANAGER_H
#define MY_CAMERA_MANAGER_H


#include "Camera.h"


namespace my {
class CameraManager {
private:
    //! カメラ
    std::shared_ptr<my::Camera> _global_camera;
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
    void RegisterGlobalCamera(const std::shared_ptr<my::Camera>& ptr);
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Update(void);
};
}
#endif // !MY_CAMERA_MANAGER_H