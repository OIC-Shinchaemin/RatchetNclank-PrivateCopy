#include "CameraComponent.h"

#include "../Gamepad.h"
#include "../Camera/FollowCameraController.h"
#include "../Camera/FirstPersonCameraController.h"
#include "../Camera/DebugCameraController.h"
#include "Player/PlayerStateComponent.h"
#include "../Event/EventReferenceTable.h"
#include "AnimationMeshComponent.h"
#include "../Component/Collision/Object/PlayerCollisionComponent.h"


void ratchet::component::CameraComponent::OnPush(void) {
    if (_current_mode != ratchet::camera::CameraController::CameraMode::Follow) {
        return;
    } // if

    if (auto state_com = _state_com.lock()) {
        auto state = state::PlayerActionStateType::kPlayerActionLookState;
        if (!state_com->CanTransition(state)) {
            return;
        } // if
        state_com->ChangeState(state);
    } // if

    auto eye_pos = super::GetOwner()->GetPosition();
    eye_pos.y += 1.0f;

    auto prev_pos = _controller_map.at(_current_mode)->GetCameraPosition();
    auto front = _controller_map.at(_current_mode)->GetViewFront();

    _current_mode = ratchet::camera::CameraController::CameraMode::FirstPerson;
    auto con = _controller_map.at(_current_mode);

    auto info = ratchet::camera::CameraController::CameraInfo();
    info.start_position = prev_pos;
    info.camera_front = front;
    info.ideal_position = eye_pos;
    con->SetInfo(info);
    _camera_controller.SetService(con);
}

void ratchet::component::CameraComponent::OnHold(void) {
    if (_current_mode != ratchet::camera::CameraController::CameraMode::FirstPerson) {
        return;
    } // if

    auto camera_pos = _controller_map.at(_current_mode)->GetCameraPosition();
    auto eye_pos = super::GetOwner()->GetPosition();
    eye_pos.y += 1.0f;

    float diff = std::fabs(camera_pos.Length() - eye_pos.Length());
    if (diff < 0.1f) {
        auto camera_front = _controller_map.at(_current_mode)->GetViewFront();

        float angle_y = std::atan2(-camera_front.z, camera_front.x) - math::kHalfPi;
        auto angle = Mof::CVector3(0.0f, angle_y, 0.0f);
        super::GetOwner()->SetRotate(angle);


        if (auto mesh = _mesh_com.lock()) {
            mesh->Inactivate();
        } // if
    } // if
}

void ratchet::component::CameraComponent::OnPull(void) {
    if (_current_mode != ratchet::camera::CameraController::CameraMode::FirstPerson) {
        return;
    } // if

    auto prev_pos = _controller_map.at(_current_mode)->GetCameraPosition();

    _current_mode = ratchet::camera::CameraController::CameraMode::Follow;
    _state_com.lock()->ChangeState(state::PlayerActionStateType::kPlayerActionIdleState);
    float ideal_angle_y = super::GetOwner()->GetRotate().y + math::kHalfPi;
    auto info = ratchet::camera::CameraController::CameraInfo();
    info.start_position = prev_pos;

    auto con = _controller_map.at(_current_mode);
    con->SetAzimuth(math::ToDegree(ideal_angle_y));
    con->SetInfo(info);
    _camera_controller.SetService(con);

    if (auto mesh = _mesh_com.lock()) {
        mesh->Activate();
    } // if
}

void ratchet::component::CameraComponent::TurnLeft(void) {
    _camera_controller.GetService()->AddAzimuth(1.0f);
}

void ratchet::component::CameraComponent::TurnRight(void) {
    _camera_controller.GetService()->AddAzimuth(-1.0f);
}

void ratchet::component::CameraComponent::LookUp(void) {
    _camera_controller.GetService()->AddAltitude(1.0f);
}

void ratchet::component::CameraComponent::LookDown(void) {
    _camera_controller.GetService()->AddAltitude(-1.0f);
}

void ratchet::component::CameraComponent::UpdateFPSMode(void) {
}

void ratchet::component::CameraComponent::ControlByKeyboardFollow(void) {
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
        this->OnPush();
    } // if
}

