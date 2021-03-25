#ifndef MY_OBSERVER_H
#define MY_OBSERVER_H


#include <memory>


namespace my {
template<class Observable>
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
    /// <param name="observable"></param>
    /// <param name="event"></param>
    virtual void OnNotify(const std::shared_ptr<Observable>& observable, const char* event) = 0;
};
template<class Observable>
inline Observer<Observable>::Observer() {
}
template<class Observable>
inline Observer<Observable>::~Observer() {
}
}
#endif // !MY_OBSERVER_H