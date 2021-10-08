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
    //! 通知用
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
    //! 通知用
    ratchet::actor::character::CharacterDamageApplyMessageSubject _character_damage_apply_message_subject;
    //! 話かけられた
    std::weak_ptr<ratchet::actor::character::Character> _talked_target;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::actor::character::Character> GetTalkedTarget(void) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Character();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Character();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTalkedTarget(const std::shared_ptr<ratchet::actor::character::Character>& ptr);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemMessageSubject(void) {
        return &this->_text_system_message_subject;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetCharacterDamageApplyMessageSubject(void) {
        return &this->_character_damage_apply_message_subject;
    }
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void);
    /// <summary>
    /// 会話
    /// </summary>
    virtual void Talk(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_CHARACTER_H