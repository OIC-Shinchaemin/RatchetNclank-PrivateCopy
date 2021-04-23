#include "MotionStateComponent.h"

#include "../State/PlayerMotion/PlayerMotionIdleState.h"
#include "../State/PlayerMotion/PlayerMotionMoveState.h"
#include "../State/PlayerMotion/PlayerMotionDamageState.h"
#include "../State/EnemyMotion/EnemyMotionIdleState.h"
#include "../State/EnemyMotion/EnemyMotionMoveState.h"
#include "../State/EnemyMotion/EnemyMotionAttackState.h"


my::MotionStateComponent::MotionStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::MotionStateComponent::MotionStateComponent(const MotionStateComponent& obj) :
    super(obj._priority),
    _state_machine(obj._state_machine) {
}

my::MotionStateComponent::~MotionStateComponent() {
}

void my::MotionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::MotionStateComponent::GetType(void) const {
    return "MotionStateComponent";
}

bool my::MotionStateComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // ŠO•”‚æ‚èì¬‚³‚ê‚½‚à‚Ì‚ðŽæ“¾
    if (super::GetOwner()->GetTag() == "Enemy") {
        this->RegisterMotionState<state::EnemyMotionIdleState>(_state_machine);
        this->RegisterMotionState<state::EnemyMotionMoveState>(_state_machine);
        this->RegisterMotionState<state::EnemyMotionAttackState>(_state_machine);
        _state_machine.ChangeState("EnemyMotionIdleState");
    } // if
    else {
        this->RegisterMotionState<state::PlayerMotionIdleState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMoveState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionDamageState>(_state_machine);
        _state_machine.ChangeState("PlayerMotionIdleState");
    } // else 
    return true;
}

bool my::MotionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::MotionStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::MotionStateComponent::Clone(void) {
    return std::make_shared<my::MotionStateComponent>(*this);
}

void my::MotionStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}