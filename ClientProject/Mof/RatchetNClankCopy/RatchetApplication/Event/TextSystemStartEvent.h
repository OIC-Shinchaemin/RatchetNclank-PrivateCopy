#ifndef RATCHET_EVENT_TEXT_SYSTEM_START_EVENT_H
#define RATCHET_EVENT_TEXT_SYSTEM_START_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>

#include "../Scene/GameScene.h"
#include "../Game/GameSystem/Text/TextSystem.h"
#include "StageViewEvent.h"


namespace ratchet::event {
class TextSystemStartEvent : public ratchet::event::Event {
    using super = ratchet::event::Event;
private:
    //! �J�n�܂ł̎���
    base::core::Timer _timer;
    //! �V�[��
    std::weak_ptr<scene::Scene> _scene;
    //! �e�L�X�g
    std::weak_ptr<ratchet::game::gamesystem::text::TextSystem> _text_system;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TextSystemStartEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    void SetGameScene(const std::shared_ptr<ratchet::scene::Scene>& ptr);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name=""></param>
    void SetTextSystem(const std::shared_ptr<ratchet::game::gamesystem::text::TextSystem>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_EVENT_TEXT_SYSTEM_START_EVENT_H