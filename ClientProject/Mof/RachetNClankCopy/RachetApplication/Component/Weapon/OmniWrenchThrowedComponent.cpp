#include "OmniWrenchThrowedComponent.h"

#include "../VelocityComponent.h"
#include "OmniWrenchActionStateComponent.h"
#include "../../State/OmniWrenchActionStateDefine.h"
#include "../Collision/Object/OmniWrenchCollisionComponent.h"


void my::OmniWrenchThrowedComponent::ChageState(const std::string& name) {
    if (auto state_com = _action_state_com.lock()) {
        state_com->ChangeState(name);
    } // if
}

my::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(int priority) :
    super(priority),
    _move_speed(10.0f),
    _moved_distance(0.0f),
    _moved_distance_threshold(800.0f),
    _ideal_move_direction(),
    _weapon_owner(),
    _velocity_com(),
    _action_state_com(),
    _collision_com() {
}

my::OmniWrenchThrowedComponent::OmniWrenchThrowedComponent(const OmniWrenchThrowedComponent& obj) :
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

my::OmniWrenchThrowedComponent::~OmniWrenchThrowedComponent() {
}

void my::OmniWrenchThrowedComponent::SetWeaponOwner(const std::shared_ptr<my::Actor>& ptr) {
    this->_weapon_owner = ptr;
}

std::string my::OmniWrenchThrowedComponent::GetType(void) const {
    return "OmniWrenchThrowedComponent";
}

std::string_view my::OmniWrenchThrowedComponent::GetStateType(void) const {
    return state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState;
}

bool my::OmniWrenchThrowedComponent::Initialize(void) {
    super::Initialize();
    _velocity_com = super::GetOwner()->GetComponent<my::VelocityComponent>();
    _action_state_com = super::GetOwner()->GetComponent<my::OmniWrenchActionStateComponent>();
    _collision_com = super::GetOwner()->GetComponent<my::OmniWrenchCollisionComponent>();
    return true;
}

bool my::OmniWrenchThrowedComponent::Update(float delta_time) {
    /*
    if (_moved_distance_threshold < _moved_distance) {
        if (auto weapon_owner = _weapon_owner.lock()) {
            auto parent = super::GetOwner()->GetParentTransform().value();
            Mof::CVector3 parent_pos;
            parent.GetTranslation(parent_pos);

            auto target_pos = weapon_owner->GetPosition();
            auto pos = super::GetOwner()->GetPosition() + parent_pos;
            _ideal_move_direction = pos - target_pos;
            _ideal_move_direction.x = 0.0f;
            _ideal_move_direction.z = 0.0f;
        } // if
    } // if
    */

    if (auto velocity_com = _velocity_com.lock()) {
        Mof::CVector3 v = math::vec3::kNegUnitZ * _move_speed;
        v.RotateAround(math::vec3::kZero, _ideal_move_direction);
        //_local_translate += v;
        //velocity_com->AddVelocityForce(v);
        //_moved_distance += v.Length();
    } // if
    return true;
}

bool my::OmniWrenchThrowedComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::OmniWrenchThrowedComponent::Clone(void) {
    return std::make_shared<my::OmniWrenchThrowedComponent>(*this);
}

bool my::OmniWrenchThrowedComponent::Start(void) {
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

    _local_translate = Mof::CVector3();

    auto owner = super::GetOwner();
    Mof::CVector3 scale, rotate, translate;
    auto mat = super::GetOwner()->GetParentTransform().value();
    mat.GetScaling(scale);
    mat.GetRotation(rotate);
    mat.GetTranslation(translate);
    owner ->SetScale(scale);
    owner ->SetPosition(translate);
    owner ->SetRotate(rotate);
    
    return true;
}

bool my::OmniWrenchThrowedComponent::End(void) {
    super::End();
    if (auto collision_com = _collision_com.lock()) {
        collision_com->Inactivate();
    } // if
    return true;
}