#pragma once

#include "Mof.h"
#include "Base/Core/Define.h"
#include "Camera/CameraManager.h"
#include "Base/Core/ServiceLocator.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"


namespace test::camera {
class CGameApp : public CSingleGameApplication {
private:
    //! �J����
    std::shared_ptr<ratchet::camera::CameraManager> _camera_manager;
    //! �Ώ�
    Mof::CVector3 _target;
    //! �J����
    std::shared_ptr<ratchet::camera::Camera> _camera;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::camera::CameraController> _camera_controller;
    //! ���[�h
    ratchet::camera::CameraController::CameraMode _current_mode;
    //! �R���g���[��
    std::unordered_map<ratchet::camera::CameraController::CameraMode, std::shared_ptr<ratchet::camera::CameraController>> _controller_map;
    //! �A�N�^�[
    Mof::CMeshContainer _gizmo;
    //! ���[���h�}�g���N�X
    def::Transform _transform;

    void InputFollow(std::shared_ptr<ratchet::camera::CameraController> controller);
    void InputFirstPerson(std::shared_ptr<ratchet::camera::CameraController> controller);
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller);
public:
    CGameApp() :
        _camera_manager(),
        _target(),
        _camera(),
        _camera_controller(),
        _current_mode(ratchet::camera::CameraController::CameraMode::Follow),
        _controller_map(),
        _gizmo(),
        _transform() {
    }
    virtual ~CGameApp() { Release(); }
    virtual MofBool Initialize(void);
    virtual MofBool Input(void);
    virtual MofBool Update(void);
    virtual MofBool Render(void);
    virtual MofBool Release(void);
};
}