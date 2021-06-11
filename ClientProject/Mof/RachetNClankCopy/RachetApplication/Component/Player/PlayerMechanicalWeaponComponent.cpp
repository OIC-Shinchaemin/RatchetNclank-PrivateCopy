#include "PlayerMechanicalWeaponComponent.h"

#include "../../Actor/Character/Player.h"


rachet::PlayerMechanicalWeaponComponent::PlayerMechanicalWeaponComponent(int priority) :
    super(priority),
    _weapon() {
}

rachet::PlayerMechanicalWeaponComponent::PlayerMechanicalWeaponComponent(const PlayerMechanicalWeaponComponent& obj) :
    super(obj),
    _weapon() {
}

rachet::PlayerMechanicalWeaponComponent::~PlayerMechanicalWeaponComponent() {
}

void rachet::PlayerMechanicalWeaponComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string rachet::PlayerMechanicalWeaponComponent::GetType(void) const {
    return "PlayerMechanicalWeaponComponent";
}

bool rachet::PlayerMechanicalWeaponComponent::Activate(void) {
    super::Activate();
    /*
    auto owner = std::dynamic_pointer_cast<rachet::Player>(super::GetOwner());
    _weapon = owner->GetChild("OmniWrench");
    if (auto weapon = _weapon.lock()) {
        // cache
        owner->OnNotify(std::dynamic_pointer_cast<rachet::Weapon>(weapon));
        _weapon_coll_com = weapon->GetComponent<rachet::OmniWrenchCollisionComponent>();
        _weapon_action_state_com = weapon->GetComponent<rachet::OmniWrenchActionStateComponent>();

        auto throw_com = weapon->GetComponent<rachet::OmniWrenchThrowedComponent>();
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

bool rachet::PlayerMechanicalWeaponComponent::Inactivate(void) {
    return true;
}

bool rachet::PlayerMechanicalWeaponComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool rachet::PlayerMechanicalWeaponComponent::Update(float delta_time) {
    return true;
}

bool rachet::PlayerMechanicalWeaponComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::PlayerMechanicalWeaponComponent::Clone(void) {
    return std::make_shared<rachet::PlayerMechanicalWeaponComponent>(*this);
}