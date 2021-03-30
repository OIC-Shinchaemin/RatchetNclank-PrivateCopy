#ifndef MY_OBSERVER_H
#define MY_OBSERVER_H


namespace my {
template<class...NotifyArgs>
class Observer {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Observer();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Observer();
    /// <summary>
    /// �ʒm�C�x���g
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
#endif // !MY_OBSERVER_H