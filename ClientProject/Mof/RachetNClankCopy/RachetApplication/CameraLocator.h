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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<class CameraManager> GetService(void) const = delete;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CameraLocator();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CameraLocator();
    /// <summary>
    /// 登録
    /// </summary>
    /// <param name="ptr"></param>
    void RegisterGlobalCamera(const std::shared_ptr<class Camera>& ptr);
};
}
#endif // !MY_CAMERA_INTERFACE_H