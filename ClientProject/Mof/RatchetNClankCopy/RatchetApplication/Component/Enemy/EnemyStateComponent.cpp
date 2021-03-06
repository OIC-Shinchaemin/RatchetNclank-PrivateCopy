#include "EnemyStateComponent.h"

#include "../../State/EnemyActionStateDefine.h"


ratchet::component::enemy::EnemyStateComponent::EnemyStateComponent(int priority) :
    super(priority) {
}

ratchet::component::enemy::EnemyStateComponent::EnemyStateComponent(const EnemyStateComponent& obj) :
    super(obj) {
}

ratchet::component::enemy::EnemyStateComponent::~EnemyStateComponent() {
}

std::string ratchet::component::enemy::EnemyStateComponent::GetType(void) const {
    return "EnemyStateComponent";
}

bool ratchet::component::enemy::EnemyStateComponent::Initialize(void) {
    super::Initialize();
    super::ChangeState("EnemyActionIdleState");
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::enemy::EnemyStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::enemy::EnemyStateComponent>(*this);
}

bool ratchet::component::enemy::EnemyStateComponent::CanTransition(const std::string& next) {
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
bool ratchet::component::enemy::EnemyStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 600.0f, "enemy state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG