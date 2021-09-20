#ifndef RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H
#define RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H


#include "Event.h"

#include "Base/Core/Timer.h"
#include "EnemyViewEvent.h"


namespace ratchet::event {
class PlayerActionAfterGettingOffElevatorEvent : 
    public ratchet::event::Event,
    public ratchet::event::EnemyViewEventEndMessageListener {
    using super = ratchet::event::Event;
private:
    //! �A�N�e�B�u
    bool _active;
    //! ����
    float _time_set;
    //! �^�C�}�[
    base::core::Timer _timer;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerActionAfterGettingOffElevatorEvent();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~PlayerActionAfterGettingOffElevatorEvent();
    /// <summary>
    /// �ʒm�C�x���g
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::event::EnemyViewEventEndMessage& message) override;
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
#endif // !RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H