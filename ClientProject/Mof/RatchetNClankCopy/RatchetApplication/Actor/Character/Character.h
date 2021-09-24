#ifndef RATCHET_ACTOR_CHARACTER_CHARACTER_H
#define RATCHET_ACTOR_CHARACTER_CHARACTER_H


#include "../Actor.h"

#include "../../Game/GameSystem/Text/TextSystem.h"



namespace ratchet::actor::character {
class Character : public ratchet::actor::Actor {
    using super = ratchet::actor::Actor;
protected:
    //! 通知用
    ratchet::game::gamesystem::text::TextSystemMessageSubject _text_system_message_subject;
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetTextSystemMessageSubject(void) {
        return &this->_text_system_message_subject;
    }
    /// <summary>
    /// 会話
    /// </summary>
    virtual void Talk(void);
};
}
#endif // !RATCHET_ACTOR_CHARACTER_CHARACTER_H