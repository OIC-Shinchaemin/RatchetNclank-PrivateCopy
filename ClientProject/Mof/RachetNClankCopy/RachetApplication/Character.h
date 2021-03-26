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
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_CHARACTER_H