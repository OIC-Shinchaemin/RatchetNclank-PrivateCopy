#include "PlayerWeaponComponent.h"

#include "../Collision/Object/OmniWrenchCollisionComponent.h"


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