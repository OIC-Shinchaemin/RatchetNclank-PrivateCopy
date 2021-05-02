#ifndef STATE_ENEMY_ACTION_STATE_DEFINE_H
#define STATE_ENEMY_ACTION_STATE_DEFINE_H


#include <string>


namespace state {
struct EnemyActionStateType {
    static std::string kEnemyActionIdleState;
    static std::string kEnemyActionGoHomeState;
    static std::string kEnemyActionMoveState;
    static std::string kEnemyActionMeleeAttackState;
    static std::string kEnemyActionRangedAttackState;
    static std::string kEnemyActionDamageState;
};
}
#endif // !STATE_ENEMY_ACTION_STATE_DEFINE_H