#ifndef BASE_CORE_OBSERVABLE_H
#define BASE_CORE_OBSERVABLE_H


#include <memory>
#include <vector>

#include "Utility.h"
#include "Observer.h"


namespace base {
namespace core {
template<class...NotifyArgs>
class Observable {
    //using Observer = base::core::Observer<NotifyArgs...>;
    using Observer = Observer<NotifyArgs...>;
private:
    //! オブザーバ
    std::vector<std::weak_ptr<Observer>> _observers;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Observable();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Observable();
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="observer"></param>
    void AddObserver(const std::shared_ptr<Observer>& observer);
    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="observer"></param>
    void RemoveObserver(const std::shared_ptr<Observer>& observer);
    /// <summary>
    /// 通知
    /// </summary>
    /// <param name="...args"></param>
    void Notify(NotifyArgs... args);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    void Clear(void) {
        _observers.clear();
    }
};
template<class ...NotifyArgs>
inline Observable<NotifyArgs...>::Observable() {
}

template<class ...NotifyArgs>
inline Observable<NotifyArgs...>::~Observable() {
}

template<class ...NotifyArgs>
inline void Observable<NotifyArgs...>::AddObserver(const std::shared_ptr<Observer>& observer) {
    _observers.push_back(observer);
}

template<class ...NotifyArgs>
inline void Observable<NotifyArgs...>::RemoveObserver(const std::shared_ptr<Observer>& observer) {
    ut::EraseRemove(_observers, [observer](const std::weak_ptr<Observer>& weak) {
        if (auto ptr = weak.lock()) {
            return ptr == observer;
        } // if
        return false;
    });
}
template<class ...NotifyArgs>
inline void Observable<NotifyArgs...>::Notify(NotifyArgs ...args) {
    auto& o = _observers;
    std::for_each(o.begin(), o.end(), [&](std::weak_ptr<Observer> weak) {
        if (auto ptr = weak.lock()) {
            ptr->OnNotify(args...);
        } // if
    });
}

}
}
#endif // !BASE_CORE_OBSERVABLE_H