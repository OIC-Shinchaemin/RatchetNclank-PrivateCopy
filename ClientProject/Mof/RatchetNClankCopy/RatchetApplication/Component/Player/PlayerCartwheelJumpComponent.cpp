#include "PlayerCartwheelJumpComponent.h"

#include "PlayerMoveComponent.h"


void ratchet::PlayerCartwheelJumpComponent::InputJumpVelocity(float speed) {
    auto velocity_com = super::GetVelocityComponent();
    auto v = velocity_com->GetVelocity();
    v.y = speed;
    velocity_com->SetVelocity(v);
}

ratchet::PlayerCartwheelJumpComponent::PlayerCartwheelJumpComponent(int priority) :
    super(priority),
    _jump_speed(0.0f),
    _jump_decrase(0.4f),
    _move_angle(0.0f),
    _move_com() {
}

ratchet::PlayerCartwheelJumpComponent::PlayerCartwheelJumpComponent(const PlayerCartwheelJumpComponent& obj) :
    super(obj),
    _jump_speed(0.0f),
    _jump_decrase(obj._jump_decrase),
    _move_angle(0.0f),
    _move_com() {
}

ratchet::PlayerCartwheelJumpComponent::~PlayerCartwheelJumpComponent() {
}

std::string ratchet::PlayerCartwheelJumpComponent::GetType(void) const {
    return "PlayerCartwheelJumpComponent";
}

std::string_view ratchet::PlayerCartwheelJumpComponent::GetStateType(void) const {
    return state::PlayerActionStateType::kPlayerActionCartwheelJumpState;
}

void ratchet::PlayerCartwheelJumpComponent::SetJumpSpeed(float speed) {
    this->_jump_speed = speed;
}

void ratchet::PlayerCartwheelJumpComponent::SetMoveAngle(float radian) {
    this->_move_angle = radian;
}

bool ratchet::PlayerCartwheelJumpComponent::Initialize(void) {
    super::Initialize();
    _move_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::PlayerMoveComponent>();
    return true;
}

bool ratchet::PlayerCartwheelJumpComponent::Input(void) {
    return false;
}

bool ratchet::PlayerCartwheelJumpComponent::Update(float delta_time) {
    if (0.0f < std::abs(_jump_speed)) {
        this->InputJumpVelocity(_jump_speed);
    } // if
    if (auto move_com = _move_com.lock()) {
        float move_speed = 1.7f;
        
        auto velocity_com = super::GetVelocityComponent();
        auto accele = Mof::CVector3(0.0f, 0.0f, -move_speed);
        accele.RotationY(_move_angle);
        velocity_com->AddVelocityForce(accele);
    } // if
    _jump_speed -= _jump_decrase;

    if (super::IsEndMotion()) {
        super::ChangeActionState(state::PlayerActionStateType::kPlayerActionJumpDownState);
    } // if
    return true;
}

bool ratchet::PlayerCartwheelJumpComponent::Release(void) {
    super::Release();
    _move_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerCartwheelJumpComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerCartwheelJumpComponent>(*this);
}

bool ratchet::PlayerCartwheelJumpComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    super::ChangeMotionState(state::PlayerMotionStateType::kPlayerMotionCartwheelJumpState);

    auto velocity_com = super::GetVelocityComponent();
    velocity_com->SetGravity(1.8f);
    _jump_speed = 10.0f;
    return true;
}