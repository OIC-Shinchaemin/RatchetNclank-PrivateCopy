#ifndef RACHET_ENEMY_BULLET_H
#define RACHET_ENEMY_BULLET_H


#include "Bullet.h"


namespace rachet {
class EnemyBullet : public rachet::Bullet {
    using super = rachet::Bullet;
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
    void Start(const rachet::Bullet::Param& in);
};
}
#endif // !RACHET_ENEMY_BULLET_H