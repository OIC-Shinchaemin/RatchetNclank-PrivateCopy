#ifndef RACHET_PYROCITOR_BULLET_H
#define RACHET_PYROCITOR_BULLET_H


#include "Bullet.h"


namespace rachet {
class PyrocitorBullet : public rachet::Bullet {
    using super = rachet::Bullet;
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
    void Start(const rachet::Bullet::Param& in);
};
}
#endif // !RACHET_PYROCITOR_BULLET_H