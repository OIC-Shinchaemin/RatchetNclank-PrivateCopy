#ifndef RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H
#define RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H


#include "Event.h"

#include <optional>

#include "Base/Core/Timer.h"
#include "EnemyViewEvent.h"


namespace ratchet::event {
struct PlayerActionAfterGettingOffElevatorEventEndMessage {
};
using PlayerActionAfterGettingOffElevatorEventEndSubject = base::core::Observable<const PlayerActionAfterGettingOffElevatorEventEndMessage&>;
using PlayerActionAfterGettingOffElevatorEventEndListener = base::core::Observer<const  PlayerActionAfterGettingOffElevatorEventEndMessage&>;

class PlayerActionAfterGettingOffElevatorEvent :
    public ratchet::event::Event,
    public ratchet::event::EnemyViewEventEndMessageListener {
    using super = ratchet::event::Event;
private:
    //! �A�N�e�B�u
    bool _active;
    //! �v���C���[�ʒm�p    
    PlayerActionAfterGettingOffElevatorEventEndSubject _player_action_after_getting_off_elevator_event_end_subject;
    //! ����
    float _start_time_set;
    //! ����
    float _time_set;
    //! �^�C�}�[
    std::optional<base::core::Timer > _start_timer;
    //! �^�C�}�[
    base::core::Timer _timer;
    //! ��������
    float _front_angle;
    //! ��������
    float _start_camera_angle;
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetPlayerActionAfterGettingOffElevatorEventEndSubject(void) {
        return &this->_player_action_after_getting_off_elevator_event_end_subject;
    };
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