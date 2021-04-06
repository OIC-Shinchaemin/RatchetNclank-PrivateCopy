#ifndef MY_BLASTER_BULLET_H
#define MY_BLASTER_BULLET_H


#include "Bullet.h"


namespace my {
class BlasterBullet : public my::Bullet {
    using super = my::Bullet;
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
    void Start(const my::Bullet::Param& in);
};
}
#endif // !MY_BLASTER_BULLET_H