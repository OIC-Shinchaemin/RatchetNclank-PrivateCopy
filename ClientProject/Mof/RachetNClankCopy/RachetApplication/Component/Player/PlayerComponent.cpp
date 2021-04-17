#include "PlayerComponent.h"

#include "../../Gamepad.h"
#include "../Player/PlayerIdleComponent.h"
#include "../Player/PlayerMoveComponent.h"
#include "../Collision/Object/PlayerCollisionObject.h"


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
    _idle_com(),
    _move_com(),
    _volume(0.5f),
    _height(1.0f) {
}

my::PlayerComponent::PlayerComponent(const PlayerComponent& obj) :
    super(obj),
    _idle_com(),
    _move_com(),
    _volume(0.5f),
    _height(1.0f) {
}

my::PlayerComponent::~PlayerComponent() {
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

bool my::PlayerComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    _idle_com = super::GetOwner()->GetComponent<my::PlayerIdleComponent>();
    _move_com = super::GetOwner()->GetComponent<my::PlayerMoveComponent>();


    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionObject>();
    coll_com->AddCollisionFunc(my::CollisionObject::CollisionFuncType::Enter,
                                 "EnemyAttackCollisionObject",
                                 my::CollisionObject::CollisionFunc([&](const my::CollisionInfo& in) {
        puts("Hited");
        return true;
    }));
    return true;
}

bool my::PlayerComponent::Update(float delta_time) {
    float angular_speed = 3.5f;
    float speed = 0.6f;

    if (!this->MoveByKeyboard(angular_speed, speed)) {
        this->MoveByGamepad(angular_speed, speed);
    } // if
    return true;
}

bool my::PlayerComponent::Render(void) {
    auto coll_com = super::GetOwner()->GetComponent<my::PlayerCollisionObject>();
    ::CGraphicsUtilities::RenderLineSphere(coll_com->GetSphere().value(), def::color_rgba::kCyan);
    return true;
}

bool my::PlayerComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerComponent::Clone(void) {
    return std::make_shared<my::PlayerComponent>(*this);
}