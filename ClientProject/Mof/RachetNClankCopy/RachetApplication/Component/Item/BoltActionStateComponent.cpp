#include "BoltActionStateComponent.h"


rachet::BoltActionStateComponent::BoltActionStateComponent(int priority) :
    super(priority) {
}

rachet::BoltActionStateComponent::BoltActionStateComponent(const BoltActionStateComponent& obj) :
    super(obj) {
}

rachet::BoltActionStateComponent::~BoltActionStateComponent() {
}

std::string rachet::BoltActionStateComponent::GetType(void) const {
    return "BoltActionStateComponent";
}

bool rachet::BoltActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::BoltActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<rachet::Component> rachet::BoltActionStateComponent::Clone(void) {
    return std::make_shared<rachet::BoltActionStateComponent>(*this);
}

bool rachet::BoltActionStateComponent::CanTransition(const std::string& next) {
    using Type = state::BoltActionType;

    auto current = _state_machine.GetCurrentStateName();
    if (next == Type::kGravitate) {
        if (current == Type::kDefault) {
            return true;
        } // if
    } // if
    else if (next == Type::kDefault) {
        if (current == Type::kMoved) {
            return true;
        } // if
    } // else if
    return false;
}

#ifdef _DEBUG
bool rachet::BoltActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "bolt state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG