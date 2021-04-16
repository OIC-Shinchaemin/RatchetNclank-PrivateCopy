#include "EnemyStateComponent.h"

#include "../../State/EnemyActionIdleState.h"
#include "../../State/EnemyActionMoveState.h"
#include "../../State/EnemyActionGoHomeState.h"
#include "../../State/EnemyActionAttackState.h"


my::EnemyStateComponent::EnemyStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::EnemyStateComponent::EnemyStateComponent(const EnemyStateComponent& obj) :
    super(obj._priority),
    _state_machine(obj._state_machine) {
}

my::EnemyStateComponent::~EnemyStateComponent() {
}

void my::EnemyStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::EnemyStateComponent::GetType(void) const {
    return "EnemyStateComponent";
}

bool my::EnemyStateComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // state
    this->RegisterState<state::EnemyActionIdleState>(_state_machine);
    this->RegisterState<state::EnemyActionMoveState>(_state_machine);
    this->RegisterState<state::EnemyActionAttackState>(_state_machine);
    this->RegisterState<state::EnemyActionGoHomeState>(_state_machine);
    _state_machine.ChangeState("EnemyActionIdleState");
    return true;
}

bool my::EnemyStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

#ifdef _DEBUG
bool my::EnemyStateComponent::Render(void) {
    ::CGraphicsUtilities::RenderString(0.0f, 200.0f, "state = %s", _state_machine.GetCurrentStateName());
    return false;
}
#endif // _DEBUG

bool my::EnemyStateComponent::Release(void) {
    super::Release();
    _state_machine.Release();
    return true;
}

std::shared_ptr<my::Component> my::EnemyStateComponent::Clone(void) {
    return std::make_shared<my::EnemyStateComponent>(*this);
}

void my::EnemyStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}