#include "EnemyMeleeAttackComponent.h"

#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


my::EnemyMeleeAttackComponent::EnemyMeleeAttackComponent(int priority) :
    super(priority),
    _range(1.7f),
    _volume(0.5f),
    _motion_com(),
    _motion_state_com() {
}

my::EnemyMeleeAttackComponent::EnemyMeleeAttackComponent(const EnemyMeleeAttackComponent& obj) :
    super(obj),
    _range(obj._range),
    _volume(obj._volume),
    _motion_com(),
    _motion_state_com() {
}

my::EnemyMeleeAttackComponent ::~EnemyMeleeAttackComponent() {
}

std::string my::EnemyMeleeAttackComponent::GetType(void) const {
    return "EnemyMeleeAttackComponent";
}

float my::EnemyMeleeAttackComponent::GetRange(void) const {
    return this->_range;
}

float my::EnemyMeleeAttackComponent::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere my::EnemyMeleeAttackComponent::GetCanAttackRangeSphere(void) const {
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _range);
}

bool my::EnemyMeleeAttackComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();

    return true;
}

bool my::EnemyMeleeAttackComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            super::End();
        } // if
    } // if
    return true;
}

bool my::EnemyMeleeAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyMeleeAttackComponent::Clone(void) {
    return std::make_shared<my::EnemyMeleeAttackComponent >(*this);
}

bool my::EnemyMeleeAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionAttackState");
    } // if
    return true;
}