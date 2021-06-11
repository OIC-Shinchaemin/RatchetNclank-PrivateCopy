#include "BoltActionStateComponent.h"


ratchet::BoltActionStateComponent::BoltActionStateComponent(int priority) :
    super(priority) {
}

ratchet::BoltActionStateComponent::BoltActionStateComponent(const BoltActionStateComponent& obj) :
    super(obj) {
}

ratchet::BoltActionStateComponent::~BoltActionStateComponent() {
}

std::string ratchet::BoltActionStateComponent::GetType(void) const {
    return "BoltActionStateComponent";
}

bool ratchet::BoltActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::BoltActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<ratchet::Component> ratchet::BoltActionStateComponent::Clone(void) {
    return std::make_shared<ratchet::BoltActionStateComponent>(*this);
}

bool ratchet::BoltActionStateComponent::CanTransition(const std::string& next) {
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
bool ratchet::BoltActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "bolt state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG