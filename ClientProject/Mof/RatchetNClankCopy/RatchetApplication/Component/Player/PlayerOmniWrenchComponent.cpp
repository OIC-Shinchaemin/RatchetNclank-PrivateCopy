#include "PlayerOmniWrenchComponent.h"

#include "../../Actor/Character/Player.h"
#include "PlayerThrowAttackComponent.h"
#include "../Collision/Object/OmniWrenchCollisionComponent.h"
#include "../Weapon/OmniWrench/OmniWrenchActionStateComponent.h"
#include "../Weapon/OmniWrench/OmniWrenchThrowedComponent.h"
#include "../../State/OmniWrenchActionStateDefine.h"


ratchet::PlayerOmniWrenchComponent::PlayerOmniWrenchComponent(int priority) :
    super(priority),
    _weapon(),
    _throw_attack_com(),
    _weapon_action_state_com(),
    _weapon_coll_com() {
}

ratchet::PlayerOmniWrenchComponent::PlayerOmniWrenchComponent(const PlayerOmniWrenchComponent& obj) :
    super(obj),
    _weapon(),
    _throw_attack_com(),
    _weapon_action_state_com(),
    _weapon_coll_com() {
}

ratchet::PlayerOmniWrenchComponent::~PlayerOmniWrenchComponent() {
}

void ratchet::PlayerOmniWrenchComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string ratchet::PlayerOmniWrenchComponent::GetType(void) const {
    return "PlayerOmniWrenchComponent";
}

bool ratchet::PlayerOmniWrenchComponent::Activate(void) {
    super::Activate();

    auto owner = std::dynamic_pointer_cast<ratchet::actor::character::Player>(super::GetOwner());
    _weapon = owner->GetChild("OmniWrench");
    if (auto weapon = _weapon.lock()) {
        // cache
        owner->OnNotify(std::dynamic_pointer_cast<ratchet::actor::weapon::Weapon>(weapon));
        _weapon_coll_com = weapon->GetComponent<ratchet::OmniWrenchCollisionComponent>();
        _weapon_action_state_com = weapon->GetComponent<ratchet::OmniWrenchActionStateComponent>();

        auto throw_com = weapon->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::OmniWrenchThrowedComponent>();
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

bool ratchet::PlayerOmniWrenchComponent::Inactivate(void) {
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        weapon_coll_com->Inactivate();
    } // if
    return true;
}

bool ratchet::PlayerOmniWrenchComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    _throw_attack_com = super::GetOwner()->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::PlayerThrowAttackComponent>();
    return true;
}

bool ratchet::PlayerOmniWrenchComponent::Release(void) {
    super::Release();
    _weapon.reset();
    _throw_attack_com.reset();
    _weapon_action_state_com.reset();
    _weapon_coll_com.reset();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerOmniWrenchComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerOmniWrenchComponent>(*this);
}