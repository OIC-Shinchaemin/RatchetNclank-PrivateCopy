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
        Damage,
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
    /// <summary>
    /// デリート
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
};
}
#endif // !MY_ENEMY_H