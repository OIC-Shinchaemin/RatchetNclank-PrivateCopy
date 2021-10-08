#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_DEFINE_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_DEFINE_H


#include "Base/Core/Observable.h"
#include "Base/Core/Observer.h"
#include "../../../MessageObservation.h"


namespace ratchet::game::gamesystem::text {
enum class TextEventType {
    TutorialEventNo0,
    TutorialEventNo1,
    TutorialEventNo0End,
    TutorialEventNo1End,
    KingTextEvent,
    KingFreeTalkTextEvent,
    QueenTextEvent,
    QueenFreeTalkTextEvent,

    TeachPlazaEvent,
    ItemCollectionCompleteEvent,
};

// リクエスト
struct TextSystemMessage {
    using CloseEvent = std::function<bool(void)>;
    TextEventType type;
    std::optional<CloseEvent> on_close;
};
using TextSystemMessageSubject = base::core::Observable<const TextSystemMessage&>;
using TextSystemMessageListener = base::core::Observer<const TextSystemMessage&>;

struct TextSystemClosedMessage {
    bool close = false;
};

struct TextSystemClosedMessageSubject : public base::core::Observable<const TextSystemClosedMessage&> {
    using Message = const TextSystemClosedMessage&;
};
struct TextSystemClosedMessageListener : public base::core::Observer<const TextSystemClosedMessage&> {
    using Message = const TextSystemClosedMessage&;
};
using TextSystemClosedMessageObservation = MessageObservation<TextSystemClosedMessageSubject, TextSystemClosedMessageListener>;

struct TextSystemOpenMessage {
};
struct TextSystemOpenMessageSubject : public base::core::Observable<const TextSystemOpenMessage&> {
    using Message = const TextSystemOpenMessage&;
};
struct TextSystemOpenMessageListener : public base::core::Observer<const TextSystemOpenMessage&> {
    using Message = const TextSystemOpenMessage&;
};

using TextSystemOpenMessageObservation = MessageObservation<TextSystemOpenMessageSubject, TextSystemOpenMessageListener>;


}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_DEFINE_H