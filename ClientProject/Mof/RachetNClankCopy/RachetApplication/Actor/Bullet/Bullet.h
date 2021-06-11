#ifndef RACHET_BULLET_H
#define RACHET_BULLET_H


#include "../../Actor.h"

#include "Base/Core/Timer.h"


namespace rachet {
class Bullet : public rachet::Actor {
    using super = rachet::Actor;
public:
    struct Param : public super::Param {
        using super = super::Param;
        //! 速度
        Mof::CVector3 speed;
        //! 持ち主の速度
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
    //! 速さ
    Mof::CVector3 _speed;
    //! 時間
    base::core::Timer _exist_time;

    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    void BulletUpdate(float delta_time);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Bullet();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Bullet();
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="in"></param>
    void Start(const rachet::Bullet::Param& in);
};
}
#endif // !RACHET_BULLET_H