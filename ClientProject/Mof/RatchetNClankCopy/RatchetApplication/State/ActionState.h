#ifndef RATCHET_STATE_ACTION_STATE_H
#define RATCHET_STATE_ACTION_STATE_H


#include "Base/Core/State.h"

#include <memory>

#include "../Component/ActionComponent.h"


namespace ratchet {
namespace state {
class ActionState : public base::core::State {
private:
    //! アクション
    std::weak_ptr<ratchet::component::ActionComponent> _action_com;
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
    virtual void SetActionComponent(const std::shared_ptr<ratchet::component::ActionComponent>& ptr);
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
}
#endif // !RATCHET_STATE_PLAYER_ACTION_STATE_H