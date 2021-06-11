#include "ActionStateComponent.h"

#include "ActionComponent.h"


rachet::ActionStateComponent::ActionStateComponent(int priority) :
    super(priority),
    _next_state(),
    _state_machine(),
    _action_map(){
}

rachet::ActionStateComponent::ActionStateComponent(const ActionStateComponent& obj) :
    super(obj),
    _next_state(),
    _state_machine(obj._state_machine),
    _action_map(){
}

rachet::ActionStateComponent::~ActionStateComponent() {
}

std::string rachet::ActionStateComponent::GetType(void) const {
    return "ActionStateComponent";
}

bool rachet::ActionStateComponent::IsEqual(std::string_view state) const {
    return _state_machine.GetCurrentStateName() == state;
}

bool rachet::ActionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto work = super::GetOwner()->GetComponent<rachet::ActionComponent>()->GetChildren();
    for (auto pair : work) {
        this->RegisterState(_state_machine, pair.second);
        _action_map.emplace(pair.second->GetStateType().data(), pair.second->GetType().c_str());
    } // for
    super::GetOwner()->GetComponent<rachet::ActionComponent>()->Activate();
    return true;
}

bool rachet::ActionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);

    /*
    if (_next_state.has_value()) {        
        _state_machine.ChangeState(_next_state.value());
        if (auto it = _action_map.find(_next_state.value()); it != _action_map.end()) {
            super::GetOwner()->GetComponent<rachet::ActionComponent>()->ChangeAction(it->second.c_str());
        } // if
        _next_state.reset();
    } // if
    */
    return false;
}

bool rachet::ActionStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<rachet::Component> rachet::ActionStateComponent::Clone(void) {
    return std::make_shared<rachet::ActionStateComponent>(*this);
}

void rachet::ActionStateComponent::ChangeState(const std::string& name) {
    //_next_state = name;
    _state_machine.ChangeState(name);
    if (auto it = _action_map.find(name); it != _action_map.end()) {
        super::GetOwner()->GetComponent<rachet::ActionComponent>()->ChangeAction(it->second.c_str());
    } // if
}