#ifndef RATCHET_ENEMY_MELEE_ATTACK_COLLISION_COMPONENT_H
#define RATCHET_ENEMY_MELEE_ATTACK_COLLISION_COMPONENT_H


#include "CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace ratchet {
class EnemyMeleeAttackCollisionComponent : public ratchet::CollisionComponent {
    using super = ratchet::CollisionComponent;
private:
    //! 攻撃
    std::weak_ptr<class EnemyMeleeAttackComponent> _attack_com;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    EnemyMeleeAttackCollisionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    EnemyMeleeAttackCollisionComponent(const EnemyMeleeAttackCollisionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyMeleeAttackCollisionComponent();
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
    virtual std::optional<Mof::CSphere> GetSphere(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<ratchet::SightObject> GetSightObject(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
#endif // !RATCHET_ENEMY_MELEE_ATTACK_COLLISION_COMPONENT_H