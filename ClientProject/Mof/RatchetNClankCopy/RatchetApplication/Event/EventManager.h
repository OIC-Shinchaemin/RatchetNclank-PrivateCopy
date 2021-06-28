#ifndef RATCHET_EVENT_MANAGER_H
#define RATCHET_EVENT_MANAGER_H


#include <memory>

#include "Event.h"
#include "EventReferenceTable.h"


namespace ratchet {
namespace event {
class EventManager :
    public std::enable_shared_from_this<ratchet::event::EventManager>,
    public base::core::Observer<const char*, const std::shared_ptr<ratchet::event::Event>&> {
private:
    //! �Q�[���C�x���g
    std::vector<std::shared_ptr<ratchet::event::Event>> _events;
    //! �f�[�^
    //ratchet::EventReferenceTable _table;
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
    /// �쐬
    /// </summary>
    template<typename Event>
    std::shared_ptr<Event> CreateGameEvent(void) {
        auto ptr = std::make_shared<Event>();
        ptr->GetSubject()->AddObserver(shared_from_this());
        this->_events.push_back(ptr);
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
}
#endif // !RATCHET_EVENT_MANAGER_H