#include "AIStateComponent.h"

#include "../State/AI/AIPatrolState.h"
#include "../State/AI/AICombatState.h"


ratchet::component::AIStateComponent::AIStateComponent(int priority) :
    super(priority),
    _state_machine(),
    _thinking_timer(),
    _behaviour_path(){
}

ratchet::component::AIStateComponent::AIStateComponent(const AIStateComponent& obj) :
    super(obj),
    _state_machine(obj._state_machine),
    _behaviour_path(obj._behaviour_path){
}

ratchet::component::AIStateComponent::~AIStateComponent() {
}

void ratchet::component::AIStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
    
    const char* behaviour = "behaviour";
    if (param.HasMember(behaviour)) {
        _ASSERT_EXPR(param[behaviour].IsArray(), L"パラメータの指定された型でありません");

        _behaviour_path.reserve(param[behaviour].GetArray().Size());

        for (int i = 0, n = param[behaviour].GetArray().Size(); i < n; i++) {
            _behaviour_path.push_back(param[behaviour].GetArray()[i].GetString());
        } // for
    } // if
}

std::string ratchet::component::AIStateComponent::GetType(void) const {
    return "AIStateComponent";
}

bool ratchet::component::AIStateComponent::IsInput(void) const {
    return true;
}

bool ratchet::component::AIStateComponent::Initialize(void) {
    super::Initialize();
    super::Activate();
    _thinking_timer.Initialize(0.4f, true);
    
    // state
    this->RegisterState<ratchet::state::ai::AIPatrolState>(_state_machine, _behaviour_path.at(0));
    this->RegisterState<ratchet::state::ai::AICombatState>(_state_machine, _behaviour_path.at(1));
    _state_machine.ChangeState("AIPatrolState");
    return true;
}

bool ratchet::component::AIStateComponent::Input(void) {
    float delta_time = def::kDeltaTime;
    if (_thinking_timer.Tick(delta_time)) {
        _state_machine.Update(delta_time);
    } // if
    return true;
}

bool ratchet::component::AIStateComponent::Update(float delta_time) {
    /*
    if (_thinking_timer.Tick(delta_time)) {
        _state_machine.Update(delta_time);
    } // if
    */
    return true;
}

bool ratchet::component::AIStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<ratchet::component::Component> ratchet::component::AIStateComponent::Clone(void) {
    return std::make_shared<ratchet::component::AIStateComponent>(*this);
}

void ratchet::component::AIStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}

#ifdef _DEBUG
bool ratchet::component::AIStateComponent::DebugRender(void) {
    _state_machine.DebugRender();
    return false;
}
#endif // _DEBUG