#ifndef RATCHET_ACTOR_WEAPON_BOMB_GLOVEL_H
#define RATCHET_ACTOR_WEAPON_BOMB_GLOVEL_H


#include "Mechanical.h"


namespace ratchet {
namespace actor {
namespace weapon {
class BombGlove  : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BombGlove();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGlove();
    /// <summary>
    /// 入力判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool IsAction(void) const override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform) override;
};
}
}
}
#endif // !RATCHET_ACTOR_WEAPON_BOMB_GLOVEL_H