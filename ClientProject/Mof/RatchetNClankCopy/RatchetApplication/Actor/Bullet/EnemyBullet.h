#ifndef RATCHET_ACTOR_BULLET_ENEMY_BULLET_H
#define RATCHET_ACTOR_BULLET_ENEMY_BULLET_H


#include "Bullet.h"


namespace ratchet {
namespace actor {
namespace bullet {
class EnemyBullet : public bullet::Bullet {
    using super = bullet::Bullet;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyBullet();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyBullet();
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
    void Start(const bullet::Bullet::Param& in);
};
}
}
}
#endif // !RATCHET_ACTOR_BULLET_ENEMY_BULLET_H