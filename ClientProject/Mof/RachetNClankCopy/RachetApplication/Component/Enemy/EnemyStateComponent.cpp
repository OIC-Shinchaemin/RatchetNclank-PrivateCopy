#include "EnemyStateComponent.h"

#include "../../State/EnemyAction/EnemyActionIdleState.h"
#include "../../State/EnemyAction/EnemyActionMoveState.h"
#include "../../State/EnemyAction/EnemyActionGoHomeState.h"
#include "../../State/EnemyAction/EnemyActionMeleeAttackState.h"
#include "../../State/EnemyAction/EnemyActionRangedAttackState.h"


my::EnemyStateComponent::EnemyStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::EnemyStateComponent::EnemyStateComponent(const EnemyStateComponent& obj) :
    super(obj._priority),
    _state_machine(obj._state_machine) {
}

my::EnemyStateComponent::~EnemyStateComponent() {
}

void my::EnemyStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::EnemyStateComponent::GetType(void) const {
    return "EnemyStateComponent";
}

bool my::EnemyStateComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // state
    this->RegisterState<state::EnemyActionIdleState>(_state_machine);
    this->RegisterState<state::EnemyActionMoveState>(_state_machine);
    this->RegisterState<state::EnemyActionMeleeAttackState>(_state_machine);
    this->RegisterState<state::EnemyActionRangedAttackState>(_state_machine);
    this->RegisterState<state::EnemyActionGoHomeState>(_state_machine);
    _state_machine.ChangeState("EnemyActionIdleState");
    return true;
}

bool my::EnemyStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::EnemyStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyStateComponent::Clone(void) {
    return std::make_shared<my::EnemyStateComponent>(*this);
}

void my::EnemyStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}