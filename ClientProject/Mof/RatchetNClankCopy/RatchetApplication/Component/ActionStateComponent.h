#ifndef RATCHET_COMPONENT_ACTION_STATE_COMPONENT_H
#define RATCHET_COMPONENT_ACTION_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include <optional>
#include <string>
#include <string_view>

#include "Base/Core/StateMachine.h"
#include "../State/ActionState.h"


namespace ratchet::component {
class ActionStateComponent : public ratchet::component::UpdateComponent {
    using super = ratchet::component::UpdateComponent;
private:
    //! 予約
    std::optional<std::string> _next_state;
protected:
    //! 状態
    base::core::StateMachine _state_machine;
    //! ステート,コンポーネント
    std::unordered_map<std::string, std::string> _action_map;
    /// <summary>
    /// 登録
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    void RegisterState(base::core::StateMachine& out, std::shared_ptr<ratchet::component::ActionComponent> com) {
        auto shared_this = super::GetOwner();
        auto ptr = std::make_shared<state::ActionState>();
        ptr->SetActionComponent(com);
        out.RegisterState(ptr);
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    ActionStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ActionStateComponent(const ActionStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActionStateComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const char* GetCurrentState(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="state"></param>
    /// <returns></returns>
    bool IsEqual(std::string_view state) const;
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
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
};
}
#endif // !RATCHET_COMPONENT_ACTION_STATE_COMPONENT_H