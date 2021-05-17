#include "PlayerWeaponComponent.h"

#include "../../Actor/Character/Player.h"
#include "../Collision/Object/OmniWrenchCollisionComponent.h"
#include "../Weapon/OmniWrenchActionStateComponent.h"
#include "../Weapon/OmniWrenchThrowedComponent.h"
#include "../../State/OmniWrenchActionStateDefine.h"


my::PlayerWeaponComponent::PlayerWeaponComponent(int priority) :
    super(priority),
    _weapon(),
    _weapon_coll_com() {
}

my::PlayerWeaponComponent::PlayerWeaponComponent(const PlayerWeaponComponent& obj) :
    super(obj) {
}

my::PlayerWeaponComponent::~PlayerWeaponComponent() {
}

void my::PlayerWeaponComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::PlayerWeaponComponent::GetType(void) const {
    return "PlayerWeaponComponent";
}

bool my::PlayerWeaponComponent::Activate(void) {
    super::Activate();
    
    auto owner =  std::dynamic_pointer_cast<my::Player>(super::GetOwner());
    _weapon = owner->GetChild("OmniWrench");
    if (auto weapon = _weapon.lock()) {
        _weapon_coll_com = weapon->GetComponent<my::OmniWrenchCollisionComponent>();        
        _weapon_action_state_com = weapon->GetComponent<my::OmniWrenchActionStateComponent>();
    
        auto throw_com = weapon->GetComponent<my::OmniWrenchThrowedComponent>();
        throw_com->SetWeaponOwner(super::GetOwner());
    } // if
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        weapon_coll_com->Activate();
    } // if
    if (auto weapon_action_state_com = _weapon_action_state_com.lock()) {
        weapon_action_state_com->ChangeState(state::OmniWrenchActionStateType::kOmniWrenchActionThrowedState);
    } // if
    return true;
}

bool my::PlayerWeaponComponent::Inactivate(void) {
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        //weapon_coll_com->Inactivate();
    } // if
    return true;
}

bool my::PlayerWeaponComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool my::PlayerWeaponComponent::Update(float delta_time) {
    return true;
}

bool my::PlayerWeaponComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerWeaponComponent::Clone(void) {
    return std::make_shared<my::PlayerWeaponComponent>(*this);
}