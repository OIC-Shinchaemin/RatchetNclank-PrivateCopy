#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_ACTION_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_ACTION_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../../Gamepad.h"
#include "../VelocityComponent.h"
#include "PlayerStateComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/PlayerActionStateDefine.h"
#include "../../State/PlayerMotionStateDefine.h"


namespace ratchet {
namespace component {
namespace player {
namespace action {
class PlayerActionComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
    //! 速度
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<ratchet::component::player::PlayerStateComponent> _state_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::component::VelocityComponent> GetVelocityComponent(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsEndMotion(void) const;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    bool CanTransitionActionState(const std::string& next) const;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    bool ChangeActionState(const std::string& name);
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    bool ChangeMotionState(const std::string& name);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerActionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerActionComponent(const PlayerActionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerActionComponent();
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
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_ACTION_COMPONENT_H