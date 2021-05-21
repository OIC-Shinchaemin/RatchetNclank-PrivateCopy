#pragma once

#include "Mof.h"
#include "My/Core/Define.h"
#include "Camera/CameraManager.h"
#include "My/Core/ServiceLocator.h"
#include "Camera/Camera.h"
#include "Camera/CameraController.h"

namespace test {
enum class CameraMode {
    Follow,
    FirstPerson,
};
class CGameApp : public CSingleGameApplication {
private:
    //! カメラ
    std::shared_ptr<my::CameraManager> _camera_manager;
    //! 対象
    Mof::CVector3 _target;
    //! カメラ
    std::shared_ptr<my::Camera> _camera;
    //! カメラコントローラ
    my::ServiceLocator<my::CameraController> _camera_controller;
    //! モード
    test::CameraMode _current_mode;
    //! コントローラ
    std::unordered_map<test::CameraMode, std::shared_ptr<my::CameraController>> _controller_map;
    //! アクター
    Mof::CMeshContainer _gizmo;
    //! ワールドマトリクス
    def::Transform _transform;

    void InputFollow(std::shared_ptr<my::CameraController> controller);
    void InputFirstPerson(std::shared_ptr<my::CameraController> controller);
    void UpdateFollow(float delta_time, std::shared_ptr<my::CameraController> controller);
    void UpdateFirstPerson(float delta_time, std::shared_ptr<my::CameraController> controller);
public:
    CGameApp() :
        _camera_manager(),
        _target(),
        _camera(),
        _camera_controller(),
        _current_mode(test::CameraMode::Follow),
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