#include "EnemyStateComponent.h"

#include "../../State/EnemyActionStateDefine.h"


my::EnemyStateComponent::EnemyStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::EnemyStateComponent::EnemyStateComponent(const EnemyStateComponent& obj) :
    super(obj),
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
    super::Activate();

    // state
    std::vector<std::weak_ptr<my::ActionComponent>> work;
    super::GetOwner()->GetComponents<my::ActionComponent>(work);
    for (auto weak : work) {
        if (auto com = weak.lock()) {
            this->RegisterState(_state_machine, com);
        } // if
    } // for

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