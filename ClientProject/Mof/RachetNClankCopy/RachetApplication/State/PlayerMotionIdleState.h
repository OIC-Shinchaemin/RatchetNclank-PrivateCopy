#ifndef STATE_PLAYER_MOTION_IDLE_STATE_H
#define STATE_PLAYER_MOTION_IDLE_STATE_H


#include "PlayerMotionState.h"


namespace state {
class PlayerMotionIdleState : public state::PlayerMotionState {
    using super = state::PlayerMotionState;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerMotionIdleState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMotionIdleState();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetName(void) const override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Update(float delta_time) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    virtual void Enter(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    virtual void Exit(void) override;
};
}
#endif // !STATE_PLAYER_MOTION_IDLE_STATE_H