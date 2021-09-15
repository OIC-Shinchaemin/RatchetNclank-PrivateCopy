#ifndef RATCHET_ACTOR_CHARACTER_SCARECROW_H
#define RATCHET_ACTOR_CHARACTER_SCARECROW_H


#include "../Actor.h"


namespace ratchet::actor::character {
struct ScarecrowEndMessage {
    bool end;
};
using ScarecrowEndMessageSubject = base::core::Observable<const ScarecrowEndMessage&>;
using ScarecrowEndMessageListener = base::core::Observer<const ScarecrowEndMessage&>;

class Scarecrow : public actor::Actor {
    using super = actor::Actor;
private:
    //! �I�����ʒm�p
    ratchet::actor::character::ScarecrowEndMessageSubject _end_message_subject;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Scarecrow();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Scarecrow();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetScarecrowEndMessageSubject(void) {
        return &this->_end_message_subject;
    }
    /// <summary>
    /// �f���[�g
    /// </summary>
    /// <param name=""></param>
    virtual void End(void);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(ratchet::actor::Actor::Param* param) override;
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
};
}
#endif // !RATCHET_ACTOR_CHARACTER_SCARECROW_H