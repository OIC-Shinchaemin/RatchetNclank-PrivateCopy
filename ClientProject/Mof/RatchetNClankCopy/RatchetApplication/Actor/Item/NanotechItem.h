#ifndef RATCHET_NANOTECH_ITEM_H
#define RATCHET_NANOTECH_ITEM_H


#include "../../Actor.h"

#include "Base/Core/Observable.h"


namespace ratchet {
class NanotechItem : public ratchet::Actor {
    using super = ratchet::Actor;
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //base::core::Observable<int>* GetMoneySubject(void);
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
    virtual bool Initialize(ratchet::Actor::Param* param) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    //virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_NANOTECH_ITEM_H