#include "OmniWrenchThrowedComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"
#include "../../Collision/Object/OmniWrenchCollisionComponent.h"


ratchet::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(int priority) :
    super(priority),
    _move_speed(25.0f),
    _moved_distance(0.0f),
    _moved_distance_threshold(800.0f),
    _ideal_move_direction(),
    _weapon_owner(),
    _velocity_com(),
    _action_state_com(),
    _collision_com() {
}

ratchet::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj) :
    super(obj),
    _move_speed(obj._move_speed),
    _moved_distance(0.0f),
    _moved_distance_threshold(obj._moved_distance_threshold),
    _ideal_move_direction(),
    _weapon_owner(),
    _velocity_com(),
    _action_state_com(),
    _collision_com() {
}

ratchet::OmniWrenchThrowedComponent::~OmniWrenchThrowedComponent() {
}

void ratchet::OmniWrenchThrowedComponent::SetWeaponOwner(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_weapon_owner = ptr;
}

std::string ratchet::OmniWrenchThrowedComponent::GetType(void) const {
    return "OmniWrenchThrowedComponent";
}

std::string_view ratchet::OmniWrenchThrowedComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState;
}

bool ratchet::OmniWrenchThrowedComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<ratchet::OmniWrenchActionStateComponent>();
    _collision_com = super::GetOwner()->GetComponent<ratchet::OmniWrenchCollisionComponent>();
    return true;
}

bool ratchet::OmniWrenchThrowedComponent::Update(float delta_time) {
    if (_moved_distance_threshold < _moved_distance) {
        if (auto state_com = _action_state_com.lock()) {
            auto state = state::OmniWrenchActionStateType::kOmniWrenchActionDefaultState;
            if (state_com->CanTransition(state)) {
                state_com->ChangeState(state);
            } // if
        } // if
    } // if
    
    if (auto velocity_com = _velocity_com.lock()) {
        Mof::CVector3 v = math::vec3::kNegUnitZ * _move_speed;
        v.RotateAround(math::vec3::kZero, _ideal_move_direction);
        velocity_com->AddVelocityForce(v);
        _moved_distance += v.Length();
    } // if
    return true;
}

bool ratchet::OmniWrenchThrowedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::OmniWrenchThrowedComponent::Clone(void) {
    return std::make_shared<ratchet::OmniWrenchThrowedComponent>(*this);
}

bool ratchet::OmniWrenchThrowedComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Activate();
    if (auto velocity_com = _velocity_com.lock()) {
        velocity_com->SetUseGravity(false);
    } // if
    if (auto collision_com = _collision_com.lock()) {
        collision_com->Activate();
    } // if
    _moved_distance = 0.0f;
    if (auto owner = _weapon_owner.lock()) {
        _ideal_move_direction = owner->GetRotate();
    } // if
    return true;
}

bool ratchet::OmniWrenchThrowedComponent::End(void) {
    super::End();
    if (auto collision_com = _collision_com.lock()) {
        collision_com->Inactivate();
    } // if
    return true;
}