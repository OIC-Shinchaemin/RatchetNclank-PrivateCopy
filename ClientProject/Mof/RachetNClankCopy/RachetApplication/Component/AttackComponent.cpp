#include "AttackComponent.h"

#include "MotionComponent.h"
#include "MotionStateComponent.h"


my::AttackComponent::AttackComponent(int priority) :
    super(priority),
    _range(2.0f),
    _volume(0.5f),
    _motion_com(), 
    _motion_state_com() {
}

my::AttackComponent::AttackComponent(const AttackComponent& obj) :
    super(obj._priority),
    _range(obj._range),
    _volume(obj._volume),
    _motion_com(),
    _motion_state_com() {
}

my::AttackComponent::~AttackComponent() {
}

std::string my::AttackComponent::GetType(void) const {
    return "AttackComponent";
}

float my::AttackComponent::GetRange(void) const {
    return this->_range;
}

float my::AttackComponent::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere my::AttackComponent::GetSphere(void) const {
    if (!this->IsActive()) {
        return Mof::CSphere();
    } // if
    auto pos = super::GetOwner()->GetPosition();
    auto rotate = super::GetOwner()->GetRotate();

    float offset = 1.0f;
    auto front = Mof::CVector3(-math::vec3::kUnitZ * offset);
    front.RotationY(rotate.y);

    pos += front;
    pos.y += 1.0f;

    return Mof::CSphere(pos, _volume);
}

Mof::CSphere my::AttackComponent::GetCanAttackRangeSphere(void) const {
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _range);
}

bool my::AttackComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<my::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<my::MotionStateComponent>();

    return true;
}

bool my::AttackComponent::Update(float delta_time) {
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            super::End();
        } // if
    } // if
    return true;
}

bool my::AttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::AttackComponent::Clone(void) {
    return std::make_shared<my::AttackComponent>(*this);
}

bool my::AttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    if (auto motion_state_com = _motion_state_com.lock()) {
        motion_state_com->ChangeState("EnemyMotionAttackState");
    } // if
    return true;
}