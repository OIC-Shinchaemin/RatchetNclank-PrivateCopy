#ifndef MY_BULLET_H
#define MY_BULLET_H


#include "../ResourceLocator.h"

#include "../Actor.h"
#include "../Velocity.h"


namespace my {
class Bullet : public my::Actor, public my::ResourceLocator {
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
private:
    //! メッシュ
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! 速度
    my::Velocity _velocity;
    //! 時間
    float _exist_time;
    //! 速さ
    Mof::CVector3 _speed;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void UpdateTransform(float delta_time);
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
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 発射
    /// </summary>
    /// <param name="in"></param>
    void Start(const my::Bullet::Param& in);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_ACTOR_H