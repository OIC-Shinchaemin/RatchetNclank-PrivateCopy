#include "OmniWrenchActionStateComponent.h"


my::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::OmniWrenchActionStateComponent::OmniWrenchActionStateComponent(const OmniWrenchActionStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine) {
}

my::OmniWrenchActionStateComponent::~OmniWrenchActionStateComponent() {
}

void my::OmniWrenchActionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::OmniWrenchActionStateComponent::GetType(void) const {
    return "OmniWrenchActionStateComponent";
}

bool my::OmniWrenchActionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    
    std::vector<std::weak_ptr<my::ActionComponent>> work;
    super::GetOwner()->GetComponents<my::ActionComponent>(work);
    for (auto weak : work) {
        if (auto com = weak.lock()) {
            this->RegisterState(_state_machine, com);
        } // if
    } // for
    using Type = state::OmniWrenchActionStateType;

    _state_machine.ChangeState(Type::kOmniWrenchActionDefaultState);
    return true;
}

bool my::OmniWrenchActionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::OmniWrenchActionStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<my::Component> my::OmniWrenchActionStateComponent::Clone(void) {
    return std::make_shared<my::OmniWrenchActionStateComponent>(*this);
}

void my::OmniWrenchActionStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
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