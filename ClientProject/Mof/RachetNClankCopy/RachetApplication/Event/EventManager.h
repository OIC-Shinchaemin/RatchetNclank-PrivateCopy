#ifndef MY_EVENT_MANAGER_H
#define MY_EVENT_MANAGER_H


#include <memory>

#include "Event.h"
#include "EventReferenceTable.h"


namespace my {
class EventManager : 
    public std::enable_shared_from_this<my::EventManager>,
    public my::Observer<const char*, const std::shared_ptr<my::Event>&> {
private:
    //! �Q�[���C�x���g
    std::vector<std::shared_ptr<my::Event>> _events;
    //! �f�[�^
    //my::EventReferenceTable _table;
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
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name=""></param>
    /// <param name=""></param>
    virtual void OnNotify(const char* type, const std::shared_ptr<my::Event>& ptr) override;
    /// <summary>
    /// �쐬
    /// </summary>
    template<typename Event>
    std::shared_ptr<Event> CreateGameEvent(void) {
        auto ptr = std::make_shared<Event>();
        ptr->GetSubject()->AddObserver(shared_from_this());
        this->_events.push_back(ptr);
        return ptr;
    }
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool InitializeGameEvent(void);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    bool Update(float delta_time);
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Release(void);
};
}
#endif // !MY_EVENT_MANAGER_H