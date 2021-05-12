#include "EnemyStateComponent.h"

#include "../../State/EnemyAction/EnemyActionIdleState.h"
#include "../../State/EnemyAction/EnemyActionMoveState.h"
#include "../../State/EnemyAction/EnemyActionGoHomeState.h"
#include "../../State/EnemyAction/EnemyActionMeleeAttackState.h"
#include "../../State/EnemyAction/EnemyActionRangedAttackState.h"
#include "../../State/EnemyAction/EnemyActionDamageState.h"


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
    this->RegisterState<state::EnemyActionDamageState>(_state_machine);
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

bool my::EnemyStateComponent::CanTransition(const std::string& next) {
    using Type = state::EnemyActionStateType;
    auto current = _state_machine.GetCurrentStateName();

    if (next == Type::kEnemyActionIdleState) {
        if (current == Type::kEnemyActionIdleState) {
            return false;
        } // if
        if (current == Type::kEnemyActionDamageState) {
            return false;
        } // if
        else {
            return true;
        } // else
    } // if
    else if (next == Type::kEnemyActionMoveState) {
        if (current == Type::kEnemyActionDamageState) {
            return false;
        } // if
        else {
            return true;
        } // else    
    } // else if
    else if (next == Type::kEnemyActionGoHomeState) {
        if (current == Type::kEnemyActionGoHomeState) {
            return false;
        } // if
        else if (current == Type::kEnemyActionDamageState) {
            return false;
        } // else if

        else {
            return true;
        } // else    
    } // else if
    else if (next == Type::kEnemyActionMeleeAttackState) {
        if (current == Type::kEnemyActionDamageState) {
            return false;
        } // if
        else if (current == Type::kEnemyActionMeleeAttackState) {
            return false;
        } // if
        else {
            return true;
        } // else    
    } // else if
    else if (next == Type::kEnemyActionRangedAttackState) {
        if (current == Type::kEnemyActionRangedAttackState) {
            return false;
        } // if
        else if (current == Type::kEnemyActionDamageState) {
            return false;
        } // else if
        else {
            return true;
        } // else    
    } // else if
    else if (next == Type::kEnemyActionDamageState) {
        if (current == Type::kEnemyActionDamageState) {
            return false;
        } // if
        else {
            return true;
        } // else    
    } // else if
    return false;
}