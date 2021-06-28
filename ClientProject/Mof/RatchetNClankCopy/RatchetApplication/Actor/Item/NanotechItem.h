#ifndef RATCHET_ACTOR_ITEM_NANOTECH_ITEM_H
#define RATCHET_ACTOR_ITEM_NANOTECH_ITEM_H


#include "../Actor.h"

#include "Base/Core/Observable.h"


namespace ratchet {
namespace actor {
namespace item {
class NanotechItem : public ratchet::actor::Actor {
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
    NanotechItem();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NanotechItem();
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
}
}
#endif // !RATCHET_ACTOR_ITEM_NANOTECH_ITEM_H