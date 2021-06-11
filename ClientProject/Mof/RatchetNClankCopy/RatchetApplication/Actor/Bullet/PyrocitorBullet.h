#ifndef RATCHET_PYROCITOR_BULLET_H
#define RATCHET_PYROCITOR_BULLET_H


#include "Bullet.h"


namespace ratchet {
class PyrocitorBullet : public ratchet::Bullet {
    using super = ratchet::Bullet;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PyrocitorBullet();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PyrocitorBullet();
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
    void Start(const ratchet::Bullet::Param& in);
};
}
#endif // !RATCHET_PYROCITOR_BULLET_H