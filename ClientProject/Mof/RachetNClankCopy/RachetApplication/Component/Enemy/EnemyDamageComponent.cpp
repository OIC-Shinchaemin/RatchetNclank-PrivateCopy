#include "EnemyDamageComponent.h"

#include "../HpComponent.h"
#include "../InvincibleComponent.h"


my::EnemyDamageComponent::EnemyDamageComponent(int priority) :
    super(priority),
    _hp_com(),
    _invincible_com() {
}

my::EnemyDamageComponent::EnemyDamageComponent(const EnemyDamageComponent& obj) :
    super(obj._priority),
    _hp_com(),
    _invincible_com() {
}

my::EnemyDamageComponent::~EnemyDamageComponent() {
}

std::string my::EnemyDamageComponent::GetType(void) const {
    return "EnemyDamageComponent";
}

bool my::EnemyDamageComponent::Initialize(void) {
    super::Initialize();
    _hp_com = super::GetOwner()->GetComponent<my::HpComponent>();
    _invincible_com = super::GetOwner()->GetComponent<my::InvincibleComponent>();
    return true;
}

bool my::EnemyDamageComponent::Update(float delta_time) {
    super::End();
    return true;
}

bool my::EnemyDamageComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyDamageComponent::Clone(void) {
    return std::make_shared<my::EnemyDamageComponent>(*this);
}

bool my::EnemyDamageComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    if (auto invincible_com = _invincible_com.lock()) {
        if (invincible_com->IsActive()) {
            return false;
        } // if
    } // if


    super::Start();       
    if (auto hp_com = _hp_com.lock()) {
        hp_com->Damage(1);
    } // if
    if (auto invincible_com = _invincible_com.lock()) {
        invincible_com->Start();
    } // if



    return true;
}