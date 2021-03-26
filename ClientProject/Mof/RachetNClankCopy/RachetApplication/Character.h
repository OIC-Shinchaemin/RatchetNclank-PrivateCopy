#ifndef MY_CHARACTER_H
#define MY_CHARACTER_H

#include "Actor.h"

#include <memory>

#include <Mof.h>
#include "Camera/CameraLocator.h"

#include "My/Core/Observable.h"
#include "GameDefine.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"


namespace my {
class Character : public my::Actor, public my::CameraLocator {
    using super = my::Actor;
    using Observable = my::Observable<my::Character>;
private:
	//! カメラ
	std::shared_ptr<my::Camera> _camera;
	//! カメラ
	std::shared_ptr<my::Camera> _top_view_camera;
    //! カメラコントローラ
    std::shared_ptr<my::CameraController>_camera_controller;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Character();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_CHARACTER_H