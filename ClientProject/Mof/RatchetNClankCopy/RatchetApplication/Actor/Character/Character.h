#ifndef RATCHET_ACTOR_CHARACTER_CHARACTER_H
#define RATCHET_ACTOR_CHARACTER_CHARACTER_H


#include "../Actor.h"

#include "Base/Core/Observer.h"
#include "Base/Core/Observable.h"
#include "../../Game/GameSystem/Text/TextSystem.h"



namespace ratchet::actor::character {
struct CharacterDamageApplyMessage {
};
using CharacterDamageApplyMessageSubject = base::core::Observable<const CharacterDamageApplyMessage&>;
using CharacterDamageApplyMessageListener = base::core::Observer<const CharacterDamageApplyMessage&>;


class Character : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
private:
    //! �ʒm�p
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
    //! �ʒm�p
    ratchet::actor::character::CharacterDamageApplyMessageSubject _character_damage_apply_message_subject;
protected:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Character();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemMessageSubject(void) {
        return &this->_text_system_message_subject;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetCharacterDamageApplyMessageSubject(void) {
        return &this->_character_damage_apply_message_subject;
    }
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// ��b
    /// </summary>
    virtual void Talk(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_CHARACTER_H