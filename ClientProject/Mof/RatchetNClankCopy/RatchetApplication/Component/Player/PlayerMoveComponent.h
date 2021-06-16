#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_MOVE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_MOVE_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>

#include "../CameraComponent.h"


namespace ratchet {
namespace component {
namespace player {
class PlayerComponent;
namespace action {
class PlayerMoveComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;
        bool jump_flag = false;
        bool attack_flag = false;

        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
            jump_flag = false;
            attack_flag = false;
        }
    };
private:
    //! 移動速度
    float _move_speed;
    //! 回転速度
    float _angular_speed;
    //! ラジアン
    float _ideal_angle;
    //! 入力情報
    ratchet::component::player::action::PlayerMoveComponent::InputInfo _input_info;
    //! 状態
    std::weak_ptr<ratchet::component::player::PlayerComponent> _type_com;
    //! カメラ
    std::weak_ptr<::ratchet::component::CameraComponent> _camera_com;
public:
    /// <summary>
    /// 加速
    /// </summary>
    /// <param name="speed"></param>
    virtual void InputMoveVelocity(float speed);
    /// <summary>
    /// 加速
    /// </summary>
    /// <param name="angle"></param>
    /// <param name="speed"></param>
    virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerMoveComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerMoveComponent(const PlayerMoveComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerMoveComponent();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetMoveSpeed(float speed);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="speed"></param>
    void SetAngularSpeed(float speed);
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="radian"></param>
    void SetIdealAngle(float radian);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDefaultMoveSpeed(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetMoveSpeed(void) const;
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
    /// 加速
    /// </summary>
    /// <param name="move_speed"></param>
    /// <param name="angular_speed"></param>
    /// <param name="ideal_angle"></param>
    /// <returns>実行</returns>
    bool Move(float move_speed, float angular_speed, float ideal_angle);
    /// <summary>
    /// 獲得
    /// </summary>
    /// <param name="stick">出力</param>
    /// <param name="move_angle">出力</param>
    /// <returns></returns>
    bool AquireInputData(Mof::CVector2& stick, float& move_angle);
};
}}}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_MOVE_COMPONENT_H