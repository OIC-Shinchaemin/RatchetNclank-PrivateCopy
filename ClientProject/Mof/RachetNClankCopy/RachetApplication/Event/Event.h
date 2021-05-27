#ifndef MY_EVENT_H
#define MY_EVENT_H


#include <memory>


namespace my {
class Event : public std::enable_shared_from_this<my::Event> {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Event();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Event();
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
};
}
#endif // !MY_EVENT_H