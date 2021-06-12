#include "BulletItemActionStateComponent.h"


ratchet::component::item::bulletitem::BulletItemActionStateComponent::BulletItemActionStateComponent(int priority) :
    super(priority) {
}

ratchet::component::item::bulletitem::BulletItemActionStateComponent::BulletItemActionStateComponent(const BulletItemActionStateComponent& obj) :
    super(obj) {
}

ratchet::component::item::bulletitem::BulletItemActionStateComponent::~BulletItemActionStateComponent() {
}

std::string ratchet::component::item::bulletitem::BulletItemActionStateComponent::GetType(void) const {
    return "BulletItemActionStateComponent";
}

bool ratchet::component::item::bulletitem::BulletItemActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::BulletItemActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::item::bulletitem::BulletItemActionStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::item::bulletitem::BulletItemActionStateComponent>(*this);
}

bool ratchet::component::item::bulletitem::BulletItemActionStateComponent::CanTransition(const std::string& next) {
    using Type = state::BulletItemActionType;

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
bool ratchet::component::item::bulletitem::BulletItemActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "BulletItem state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG