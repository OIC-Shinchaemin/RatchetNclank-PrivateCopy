#include "NanotechItemActionStateComponent.h"


rachet::NanotechItemActionStateComponent::NanotechItemActionStateComponent(int priority) :
    super(priority) {
}

rachet::NanotechItemActionStateComponent::NanotechItemActionStateComponent(const NanotechItemActionStateComponent& obj) :
    super(obj) {
}

rachet::NanotechItemActionStateComponent::~NanotechItemActionStateComponent() {
}

std::string rachet::NanotechItemActionStateComponent::GetType(void) const {
    return "NanotechItemActionStateComponent";
}

bool rachet::NanotechItemActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::NanotechItemActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<rachet::Component> rachet::NanotechItemActionStateComponent::Clone(void) {
    return std::make_shared<rachet::NanotechItemActionStateComponent>(*this);
}

bool rachet::NanotechItemActionStateComponent::CanTransition(const std::string& next) {
    using Type = state::NanotechItemActionType;

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
bool rachet::NanotechItemActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "NanotechItem state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG