#include "BulletItemActionStateComponent.h"


my::BulletItemActionStateComponent::BulletItemActionStateComponent(int priority) :
    super(priority) {
}

my::BulletItemActionStateComponent::BulletItemActionStateComponent(const BulletItemActionStateComponent& obj) :
    super(obj) {
}

my::BulletItemActionStateComponent::~BulletItemActionStateComponent() {
}

std::string my::BulletItemActionStateComponent::GetType(void) const {
    return "BulletItemActionStateComponent";
}

bool my::BulletItemActionStateComponent::Initialize(void) {
    super::Initialize();
    using Type = state::BulletItemActionType;
    //super::ChangeState(Type::kMoved);
    super::ChangeState(Type::kDefault);
    return true;
}

std::shared_ptr<my::Component> my::BulletItemActionStateComponent::Clone(void) {
    return std::make_shared<my::BulletItemActionStateComponent>(*this);
}

bool my::BulletItemActionStateComponent::CanTransition(const std::string& next) {
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
bool my::BulletItemActionStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 550.0f, "BulletItem state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG