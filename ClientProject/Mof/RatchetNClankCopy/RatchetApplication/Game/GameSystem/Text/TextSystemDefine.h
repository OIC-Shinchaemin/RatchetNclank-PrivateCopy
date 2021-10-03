#ifndef RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_DEFINE_H
#define RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_DEFINE_H


#include "Base/Core/Observable.h"
#include "Base/Core/Observer.h"


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





struct TextSystemOpenMessage {
};
struct TextSystemOpenMessageSubject : public base::core::Observable<const TextSystemOpenMessage&> {
    using Message = const TextSystemOpenMessage&;
};
struct TextSystemOpenMessageListener : public base::core::Observer<const TextSystemOpenMessage&> {
    using Message = const TextSystemOpenMessage&;
};

class TextSystemOpenMessageObservation {
private:
    //! 監視対象
    std::vector<std::shared_ptr<TextSystemOpenMessageSubject>> _subjects;
    //! 監視者
    std::vector<std::shared_ptr<TextSystemOpenMessageListener>> _listeners;
public:
    /// <summary>
    /// シングルトン
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static TextSystemOpenMessageObservation& Singleton(void) {
        static TextSystemOpenMessageObservation instance;
        return instance;
    }
    TextSystemOpenMessage CreateMessage(void) {
        return TextSystemOpenMessage();
    }
    std::shared_ptr<TextSystemOpenMessageSubject> CreateSubject(void) {
        auto ret = std::make_shared<TextSystemOpenMessageSubject>();
        _subjects.push_back(ret);
        for (auto& listener : _listeners) {
            ret->AddObserver(listener);
        } // for
        return ret;
    }
    void LinkObservation(const std::shared_ptr<TextSystemOpenMessageListener>& observer) {
        _listeners.push_back(observer);
        for (auto& subject : _subjects) {
            subject->AddObserver(observer);
        } // for
    }
    void Clear(void) {
        for (auto& subject : _subjects) {
            subject->Clear();
        } // for
        for (auto& listener : _listeners) {
            //listener;
        } // for


        _subjects.clear();
        _listeners.clear();
    }
};
}
#endif // !RATCHET_GAME_GAME_SYSTEM_TEXT_TEXT_SYSTEM_DEFINE_H