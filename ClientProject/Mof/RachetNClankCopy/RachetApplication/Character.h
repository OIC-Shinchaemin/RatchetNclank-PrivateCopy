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
    ~Character();
    bool Initialize(void);
    bool Release(void);
};
}
#endif // !MY_CHARACTER_H