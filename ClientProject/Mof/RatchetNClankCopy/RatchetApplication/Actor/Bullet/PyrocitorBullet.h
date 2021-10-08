#ifndef RATCHET_ACTOR_BULLET_PYROCITOR_BULLET_H
#define RATCHET_ACTOR_BULLET_PYROCITOR_BULLET_H


#include "Bullet.h"


namespace ratchet::actor::bullet {
class PyrocitorBullet : public ratchet::actor::bullet::Bullet {
    using super = ratchet::actor::bullet::Bullet;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PyrocitorBullet();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PyrocitorBullet();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="in"></param>
    void Start(const ratchet::actor::bullet::Bullet::Param& in);
};
}
#endif // !RATCHET_ACTOR_BULLET_PYROCITOR_BULLET_H