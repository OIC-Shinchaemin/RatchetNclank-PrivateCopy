#ifndef RATCHET_ACTOR_CHARACTER_CHARACTER_H
#define RATCHET_ACTOR_CHARACTER_CHARACTER_H


#include "../Actor.h"

#include "Base/Core/Observer.h"
#include "Base/Core/Observable.h"
#include "../../Game/GameSystem/Text/TextSystem.h"
#include "../../Game/Audio/AudioUtility.h"
#include "CharacterDefine.h"


namespace ratchet::actor::character {
struct CharacterDamageApplyMessage {
    std::string damaged_character_tag;
};
struct CharacterDamageApplyMessageSubject : public base::core::Observable<const CharacterDamageApplyMessage&> {
};
struct CharacterDamageApplyMessageListener : public base::core::Observer<const CharacterDamageApplyMessage&> {
};

struct CharacterDamageApplyMessageFactory {
    CharacterDamageApplyMessageFactory() {
    }
    CharacterDamageApplyMessage Create(const std::shared_ptr<ratchet::actor::Actor>& actor) {
        auto ret = CharacterDamageApplyMessage();
        ret.damaged_character_tag = actor->GetTag();
        return ret;
    }
};


class Character : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
private:
    //! �ʒm�p
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
    //! �ʒm�p
    ratchet::actor::character::CharacterDamageApplyMessageSubject _character_damage_apply_message_subject;
    //! �b������ꂽ
    std::weak_ptr<ratchet::actor::character::Character> _talked_target;
protected:
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::character::Character> GetTalkedTarget(void) const;
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTalkedTarget(const std::shared_ptr<ratchet::actor::character::Character>& ptr);
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