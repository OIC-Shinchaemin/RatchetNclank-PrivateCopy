#ifndef MY_OBSERVER_H
#define MY_OBSERVER_H


#include <memory>


namespace my {
template<class Observable>
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