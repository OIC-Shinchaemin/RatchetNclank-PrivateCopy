#ifndef MY_PYROCITOR_BULLET_H
#define MY_PYROCITOR_BULLET_H


#include "Bullet.h"


namespace my {
class PyrocitorBullet : public my::Bullet {
    using super = my::Bullet;
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
    void Start(const my::Bullet::Param& in);
};
}
#endif // !MY_PYROCITOR_BULLET_H