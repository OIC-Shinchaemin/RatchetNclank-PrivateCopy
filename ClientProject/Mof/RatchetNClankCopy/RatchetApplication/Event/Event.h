#ifndef RATCHET_EVENT_H
#define RATCHET_EVENT_H


#include "Base/Core/Observable.h"

#include <memory>


namespace ratchet {
namespace event {
class Event : public std::enable_shared_from_this<ratchet::event::Event> {
protected:
    //! �ʒm�p
    base::core::Observable<const char*, const std::shared_ptr<ratchet::event::Event>&> _subject;
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    base::core::Observable<const char*, const std::shared_ptr<ratchet::event::Event>&>* GetSubject(void);
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
}
#endif // !RATCHET_EVENT_H