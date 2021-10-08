#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_MELEE_ATTACK_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_MELEE_ATTACK_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


namespace ratchet::component::collision { class EnemyMeleeAttackCollisionComponent; }
namespace ratchet::component::enemy {
class EnemyMeleeAttackComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
private:
    //! 攻撃範囲
    float _range;
    //! サイズ
    float _volume;
    //! 攻撃開始までの猶予
    base::core::Timer _wait;
    //! モーション
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! モーション
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
    //! モーション
    std::weak_ptr<ratchet::component::collision::EnemyMeleeAttackCollisionComponent> _collision_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyMeleeAttackComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyMeleeAttackComponent(const EnemyMeleeAttackComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyMeleeAttackComponent();
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
    /// <summary>
    /// 終了
    /// </summary>
    /// <param name=""></param>
    /// <returns>成功</returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_ATTACK_COMPONENT_H