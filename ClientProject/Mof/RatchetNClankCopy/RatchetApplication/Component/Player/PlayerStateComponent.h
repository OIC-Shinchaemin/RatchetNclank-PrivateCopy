#ifndef RATCHET_COMPONENT_PLAYER_PLAYER_STATE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_PLAYER_STATE_COMPONENT_H


#include "../ActionStateComponent.h"

#include "../../State/PlayerActionStateDefine.h"


namespace ratchet {
namespace component {
namespace player {
class PlayerStateComponent : public ratchet::component::ActionStateComponent {
    using super = ratchet::component::ActionStateComponent;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerStateComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerStateComponent(const PlayerStateComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerStateComponent();
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
};
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_PLAYER_STATE_COMPONENT_H