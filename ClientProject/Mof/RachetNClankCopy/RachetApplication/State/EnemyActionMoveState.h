#ifndef STATE_ENEMY_ACTION_MOVE_STATE_H
#define STATE_ENEMY_ACTION_MOVE_STATE_H


#include "EnemyActionState.h"

#include "../Component/Enemy/EnemyIdleComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyAttackComponent.h"


namespace state {
class EnemyActionMoveState : public state::EnemyActionState {
    using super = state::EnemyActionState;
private:
    //! 待機
    std::weak_ptr<my::EnemyIdleComponent> _idle_com;
    //! 移動
    std::weak_ptr<my::EnemyMoveComponent> _move_com;
    //! 攻撃
    std::weak_ptr<my::EnemyAttackComponent> _attack_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyActionMoveState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyActionMoveState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr) override;
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
#endif // !STATE_ENEMY_ACTION_MOVE_STATE_H