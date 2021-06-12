#include "OmniWrenchActionStateComponent.h"


ratchet::component::weapon::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(int priority) :
    super(priority) {
}

ratchet::component::weapon::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(const OmniWrenchActionStateComponent& obj) :
    super(obj) {
}

ratchet::component::weapon::OmniWrenchActionStateComponent::~OmniWrenchActionStateComponent() {
}

std::string ratchet::component::weapon::OmniWrenchActionStateComponent::GetType(void) const {
    return "OmniWrenchActionStateComponent";
}

bool ratchet::component::weapon::OmniWrenchActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::OmniWrenchActionStateType;
    super::ChangeState(Type::kOmniWrenchActionDefaultState);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::weapon::OmniWrenchActionStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::weapon::OmniWrenchActionStateComponent>(*this);
}

bool ratchet::component::weapon::OmniWrenchActionStateComponent::CanTransition(const std::string& next) {
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
bool ratchet::component::weapon::OmniWrenchActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 400.0f, "omniwrench state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG