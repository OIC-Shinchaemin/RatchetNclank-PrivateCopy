#include "MotionStateComponent.h"

#include "../State/PlayerMotion/PlayerMotionIdleState.h"
#include "../State/PlayerMotion/PlayerMotionMoveState.h"
#include "../State/PlayerMotion/PlayerMotionJumpSetState.h"
#include "../State/PlayerMotion/PlayerMotionJumpUpState.h"
#include "../State/PlayerMotion/PlayerMotionJumpDownState.h"
#include "../State/PlayerMotion/PlayerMotionJumpLandingState.h"
#include "../State/PlayerMotion/PlayerMotionMeleeAttackOneState.h"
#include "../State/PlayerMotion/PlayerMotionMeleeAttackOneEndState.h"
#include "../State/PlayerMotion/PlayerMotionMeleeAttackTwoState.h"
#include "../State/PlayerMotion/PlayerMotionMeleeAttackTwoEndState.h"
#include "../State/PlayerMotion/PlayerMotionMeleeAttackThreeState.h"
#include "../State/PlayerMotion/PlayerMotionMeleeAttackThreeEndState.h"
#include "../State/PlayerMotion/PlayerMotionDamageState.h"
#include "../State/EnemyMotion/EnemyMotionIdleState.h"
#include "../State/EnemyMotion/EnemyMotionMoveState.h"
#include "../State/EnemyMotion/EnemyMotionAttackState.h"
#include "../State/EnemyMotion/EnemyMotionRangedAttackState.h"


my::MotionStateComponent::MotionStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::MotionStateComponent::MotionStateComponent(const MotionStateComponent& obj) :
    super(obj._priority),
    _state_machine(obj._state_machine) {
}

my::MotionStateComponent::~MotionStateComponent() {
}

void my::MotionStateComponent::SetParam(const rapidjson::Value& param) {
    super::SetParam(param);
}

std::string my::MotionStateComponent::GetType(void) const {
    return "MotionStateComponent";
}

bool my::MotionStateComponent::Initialize(void) {
    super::Initialize();
    super::Start();

    // ŠO•”‚æ‚èì¬‚³‚ê‚½‚à‚Ì‚ðŽæ“¾
    if (super::GetOwner()->GetTag() == "Enemy") {
        this->RegisterMotionState<state::EnemyMotionIdleState>(_state_machine);
        this->RegisterMotionState<state::EnemyMotionMoveState>(_state_machine);
        this->RegisterMotionState<state::EnemyMotionAttackState>(_state_machine);
        this->RegisterMotionState<state::EnemyMotionRangedAttackState>(_state_machine);
        _state_machine.ChangeState("EnemyMotionIdleState");
    } // if
    else {
        this->RegisterMotionState<state::PlayerMotionIdleState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMoveState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionJumpSetState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionJumpUpState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionJumpDownState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionJumpLandingState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMeleeAttackOneState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMeleeAttackOneEndState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMeleeAttackTwoState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMeleeAttackTwoEndState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMeleeAttackThreeState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionMeleeAttackThreeEndState>(_state_machine);
        this->RegisterMotionState<state::PlayerMotionDamageState>(_state_machine);
        _state_machine.ChangeState("PlayerMotionIdleState");
    } // else 
    return true;
}

bool my::MotionStateComponent::Update(float delta_time) {
    _state_machine.Update(delta_time);
    return false;
}

bool my::MotionStateComponent::Release(void) {
    super::Release();
    return true;
}

std::shared_ptr<my::Component> my::MotionStateComponent::Clone(void) {
    return std::make_shared<my::MotionStateComponent>(*this);
}

void my::MotionStateComponent::ChangeState(const std::string& name) {
    _state_machine.ChangeState(name);
}