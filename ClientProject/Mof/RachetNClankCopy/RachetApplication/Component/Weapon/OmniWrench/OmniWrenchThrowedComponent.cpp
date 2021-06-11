#include "OmniWrenchThrowedComponent.h"

#include "../../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"
#include "../../Collision/Object/OmniWrenchCollisionComponent.h"


rachet::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(int priority) :
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

rachet::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj) :
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

rachet::OmniWrenchThrowedComponent::~OmniWrenchThrowedComponent() {
}

void rachet::OmniWrenchThrowedComponent::SetWeaponOwner(const std::shared_ptr<rachet::Actor>& ptr) {
    this->_weapon_owner = ptr;
}

std::string rachet::OmniWrenchThrowedComponent::GetType(void) const {
    return "OmniWrenchThrowedComponent";
}

std::string_view rachet::OmniWrenchThrowedComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState;
}

bool rachet::OmniWrenchThrowedComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<rachet::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<rachet::OmniWrenchActionStateComponent>();
    _collision_com = super::GetOwner()->GetComponent<rachet::OmniWrenchCollisionComponent>();
    return true;
}

bool rachet::OmniWrenchThrowedComponent::Update(float delta_time) {
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

bool rachet::OmniWrenchThrowedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::OmniWrenchThrowedComponent::Clone(void) {
    return std::make_shared<rachet::OmniWrenchThrowedComponent>(*this);
}

bool rachet::OmniWrenchThrowedComponent::Start(void) {
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

bool rachet::OmniWrenchThrowedComponent::End(void) {
    super::End();
    if (auto collision_com = _collision_com.lock()) {
        collision_com->Inactivate();
    } // if
    return true;
}