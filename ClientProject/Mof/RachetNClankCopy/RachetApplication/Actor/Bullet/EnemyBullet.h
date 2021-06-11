#ifndef RATCHET_ENEMY_BULLET_H
#define RATCHET_ENEMY_BULLET_H


#include "Bullet.h"


namespace ratchet {
class EnemyBullet : public ratchet::Bullet {
    using super = ratchet::Bullet;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyBullet();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyBullet();
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
#endif // !RATCHET_ENEMY_BULLET_H