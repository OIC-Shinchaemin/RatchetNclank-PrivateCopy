#include "PlayerWeaponComponent.h"

#include "../Collision/Object/OmniWrenchCollisionComponent.h"
#include "../../Actor/Character/Player.h"


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
    } // if
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        weapon_coll_com->Activate();
    } // if
    return true;
}

bool my::PlayerWeaponComponent::Inactivate(void) {
    if (auto weapon_coll_com = _weapon_coll_com.lock()) {
        weapon_coll_com->Inactivate();
    } // if
    return true;
}

bool my::PlayerWeaponComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    return true;
}

bool my::PlayerWeaponComponent::Update(float delta_time) {
    if (auto weapon = _weapon.lock()) {
        _weapon_coll_com = weapon->GetComponent<my::OmniWrenchCollisionComponent>();
    } // if
    return false;
}

bool my::PlayerWeaponComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::PlayerWeaponComponent::Clone(void) {
    return std::make_shared<my::PlayerWeaponComponent>(*this);
}