void ratchet::component::CameraComponent::ControlByKeyboardFirstPerson(void) {
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

    if (::g_pInput->IsKeyHold(MOFKEY_Q)) {
        this->OnHold();
    } // if
    else if (::g_pInput->IsKeyPull(MOFKEY_Q)) {
        this->OnPull();
    } // else if
}

void ratchet::component::CameraComponent::ControlByKeyboard(void) {
    using Mode = ratchet::camera::CameraController::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            this->ControlByKeyboardFollow();
            break;
        case Mode::FirstPerson:
            this->ControlByKeyboardFirstPerson();
            break;
    } // switch
}

void ratchet::component::CameraComponent::ControlByGamepad(void) {
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
    if (::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_L_BTN) || ::g_pGamepad->IsKeyPush(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->OnPush();
    } // if
    else if (::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_BTN) || ::g_pGamepad->IsKeyHold(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->OnHold();
    } // else if
    else if (::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_BTN) || ::g_pGamepad->IsKeyPull(Mof::XInputButton::XINPUT_L_TRIGGER)) {
        this->OnPull();
    } // else if
}

void ratchet::component::CameraComponent::UpdateFollow(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller) {
    if (_collisioned_stage) {
        //controller->SetAzimuth(math::ToDegree(_preview_angle.x));
        //controller->SetAltitude(math::ToDegree(_preview_angle.y));
        //_collisioned_stage = false;
    } // if

    auto pos = super::GetOwner()->GetPosition();
    auto camera_info = ratchet::camera::CameraController::CameraInfo();

    if (_follow_camera_prev_position_update) {
        pos.y = _preview_position.y;
        camera_info.target_position = pos;
        controller->Update(delta_time, camera_info);
        return;
    } // if

    _preview_angle.x = controller->GetAzimuth();
    _preview_angle.y = controller->GetAltitude();
    _preview_position = pos;

    camera_info.target_position = pos;
    if (::g_pInput->IsKeyHold(MOFKEY_SPACE)) {
        auto p = pos;
        p.y = 10.0f;
        camera_info.target_position = p;
        //super::GetOwner()->SetPosition(p);
    } // if
    controller->Update(delta_time, camera_info);
}

void ratchet::component::CameraComponent::UpdateFirstPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller) {
    auto eye_pos = super::GetOwner()->GetPosition();
    eye_pos.y += 1.0f;

    auto camera_info = ratchet::camera::CameraController::CameraInfo();
    camera_info.ideal_position = eye_pos;
    controller->Update(delta_time, camera_info);
}

void ratchet::component::CameraComponent::UpdateThirdPerson(float delta_time, std::shared_ptr<ratchet::camera::CameraController> controller) {
}

ratchet::component::CameraComponent::CameraComponent(int priority) :
    super(priority),
    _target(),
    _camera(),
    _camera_controller(),
    _current_mode(ratchet::camera::CameraController::CameraMode::Follow),
    _ideal_fps_camera_angle(0.0f),
    _default_distance(8.0f),
    _preview_position(),
    _collisioned_stage(),
    _preview_angle(),
    _follow_camera_prev_position_update(false) {
}

ratchet::component::CameraComponent::CameraComponent(const CameraComponent& obj) :
    super(obj),
    _target(),
    _camera(),
    _camera_controller(),
    _current_mode(ratchet::camera::CameraController::CameraMode::Follow),
    _ideal_fps_camera_angle(0.0f),
    _default_distance(obj._default_distance),
    _preview_position(),
    _collisioned_stage(),
    _preview_angle(),
    _follow_camera_prev_position_update() {
}

ratchet::component::CameraComponent::~CameraComponent() {
}

void ratchet::component::CameraComponent::OnNotify(const ratchet::camera::CameraController::CameraInfo& info) {
    _camera->SetPosition(info.start_position);
    _camera->SetTarget(info.target_position);
    _camera->Update();
    _camera_controller.GetService()->RegisterGlobalCamera();
    _camera_controller.GetService()->SetAzimuth(math::ToDegree(super::GetOwner()->GetRotate().y + math::kHalfPi));
    _camera_controller.GetService()->SetAltitude(20.0f);
    _camera_controller.GetService()->SetDistance(_default_distance);
}

