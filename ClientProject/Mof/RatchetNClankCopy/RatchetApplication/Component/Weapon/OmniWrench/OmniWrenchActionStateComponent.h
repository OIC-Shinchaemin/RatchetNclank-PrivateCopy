#ifndef RATCHET_OMNI_WRENCH_ACTION_STATE_COMPONENT_H
#define RATCHET_OMNI_WRENCH_ACTION_STATE_COMPONENT_H


#include "../../ActionStateComponent.h"

#include "../../../State/OmniWrenchActionStateDefine.h"


namespace ratchet {
class OmniWrenchActionStateComponent : public ratchet::ActionStateComponent {
    using super = ratchet::ActionStateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    OmniWrenchActionStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    OmniWrenchActionStateComponent(const OmniWrenchActionStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~OmniWrenchActionStateComponent();
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
};
}
#endif // !RATCHET_OMNI_WRENCH_ACTION_STATE_COMPONENT_H