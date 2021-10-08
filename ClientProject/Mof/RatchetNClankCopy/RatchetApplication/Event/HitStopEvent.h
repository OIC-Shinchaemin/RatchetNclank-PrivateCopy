#ifndef RATCHET_EVENT_HIT_STOP_EVENT_H
#define RATCHET_EVENT_HIT_STOP_EVENT_H


#include "Event.h"
#include "Base/Core/Observable.h"

#include <memory>


#include "Base/Core/ServiceLocator.h"
#include "../Scene/GameScene.h"


namespace ratchet::event {
class HitStopEvent : public ratchet::event::Event {
    using super = ratchet::event::Event;
private:
    //! ��~����
    float _time;
    //! �^�C�}�[
    base::core::Timer _timer;
    //! ������
    std::weak_ptr<ratchet::scene::GameScene> _game_scene;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    HitStopEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~HitStopEvent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    void SetGameScene(const std::shared_ptr<ratchet::scene::GameScene> ptr) {
        this->_game_scene = ptr;
    }
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
#endif // !RATCHET_EVENT_HIT_STOP_EVENT_H