#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_UP_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_UP_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace ratchet ::component ::player::action {
class PlayerJumpUpComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    using This = ratchet::component::player::action::PlayerJumpUpComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;

        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
        }
    };
private:
    //! 力
    float _jump_speed;
    //! 減少
    float _jump_decrase;
    //! 速さ
    float _move_speed;
    //! 速さ
    float _angular_speed;
    //!  下降
    float _gravity_down;
    //! 強制的向く方向
    std::optional<float> _force_move_radian_angle;
    //! 入力情報
    This::InputInfo _input_info;
    //! 移動
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    /// <summary>
    /// ジャンプ速度入力
    /// </summary>
    /// <param name="speed"></param>
    virtual void InputJumpVelocity(float speed);
public:
    //! アクセッサ
    base::accessor::Accessor<decltype(_force_move_radian_angle)> force_move_radian_angle = _force_move_radian_angle;
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpUpComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpUpComponent(const PlayerJumpUpComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerJumpUpComponent();
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
    /// <param name="scalar"></param>
    void SetMoveSpeed(float scalar);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="scalar"></param>
    void SetAngularSpeed(float scalar);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetJumpSpeed(float scalar);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetGravityDown(float scalar);
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_UP_COMPONENT_H