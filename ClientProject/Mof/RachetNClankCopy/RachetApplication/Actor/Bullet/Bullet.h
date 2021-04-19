#ifndef MY_BULLET_H
#define MY_BULLET_H


#include "../../Actor.h"

#include "My/Core/Timer.h"


namespace my {
class Bullet : public my::Actor {
    using super = my::Actor;
public:
    struct Param : public super::Param {
        using super = super::Param;
        //! ���x
        Mof::CVector3 speed;
        Param() :
            super() {
        }
        Param(Mof::CVector3 spd) :
            super(),
            speed(spd) {
        }
        virtual ~Param() {
        }
    };
protected:
    //! ����
    Mof::CVector3 _speed;
    //! ����
    my::Timer _exist_time;

    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    void BulletUpdate(float delta_time);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Bullet();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Bullet();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="in"></param>
    void Start(const my::Bullet::Param& in);
};
}
#endif // !MY_BULLET_H