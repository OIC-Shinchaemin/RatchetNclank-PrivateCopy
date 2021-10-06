#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_RANGED_ATTACK_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_RANGED_ATTACK_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"

#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


namespace ratchet::component::enemy {
class EnemyRangedAttackComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
    //! 弾の大きさ
    float _shot_bullet_scale;
    //! 攻撃範囲
    float _range;
    //! サイズ
    float _volume;
    //! 発射速さ
    float _shot_speed;
    //! 間隔
    base::core::Timer _interval;
    //! 速度
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
    //! 型
    std::weak_ptr<class EnemyComponent> _enemy_com;
    //! 状態
    std::weak_ptr<class EnemyStateComponent> _state_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyRangedAttackComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyRangedAttackComponent(const EnemyRangedAttackComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyRangedAttackComponent();
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
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(void) const;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetCanAttackRangeSphere(void) const;
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
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_RANGED_ATTACK_COMPONENT_H