#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_GO_HOME_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_GO_HOME_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "../VelocityComponent.h"
#include "../MotionStateComponent.h"


namespace ratchet {
namespace component {
namespace enemy {
class EnemyGoHomeComponent : public ::ratchet::component::ActionComponent {
    using super = ::ratchet::component::ActionComponent;
private:
    //! 移動速度
    float _move_speed;
    //! 回転速度
    float _angular_speed;
    //! ラジアン
    float _ideal_angle;
    //! 速度
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
    //! 状態
    std::weak_ptr<class EnemyStateComponent> _action_state_com;
    //! 型
    std::weak_ptr<class EnemyComponent> _ENEMY_com;
    virtual void InputMoveVelocity(float speed);
    virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyGoHomeComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyGoHomeComponent(const EnemyGoHomeComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyGoHomeComponent();
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
    virtual std::string GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string_view GetStateType(void) const;
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
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_GO_HOME_COMPONENT_H