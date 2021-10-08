#ifndef RATCHET_STATE_ENEMY_MOTION_STATE_DEFINE_H
#define RATCHET_STATE_ENEMY_MOTION_STATE_DEFINE_H


#include <string>


namespace ratchet::state {
struct EnemyMotionStateType {
    static std::string kEnemyMotionIdleState;
    static std::string kEnemyMotionMoveState;
    static std::string kEnemyMotionMeleeAttackState;
    static std::string kEnemyMotionRangedAttackState;
    static std::string kEnemyMotionDamageState;
};
}
#endif // !RATCHET_STATE_ENEMY_MOTION_STATE_DEFINE_H