#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"


namespace my {
class Enemy : public my::Character {
    using super = my::Character;
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        AttackOne,
        CountMax,
    };
    enum class ActionType {
        IdleWait,
        MoveRun,
        MoveGoHome,
        AttackOne,
        CountMax,
    };
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Enemy();
};
}
#endif // !MY_ENEMY_H