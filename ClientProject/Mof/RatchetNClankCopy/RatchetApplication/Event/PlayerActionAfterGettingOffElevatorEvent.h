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
    //! アクティブ
    bool _active;
    //! 時間
    float _time_set;
    //! タイマー
    base::core::Timer _timer;
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