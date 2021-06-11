#pragma once

#include "Mof.h"
#include "Base/Core/Define.h"
#include "Camera/CameraManager.h"
#include "Base/Core/ServiceLocator.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"

namespace test {
class CGameApp : public CSingleGameApplication {
private:
    //! カメラ
    std::shared_ptr<ratchet::CameraManager> _camera_manager;
    //! 対象
    Mof::CVector3 _target;
    //! カメラ
    std::shared_ptr<ratchet::Camera> _camera;
    //! カメラコントローラ
    base::core::ServiceLocator<ratchet::CameraController> _camera_controller;
    //! モード
    ratchet::CameraController::CameraMode _current_mode;
    //! コントローラ
    std::unordered_map<ratchet::CameraController::CameraMode, std::shared_ptr<ratchet::CameraController>> _controller_map;
    //! アクター
    Mof::CMeshContainer _gizmo;
    //! ワールドマトリクス
    def::Transform _transform;

    void InputFollow(std::shared_ptr<ratchet::CameraController> controller);
    void InputFirstPerson(std::shared_ptr<ratchet::CameraController> controller);
    void UpdateFollow(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
    void UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::CameraController> controller);
public:
    CGameApp() :
        _camera_manager(),
        _target(),
        _camera(),
        _camera_controller(),
        _current_mode(ratchet::CameraController::CameraMode::Follow),
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