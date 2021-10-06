#ifndef RATCHET_ACTOR_BULLET_BLASTER_BULLET_H
#define RATCHET_ACTOR_BULLET_BLASTER_BULLET_H


#include "Bullet.h"


namespace ratchet::actor::bullet {
class BlasterBullet : public ratchet::actor::bullet::Bullet {
    using super = ratchet::actor::bullet::Bullet;
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BlasterBullet();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BlasterBullet();
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
    void Start(const Param& in);
};
}
#endif // !RATCHET_ACTOR_BULLET_BLASTER_BULLET_H