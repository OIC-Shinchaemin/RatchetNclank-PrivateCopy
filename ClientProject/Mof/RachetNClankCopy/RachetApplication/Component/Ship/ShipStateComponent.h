#ifndef MY_SHIP_STATE_COMPONENT_H
#define MY_SHIP_STATE_COMPONENT_H


#include "../UpdateComponent.h"

#include <string_view>

#include "My/Core/StateMachine.h"
#include "../../State/ActionState.h"
#include "../../State/ShipActionStateDefine.h"


namespace my {
class ShipStateComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! 状態
    my::StateMachine _state_machine;
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
    ShipStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ShipStateComponent(const ShipStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ShipStateComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="param"></param>
    virtual void SetParam(const rapidjson::Value& param) override;
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
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool CanTransition(std::string_view next) const;
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};
}
#endif // !MY_SHIP_STATE_COMPONENT_H