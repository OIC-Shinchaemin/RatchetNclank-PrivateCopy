#include "BoltActionStateComponent.h"


my::BoltActionStateComponent::BoltActionStateComponent(int priority) :
    super(priority) {
}

my::BoltActionStateComponent::BoltActionStateComponent(const BoltActionStateComponent& obj) :
    super(obj) {
}

my::BoltActionStateComponent::~BoltActionStateComponent() {
}

std::string my::BoltActionStateComponent::GetType(void) const {
    return "BoltActionStateComponent";
}

bool my::BoltActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::BoltActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<my::Component> my::BoltActionStateComponent::Clone(void) {
    return std::make_shared<my::BoltActionStateComponent>(*this);
}

bool my::BoltActionStateComponent::CanTransition(const std::string& next) {
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
bool my::BoltActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "bolt state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG