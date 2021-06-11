#ifndef RATCHET_NanotechItem_ACTION_STATE_COMPONENT_H
#define RATCHET_NanotechItem_ACTION_STATE_COMPONENT_H


#include "../../ActionStateComponent.h"

#include "../../../State/NanotechItemActionStateDefine.h"


namespace ratchet {
class NanotechItemActionStateComponent : public ratchet::ActionStateComponent {
    using super = ratchet::ActionStateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    NanotechItemActionStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    NanotechItemActionStateComponent(const NanotechItemActionStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NanotechItemActionStateComponent();
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
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
#endif // !RATCHET_NanotechItem_ACTION_STATE_COMPONENT_H