#ifndef MY_BLASTER_BULLET_H
#define MY_BLASTER_BULLET_H


#include "Bullet.h"


namespace my {
class BlasterBullet : public my::Bullet {
    using super = my::Bullet;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BlasterBullet();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BlasterBullet();
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
    void Start(const my::Bullet::Param& in);
};
}
#endif // !MY_BLASTER_BULLET_H