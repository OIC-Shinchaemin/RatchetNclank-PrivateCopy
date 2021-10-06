#ifndef RATCHET_ACTOR_BULLET_ENEMY_BULLET_H
#define RATCHET_ACTOR_BULLET_ENEMY_BULLET_H


#include "Bullet.h"


namespace ratchet::actor::bullet {
class EnemyBullet : public bullet::Bullet {
    using super = bullet::Bullet;
private:
    //! �g�嗦
    float _scale_multiply;
    //! �g�嗦
    float _scale_threshold;
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
    void Start(const bullet::Bullet::Param& in);
};
}
#endif // !RATCHET_ACTOR_BULLET_ENEMY_BULLET_H