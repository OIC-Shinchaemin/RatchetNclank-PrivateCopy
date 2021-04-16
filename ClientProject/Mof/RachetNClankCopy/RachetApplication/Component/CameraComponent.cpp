#include "CameraComponent.h"

#include "../Gamepad.h"


void my::CameraComponent::ControlByKeyboard(void) {
    if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
        _camera_controller.AddAzimuth(1.0f);
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
        _camera_controller.AddAzimuth(-1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        _camera_controller.AddAltitude(1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        _camera_controller.AddAltitude(-1.0f);
    } // else if
}

void my::CameraComponent::ControlByGamepad(void) {
    float horizontal = ::g_pGamepad->GetRightStickHorizontal();
    float vertical = ::g_pGamepad->GetRightStickVertical();
    float threshold = 0.5f;
    if (auto in = Mof::CVector2(horizontal, vertical); in.Length() > threshold) {
        // x
        if (threshold <= std::abs(in.x)) {
            if (0.0f < in.x) {
                _camera_controller.AddAzimuth(1.0f);
            } // if
            else {
                _camera_controller.AddAzimuth(-1.0f);
            } // else
        } // if
        // y
        if (threshold <= std::abs(in.y)) {
            if (0.0f < in.y) {
                _camera_controller.AddAltitude(1.0f);
            } // if
            else {
                _camera_controller.AddAltitude(-1.0f);
            } // else 
        } // if
    } // if
}

my::CameraComponent::CameraComponent(int priority) :
    super(priority),
    _target(),
    _player_view_camera(),
    _camera_controller() {
}

my::CameraComponent::CameraComponent(const CameraComponent& obj) :
    super(obj._priority),
    _target(),
    _player_view_camera(),
    _camera_controller() {
}

my::CameraComponent::~CameraComponent() {
}

void my::CameraComponent::SetTarget(Mof::CVector3 pos) {
    this->_target = pos;
}

std::string my::CameraComponent::GetType(void) const {
    return "CameraComponent";
}

bool my::CameraComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // camera
    _player_view_camera = (std::make_shared<my::Camera>());
    auto pos = Mof::CVector3(0.0f, 5.0f, 5.0f);
    _player_view_camera->SetPosition(pos);
    _player_view_camera->SetTarget(math::vec3::kZero);
    _player_view_camera->Initialize();
    _camera_controller.SetCamera(_player_view_camera);
    //_camera_controller.RegisterGlobalCamera();
    return true;
}

bool my::CameraComponent::Update(float delta_time) {
    this->ControlByGamepad();
    this->ControlByKeyboard();

    auto pos = super::GetOwner()->GetPosition();
    pos.y += 1.0f;
    //_camera_controller.SetCameraTarget(Mof::CVector3(pos.x, pos.y + super::_height, pos.z));

    _camera_controller.SetCameraTarget(pos);
    //_camera_controller.SetCameraTarget(_target);
    _camera_controller.Update();
    return true;
}

bool my::CameraComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::CameraComponent::Clone(void) {
    return std::make_shared<my::CameraComponent>(*this);
}