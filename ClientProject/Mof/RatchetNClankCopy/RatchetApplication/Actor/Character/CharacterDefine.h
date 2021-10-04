#ifndef RATCHET_ACTOR_CHARACTER_CHARACTER_DEFINE_H
#define RATCHET_ACTOR_CHARACTER_CHARACTER_DEFINE_H


#include "Base/Core/Observer.h"
#include "Base/Core/Observable.h"


namespace ratchet::actor::character {
struct CharacterTalkableMessage {
    bool can;
};
struct CharacterTalkableMessageSubject : public base::core::Observable<const CharacterTalkableMessage&> {
    using Message = CharacterTalkableMessage;
};
struct CharacterTalkableMessageListener : public base::core::Observer<const CharacterTalkableMessage&> {
    using Message = CharacterTalkableMessage;
};
}
#endif // !RATCHET_ACTOR_CHARACTER_CHARACTER_DEFINE_H