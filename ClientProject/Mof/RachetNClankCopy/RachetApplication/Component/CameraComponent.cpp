#include "CameraComponent.h"

#include "../Gamepad.h"
#include "../Camera/FollowCameraController.h"
#include "../Camera/FirstPersonCameraController.h"
#include "../Camera/DebugCameraController.h"
#include "Player/PlayerStateComponent.h"


void my::CameraComponent::TurnLeft(void) {
    _camera_controller.GetService()->AddAzimuth(1.0f);
    if (_current_mode == my::CameraComponent::CameraMode::FirstPerson) {
        _ideal_fps_camera_angle += math::ToRadian(1.0f);
    } // if
}

void my::CameraComponent::TurnRight(void) {
    _camera_controller.GetService()->AddAzimuth(-1.0f);
    if (_current_mode == my::CameraComponent::CameraMode::FirstPerson) {
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
    _current_mode = my::CameraComponent::CameraMode::FirstPerson;

    if (_camera_controller.GetService()->GetVelocity().Length() < 0.5f) {
        auto rotate = super::GetOwner()->GetRotate();
        rotate.y = _ideal_fps_camera_angle - math::kHalfPi;
        super::GetOwner()->SetRotate(rotate);
    } // if
}

void my::CameraComponent::ExitFPSMode(void) {
    _current_mode = my::CameraComponent::CameraMode::Follow;

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
        _state_com.lock()->ChangeState(state::PlayerActionStateType::kPlayerActionLookState);
        this->IdealAngle();
        auto con = _controller_map.at(_current_mode);
        _camera_controller.SetService(con);
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_Q)) {
        this->UpdateFPSMode();
    } // if
    else if (::g_pInput->IsKeyPull(MOFKEY_Q)) {
        _state_com.lock()->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
        this->ExitFPSMode();
        //_camera_controller.SetService(_follow_camera_controller);
        auto con = _controller_map.at(_current_mode);
        _camera_controller.SetService(con);
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
        _state_com.lock()->ChangeState(state::PlayerActionStateType::kPlayerActionLookState);
        this->IdealAngle();
        auto con = _controller_map.at(_current_mode);
        _camera_controller.SetService(con);
    } // if
    else if (::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_BTN) ||
             ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->UpdateFPSMode();
    } // else if
    else if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_BTN) ||
             ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        _state_com.lock()->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
        this->ExitFPSMode();

        auto con = _controller_map.at(_current_mode);
        _camera_controller.SetService(con);
    } // else if
}

void my::CameraComponent::UpdateFollow(float delta_time, std::shared_ptr<my::CameraController> controller) {
    if (_collisioned_stage) {
        controller->SetAzimuth(math::ToDegree(_preview_angle.x));
        controller->SetAltitude(math::ToDegree(_preview_angle.y));
        _collisioned_stage = false;
    } // if

    auto pos = super::GetOwner()->GetPosition();
    auto camera_info = my::CameraController::CameraInfo();

    auto state_com = _state_com.lock();
    if (state_com->IsEqual(state::PlayerActionStateType::kPlayerActionJumpUpState) || state_com->IsEqual(state::PlayerActionStateType::kPlayerActionJumpDownState) || state_com->IsEqual(state::PlayerActionStateType::kPlayerActionDoubleJumpState)) {
        pos.y = _preview_position.y;
        controller->SetCameraTarget(pos);
        controller->Update(delta_time, camera_info);
        return;
    } // if
    else {
        _preview_position = pos;
        controller->SetCameraTarget(pos);
        camera_info.target = pos;
    } // else

    _preview_angle.x = controller->GetAzimuth();
    _preview_angle.y = controller->GetAltitude();
    controller->Update(delta_time, camera_info);
}

void my::CameraComponent::UpdateFirstPerson(float delta_time, std::shared_ptr<my::CameraController> controller) {
    auto pos = super::GetOwner()->GetPosition();
    auto camera_info = my::CameraController::CameraInfo();

    auto offset = Mof::CVector3(0.0f, 0.0f, 1.0f);
    offset.RotationY(_ideal_fps_camera_angle + MOF_MATH_HALFPI);
    controller->SetCameraTarget(pos + offset);
    camera_info.target = pos + offset;
    controller->Update(delta_time, camera_info);
}

my::CameraComponent::CameraComponent(int priority) :
    super(priority),
    _target(),
    _camera(),
    _camera_controller(),
    _current_mode(my::CameraComponent::CameraMode::Follow),
    _ideal_fps_camera_angle(0.0f),
    _default_distance(8.0f),
    _preview_position(),
    _collisioned_stage(),
    _preview_angle() {
}

my::CameraComponent::CameraComponent(const CameraComponent& obj) :
    super(obj),
    _target(),
    _camera(),
    _camera_controller(),
    _current_mode(my::CameraComponent::CameraMode::Follow),
    _ideal_fps_camera_angle(0.0f),
    _default_distance(obj._default_distance),
    _preview_position(),
    _collisioned_stage(),
    _preview_angle() {
}

my::CameraComponent::~CameraComponent() {
}

void my::CameraComponent::OnNotify(const my::CameraController::CameraInfo& info) {
    _camera->SetPosition(info.position);
    _camera->SetTarget(info.target);
    _camera->Update();
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
    _camera = (std::make_shared<my::Camera>());
    _camera->Initialize();

    using Mode = my::CameraComponent::CameraMode;

    _controller_map.emplace(Mode::Follow, std::make_shared<my::FollowCameraController>());
    _controller_map.emplace(Mode::FirstPerson, std::make_shared<my::FirstPersonCameraController>());
    _controller_map.at(Mode::Follow)->SetCamera(_camera);
    _controller_map.at(Mode::FirstPerson)->SetCamera(_camera);
    _camera_controller.SetService(_controller_map.at(Mode::Follow));

    auto pos = super::GetOwner()->GetPosition();
    auto offset = math::vec3::kNegUnitZ;
    offset *= 9.0f;
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());

    _state_com = super::GetOwner()->GetComponent<my::PlayerStateComponent>();
    return true;
}

bool my::CameraComponent::Update(float delta_time) {
    this->ControlByGamepad();
    this->ControlByKeyboard();


    auto camera_controller = _camera_controller.GetService();
    using Mode = my::CameraComponent::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            this->UpdateFollow(delta_time, camera_controller); break;
        case Mode::FirstPerson:
            this->UpdateFirstPerson(delta_time, camera_controller); break;
    } // switch

    /*
    auto pos = super::GetOwner()->GetPosition();
    pos.y += 1.0f;
    auto camera_info = my::CameraController::CameraInfo();
    camera_info.rotate = super::GetOwner()->GetRotate();
    camera_info.position = pos;
    if (_current_mode == my::CameraComponent::CameraMode::FirstPerson) {
    } // if
    */
    return true;
}

bool my::CameraComponent::Release(void) {
    super::Release();
    _camera.reset();
    _camera_controller.GetService()->Release();
    _controller_map.clear();
    _state_com.reset();
    return true;
}

std::shared_ptr<my::Component> my::CameraComponent::Clone(void) {
    return std::make_shared<my::CameraComponent>(*this);
}

void my::CameraComponent::CollisionStage(void) {
    _collisioned_stage = true;
}

bool my::CameraComponent::DebugRender(void) {
    auto render = [](const char* name) {
        ::CGraphicsUtilities::RenderString(
            20.0f, 200.0f, "camera state = %s", name);
    };
    using Mode = my::CameraComponent::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            render("Mode::Follow");
            break;
        case Mode::FirstPerson:
            render("Mode::FirstPerson");
            break;
        default:
            break;
    } // switch
    return true;
}