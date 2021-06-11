#ifndef RATCHET_BOMB_GLOVE_BULLET_H
#define RATCHET_BOMB_GLOVE_BULLET_H


#include "Bullet.h"


namespace ratchet {
class BombGloveBullet : public ratchet::Bullet {
    using super = ratchet::Bullet;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BombGloveBullet();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BombGloveBullet();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetGravity(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDrag(void) const;
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
#endif // !RATCHET_BOMB_GLOVE_BULLET_H