void ratchet::component::CameraComponent::SetFollowCameraPrevPositionUpdateFlag(bool flag) {
    this->_follow_camera_prev_position_update = flag;
}

std::string ratchet::component::CameraComponent::GetType(void) const {
    return "CameraComponent";
}

Mof::CVector3 ratchet::component::CameraComponent::GetViewFront(void) const {
    return this->_camera_controller.GetService()->GetViewFront();
}

Mof::CVector3 ratchet::component::CameraComponent::GetPosition(void) const {
    return this->_camera_controller.GetService()->GetCameraPosition();
}

Mof::CVector3 ratchet::component::CameraComponent::GetVelocity(void) const {
    return this->_camera_controller.GetService()->GetVelocity();
}

Mof::CVector3 ratchet::component::CameraComponent::GetPreviewPosition(void) const {
    return this->_camera_controller.GetService()->GetPreviewPosition();
}

bool ratchet::component::CameraComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    _state_com = super::GetOwner()->GetComponent<ratchet::component::player::PlayerStateComponent>();
    _mesh_com = super::GetOwner()->GetComponent<ratchet::component::AnimationMeshComponent>();

    // camera
    using Mode = ratchet::camera::CameraController::CameraMode;
    _camera = (std::make_shared<ratchet::camera::Camera>());
    _camera->Initialize();
    _controller_map.emplace(Mode::Follow, std::make_shared<ratchet::camera::FollowCameraController>());
    _controller_map.emplace(Mode::FirstPerson, std::make_shared<ratchet::camera::FirstPersonCameraController>());
    _controller_map.at(Mode::Follow)->SetCamera(_camera);
    _controller_map.at(Mode::FirstPerson)->SetCamera(_camera);
    _camera_controller.SetService(_controller_map.at(Mode::Follow));
    auto pos = super::GetOwner()->GetPosition();
    auto offset = Mof::CVector3(math::vec3::kNegUnitZ * _default_distance);
    offset.RotateAround(math::vec3::kZero, super::GetOwner()->GetRotate());

    ratchet::event::EventReferenceTable::Singleton().Register("CameraComponent", std::dynamic_pointer_cast<ratchet::component::CameraComponent>(shared_from_this()));
    return true;
}

bool ratchet::component::CameraComponent::Update(float delta_time) {
    this->ControlByGamepad();
    this->ControlByKeyboard();

    auto camera_controller = _camera_controller.GetService();
    using Mode = ratchet::camera::CameraController::CameraMode;
    switch (_current_mode) {
        case Mode::Follow:
            this->UpdateFollow(delta_time, camera_controller);
            break;
        case Mode::FirstPerson:
            this->UpdateFirstPerson(delta_time, camera_controller);
            break;
        case Mode::ThirdPerson:
            this->UpdateThirdPerson(delta_time, camera_controller);
            break;
    } // switch
    return true;
}

bool ratchet::component::CameraComponent::Release(void) {
    super::Release();
    _camera.reset();
    _camera_controller.GetService()->Release();
    _controller_map.clear();
    _state_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::CameraComponent::Clone(void) {
    return std::make_shared<ratchet::component::CameraComponent>(*this);
}

void ratchet::component::CameraComponent::CollisionStage(void) {
    _collisioned_stage = true;
}
#ifdef _DEBUG
bool ratchet::component::CameraComponent::DebugRender(void) {
    auto render = [](const char* name) {
        ::CGraphicsUtilities::RenderString(
            20.0f, 200.0f, "camera state = %s", name);
    };

    auto coll_com = super::GetOwner()->GetComponent<component::collision::PlayerCollisionComponent>();
    auto point = coll_com->collision_point_stage_down_ray;
    ::CGraphicsUtilities::RenderSphere(Mof::CSphere(point, 1.0f), def::color_rgba::kBlue);


    using Mode = ratchet::camera::CameraController::CameraMode;
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
#endif // _DEBUG