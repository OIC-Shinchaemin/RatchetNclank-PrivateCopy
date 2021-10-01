#include "EnemyMeleeAttackComponent.h"

#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/EnemyActionStateDefine.h"
#include "../../State/EnemyMotionStateDefine.h"
#include "../Collision/Object/EnemyMeleeAttackCollisionComponent.h"


ratchet::component::enemy::EnemyMeleeAttackComponent::EnemyMeleeAttackComponent(int priority) :
    super(priority),
    _range(1.7f),
    _volume(0.5f),
    _wait(),
    _motion_com(),
    _motion_state_com(),
    _collision_com() {
}

ratchet::component::enemy::EnemyMeleeAttackComponent::EnemyMeleeAttackComponent(const EnemyMeleeAttackComponent& obj) :
    super(obj),
    _range(obj._range),
    _volume(obj._volume),
    _wait(),
    _motion_com(),
    _motion_state_com(),
    _collision_com() {
}

ratchet::component::enemy::EnemyMeleeAttackComponent ::~EnemyMeleeAttackComponent() {
}

std::string ratchet::component::enemy::EnemyMeleeAttackComponent::GetType(void) const {
    return "EnemyMeleeAttackComponent";
}

std::string_view ratchet::component::enemy::EnemyMeleeAttackComponent::GetStateType(void) const {
    return state::EnemyActionStateType::kEnemyActionMeleeAttackState;
}

float ratchet::component::enemy::EnemyMeleeAttackComponent::GetRange(void) const {
    return this->_range;
}

float ratchet::component::enemy::EnemyMeleeAttackComponent::GetVolume(void) const {
    return this->_volume;
}

Mof::CSphere ratchet::component::enemy::EnemyMeleeAttackComponent::GetCanAttackRangeSphere(void) const {
    auto pos = super::GetOwner()->GetPosition();
    return Mof::CSphere(pos, _range);
}

bool ratchet::component::enemy::EnemyMeleeAttackComponent::Initialize(void) {
    super::Initialize();

    _motion_com = super::GetOwner()->GetComponent<ratchet::component::MotionComponent>();
    _motion_state_com = super::GetOwner()->GetComponent<ratchet::component::MotionStateComponent>();
    _collision_com = super::GetOwner()->GetComponent<ratchet::component::collision::EnemyMeleeAttackCollisionComponent>();
    return true;
}

bool ratchet::component::enemy::EnemyMeleeAttackComponent::Update(float delta_time) {
    if (_wait.Tick(delta_time)) {
        if (auto motion_state_com = _motion_state_com.lock()) {
            motion_state_com->ChangeState(state::EnemyMotionStateType::kEnemyMotionMeleeAttackState);
            _collision_com.lock()->Activate();
        } // if
    } // if
    if (auto motion_com = _motion_com.lock()) {
        if (motion_com->IsEndMotion()) {
            _collision_com.lock()->Inactivate();
            super::End();
        } // if
    } // if
    return true;
}

bool ratchet::component::enemy::EnemyMeleeAttackComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::enemy::EnemyMeleeAttackComponent::Clone(void) {
    return std::make_shared<ratchet::component::enemy::EnemyMeleeAttackComponent >(*this);
}

bool ratchet::component::enemy::EnemyMeleeAttackComponent::Start(void) {
    if (this->IsActive()) {
        return false;
    } // if
    super::Start();
    _wait.Initialize(0.3f, false);
    return true;
}

bool ratchet::component::enemy::EnemyMeleeAttackComponent::End(void) {
    super::End();
    _collision_com.lock()->Inactivate();
    return true;
}