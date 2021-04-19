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
        //! 速度
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
    //! 速さ
    Mof::CVector3 _speed;
    //! 時間
    my::Timer _exist_time;

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
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Release(void) override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="in"></param>
    void Start(const my::Bullet::Param& in);
};
}
#endif // !MY_BULLET_H