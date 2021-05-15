#ifndef STATE_ENEMY_ACTION_GO_HOME_STATE_H
#define STATE_ENEMY_ACTION_GO_HOME_STATE_H


#include "EnemyActionState.h"

#include "../../Component/Enemy/EnemyGoHomeComponent.h"


namespace state {
class EnemyActionGoHomeState : public state::EnemyActionState {
    using super = state::EnemyActionState;
private:
    //! 移動
    std::weak_ptr<my::EnemyGoHomeComponent> _move_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyActionGoHomeState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyActionGoHomeState();
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
#endif // !STATE_ENEMY_ACTION_GO_HOME_STATE_H