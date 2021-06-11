#pragma once

#include "Mof.h"

#include "Base/Core/Define.h"


namespace test {
class CGameApp : public CSingleGameApplication {
private:
    /*
    //! �J����
    std::shared_ptr<ratchet::CameraManager> _camera_manager;
    //! �Ώ�
    Mof::CVector3 _target;
    //! �J����
    std::shared_ptr<ratchet::Camera> _camera;
    //! �J�����R���g���[��
    base::core::ServiceLocator<ratchet::CameraController> _camera_controller;
    //! ���[�h
    ratchet::CameraController::CameraMode _current_mode;
    //! �R���g���[��
    std::unordered_map<ratchet::CameraController::CameraMode, std::shared_ptr<ratchet::CameraController>> _controller_map;

    void InputFollow(std::shared_ptr<ratchet::CameraController> controller);
    void InputFirstPerson(std::shared_ptr<ratchet::CameraController> controller);
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
    */
    //! �J����
    Mof::CCamera _camera;
    //! �A�N�^�[
    Mof::CMeshContainer _gizmo;
    //! ���[���h�}�g���N�X
    def::Transform _transform;
public:
    CGameApp() :
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