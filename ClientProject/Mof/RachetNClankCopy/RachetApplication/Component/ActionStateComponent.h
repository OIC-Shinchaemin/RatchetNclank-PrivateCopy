#ifndef MY_ACTION_STATE_COMPONENT_H
#define MY_ACTION_STATE_COMPONENT_H


#include "UpdateComponent.h"

#include <string_view>

#include "My/Core/StateMachine.h"
#include "../State/ActionState.h"


namespace my {
class ActionStateComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
protected:
    //! 状態
    my::StateMachine _state_machine;
    //! ステート,コンポーネント
    std::unordered_map<std::string, std::string> _action_map;
    /// <summary>
    /// 登録
    /// </summary>
    /// <typeparam name="State"></typeparam>
    /// <param name="out"></param>
    void RegisterState(my::StateMachine& out, std::shared_ptr<my::ActionComponent> com) {
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChangeState(const std::string& name);
};
}
#endif // !MY_ACTION_STATE_COMPONENT_H