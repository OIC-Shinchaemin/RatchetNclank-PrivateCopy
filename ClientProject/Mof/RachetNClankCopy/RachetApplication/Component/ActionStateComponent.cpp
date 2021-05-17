#include "ActionStateComponent.h"


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

void my::ActionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::ActionStateComponent::GetType(void) const {
    return "ActionStateComponent";
}

bool my::ActionStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();

    std::vector<std::weak_ptr<my::ActionComponent>> work;
    super::GetOwner()->GetComponents<my::ActionComponent>(work);
    for (auto weak : work) {
        if (auto com = weak.lock()) {
            this->RegisterState(_state_machine, com);
        } // if
    } // for
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
}