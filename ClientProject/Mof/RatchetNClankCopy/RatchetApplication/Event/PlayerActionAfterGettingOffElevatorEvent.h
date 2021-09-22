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
    //! アクティブ
    bool _active;
    //! プレイヤー通知用    
    PlayerActionAfterGettingOffElevatorEventEndSubject _player_action_after_getting_off_elevator_event_end_subject;
    //! 時間
    float _start_time_set;
    //! 時間
    float _time_set;
    //! タイマー
    std::optional<base::core::Timer > _start_timer;
    //! タイマー
    base::core::Timer _timer;
    //! 歩く方向
    float _front_angle;
    //! 歩く方向
    float _start_camera_angle;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerActionAfterGettingOffElevatorEvent();
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~PlayerActionAfterGettingOffElevatorEvent();
    /// <summary>
    /// 通知イベント
    /// </summary>
    /// <param name="message"></param>
    virtual void OnNotify(const ratchet::event::EnemyViewEventEndMessage& message) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    auto GetPlayerActionAfterGettingOffElevatorEventEndSubject(void) {
        return &this->_player_action_after_getting_off_elevator_event_end_subject;
    };
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
};
}
#endif // !RATCHET_EVENT_PLAYER_ACTION_AFTER_GETTING_OFF_ELEVATOR_EVENT_H