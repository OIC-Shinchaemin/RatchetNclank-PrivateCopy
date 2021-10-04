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
    //std::vector<std::shared_ptr<Subject>> _subjects;
    std::vector<std::weak_ptr<Subject>> _subjects;
    //! ŠÄ‹Ò
    std::vector<std::weak_ptr<Listener>> _listeners;
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
        for (auto weak : _listeners) {
            if (auto listener = weak.lock()) {
                ret->AddObserver(listener);
            } // if
        } // for
        return ret;
    }
    void LinkObservation(const std::shared_ptr<Listener>& observer) {
        _listeners.push_back(observer);
        for (auto weak : _subjects) {
            if (auto subject = weak.lock()) {
                subject->AddObserver(observer);
            } // if
        } // for
    }
    void Clear(void) {
        for (auto weak : _subjects) {
            if (auto subject = weak.lock()) {
                subject->Clear();
            } // if
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