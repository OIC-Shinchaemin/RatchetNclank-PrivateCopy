#ifndef MY_BOLT_ACTION_COMPONENT_H
#define MY_BOLT_ACTION_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../VelocityComponent.h"
#include "BoltActionStateComponent.h"
#include "../../State/BoltActionStateDefine.h"


namespace my {
class BoltActionComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! 速度
    std::weak_ptr<my::VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<my::BoltActionStateComponent> _state_com;
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
    BoltActionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BoltActionComponent(const BoltActionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BoltActionComponent();
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
#endif // !MY_BOLT_ACTION_COMPONENT_H