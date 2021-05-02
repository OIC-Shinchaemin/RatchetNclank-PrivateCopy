#ifndef STATE_ENEMY_MOTION_STATE_DEFINE_H
#define STATE_ENEMY_MOTION_STATE_DEFINE_H


#include <string>


namespace state {
struct EnemyMotionStateType {
    static std::string kEnemyMotionIdleState;
    static std::string kEnemyMotionMoveState;
    static std::string kEnemyMotionMeleeAttackState;
    static std::string kEnemyMotionRangedAttackState;
    static std::string kEnemyMotionDamageState;
};
}
#endif // !STATE_ENEMY_MOTION_STATE_DEFINE_H