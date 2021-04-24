#ifndef STATE_ENEMY_MOTION_ATTACK_STATE_H
#define STATE_ENEMY_MOTION_ATTACK_STATE_H


#include "EnemyMotionState.h"

#include <memory>

#include "../../Component/Enemy/EnemyMeleeAttackComponent.h"


namespace state {
class EnemyMotionAttackState : public state::EnemyMotionState {
    using super = state::EnemyMotionState;
private:
    //! 攻撃
    std::weak_ptr<my::EnemyMeleeAttackComponent> _attack_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyMotionAttackState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyMotionAttackState();
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
#endif // !STATE_ENEMY_MOTION_ATTACK_STATE_H