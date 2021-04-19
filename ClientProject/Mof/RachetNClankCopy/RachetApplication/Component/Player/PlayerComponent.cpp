#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../../Component/HpComponent.h"
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
    _volume(0.5f),
    _height(1.0f),
    _target(),
    _idle_com(),
    _move_com(),
    _damage_com() {
}

my::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _volume(0.5f),
    _height(1.0f),
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

float my::PlayerComponent::GetVolume(void) const {
    return this->_volume;
}

float my::PlayerComponent::GetHeight(void) const {
    return this->_height;
}

std::weak_ptr<my::Actor> my::PlayerComponent::GetTarget(void) const {
    return this->_target;
}

bool my::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    _idle_com = super::GetOwner()->GetComponent<my::PlayerIdleComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();
    _damage_com = super::GetOwner()->GetComponent<my::PlayerDamageComponent>();

    if (auto canvas = super::_ui_canvas.lock()) {
        auto menu = std::make_shared<my::LockOnCursorMenu>("LockOnCursorMenu");
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
        _observable.Notify(target->GetPosition());
    } // if
    else {
        _observable.Notify(std::optional<Mof::CVector3>());
    } // else 
    return true;
}

bool my::PlayerComponent::Render(void) {
    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionComponent>();
    if (coll_com->GetSphere().has_value()) {
        ::CGraphicsUtilities::RenderLineSphere(coll_com->GetSphere().value(), def::color_rgba::kCyan);
    } // if

    if (auto target = _target.lock()) {
        auto sphere = Mof::CSphere(target->GetPosition(), 1.0f);
        ::CGraphicsUtilities::RenderLineSphere(sphere, def::color_rgba::kYellow);
    } // if
    return true;
}

bool my::PlayerComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerComponent::Clone(void) {
    return std::make_shared<my::PlayerComponent>(*this);
}