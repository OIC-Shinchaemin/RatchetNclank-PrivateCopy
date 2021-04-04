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
private:
    //! ���b�V��
    std::weak_ptr<Mof::CMeshContainer> _mesh;
    //! ���x
    my::Velocity _velocity;
    //! ����
    float _exist_time;
    //! ����
    Mof::CVector3 _speed;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void UpdateTransform(float delta_time);
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
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="in"></param>
    void Start(const my::Bullet::Param& in);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_ACTOR_H