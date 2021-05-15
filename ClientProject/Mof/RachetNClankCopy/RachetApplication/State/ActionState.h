#ifndef STATE_ACTION_STATE_H
#define STATE_ACTION_STATE_H


#include "My/Core/State.h"

#include <memory>

#include "../Actor.h"
#include "../Component/ActionComponent.h"
#include "../Component/ActionStateComponent.h"


namespace state {
class ActionState : public my::State {
private:
    //! アクター
    std::weak_ptr<my::Actor> _actor;
    //! アクション
    std::weak_ptr<my::ActionComponent> _action_com;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::Actor>GetActor(void) const;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ActionState();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActionState();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActor(const std::shared_ptr<my::Actor>& ptr);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    virtual void SetActionComponent(const std::shared_ptr<my::ActionComponent>& ptr);
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
#endif // !STATE_PLAYER_ACTION_STATE_H