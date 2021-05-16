#ifndef MY_PLAYER_MOVE_COMPONENT_H
#define MY_PLAYER_MOVE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerMoveComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! 移動速度
    float _move_speed;
    //! 回転速度
    float _angular_speed;
    //! ラジアン
    float _ideal_angle;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! 状態
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! カメラ
    std::weak_ptr<class CameraComponent> _camera_com;
    //! 状態
    std::weak_ptr<class PlayerComponent> _type_com;
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="name"></param>
    void ChageState(const std::string& name);
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
}
#endif // !MY_PLAYER_MOVE_COMPONENT_H