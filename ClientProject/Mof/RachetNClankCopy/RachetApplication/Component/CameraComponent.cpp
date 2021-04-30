#include "CameraComponent.h"

#include "../Gamepad.h"
#include "../Camera/FollowCameraController.h"
#include "../Camera/DebugCameraController.h"
#include "VelocityComponent.h"
#include "Player/PlayerJumpUpComponent.h"
#include "Player/PlayerJumpDownComponent.h"


void my::CameraComponent::ControlByKeyboard(void) {
    if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
        _camera_controller.GetService()->AddAzimuth(1.0f);

        if (_camera_fps_mode) {
            _ideal_fps_camera_angle += math::ToRadian(1.0f);
        } // if

    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
        _camera_controller.GetService()->AddAzimuth(-1.0f);

        if (_camera_fps_mode) {
            _ideal_fps_camera_angle -= math::ToRadian(1.0f);
        } // if

    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        _camera_controller.GetService()->AddAltitude(1.0f);
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        _camera_controller.GetService()->AddAltitude(-1.0f);
    } // else if

    // chara front
    if (::g_pInput->IsKeyPush(MOFKEY_Q)) {
        _ideal_fps_camera_angle = std::atan2(-_camera_controller.GetService()->GetViewFront().z,
                                             _camera_controller.GetService()->GetViewFront().x);
    } // if

    if (::g_pInput->IsKeyHold(MOFKEY_Q)) {
        _camera_fps_mode = true;
        _camera_controller.GetService()->SetDistance(0.1f);

        if (_camera_controller.GetService()->GetVelocity().Length() < 0.5f) {
            auto rotate = super::GetOwner()->GetRotate();
            rotate.y = _ideal_fps_camera_angle - math::kHalfPi;
            super::GetOwner()->SetRotate(rotate);
        } // if
    } // if
    if (::g_pInput->IsKeyPull(MOFKEY_Q)) {
        _camera_fps_mode = false;
        _camera_controller.GetService()->SetDistance(5.0f);

        float angle_y = super::GetOwner()->GetRotate().y - math::kPi - MOF_MATH_HALFPI;
        float azimuth_degree = math::ToDegree(angle_y);
        _camera_controller.GetService()->SetAzimuth(azimuth_degree);
    } // if
}

void my::CameraComponent::ControlByGamepad(void) {
    float horizontal = ::g_pGamepad->GetRightStickHorizontal();
    float vertical = ::g_pGamepad->GetRightStickVertical();
    float threshold = 0.5f;
    if (auto in = Mof::CVector2(horizontal, vertical); in.Length() > threshold) {
        // x
        if (threshold <= std::abs(in.x)) {
            if (0.0f < in.x) {
                _camera_controller.GetService()->AddAzimuth(1.0f);

                if (_camera_fps_mode) {
                    _ideal_fps_camera_angle += math::ToRadian(1.0f);
                } // if
            } // if
            else {
                _camera_controller.GetService()->AddAzimuth(-1.0f);
                if (_camera_fps_mode) {
                    _ideal_fps_camera_angle -= math::ToRadian(1.0f);
                } // if
            } // else
        } // if
        // y
        if (threshold <= std::abs(in.y)) {
            if (0.0f < in.y) {
                _camera_controller.GetService()->AddAltitude(1.0f);
            } // if
            else {
                _camera_controller.GetService()->AddAltitude(-1.0f);
            } // else 
        } // if
    } // if


    // chara front
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_L_BTN) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        _ideal_fps_camera_angle = std::atan2(-_camera_controller.GetService()->GetViewFront().z,
                                             _camera_controller.GetService()->GetViewFront().x);
    } // if

    if (::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_BTN) ||
        ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        _camera_fps_mode = true;
        _camera_controller.GetService()->SetDistance(0.1f);

        if (_camera_controller.GetService()->GetVelocity().Length() < 0.5f) {
            auto rotate = super::GetOwner()->GetRotate();
            rotate.y = _ideal_fps_camera_angle - math::kHalfPi;
            super::GetOwner()->SetRotate(rotate);
        } // if
    } // if


    if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_BTN) ||
        ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        _camera_fps_mode = false;
        _camera_controller.GetService()->SetDistance(5.0f);

        float angle_y = super::GetOwner()->GetRotate().y - math::kPi - MOF_MATH_HALFPI;
        float azimuth_degree = math::ToDegree(angle_y);
        _camera_controller.GetService()->SetAzimuth(azimuth_degree);
    } // if
}

