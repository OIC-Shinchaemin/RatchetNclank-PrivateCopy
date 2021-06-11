#ifndef RATCHET_ENEMY_DAMAGE_COMPONENT_H
#define RATCHET_ENEMY_DAMAGE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"
#include "../Collision/Object/CollisionComponent.h"


namespace ratchet {
class EnemyDamageComponent : public ratchet::ActionComponent {
    using super = ratchet::ActionComponent;
private:
    //! 被弾量
    int _damage_value;
    //! 被弾角度
    Mof::CVector3 _damage_angle;
    //! 被弾速
    float _damage_speed;
    //! 速度
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<class MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! Hp
    std::weak_ptr<class HpComponent> _hp_com;
    //! 型
    std::weak_ptr<class EnemyComponent> _ENEMY_com;
    //! 状態
    std::weak_ptr<class EnemyStateComponent> _state_com;
private:
    /// <summary>
    /// 衝突処理
    /// </summary>
    /// <param name=""></param>
    void CollisionAction(const ratchet::CollisionInfo& in);
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
    /// <summary>
    /// 開始
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool Start(void) override;
};
}
#endif // !RATCHET_ENEMY_DAMAGE_COMPONENT_H