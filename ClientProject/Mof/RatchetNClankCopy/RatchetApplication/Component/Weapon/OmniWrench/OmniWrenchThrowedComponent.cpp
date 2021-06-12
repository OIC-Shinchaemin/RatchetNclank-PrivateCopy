#include "OmniWrenchThrowedComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"
#include "../../Collision/Object/OmniWrenchCollisionComponent.h"


ratchet::component::weapon::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(int priority) :
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

ratchet::component::weapon::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj) :
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

ratchet::component::weapon::OmniWrenchThrowedComponent::~OmniWrenchThrowedComponent() {
}

void ratchet::component::weapon::OmniWrenchThrowedComponent::SetWeaponOwner(const std::shared_ptr<ratchet::actor::Actor>& ptr) {
    this->_weapon_owner = ptr;
}

std::string ratchet::component::weapon::OmniWrenchThrowedComponent::GetType(void) const {
    return "OmniWrenchThrowedComponent";
}

std::string_view ratchet::component::weapon::OmniWrenchThrowedComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState;
}

bool ratchet::component::weapon::OmniWrenchThrowedComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<ratchet::component::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<ratchet::component::weapon::OmniWrenchActionStateComponent>();
    _collision_com = super::GetOwner()->GetComponent<ratchet::component::collision::OmniWrenchCollisionComponent>();
    return true;
}

bool ratchet::component::weapon::OmniWrenchThrowedComponent::Update(float delta_time) {
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

bool ratchet::component::weapon::OmniWrenchThrowedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::weapon::OmniWrenchThrowedComponent::Clone(void) {
    return std::make_shared<ratchet::component::weapon::OmniWrenchThrowedComponent>(*this);
}

bool ratchet::component::weapon::OmniWrenchThrowedComponent::Start(void) {
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

bool ratchet::component::weapon::OmniWrenchThrowedComponent::End(void) {
    super::End();
    if (auto collision_com = _collision_com.lock()) {
        collision_com->Inactivate();
    } // if
    return true;
}