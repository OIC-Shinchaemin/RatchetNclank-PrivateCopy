#ifndef RATCHET_MESSAGE_OBSERVATION_H
#define RATCHET_MESSAGE_OBSERVATION_H


#include <memory>
#include <vector>

#include "Base/Core/Observable.h"
#include "Base/Core/Observer.h"


namespace ratchet {
template<typename SubjectType, typename ListenerType>
class MessageObservation {
public:
    using Subject = SubjectType;
    using Listener = ListenerType;
private:
    //! ŠÄ‹‘ÎÛ
    std::vector<std::shared_ptr<Subject>> _subjects;
    //! ŠÄ‹Ò
    std::vector<std::shared_ptr<Listener>> _listeners;
public:
    /// <summary>
    /// ƒVƒ“ƒOƒ‹ƒgƒ“
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    static MessageObservation& Singleton(void) {
        static MessageObservation instance;
        return instance;
    }
    std::shared_ptr<Subject> CreateSubject(void) {
        auto ret = std::make_shared<Subject>();
        _subjects.push_back(ret);
        for (auto& listener : _listeners) {
            ret->AddObserver(listener);
        } // for
        return ret;
    }
    void LinkObservation(const std::shared_ptr<Listener>& observer) {
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
#endif // !RATCHET_MESSAGE_OBSERVATION_H