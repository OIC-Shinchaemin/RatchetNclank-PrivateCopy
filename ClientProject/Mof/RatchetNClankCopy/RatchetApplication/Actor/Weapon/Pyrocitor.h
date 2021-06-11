#ifndef RATCHET_ACTOR_WEAPON_PYROCITOR_H
#define RATCHET_ACTOR_WEAPON_PYROCITOR_H


#include "Mechanical.h"


namespace ratchet {
namespace actor {
namespace weapon {
class Pyrocitor : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Pyrocitor();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Pyrocitor();
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
#endif // !RATCHET_ACTOR_WEAPON_PYROCITOR_H