#ifndef RATCHET_BLASTER_BULLET_H
#define RATCHET_BLASTER_BULLET_H


#include "Bullet.h"


namespace ratchet {
class BlasterBullet : public ratchet::Bullet {
    using super = ratchet::Bullet;
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
    void Start(const ratchet::Bullet::Param& in);
};
}
#endif // !RATCHET_BLASTER_BULLET_H