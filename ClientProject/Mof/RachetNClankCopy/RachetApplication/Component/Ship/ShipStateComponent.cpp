#include "ShipStateComponent.h"


my::ShipStateComponent::ShipStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::ShipStateComponent::ShipStateComponent(const ShipStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine) {
}

my::ShipStateComponent::~ShipStateComponent() {
}

void my::ShipStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::ShipStateComponent::GetType(void) const {
    return "ShipStateComponent";
}

bool my::ShipStateComponent::IsEqual(std::string_view state) const {
    return _state_machine.GetCurrentStateName() == state;
}

bool my::ShipStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    std::vector<std::weak_ptr<my::ActionComponent>> work;
    super::GetOwner()->GetComponents<my::ActionComponent>(work);
    for (auto weak : work) {
        if (auto com = weak.lock()) {
            this->RegisterState(_state_machine, com);
        } // if
    } // for

    //_state_machine.ChangeState(state::ShipActionStateType::kShipActionIdleState);
    _state_machine.ChangeState(state::ShipActionStateType::kShipActionLandingState);
    return true;
}

bool my::ShipStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    std::cout << "ship state = " << _state_machine.GetCurrentStateName() << "\n";
    return false;
}

bool my::ShipStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<my::Component> my::ShipStateComponent::Clone(void) {
    return std::make_shared<my::ShipStateComponent>(*this);
}

void my::ShipStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}

bool my::ShipStateComponent::CanTransition(std::string_view next) const {
    using Type = state::ShipActionStateType;
    auto current = _state_machine.GetCurrentStateName();
    if (current == Type::kShipActionIdleState) {
        if (next == Type::kShipActionTakeoffState) {
            return true;
        } // if
    } // if
    else if (current == Type::kShipActionLandingState) {
        if (next == Type::kShipActionIdleState) {
            return true;
        } // if
    } // else if
    else if (current == Type::kShipActionTakeoffState) {
        if (next == Type::kShipActionLandingState) {
            return true;
        } // if
    } // else if
    return false;
}

#ifdef _DEBUG
bool my::ShipStateComponent::DebugRender(void) {
    ::CGraphicsUtilities::RenderString(
        20.0f, 100.0f, "ship state = %s", this->_state_machine.GetCurrentStateName());
    return true;
}
#endif // _DEBUG