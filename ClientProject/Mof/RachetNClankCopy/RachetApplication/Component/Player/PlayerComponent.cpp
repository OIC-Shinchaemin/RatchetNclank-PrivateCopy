#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../../Component/HpComponent.h"
#include "../../Component/VelocityComponent.h"
#include "../Player/PlayerIdleComponent.h"
#include "../Player/PlayerMoveComponent.h"
#include "../Player/PlayerDamageComponent.h"
#include "../Collision/Object/PlayerCollisionComponent.h"
#include "../../UI/LockOnCursorMenu.h"


bool my::PlayerComponent::MoveByKeyboard(float angular_speed, float speed) {
    // keyboard
    bool action = false; bool left = false; bool right = false;
    auto in = Mof::CVector2(1.0f, 0.0f);
    float move_angle = 0.0f;

    
    if (::g_pInput->IsKeyHold(MOFKEY_A)) {
        action = true;
        left = true;
        move_angle = 180.0f;
    } // if
    else if (::g_pInput->IsKeyHold(MOFKEY_D)) {
        action = true;
        right = true;
        move_angle = 0.0f;
    } // else if
    if (::g_pInput->IsKeyHold(MOFKEY_W)) {
        action = true;
        move_angle = 90.0f;
        if (right) {
            move_angle -= 45.0f;
        } // if
        else if (left) {
            move_angle += 45.0f;
        } // else if
    } // else if
    else if (::g_pInput->IsKeyHold(MOFKEY_S)) {
        action = true;
        move_angle = 270.0f;
        if (right) {
            move_angle += 45.0f;
        } // if
        else if (left) {
            move_angle -= 45.0f;
        } // else if
    } // else if

    if (::g_pInput->IsKeyHold(MOFKEY_J)) {
        auto v = super::GetOwner()->GetComponent<my::VelocityComponent>();
        v->AddVelocityForce(Mof::CVector3(0.0f, 10.0f, 0.0f));
    } // if


    if (action) {
        if (auto move_com = _move_com.lock()) {
            in = math::Rotate(in.x, in.y, math::ToRadian(move_angle));
            move_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
            move_com->SetAngularSpeed(angular_speed);
            move_com->SetMoveSpeed(speed);
            move_com->Start();
        } // if
    } // if
    else {
        if (auto idle_com = _idle_com.lock()) {
            idle_com->Start();
        } // if
    } // else 

    return action;
}

void my::PlayerComponent::MoveByGamepad(float angular_speed, float speed) {
    float h = 0.0f;
    float v = 0.0f;
    float threshold = 0.5f;

    h = ::g_pGamepad->GetStickHorizontal();
    v = ::g_pGamepad->GetStickVertical();
    if (auto in = Mof::CVector2(h, v); in.Length() > threshold) {
        if (auto move_com = _move_com.lock()) {
            move_com->SetIdealAngle(std::atan2(-in.y, in.x) - math::kHalfPi);
            move_com->SetAngularSpeed(angular_speed);
            move_com->SetMoveSpeed(speed);
            move_com->Start();
        } // if
    } // if
    else {
        if (auto idle_com = _idle_com.lock()) {
            idle_com->Start();
        } // if
    } // else
}

my::PlayerComponent::PlayerComponent(int priority) :
    super(priority),
    _target(),
    _idle_com(),
    _move_com(),
    _damage_com() {
    super::_volume = 0.5f;
    super::_height = 1.0f;
}

my::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _target(),
    _idle_com(),
    _move_com(),
    _damage_com() {
}

my::PlayerComponent::~PlayerComponent() {
}

void my::PlayerComponent::SetTarget(const std::shared_ptr<my::Actor>& ptr) {
    this->_target = ptr;
}

std::string my::PlayerComponent::GetType(void) const {
    return "PlayerComponent";
}

std::weak_ptr<my::Actor> my::PlayerComponent::GetTarget(void) const {
    return this->_target;
}

bool my::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    auto velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _idle_com = super::GetOwner()->GetComponent<my::PlayerIdleComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    _damage_com = super::GetOwner()->GetComponent<my::PlayerDamageComponent>();

    velocity_com->SetGravity(0.98f);

    if (auto canvas = super::_ui_canvas.lock()) {
        canvas->RemoveElement("LockOnCursorMenu");
        auto menu = std::make_shared<my::LockOnCursorMenu>("LockOnCursorMenu");
        menu->SetResourceManager(_resource_manager);
        _observable.AddObserver(menu);
        canvas->AddElement(menu);
    } // if
    return true;
}

bool my::PlayerComponent::Update(float delta_time) {
    float angular_speed = 3.5f;
    float speed = 0.6f;

    if (auto damage_com = _damage_com.lock()) {
        if (!damage_com->IsActive()) {

            if (!this->MoveByKeyboard(angular_speed, speed)) {
                this->MoveByGamepad(angular_speed, speed);
            } // if
        } // if
    } // if

    if (auto target = _target.lock()) {
        auto enemy_com = target->GetComponent<super>();
        auto pos = target->GetPosition();
        pos.y += enemy_com->GetHeight();
        _observable.Notify(pos);
    } // if
    else {
        _observable.Notify(std::optional<Mof::CVector3>());
    } // else 
    return true;
}

bool my::PlayerComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerComponent::Clone(void) {
    return std::make_shared<my::PlayerComponent>(*this);
}