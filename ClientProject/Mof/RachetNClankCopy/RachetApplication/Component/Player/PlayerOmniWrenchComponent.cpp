#include "PlayerOmniWrenchComponent.h"

#include "../../Actor/Character/Player.h"
#include "PlayerThrowAttackComponent.h"
#include "../Collision/Object/OmniWrenchCollisionComponent.h"
#include "../Weapon/OmniWrench/OmniWrenchActionStateComponent.h"
#include "../Weapon/OmniWrench/OmniWrenchThrowedComponent.h"
#include "../../State/OmniWrenchActionStateDefine.h"


my::PlayerOmniWrenchComponent::PlayerOmniWrenchComponent(int priority) :
    super(priority),
    _weapon(),
    _throw_attack_com(),
    _weapon_action_state_com(),
    _weapon_coll_com() {
}

my::PlayerOmniWrenchComponent::PlayerOmniWrenchComponent(const PlayerOmniWrenchComponent& obj) :
    super(obj),
    _weapon(),
    _throw_attack_com(),
    _weapon_action_state_com(),
    _weapon_coll_com() {
}

my::PlayerOmniWrenchComponent::~PlayerOmniWrenchComponent() {
}

void my::PlayerOmniWrenchComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::PlayerOmniWrenchComponent::GetType(void) const {
    return "PlayerOmniWrenchComponent";
}

bool my::PlayerOmniWrenchComponent::Activate(void) {
    super::Activate();
    
    auto owner = std::dynamic_pointer_cast<my::Player>(super::GetOwner());
    _weapon = owner->GetChild("OmniWrench");
    if (auto weapon = _weapon.lock()) {
        // cache
        owner->OnNotify(std::dynamic_pointer_cast<my::Weapon>(weapon));
        _weapon_coll_com = weapon->GetComponent<my::OmniWrenchCollisionComponent>();
        _weapon_action_state_com = weapon->GetComponent<my::OmniWrenchActionStateComponent>();
        
        auto throw_com = weapon->GetComponent<my::OmniWrenchThrowedComponent>();
        throw_com->SetWeaponOwner(super::GetOwner());
    } // if
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        weapon_coll_com->Activate();
    } // if
    // throw
    if (auto throw_attack_com = _throw_attack_com.lock()) {
        if (throw_attack_com->IsActive()) {
            if (auto weapon_action_state_com = _weapon_action_state_com.lock()) {
                weapon_action_state_com->ChangeState(state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState);
            } // if
        } // if
    } // if
    return true;
}

bool my::PlayerOmniWrenchComponent::Inactivate(void) {
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        weapon_coll_com->Inactivate();
    } // if
    return true;
}

bool my::PlayerOmniWrenchComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _throw_attack_com = super::GetOwner()->GetComponent<my::PlayerThrowAttackComponent>();
    return true;
}

bool my::PlayerOmniWrenchComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerOmniWrenchComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerOmniWrenchComponent::Clone(void) {
    return std::make_shared<my::PlayerOmniWrenchComponent>(*this);
}