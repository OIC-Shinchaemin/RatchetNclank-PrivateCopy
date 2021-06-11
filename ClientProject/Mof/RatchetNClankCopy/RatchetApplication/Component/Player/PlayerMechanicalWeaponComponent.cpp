#include "PlayerMechanicalWeaponComponent.h"

#include "../../Actor/Character/Player.h"


ratchet::PlayerMechanicalWeaponComponent::PlayerMechanicalWeaponComponent(int priority) :
    super(priority),
    _weapon() {
}

ratchet::PlayerMechanicalWeaponComponent::PlayerMechanicalWeaponComponent(const PlayerMechanicalWeaponComponent& obj) :
    super(obj),
    _weapon() {
}

ratchet::PlayerMechanicalWeaponComponent::~PlayerMechanicalWeaponComponent() {
}

void ratchet::PlayerMechanicalWeaponComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string ratchet::PlayerMechanicalWeaponComponent::GetType(void) const {
    return "PlayerMechanicalWeaponComponent";
}

bool ratchet::PlayerMechanicalWeaponComponent::Activate(void) {
    super::Activate();
    /*
    auto owner = std::dynamic_pointer_cast<ratchet::Player>(super::GetOwner());
    _weapon = owner->GetChild("OmniWrench");
    if (auto weapon = _weapon.lock()) {
        // cache
        owner->OnNotify(std::dynamic_pointer_cast<ratchet::actor::weapon::Weapon>(weapon));
        _weapon_coll_com = weapon->GetComponent<ratchet::actor::weapon::OmniWrenchCollisionComponent>();
        _weapon_action_state_com = weapon->GetComponent<ratchet::actor::weapon::OmniWrenchActionStateComponent>();

        auto throw_com = weapon->GetComponent<ratchet::actor::weapon::OmniWrenchThrowedComponent>();
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
    */
    return true;
}

bool ratchet::PlayerMechanicalWeaponComponent::Inactivate(void) {
    return true;
}

bool ratchet::PlayerMechanicalWeaponComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool ratchet::PlayerMechanicalWeaponComponent::Update(float delta_time) {
    return true;
}

bool ratchet::PlayerMechanicalWeaponComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::PlayerMechanicalWeaponComponent::Clone(void) {
    return std::make_shared<ratchet::PlayerMechanicalWeaponComponent>(*this);
}