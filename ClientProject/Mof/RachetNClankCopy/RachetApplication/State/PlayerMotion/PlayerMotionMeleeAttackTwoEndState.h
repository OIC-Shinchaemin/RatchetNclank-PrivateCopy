#ifndef STATE_PLAYER_MOTION_MELEE_ATTACK_TWO_END_STATE_H
#define STATE_PLAYER_MOTION_MELEE_ATTACK_TWO_END_STATE_H


#include "PlayerMotionState.h"


namespace state {
class PlayerMotionMeleeAttackTwoEndState : public state::PlayerMotionState {
    using super = state::PlayerMotionState;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerMotionMeleeAttackTwoEndState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMotionMeleeAttackTwoEndState();
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
#endif // !STATE_PLAYER_MOTION_MELEE_ATTACK_TWO_END_STATE_H