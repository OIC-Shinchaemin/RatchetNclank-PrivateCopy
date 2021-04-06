#ifndef STATE_ENEMY_MOTION_MOVE_STATE_H
#define STATE_ENEMY_MOTION_MOVE_STATE_H


#include "EnemyMotionState.h"


namespace state {
class EnemyMotionMoveState : public state::EnemyMotionState {
    using super = state::EnemyMotionState;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyMotionMoveState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyMotionMoveState();
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
#endif // !STATE_ENEMY_MOTION_MOVE_STATE_H