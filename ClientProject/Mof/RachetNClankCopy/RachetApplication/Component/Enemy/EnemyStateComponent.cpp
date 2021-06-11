#include "EnemyStateComponent.h"

#include "../../State/EnemyActionStateDefine.h"


rachet::EnemyStateComponent::EnemyStateComponent(int priority) :
    super(priority)//
    //,
    //_state_machine() 
{
}

rachet::EnemyStateComponent::EnemyStateComponent(const EnemyStateComponent& obj) :
    super(obj)
    //,
    //_state_machine(obj._state_machine) 
{
}

rachet::EnemyStateComponent::~EnemyStateComponent() {
}
/*
void rachet::EnemyStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}
*/
std::string rachet::EnemyStateComponent::GetType(void) const {
    return "EnemyStateComponent";
}
/*
bool rachet::EnemyStateComponent::IsEqual(std::string_view state) const {
    return this->_state_machine.GetCurrentStateName() == state;
}
*/
bool rachet::EnemyStateComponent::Initialize(void) {
    super::Initialize();
    /*
    super::Activate();

    // state
    std::vector<std::weak_ptr<rachet::ActionComponent>> work;
    super::GetOwner()->GetComponents<rachet::ActionComponent>(work);
    for (auto weak : work) {
        if (auto com = weak.lock()) {
            this->RegisterState(_state_machine, com);
        } // if
    } // for
    */
    super::ChangeState("EnemyActionIdleState");
    //_state_machine.ChangeState("EnemyActionIdleState");
    return true;
}
/*
bool rachet::EnemyStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool rachet::EnemyStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}
*/
std::shared_ptr<rachet::Component> rachet::EnemyStateComponent::Clone(void) {
    return std::make_shared<rachet::EnemyStateComponent>(*this);
}
/*
void rachet::EnemyStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}
*/

bool rachet::EnemyStateComponent::CanTransition(const std::string& next) {
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
        else if (current == Type::kEnemyActionMoveState) {
            return false;
        } // else if
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

#ifdef _DEBUG
bool rachet::EnemyStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 600.0f, "enemy state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG