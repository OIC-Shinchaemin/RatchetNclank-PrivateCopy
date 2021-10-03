#ifndef BASE_CORE_OBSERVER_H
#define BASE_CORE_OBSERVER_H


namespace base::core {
template<class...NotifyArgs>
class Observer {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Observer();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Observer();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="..."></param>
    virtual void OnNotify(NotifyArgs...) = 0;
};
template<class ...NotifyArgs>
inline Observer<NotifyArgs...>::Observer() {
}
template<class ...NotifyArgs>
inline Observer<NotifyArgs...>::~Observer() {
}
}
#endif // !BASE_CORE_OBSERVER_H