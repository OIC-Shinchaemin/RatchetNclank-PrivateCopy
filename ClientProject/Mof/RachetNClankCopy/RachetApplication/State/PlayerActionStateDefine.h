#ifndef STATE_PLAYER_ACTION_STATE_DEFINE_H
#define STATE_PLAYER_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct PlayerActionStateType {
    static std::string kPlayerActionIdleState;
    static std::string kPlayerActionMoveState;
    static std::string kPlayerActionJumpSetState;
    static std::string kPlayerActionJumpUpState;
    static std::string kPlayerActionJumpDownState;
    static std::string kPlayerActionJumpLandingState;
    static std::string kPlayerActionDoubleJumpState;
    static std::string kPlayerActionMeleeAttackOneState;
    static std::string kPlayerActionMeleeAttackOneEndState;
    static std::string kPlayerActionMeleeAttackTwoState;
    static std::string kPlayerActionMeleeAttackTwoEndState;
    static std::string kPlayerActionMeleeAttackThreeState;
    static std::string kPlayerActionMeleeAttackThreeEndState;
    static std::string kPlayerActionThrowAttackSetState;
    static std::string kPlayerActionThrowAttackState;
    static std::string kPlayerActionThrowAttackEndState;
    static std::string kPlayerActionJumpAttackSetState;
    static std::string kPlayerActionJumpAttackState;
    static std::string kPlayerActionLookState;
    static std::string kPlayerActionDamageState;
    static std::string kPlayerActionDeadState;
};
}
#endif // !STATE_PLAYER_ACTION_STATE_DEFINE_H