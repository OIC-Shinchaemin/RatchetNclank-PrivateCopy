#ifndef RATCHET_ACTOR_BULLET_BOMB_GLOVE_BULLET_H
#define RATCHET_ACTOR_BULLET_BOMB_GLOVE_BULLET_H


#include "Bullet.h"


namespace ratchet {
namespace actor {
namespace bullet {
class BombGloveBullet : public ratchet::actor::bullet::Bullet {
    using super = ratchet::actor::bullet::Bullet;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BombGloveBullet();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGloveBullet();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetGravity(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDrag(void) const;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="in"></param>
    void Start(const Bullet::Param& in);
};
}
}
}
#endif // !RATCHET_ACTOR_BULLET_BOMB_GLOVE_BULLET_H