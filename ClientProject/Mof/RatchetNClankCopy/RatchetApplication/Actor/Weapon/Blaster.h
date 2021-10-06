#ifndef RATCHET_ACTOR_WEAPON_BLASTER_H
#define RATCHET_ACTOR_WEAPON_BLASTER_H


#include "Mechanical.h"


namespace ratchet::actor::weapon {
class Blaster : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
private:
    //! 弾の大きさ
    float _bullet_scale;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Blaster();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Blaster();
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
#endif // !RATCHET_ACTOR_WEAPON_BLASTER_H