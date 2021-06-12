#include "ActionStateComponent.h"

#include "ActionComponent.h"


ratchet::component::ActionStateComponent::ActionStateComponent(int priority) :
    super(priority),
    _next_state(),
    _state_machine(),
    _action_map(){
}

ratchet::component::ActionStateComponent::ActionStateComponent(const ActionStateComponent& obj) :
    super(obj),
    _next_state(),
    _state_machine(obj._state_machine),
    _action_map(){
}

ratchet::component::ActionStateComponent::~ActionStateComponent() {
}

std::string ratchet::component::ActionStateComponent::GetType(void) const {
    return "ActionStateComponent";
}

bool ratchet::component::ActionStateComponent::IsEqual(std::string_view state) const {
    return _state_machine.GetCurrentStateName() == state;
}

bool ratchet::component::ActionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto work = super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->GetChildren();
    for (auto pair : work) {
        this->RegisterState(_state_machine, pair.second);
        _action_map.emplace(pair.second->GetStateType().data(), pair.second->GetType().c_str());
    } // for
    super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->Activate();
    return true;
}

bool ratchet::component::ActionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);

    /*
    if (_next_state.has_value()) {        
        _state_machine.ChangeState(_next_state.value());
        if (auto it = _action_map.find(_next_state.value()); it != _action_map.end()) {
            super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->ChangeAction(it->second.c_str());
        } // if
        _next_state.reset();
    } // if
    */
    return false;
}

bool ratchet::component::ActionStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::ActionStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::ActionStateComponent>(*this);
}

void ratchet::component::ActionStateComponent::ChangeState(const std::string& name) {
    //_next_state = name;
    _state_machine.ChangeState(name);
    if (auto it = _action_map.find(name); it != _action_map.end()) {
        super::GetOwner()->GetComponent<ratchet::component::ActionComponent>()->ChangeAction(it->second.c_str());
    } // if
}