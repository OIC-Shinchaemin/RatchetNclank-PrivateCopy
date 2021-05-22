#ifndef STATE_PLAYER_MOTION_STATE_DEFINE_H
#define STATE_PLAYER_MOTION_STATE_DEFINE_H


#include <string>


namespace state {
struct PlayerMotionStateType {
    static std::string kPlayerMotionIdleState;
    static std::string kPlayerMotionMoveState;
    static std::string kPlayerMotionCrouchState;
    static std::string kPlayerMotionJumpSetState;
    static std::string kPlayerMotionJumpUpState;
    static std::string kPlayerMotionJumpDownState;
    static std::string kPlayerMotionJumpLandingState;
    static std::string kPlayerMotionDoubleJumpState;
    static std::string kPlayerMotionMeleeAttackOneState;
    static std::string kPlayerMotionMeleeAttackOneEndState;
    static std::string kPlayerMotionMeleeAttackTwoState;
    static std::string kPlayerMotionMeleeAttackTwoEndState;
    static std::string kPlayerMotionMeleeAttackThreeState;
    static std::string kPlayerMotionMeleeAttackThreeEndState;
    static std::string kPlayerMotionThrowAttackSetState;
    static std::string kPlayerMotionThrowAttackState;
    static std::string kPlayerMotionThrowAttackEndState;
    static std::string kPlayerMotionJumpAttackSetState;
    static std::string kPlayerMotionJumpAttackState;
    //static std::string kPlayerMotionJumpAttackEndState;
    static std::string kPlayerMotionDamageState;
    static std::string kPlayerMotionDeadState;
};
}
#endif // !STATE_PLAYER_MOTION_STATE_DEFINE_H