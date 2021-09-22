#ifndef RATCHET_EVENT_MANAGER_H
#define RATCHET_EVENT_MANAGER_H


#include <memory>

#include "Event.h"
#include "EventReferenceTable.h"


namespace ratchet ::event {
class EventManager :
    public std::enable_shared_from_this<ratchet::event::EventManager>,
    public base::core::Observer<const char*, const std::shared_ptr<ratchet::event::Event>&> {
private:
    //! �Q�[���C�x���g
    std::vector<std::shared_ptr<ratchet::event::Event>> _events;
    //! �ǉ�
    std::vector<std::shared_ptr<ratchet::event::Event>> _created_events;
    //! �폜
    std::vector<std::shared_ptr<ratchet::event::Event>> _delete_events;
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
    virtual void OnNotify(const char* type, const std::shared_ptr<ratchet::event::Event>& ptr) override;
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    //void AddElement(const std::shared_ptr<ratchet::event::Event>& ptr);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="ptr"></param>
    //void RemoveElement(const std::shared_ptr<ratchet::event::Event>& ptr);
    /// <summary>
    /// �쐬
    /// </summary>
    template<typename Event>
    std::shared_ptr<Event> CreateGameEvent(void) {
        auto ptr = std::make_shared<Event>();
        ptr->GetSubject()->AddObserver(shared_from_this());
        this->_events.push_back(ptr);
        //this->OnNotify("AddRequest", ptr);
        return ptr;
    }
    template<typename T>
    std::shared_ptr<T>GetEvent(void) const {
        for (auto& e : _events) {
            auto ret = std::dynamic_pointer_cast<T>(e);
            if (ret) {
                return ret;
            } // if
        } // for
        return nullptr;
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
#endif // !RATCHET_EVENT_MANAGER_H