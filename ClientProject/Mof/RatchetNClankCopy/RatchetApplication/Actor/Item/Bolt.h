#ifndef RATCHET_ACTOR_ITEM_BOLT_H
#define RATCHET_ACTOR_ITEM_BOLT_H


#include "../Actor.h"

#include "Base/Core/Observable.h"


namespace ratchet::actor::item {
class Bolt : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
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
    base::core::Observable<int> _money_subject;
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<int>* GetMoneySubject(void);
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
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
};
}
#endif // !RATCHET_ACTOR_ITEM_BOLT_H