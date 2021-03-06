#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_CARTWHEEL_JUMP_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_CARTWHEEL_JUMP_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace ratchet {
namespace component {
namespace player {
namespace action {
class PlayerCartwheelJumpComponent : public ratchet::component::player::action::PlayerActionComponent {
    using super = ratchet::component::player::action::PlayerActionComponent;
private:
    //! 速度
    float _jump_speed;
    //! 減少
    float _jump_decrase;
    //! 方向
    float _move_angle;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name="speed"></param>
    virtual void InputJumpVelocity(float speed);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerCartwheelJumpComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerCartwheelJumpComponent(const PlayerCartwheelJumpComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerCartwheelJumpComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string_view GetStateType(void) const override;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetJumpSpeed(float speed);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetMoveAngle(float radian);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time">時間</param>
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
    virtual std::shared_ptr<::ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_CARTWHEEL_JUMP_COMPONENT_H