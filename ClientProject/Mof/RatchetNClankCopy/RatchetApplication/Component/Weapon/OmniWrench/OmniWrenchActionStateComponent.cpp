#include "OmniWrenchActionStateComponent.h"


ratchet::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(int priority) :
    super(priority) {
}

ratchet::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(const OmniWrenchActionStateComponent& obj) :
    super(obj) {
}

ratchet::OmniWrenchActionStateComponent::~OmniWrenchActionStateComponent() {
}

std::string ratchet::OmniWrenchActionStateComponent::GetType(void) const {
    return "OmniWrenchActionStateComponent";
}

bool ratchet::OmniWrenchActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::OmniWrenchActionStateType;
    super::ChangeState(Type::kOmniWrenchActionDefaultState);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::OmniWrenchActionStateComponent::Clone(void) {
    return std::make_shared<ratchet::OmniWrenchActionStateComponent>(*this);
}

bool ratchet::OmniWrenchActionStateComponent::CanTransition(const std::string& next) {
    using Type = state::OmniWrenchActionStateType;

    auto current = _state_machine.GetCurrentStateName();
    if (next == Type::kOmniWrenchActionDefaultState) {
        if (current == Type::kOmniWrenchActionThrowedState) {
            return true;
        } // if
    } // if
    if (next == Type::kOmniWrenchActionThrowedState) {
        if (current == Type::kOmniWrenchActionDefaultState) {
            return true;
        } // if
    } // if
    return false;
}

#ifdef _DEBUG
bool ratchet::OmniWrenchActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 400.0f, "omniwrench state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG