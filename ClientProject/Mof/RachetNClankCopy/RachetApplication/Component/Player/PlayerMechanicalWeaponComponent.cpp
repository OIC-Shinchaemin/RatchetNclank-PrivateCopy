#include "PlayerMechanicalWeaponComponent.h"

#include "../../Actor/Character/Player.h"


my::PlayerMechanicalWeaponComponent::PlayerMechanicalWeaponComponent(int priority) :
    super(priority),
    _weapon() {
}

my::PlayerMechanicalWeaponComponent::PlayerMechanicalWeaponComponent(const PlayerMechanicalWeaponComponent& obj) :
    super(obj),
    _weapon() {
}

my::PlayerMechanicalWeaponComponent::~PlayerMechanicalWeaponComponent() {
}

void my::PlayerMechanicalWeaponComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::PlayerMechanicalWeaponComponent::GetType(void) const {
    return "PlayerMechanicalWeaponComponent";
}

bool my::PlayerMechanicalWeaponComponent::Activate(void) {
    super::Activate();
    /*
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
    */
    return true;
}

bool my::PlayerMechanicalWeaponComponent::Inactivate(void) {
    return true;
}

bool my::PlayerMechanicalWeaponComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool my::PlayerMechanicalWeaponComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerMechanicalWeaponComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerMechanicalWeaponComponent::Clone(void) {
    return std::make_shared<my::PlayerMechanicalWeaponComponent>(*this);
}