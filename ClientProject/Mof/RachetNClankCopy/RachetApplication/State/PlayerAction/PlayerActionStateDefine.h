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
    static std::string kPlayerActionDamageState;
};
}
#endif // !STATE_PLAYER_ACTION_STATE_DEFINE_H