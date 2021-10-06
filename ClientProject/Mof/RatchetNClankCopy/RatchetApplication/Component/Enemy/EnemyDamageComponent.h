#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_DAMAGE_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_DAMAGE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"
#include "../Collision/CollisionComponent.h"

#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"
#include "../HpComponent.h"
#include "../InvincibleComponent.h"


namespace ratchet::component::enemy {
class EnemyDamageComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
    //! 被弾量
    int _damage_value;
    //! 被弾角度
    Mof::CVector3 _damage_angle;
    //! 被弾速
    float _damage_speed;
    //! 速度
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
    //! Hp
    std::weak_ptr<ratchet::component::HpComponent> _hp_com;
    //! 型
    std::weak_ptr<class EnemyComponent> _enemy_com;
    //! 状態
    std::weak_ptr<class EnemyStateComponent> _state_com;
    //! 無敵
    std::weak_ptr<ratchet::component::InvincibleComponent> _invincible_com;
private:
    /// <summary>
    /// 衝突処理
    /// </summary>
    /// <param name=""></param>
    void CollisionAction(const component::collision::CollisionInfo& in);
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_DAMAGE_COMPONENT_H