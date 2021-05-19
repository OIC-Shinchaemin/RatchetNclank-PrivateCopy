#include "MotionStateComponent.h"

#include "../State/PlayerMotionStateDefine.h"
#include "../State/EnemyMotionStateDefine.h"
#include "../Actor/Character/Player.h"
#include "../Actor/Character/Enemy.h"


my::MotionStateComponent::MotionStateComponent(int priority) :
    super(priority),
    _state_machine() {
}

my::MotionStateComponent::MotionStateComponent(const MotionStateComponent& obj) :
    super(obj),
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
    super::Activate();

    using Param = state::MotionState::Param;

    // ŠO•”‚æ‚èì¬‚³‚ê‚½‚à‚Ì‚ðŽæ“¾
    if (super::GetOwner()->GetTag() == "Enemy") {
        using State = state::EnemyMotionStateType;
        using Type = my::Enemy::MotionType;

        this->RegisterState(Param(State::kEnemyMotionIdleState, Type::IdleWait, 1.0f, true, false));
        this->RegisterState(Param(State::kEnemyMotionMoveState, Type::MoveRun, 1.0f, true, false));
        this->RegisterState(Param(State::kEnemyMotionMeleeAttackState, Type::AttackOne, 1.0f, false, false));
        this->RegisterState(Param(State::kEnemyMotionRangedAttackState, Type::AttackOne, 1.0f, false, false));
        this->RegisterState(Param(State::kEnemyMotionDamageState, Type::Damage, 1.0f, false, false));

        _state_machine.ChangeState(State::kEnemyMotionIdleState);
    } // if
    else {
        using State = state::PlayerMotionStateType;
        using Type = my::Player::MotionType;

        this->RegisterState(Param(State::kPlayerMotionIdleState, Type::IdleWait, 1.0f, true, false));
        this->RegisterState(Param(State::kPlayerMotionMoveState, Type::MoveRun, 1.0f, true, false));
        this->RegisterState(Param(State::kPlayerMotionJumpSetState, Type::JumpSet, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionJumpUpState, Type::JumpUp, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionJumpDownState, Type::JumpDown, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionJumpLandingState, Type::JumpLanding, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionDoubleJumpState, Type::DoubleJump, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionMeleeAttackOneState, Type::MeleeAttackOne, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionMeleeAttackOneEndState, Type::MeleeAttackOneEnd, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionMeleeAttackTwoState, Type::MeleeAttackTwo, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionMeleeAttackTwoEndState, Type::MeleeAttackTwoEnd, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionMeleeAttackThreeState, Type::MeleeAttackThree, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionMeleeAttackThreeEndState, Type::MeleeAttackThreeEnd, 1.0f, false, false));

        this->RegisterState(Param(State::kPlayerMotionThrowAttackSetState, Type::ThrowAttackSet, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionThrowAttackState, Type::ThrowAttack, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionThrowAttackEndState, Type::ThrowAttackEnd, 1.0f, false, false));

        this->RegisterState(Param(State::kPlayerMotionJumpAttackSetState, Type::JumpAttackSet, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionJumpAttackState, Type::JumpAttack, 1.0f, false, false));

        this->RegisterState(Param(State::kPlayerMotionDamageState, Type::DamageA, 1.0f, false, false));
        this->RegisterState(Param(State::kPlayerMotionDeadState, Type::DamageDead, 1.0f, false, false));

        _state_machine.ChangeState(State::kPlayerMotionIdleState);
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