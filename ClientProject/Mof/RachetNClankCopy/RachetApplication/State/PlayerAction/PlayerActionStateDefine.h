#ifndef STATE_PLAYER_ACTION_STATE_DEFINE_H
#define STATE_PLAYER_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct PlayerActionStateType {
    static std::string kPlayerActionIdleState;
    static std::string kPlayerActionMoveState;
    static std::string kPlayerActionJumpState;
    static std::string kPlayerActionDamageState;
};
}
#endif // !STATE_PLAYER_ACTION_STATE_DEFINE_H