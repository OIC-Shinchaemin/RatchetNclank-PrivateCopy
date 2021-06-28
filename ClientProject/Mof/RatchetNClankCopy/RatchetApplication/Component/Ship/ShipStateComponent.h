#ifndef RATCHET_COMPONENT_SHIP_SHIP_STATE_COMPONENT_H
#define RATCHET_COMPONENT_SHIP_SHIP_STATE_COMPONENT_H


#include "../ActionStateComponent.h"

#include "../../State/ShipActionStateDefine.h"


namespace ratchet { namespace component { namespace ship {
class ShipStateComponent : public ratchet::component::ActionStateComponent {
    using super = ratchet::component::ActionStateComponent;
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
    bool CanTransition(std::string_view next) const;
#ifdef _DEBUG
    virtual bool DebugRender(void) override;
#endif // _DEBUG
};}}
}
#endif // !RATCHET_COMPONENT_SHIP_SHIP_STATE_COMPONENT_H