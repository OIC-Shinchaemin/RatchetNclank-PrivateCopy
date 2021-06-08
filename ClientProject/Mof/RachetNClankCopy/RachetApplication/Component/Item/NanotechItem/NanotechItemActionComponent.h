#ifndef MY_NanotechItem_ACTION_COMPONENT_H
#define MY_NanotechItem_ACTION_COMPONENT_H


#include "../../ActionComponent.h"

#include <memory>

#include "../../VelocityComponent.h"
#include "NanotechItemActionStateComponent.h"
#include "../../../State/NanotechItemActionStateDefine.h"


namespace my {
class NanotechItemActionComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! 速度
    std::weak_ptr<my::VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<my::NanotechItemActionStateComponent> _state_com;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<my::VelocityComponent> GetVelocityComponent(void) const;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    bool ChangeActionState(const std::string& name);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemActionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemActionComponent(const NanotechItemActionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NanotechItemActionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 解放
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
};
}
#endif // !MY_NanotechItem_ACTION_COMPONENT_H