#ifndef MY_CHARACTER_H
#define MY_CHARACTER_H

#include <memory>

#include <Mof.h>
#include "CameraLocator.h"

#include "My/Core/Observable.h"
#include "Define.h"
#include "Camera.h"
#include "CameraController.h"


namespace my {
class Character : public  std::enable_shared_from_this<my::Character>, public my::CameraLocator {
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