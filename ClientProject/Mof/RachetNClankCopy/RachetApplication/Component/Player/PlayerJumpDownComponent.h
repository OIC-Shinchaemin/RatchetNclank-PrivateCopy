#ifndef MY_PLAYER_JUMP_DOWN_COMPONENT_H
#define MY_PLAYER_JUMP_DOWN_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerJumpDownComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! 最大
    float _jump_speed_max;
    //! 速度
    float _jump_speed;
    //! 減少
    float _jump_decrase;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;     
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpDownComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpDownComponent(const PlayerJumpDownComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerJumpDownComponent();
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
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !MY_PLAYER_JUMP_DOWN_COMPONENT_H