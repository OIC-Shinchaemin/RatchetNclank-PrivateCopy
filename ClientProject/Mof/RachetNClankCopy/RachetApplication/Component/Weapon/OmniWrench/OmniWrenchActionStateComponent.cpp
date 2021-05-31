#include "OmniWrenchActionStateComponent.h"


my::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(int priority) :
    super(priority) {
}

my::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(const OmniWrenchActionStateComponent& obj) :
    super(obj) {
}

my::OmniWrenchActionStateComponent::~OmniWrenchActionStateComponent() {
}

std::string my::OmniWrenchActionStateComponent::GetType(void) const {
    return "OmniWrenchActionStateComponent";
}

bool my::OmniWrenchActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::OmniWrenchActionStateType;
    super::ChangeState(Type::kOmniWrenchActionDefaultState);
    return true;
}

std::shared_ptr<my::Component> my::OmniWrenchActionStateComponent::Clone(void) {
    return std::make_shared<my::OmniWrenchActionStateComponent>(*this);
}

bool my::OmniWrenchActionStateComponent::CanTransition(const std::string& next) {
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
bool my::OmniWrenchActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 400.0f, "omniwrench state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG