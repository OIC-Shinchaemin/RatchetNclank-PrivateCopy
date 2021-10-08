#ifndef RATCHET_ACTOR_WEAPON_BLASTER_H
#define RATCHET_ACTOR_WEAPON_BLASTER_H


#include "Mechanical.h"


namespace ratchet::actor::weapon {
class Blaster : public ratchet::actor::weapon::Mechanical {
    using super = ratchet::actor::weapon::Mechanical;
private:
    //! 弾の大きさ
    float _bullet_scale;
    //! 拡大中
    bool _scaling;
    //! 拡大率
    float _scaling_maltiply;
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
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Fire(const def::Transform& transform) override;
    /// <summary>
    /// 拡大
    /// </summary>
    /// <param name=""></param>
    virtual void Scaling(void) override;
};
}
#endif // !RATCHET_ACTOR_WEAPON_BLASTER_H