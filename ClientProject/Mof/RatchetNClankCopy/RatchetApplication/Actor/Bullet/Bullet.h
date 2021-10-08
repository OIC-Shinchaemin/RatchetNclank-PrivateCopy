#ifndef RATCHET_ACTOR_BULLET_BULLET_H
#define RATCHET_ACTOR_BULLET_BULLET_H


#include "../Actor.h"

#include "Base/Core/Timer.h"


namespace ratchet ::actor ::bullet {
class Bullet : public actor::Actor {
    using super = actor::Actor;
public:
    struct Param : public super::Param {
        using super = super::Param;
        //! ���x
        Mof::CVector3 speed;
        //! ������̑��x
        Mof::CVector3 inertia;

        Param() :
            super() {
        }
        Param(Mof::CVector3 spd) :
            super(),
            speed(spd),
            inertia() {
        }
        Param(Mof::CVector3 spd, Mof::CVector3 first_spd) :
            super(),
            speed(spd),
            inertia(first_spd) {
        }
        virtual ~Param() {
        }
    };
protected:
    //! ����
    Mof::CVector3 _speed;
    //! ����
    ::base::core::Timer _exist_time;

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
    /// ����
    /// </summary>
    /// <param name="in"></param>
    void Start(const Bullet::Param& in);
};
}
#endif // !RATCHET_ACTOR_BULLET_BULLET_H