#ifndef RATCHET_SHIP_ACTION_COMPONENT_H
#define RATCHET_SHIP_ACTION_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../../Gamepad.h"
#include "../VelocityComponent.h"
#include "ShipStateComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../../State/ShipActionStateDefine.h"
#include "../../State/ShipMotionStateDefine.h"


namespace ratchet {
class ShipActionComponent : public ratchet::ActionComponent {
    using super = ratchet::ActionComponent;
private:
    //! 速度
    std::weak_ptr<ratchet::VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<ratchet::ShipStateComponent> _state_com;
    //! モーション
    std::weak_ptr<ratchet::MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<ratchet::MotionStateComponent> _motion_state_com;
protected:
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    std::shared_ptr<ratchet::VelocityComponent> GetVelocityComponent(void) const;
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
    ShipActionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    ShipActionComponent(const ShipActionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ShipActionComponent();
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
#endif // !RATCHET_SHIP_ACTION_COMPONENT_H