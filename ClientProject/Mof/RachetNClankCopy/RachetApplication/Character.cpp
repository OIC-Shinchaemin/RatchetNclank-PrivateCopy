#include "Character.h"


my::Character::Character() :
    super(),
    _camera(),
    _top_view_camera(),
    _camera_controller(std::make_shared<my::CameraController>()) {
}

my::Character::~Character() {
}

bool my::Character::Initialize(const def::Transform& transform) {
    super::Initialize(transform);
    _top_view_camera = (std::make_shared<my::Camera>());
    _top_view_camera->SetPosition(Mof::CVector3(0.0f, 1.5f, 5.0f));
    _top_view_camera->SetTarget(math::vec3::kUnitY * 2.0f);
    _top_view_camera->Initialize();

    _camera = (std::make_shared<my::Camera>());
    auto pos = Mof::CVector3(0.0f, 5.0f, 5.0f);
    _camera->SetPosition(pos);
    _camera->SetTarget(math::vec3::kZero);
    _camera->Initialize();
    _camera_controller->SetCamera(_camera);

    my::CameraLocator::RegisterGlobalCamera(_camera);
    return true;
}


bool my::Character::Release(void) {
    super::Release();
    _camera.reset();
    return true;
}