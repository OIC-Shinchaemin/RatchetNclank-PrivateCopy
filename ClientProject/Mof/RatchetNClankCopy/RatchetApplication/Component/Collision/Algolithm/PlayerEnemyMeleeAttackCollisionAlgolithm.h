#ifndef RATCHET_PLAYER_ENEMY_MELEE_ATTACK_COLLISION_ALGOLITHM_H
#define RATCHET_PLAYER_ENEMY_MELEE_ATTACK_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace ratchet {
class PlayerEnemyMeleeAttackCollisionAlgolithm : public ratchet::CollisionAlgolithm {
    using super = ratchet::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerEnemyMeleeAttackCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerEnemyMeleeAttackCollisionAlgolithm();
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
#endif // !RATCHET_PLAYER_ENEMY_MELEE_ATTACK_COLLISION_ALGOLITHM_H