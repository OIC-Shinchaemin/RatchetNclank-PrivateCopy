#include "EnemyMeleeAttackComponent.h"

#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/EnemyActionStateDefine.h"
#include "../../State/EnemyMotionStateDefine.h"
#include "../Collision/Object/EnemyMeleeAttackCollisionComponent.h"


ratchet::EnemyMeleeAttackComponent::EnemyMeleeAttackComponent(int priority) :
    super(priority),
    _range(1.7f),
    _volume(0.5f),
    _wait(),
    _motion_com(),
    _motion_state_com(),
    _collision_com() {
}

ratchet::EnemyMeleeAttackComponent::EnemyMeleeAttackComponent(const EnemyMeleeAttackComponent& obj) :
    super(obj),
    _range(obj._range),
    _volume(obj._volume),
    _wait(),
    _motion_com(),
    _motion_state_com(),
    _collision_com() {
}

ratchet::EnemyMeleeAttackComponent ::~EnemyMeleeAttackComponent() {
}

std::string ratchet::EnemyMeleeAttackComponent::GetType(void) const {
    return "EnemyMeleeAttackComponent";
}

std::string_view ratchet::EnemyMeleeAttackComponent::GetStateType(void) const {
    return state::EnemyActionStateType::kEnemyActionMeleeAttackState;
}

float ratchet::EnemyMeleeAttackComponent::GetRange(void) const {
    return this->_range;
}

float ratchet::EnemyMeleeAttackComponent::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere ratchet::EnemyMeleeAttackComponent::GetCanAttackRangeSphere(void) const {
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _range);
}

bool ratchet::EnemyMeleeAttackComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<ratchet::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::MotionStateComponent>();
    _collision_com = super::GetOwner()->GetComponent<ratchet::EnemyMeleeAttackCollisionComponent>();
    return true;
}

bool ratchet::EnemyMeleeAttackComponent::Update(float delta_time) {
    if (_wait.Tick(delta_time)) {
        if (auto motion_state_com = _motion_state_com.lock()) {
            motion_state_com->ChangeState(state::EnemyMotionStateType::kEnemyMotionMeleeAttackState);
            _collision_com.lock()->Activate();
        } // if
    } // if
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            super::End();
        } // if
    } // if
    return true;
}

bool ratchet::EnemyMeleeAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::EnemyMeleeAttackComponent::Clone(void) {
    return std::make_shared<ratchet::EnemyMeleeAttackComponent >(*this);
}

bool ratchet::EnemyMeleeAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    _wait.Initialize(0.3f, false);
    return true;
}

bool ratchet::EnemyMeleeAttackComponent::End(void) {
    super::End();
    _collision_com.lock()->Inactivate();
    return true;
}