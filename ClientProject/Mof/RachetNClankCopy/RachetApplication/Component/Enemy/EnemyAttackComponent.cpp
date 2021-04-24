#include "EnemyAttackComponent.h"

#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


my::EnemyAttackComponent::EnemyAttackComponent(int priority) :
    super(priority),
    _range(2.0f),
    _volume(0.5f),
    _motion_com(),
    _motion_state_com() {
}

my::EnemyAttackComponent::EnemyAttackComponent(const EnemyAttackComponent& obj) :
    super(obj),
    _range(obj._range),
    _volume(obj._volume),
    _motion_com(),
    _motion_state_com() {
}

my::EnemyAttackComponent ::~EnemyAttackComponent() {
}

std::string my::EnemyAttackComponent::GetType(void) const {
    return "EnemyAttackComponent";
}

float my::EnemyAttackComponent::GetRange(void) const {
    return this->_range;
}

float my::EnemyAttackComponent::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere my::EnemyAttackComponent::GetCanAttackRangeSphere(void) const {
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _range);
}

bool my::EnemyAttackComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();

    return true;
}

bool my::EnemyAttackComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            super::End();
        } // if
    } // if
    return true;
}

bool my::EnemyAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyAttackComponent::Clone(void) {
    return std::make_shared<my::EnemyAttackComponent >(*this);
}

bool my::EnemyAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionAttackState");
    } // if
    return true;
}