my::CameraComponent::CameraComponent(int priority) :
    super(priority),
    _target(),
    _player_view_camera(),
    _camera_controller(),
    _camera_fps_mode(false),
    _ideal_fps_camera_angle(0.0f),
    _preview_position(),
    _jump_up_com(),
    _jump_down_com() {
}

my::CameraComponent::CameraComponent(const CameraComponent& obj) :
    super(obj._priority),
    _target(),
    _player_view_camera(),
    _camera_controller(),
    _camera_fps_mode(false),
    _ideal_fps_camera_angle(0.0f),
    _preview_position(),
    _jump_up_com(),
    _jump_down_com() {
}

my::CameraComponent::~CameraComponent() {
}

void my::CameraComponent::SetPosition(Mof::CVector3 pos) {
    return this->_camera_controller.GetService()->SetCameraPosition(pos);
}

void my::CameraComponent::SetTarget(Mof::CVector3 pos) {
    this->_target = pos;
}

std::string my::CameraComponent::GetType(void) const {
    return "CameraComponent";
}

Mof::CVector3 my::CameraComponent::GetViewFront(void) const {
    return this->_camera_controller.GetService()->GetViewFront();
}

Mof::CVector3 my::CameraComponent::GetPosition(void) const {
    return this->_camera_controller.GetService()->GetCameraPosition();
}

Mof::CVector3 my::CameraComponent::GetVelocity(void) const {
    return this->_camera_controller.GetService()->GetVelocity();
}

Mof::CVector3 my::CameraComponent::GetPreviewPosition(void) const {
    return this->_camera_controller.GetService()->GetPreviewPosition();
}

bool my::CameraComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // camera
    _player_view_camera = (std::make_shared<my::Camera>());
    _player_view_camera->Initialize();
    auto pos = super::GetOwner()->GetPosition();
    auto offset = math::vec3::kNegUnitZ;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());

    _player_view_camera->SetPosition(pos - offset);
    _player_view_camera->SetTarget(pos);
    _player_view_camera->Update();
    _camera_controller.SetService(std::make_shared<my::CameraController>());
    _camera_controller.GetService()->SetCamera(_player_view_camera);
    _camera_controller.GetService()->RegisterGlobalCamera();
    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(super::GetOwner()->GetRotate().y + math::kHalfPi));
    _camera_controller.GetService()->SetAltitude(20.0f);


    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _jump_up_com = super::GetOwner()->GetComponent<my::PlayerJumpUpComponent>();
    _jump_down_com = super::GetOwner()->GetComponent<my::PlayerJumpDownComponent>();
    return true;
}

bool my::CameraComponent::Update(float delta_time) {
    this->ControlByGamepad();
    this->ControlByKeyboard();

    auto pos = super::GetOwner()->GetPosition();
    pos.y += 1.0f;

    if (_camera_fps_mode) {
        auto offset = Mof::CVector3(0.0f, 0.0f, 1.0f);
        offset.RotationY(_ideal_fps_camera_angle + MOF_MATH_HALFPI);
        _camera_controller.GetService()->SetCameraTarget(pos + offset);
    } // if
    else {
        auto jump_up_com = _jump_up_com.lock();
        auto jump_down_com = _jump_down_com.lock();
        if (jump_up_com->IsActive() || jump_down_com->IsActive()) {
            auto temp = pos;
            temp.y = _preview_position.y;
            _camera_controller.GetService()->SetCameraTarget(temp);
        } // if
        else {
            _preview_position = pos;
            _camera_controller.GetService()->SetCameraTarget(pos);
        } // else
    } // else
    _camera_controller.GetService()->Update();

    if (::g_pInput->IsKeyPush(MOFKEY_F1)) {
        auto controller = std::make_shared<my::FollowCameraController>();
        auto camera = _camera_controller.GetService()->GetCamera();
        _camera_controller.SetService(controller);
        _camera_controller.GetService()->SetCamera(camera);
    } // if
    if (::g_pInput->IsKeyPush(MOFKEY_F2)) {
        auto controller = std::make_shared<my::DebugCameraController>();
        auto camera = _camera_controller.GetService()->GetCamera();
        _camera_controller.SetService(controller);
        _camera_controller.GetService()->SetCamera(camera);
    } // if
    return true;
}

bool my::CameraComponent::Release(void) {
    super::Release();
    _camera_controller.GetService()->Release();
    _player_view_camera.reset();
    return true;
}

std::shared_ptr<my::Component> my::CameraComponent::Clone(void) {
    return std::make_shared<my::CameraComponent>(*this);
}