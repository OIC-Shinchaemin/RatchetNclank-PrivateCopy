#ifndef RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H
#define RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H


#include "Event.h"

#include <optional>

#include "Base/Core/Timer.h"
#include "EnemyViewEvent.h"


namespace ratchet::event {
/*
struct PlayerActionAfterGettingOffElevatorEventEndMessage {
};
using PlayerActionAfterGettingOffElevatorEventEndSubject = base::core::Observable<const PlayerActionAfterGettingOffElevatorEventEndMessage&>;
using PlayerActionAfterGettingOffElevatorEventEndListener = base::core::Observer<const  PlayerActionAfterGettingOffElevatorEventEndMessage&>;
*/
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
    //! �^�C�}�[
    base::core::Timer _timer;
    //! �f�t�H���g�l
    float _default_jump_set_first_speed;
    //! �f�t�H���g�l
    float _default_jump_up_move_speed;
    //! �f�t�H���g�l
    float _default_jump_up_angular_speed;
    //! �f�t�H���g�l
    float _default_jump_up_gravity;
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
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    void Start(void);
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