#include "NanotechItemActionStateComponent.h"


ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::NanotechItemActionStateComponent(int priority) :
    super(priority) {
}

ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::NanotechItemActionStateComponent(const NanotechItemActionStateComponent& obj) :
    super(obj) {
}

ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::~NanotechItemActionStateComponent() {
}

std::string ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::GetType(void) const {
    return "NanotechItemActionStateComponent";
}

bool ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::NanotechItemActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::nanotechitem::NanotechItemActionStateComponent>(*this);
}

bool ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::CanTransition(const std::string& next) {
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
bool ratchet::component::item::nanotechitem::NanotechItemActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "NanotechItem state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG