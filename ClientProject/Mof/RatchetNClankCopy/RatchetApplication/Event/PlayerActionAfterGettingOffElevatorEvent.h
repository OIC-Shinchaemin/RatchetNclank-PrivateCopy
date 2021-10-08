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
    //! アクティブ
    bool _active;
    //! 時間
    float _time_set;
    //! タイマー
    //! タイマー
    base::core::Timer _timer;
    //! デフォルト値
    float _default_jump_set_first_speed;
    //! デフォルト値
    float _default_jump_up_move_speed;
    //! デフォルト値
    float _default_jump_up_angular_speed;
    //! デフォルト値
    float _default_jump_up_gravity;
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
    /// 開始
    /// </summary>
    /// <param name=""></param>
    void Start(void);
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