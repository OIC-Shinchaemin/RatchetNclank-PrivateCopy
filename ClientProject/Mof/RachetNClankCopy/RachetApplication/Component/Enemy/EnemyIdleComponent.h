#ifndef RACHET_ENEMY_IDLE_COMPONENT_H
#define RACHET_ENEMY_IDLE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace rachet {
class EnemyIdleComponent : public rachet::ActionComponent {
    using super = rachet::ActionComponent;
private:
    //! 回転速度
    float _angular_speed;
    //! ラジアン
    float _ideal_angle;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    
    virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyIdleComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyIdleComponent(const EnemyIdleComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyIdleComponent();
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
    float GetIdealAngle(void) const;
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !RACHET_ENEMY_IDLE_COMPONENT_H