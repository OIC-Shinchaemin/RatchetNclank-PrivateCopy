#ifndef MY_ENEMY_DAMAGE_COMPONENT_H
#define MY_ENEMY_DAMAGE_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "My/Core/Timer.h"
#include "../Collision/Object/CollisionComponent.h"


namespace my {
class EnemyDamageComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! 被弾量
    int _damage_value;
    //! 被弾角度
    Mof::CVector3 _damage_angle;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! Hp
    std::weak_ptr<class HpComponent> _hp_com;
    //! 型
    std::weak_ptr<class EnemyComponent> _enemy_com;
    //! 状態
    std::weak_ptr<class EnemyStateComponent> _state_com;
private:
    /// <summary>
    /// 衝突処理
    /// </summary>
    /// <param name=""></param>
    void CollisionAction(const my::CollisionInfo& in);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyDamageComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyDamageComponent(const EnemyDamageComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyDamageComponent();
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
#endif // !MY_ENEMY_DAMAGE_COMPONENT_H