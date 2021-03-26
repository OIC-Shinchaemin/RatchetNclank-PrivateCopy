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
	//! �J����
	std::shared_ptr<my::Camera> _camera;
	//! �J����
	std::shared_ptr<my::Camera> _top_view_camera;
    //! �J�����R���g���[��
    std::shared_ptr<my::CameraController>_camera_controller;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Character();
    ~Character();
    bool Initialize(void);
    bool Release(void);
};
}
#endif // !MY_CHARACTER_H