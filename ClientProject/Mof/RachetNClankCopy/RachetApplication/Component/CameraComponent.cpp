#include "CameraComponent.h"

#include "../Gamepad.h"
#include "../Camera/FollowCameraController.h"
#include "../Camera/DebugCameraController.h"
#include "VelocityComponent.h"
#include "Player/PlayerJumpUpComponent.h"
#include "Player/PlayerJumpDownComponent.h"
#include "Player/PlayerDoubleJumpComponent.h"


void my::CameraComponent::TurnLeft(void) {
    _camera_controller.GetService()->AddAzimuth(1.0f);
    if (_camera_fps_mode) {
        _ideal_fps_camera_angle += math::ToRadian(1.0f);
    } // if
}

void my::CameraComponent::TurnRight(void) {
    _camera_controller.GetService()->AddAzimuth(-1.0f);
    if (_camera_fps_mode) {
        _ideal_fps_camera_angle -= math::ToRadian(1.0f);
    } // if
}

void my::CameraComponent::LookUp(void) {
    _camera_controller.GetService()->AddAltitude(1.0f);
}

void my::CameraComponent::LookDown(void) {
    _camera_controller.GetService()->AddAltitude(-1.0f);
}

void my::CameraComponent::IdealAngle(void) {
    _ideal_fps_camera_angle = std::atan2(-_camera_controller.GetService()->GetViewFront().z,
                                         _camera_controller.GetService()->GetViewFront().x);
}

void my::CameraComponent::UpdateFPSMode(void) {
    _camera_fps_mode = true;
    _camera_controller.GetService()->SetDistance(0.1f);

    if (_camera_controller.GetService()->GetVelocity().Length() < 0.5f) {
        auto rotate = super::GetOwner()->GetRotate();
        rotate.y = _ideal_fps_camera_angle - math::kHalfPi;
        super::GetOwner()->SetRotate(rotate);
    } // if
}

void my::CameraComponent::ExitFPSMode(void) {
    _camera_fps_mode = false;
    _camera_controller.GetService()->SetDistance(_default_distance);

    float angle_y = super::GetOwner()->GetRotate().y - math::kPi - MOF_MATH_HALFPI;
    float azimuth_degree = math::ToDegree(angle_y);
    _camera_controller.GetService()->SetAzimuth(azimuth_degree);
}

void my::CameraComponent::ControlByKeyboard(void) {
    if (::g_pInput->IsKeyHold(MOFKEY_LEFT)) {
        this->TurnLeft();
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_RIGHT)) {
        this->TurnRight();
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_UP)) {
        this->LookUp();
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_DOWN)) {
        this->LookDown();
    } // else if

    // chara front
    if (::g_pInput->IsKeyPush(MOFKEY_Q)) {
        this->IdealAngle();
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_Q)) {
        this->UpdateFPSMode();
    } // if
    else if (::g_pInput->IsKeyPull(MOFKEY_Q)) {
        this->ExitFPSMode();
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
                this->TurnLeft();
            } // if
            else {
                this->TurnRight();
            } // else
        } // if
        // y
        if (threshold <= std::abs(in.y)) {
            if (0.0f < in.y) {
                this->LookUp();
            } // if
            else {
                this->LookDown();
            } // else 
        } // if
    } // if

    // chara front
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_L_BTN) ||
        ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->IdealAngle();
    } // if
    else if (::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_BTN) ||
        ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->UpdateFPSMode();
    } // else if
    else if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_BTN) ||
        ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->ExitFPSMode();
    } // else if
}

my::CameraComponent::CameraComponent(int priority) :
    super(priority),
    _target(),
    _player_view_camera(),
    _camera_controller(),
    _camera_fps_mode(false),
    _ideal_fps_camera_angle(0.0f),
    _default_distance(8.0f),
    _preview_position(),
    _collisioned_stage(),
    _preview_angle(),
    _jump_up_com(),
    _jump_down_com(),
    _double_jump_com() {
}

my::CameraComponent::CameraComponent(const CameraComponent& obj) :
    super(obj),
    _target(),
    _player_view_camera(),
    _camera_controller(),
    _camera_fps_mode(false),
    _ideal_fps_camera_angle(0.0f),
    _default_distance(obj._default_distance),
    _preview_position(),
    _collisioned_stage(),
    _preview_angle(),
    _jump_up_com(),
    _jump_down_com(),
    _double_jump_com() {
}

my::CameraComponent::~CameraComponent() {
}

void my::CameraComponent::OnNotify(const my::CameraController::CameraInfo& info) {
    _player_view_camera->SetPosition(info.position);
    _player_view_camera->SetTarget(info.target);
    _player_view_camera->Update();
    _camera_controller.GetService()->RegisterGlobalCamera();
    _camera_controller.GetService()->SetAzimuth(
        math::ToDegree(super::GetOwner()->GetRotate().y + math::kHalfPi));
    _camera_controller.GetService()->SetAltitude(20.0f);
    _camera_controller.GetService()->SetDistance(_default_distance);
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
    super::Activate();

    // camera
    _player_view_camera = (std::make_shared<my::Camera>());
    _player_view_camera->Initialize();
    _camera_controller.SetService(std::make_shared<my::CameraController>());
    _camera_controller.GetService()->SetCamera(_player_view_camera);

    auto pos = super::GetOwner()->GetPosition();
    auto offset = math::vec3::kNegUnitZ;
    offset *= 9.0f;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());
    
    
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _jump_up_com = super::GetOwner()->GetComponent<my::PlayerJumpUpComponent>();
    _jump_down_com = super::GetOwner()->GetComponent<my::PlayerJumpDownComponent>();
    _double_jump_com = super::GetOwner()->GetComponent<my::PlayerDoubleJumpComponent>();
    return true;
}

bool my::CameraComponent::Update(float delta_time) {
    this->ControlByGamepad();
    this->ControlByKeyboard();

    auto pos = super::GetOwner()->GetPosition();
    pos.y += 1.0f;

    auto camera_controller = _camera_controller.GetService();

    if (_camera_fps_mode) {
        auto offset = Mof::CVector3(0.0f, 0.0f, 1.0f);
        offset.RotationY(_ideal_fps_camera_angle + MOF_MATH_HALFPI);
        camera_controller->SetCameraTarget(pos + offset);
    } // if
    else {
        auto jump_up_com = _jump_up_com.lock();
        auto jump_down_com = _jump_down_com.lock();
        auto double_jump_com = _double_jump_com.lock();
        if (jump_up_com->IsActive() || jump_down_com->IsActive() || double_jump_com->IsActive()) {
            auto temp = pos;
            temp.y = _preview_position.y;
            camera_controller->SetCameraTarget(temp);
        } // if
        else {
            _preview_position = pos;
            camera_controller->SetCameraTarget(pos);
        } // else

        if (_collisioned_stage) {
            camera_controller->SetAzimuth(math::ToDegree(_preview_angle.x));
            camera_controller->SetAltitude(math::ToDegree(_preview_angle.y));
            _collisioned_stage = false;
        } // if
        _preview_angle.x = camera_controller->GetAzimuth();
        _preview_angle.y = camera_controller->GetAltitude();
    } // else
    camera_controller->Update(delta_time);

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

void my::CameraComponent::CollisionStage(void) {
    _collisioned_stage = true;
}
