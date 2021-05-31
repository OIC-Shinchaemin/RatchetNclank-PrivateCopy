#include "ActionStateComponent.h"

#include "ActionComponent.h"


my::ActionStateComponent::ActionStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::ActionStateComponent::ActionStateComponent(const ActionStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine) {
}

my::ActionStateComponent::~ActionStateComponent() {
}

std::string my::ActionStateComponent::GetType(void) const {
    return "ActionStateComponent";
}

bool my::ActionStateComponent::IsEqual(std::string_view state) const {
    return _state_machine.GetCurrentStateName() == state;
}

bool my::ActionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    auto work = super::GetOwner()->GetComponent<my::ActionComponent>()->GetChildren();
    for (auto pair : work) {
        this->RegisterState(_state_machine, pair.second);
        _action_map.emplace(pair.second->GetStateType().data(), pair.second->GetType().c_str());
    } // for
    super::GetOwner()->GetComponent<my::ActionComponent>()->Activate();
    
    return true;
}

bool my::ActionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::ActionStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<my::Component> my::ActionStateComponent::Clone(void) {
    return std::make_shared<my::ActionStateComponent>(*this);
}

void my::ActionStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
    if (auto it = _action_map.find(name); it != _action_map.end()) {
        super::GetOwner()->GetComponent<my::ActionComponent>()->ChangeAction(it->second.c_str());
    } // if
}