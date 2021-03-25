#ifndef MY_OBSERVABLE_H
#define MY_OBSERVABLE_H


#include <any>
#include <memory>
#include <vector>

#include "My/Core/Utility.h"
#include "My/Core/Observer.h"


namespace my {
template<class Derived>
class Observable {
    using Observer = my::Observer<Derived>;
private:
    //! �I�u�U�[�o
    std::vector<std::weak_ptr<Observer>> _observers;
protected:
    /// <summary>
    /// �ʒm
    /// </summary>
    /// <param name="data"></param>
    /// <param name="event"></param>
    void Notify(const std::shared_ptr<Derived>& shared_this, const char* event);
//    void Notify(const std::shared_ptr<Derived>& shared_this, const char* event, std::any);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Observable();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Observable();
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="observer"></param>
    void AddObserver(const std::shared_ptr<Observer>& observer);
    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="observer"></param>
    void RemoveObserver(const std::shared_ptr<Observer>& observer);
};
template<class Derived>
inline void Observable<Derived>::Notify(const std::shared_ptr<Derived>& shared_this, const char* event) {
    auto& o = _observers;
    std::for_each(o.begin(), o.end(), [&](std::weak_ptr<Observer> weak) {
        if (auto ptr = weak.lock()) {
            ptr->OnNotify(shared_this, event);
        } // if
    });
}
template<class Derived>
inline Observable<Derived>::Observable() {
}
template<class Derived>
inline Observable<Derived>::~Observable() {
}
template<class Derived>
inline void Observable<Derived>::AddObserver(const std::shared_ptr<Observer>& observer) {
    _observers.push_back(observer);
}
template<class Derived>
inline void Observable<Derived>::RemoveObserver(const std::shared_ptr<Observer>& observer) {
    ut::EraseRemove(_observers, [observer](const std::weak_ptr<Observer>& weak) {
        if (auto ptr = weak.lock()) {
            return ptr == observer;
        } // if
        return false;
    });
}
}
#endif // !MY_OBSERVABLE_H