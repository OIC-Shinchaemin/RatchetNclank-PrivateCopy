#ifndef RATCHET_ENEMY_MELEE_ATTACK_PLAYER_COLLISION_ALGOLITHM_H
#define RATCHET_ENEMY_MELEE_ATTACK_PLAYER_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace ratchet {
class EnemyMeleeAttackPlayerCollisionAlgolithm : public ratchet::CollisionAlgolithm {
    using super = ratchet::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyMeleeAttackPlayerCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyMeleeAttackPlayerCollisionAlgolithm();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetLayerType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetTargetType(void) const override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<ratchet::CollisionComponent >object, std::shared_ptr<ratchet::CollisionComponent >target, ratchet::CollisionInfo& out) override;
};
}
#endif // !RATCHET_ENEMY_MELEE_ATTACK_PLAYER_COLLISION_ALGOLITHM_H