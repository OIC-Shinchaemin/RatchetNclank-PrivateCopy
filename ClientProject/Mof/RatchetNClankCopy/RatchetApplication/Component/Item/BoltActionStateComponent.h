#ifndef RATCHET_COMPONENT_ITEM_BOLT_ACTION_STATE_COMPONENT_H
#define RATCHET_COMPONENT_ITEM_BOLT_ACTION_STATE_COMPONENT_H


#include "../ActionStateComponent.h"

#include "../../State/BoltActionStateDefine.h"


namespace ratchet { namespace component { namespace item { 
class BoltActionStateComponent : public ratchet::component::ActionStateComponent {
    using super = ratchet::component::ActionStateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BoltActionStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BoltActionStateComponent(const BoltActionStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BoltActionStateComponent();
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
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="name"></param>
    /// <returns></returns>
    bool CanTransition(const std::string& next);
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};}}
}
#endif // !RATCHET_COMPONENT_ITEM_BOLT_ACTION_STATE_COMPONENT_H