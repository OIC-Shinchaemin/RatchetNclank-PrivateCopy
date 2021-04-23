#include "AIStateComponent.h"

#include "../State/AI/AIPatrolState.h"
#include "../State/AI/AICombatState.h"


my::AIStateComponent::AIStateComponent(int priority) :
    super(priority),
    _state_machine(),
    _thinking_time() {
}

my::AIStateComponent::AIStateComponent(const AIStateComponent& obj) :
    super(obj._priority),
    _state_machine(obj._state_machine) {
}

my::AIStateComponent::~AIStateComponent() {
}

void my::AIStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::AIStateComponent::GetType(void) const {
    return "AIStateComponent";
}

bool my::AIStateComponent::Initialize(void) {
    super::Initialize();
    super::Start();
    _thinking_time.Initialize(0.0f, true);

    // state
    this->RegisterState<state::AIPatrolState>(_state_machine);
    this->RegisterState<state::AICombatState>(_state_machine);
    _state_machine.ChangeState("AIPatrolState");
    return true;
}

bool my::AIStateComponent::Update(float delta_time) {
    if (_thinking_time.Tick(delta_time)) {
        _state_machine.Update(delta_time);
    } // if
    return false;
}

bool my::AIStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::AIStateComponent::Clone(void) {
    return std::make_shared<my::AIStateComponent>(*this);
}

void my::AIStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}