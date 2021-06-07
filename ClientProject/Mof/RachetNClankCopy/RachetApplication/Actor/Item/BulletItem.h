#ifndef MY_BULLET_ITEM_H
#define MY_BULLET_ITEM_H


#include "../../Actor.h"

#include "My/Core/Observable.h"


namespace my {
class BulletItem : public my::Actor {
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
    //! �ʒm�p
    my::Observable<int> _money_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BulletItem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BulletItem();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //my::Observable<int>* GetMoneySubject(void);
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void) override;
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
#endif // !MY_BULLET_ITEM_H