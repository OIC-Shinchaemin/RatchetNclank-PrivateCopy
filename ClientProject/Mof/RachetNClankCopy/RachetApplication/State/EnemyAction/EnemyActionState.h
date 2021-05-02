#ifndef STATE_ENEMY_ACTION_STATE_H
#define STATE_ENEMY_ACTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include <Mof.h>

#include "EnemyActionStateDefine.h"
#include "../../Actor.h"
#include "../../Component/Enemy/EnemyStateComponent.h"


namespace state {
class EnemyActionState : public my::State {
private:
    //! アクター
    std::weak_ptr<my::Actor> _actor;
    //! 状態
    std::weak_ptr<my::EnemyStateComponent> _state_com;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor>GetActor(void) const;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    bool ChangeState(const char* next) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyActionState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyActionState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
};
}
#endif // !STATE_ENEMY_ACTION_STATE_H