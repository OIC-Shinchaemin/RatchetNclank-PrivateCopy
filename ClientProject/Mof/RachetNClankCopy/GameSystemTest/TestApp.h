#pragma once

#include "Mof.h"

#include "Base/Core/Define.h"


namespace test {
class CGameApp : public CSingleGameApplication {
private:
    /*
    //! カメラ
    std::shared_ptr<rachet::CameraManager> _camera_manager;
    //! 対象
    Mof::CVector3 _target;
    //! カメラ
    std::shared_ptr<rachet::Camera> _camera;
    //! カメラコントローラ
    base::core::ServiceLocator<rachet::CameraController> _camera_controller;
    //! モード
    rachet::CameraController::CameraMode _current_mode;
    //! コントローラ
    std::unordered_map<rachet::CameraController::CameraMode, std::shared_ptr<rachet::CameraController>> _controller_map;

    void InputFollow(std::shared_ptr<rachet::CameraController> controller);
    void InputFirstPerson(std::shared_ptr<rachet::CameraController> controller);
    void UpdateFollow(float delta_time, std::shared_ptr<rachet::CameraController> controller);
    void UpdateFirstPerson(float delta_time, std::shared_ptr<rachet::CameraController> controller);
    */
    //! カメラ
    Mof::CCamera _camera;
    //! アクター
    Mof::CMeshContainer _gizmo;
    //! ワールドマトリクス
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