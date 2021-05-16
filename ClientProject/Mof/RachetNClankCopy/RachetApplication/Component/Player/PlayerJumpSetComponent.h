#ifndef MY_PLAYER_JUMP_SET_COMPONENT_H
#define MY_PLAYER_JUMP_SET_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerJumpSetComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! ジャンプ
    float _jump_speed;
    //! ジャンプ
    float _jump_speed_first;
    //! ジャンプ
    float _jump_speed_increase;
    //! モーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! 移動
    std::weak_ptr<class PlayerJumpUpComponent> _jump_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpSetComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpSetComponent(const PlayerJumpSetComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerJumpSetComponent();
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
#endif // !MY_PLAYER_JUMP_SET_COMPONENT_H