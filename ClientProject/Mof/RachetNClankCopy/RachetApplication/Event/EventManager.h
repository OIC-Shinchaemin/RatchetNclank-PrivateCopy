#ifndef MY_EVENT_MANAGER_H
#define MY_EVENT_MANAGER_H


namespace my {
class EventManager {
private:
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EventManager();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~EventManager();
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
};
}
#endif // !MY_EVENT_MANAGER_H