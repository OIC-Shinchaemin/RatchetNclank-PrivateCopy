#ifndef MY_BOLT_H
#define MY_BOLT_H


#include "../../Actor.h"


namespace my {
class Bolt : public my::Actor {
    using super = my::Actor;
public:
    struct Param : public super::Param {
        //! �ړ�
        Mof::CVector3 speed;
        //! ��]
        Mof::CVector3 angle;
    };
private:
    //! �ړ�
    Mof::CVector3 _init_speed;
    //! ��]
    Mof::CVector3 _init_angle;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Bolt();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Bolt();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
};
}
#endif // !MY_BOLT_H