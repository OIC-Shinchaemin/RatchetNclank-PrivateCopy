#ifndef RACHET_ENEMY_BOMB_GLOVE_EFFECT_COLLISION_ALGOLITHM_H
#define RACHET_ENEMY_BOMB_GLOVE_EFFECT_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace rachet {
class EnemyBombGloveEffectCollisionAlgolithm : public rachet::CollisionAlgolithm {
    using super = rachet::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyBombGloveEffectCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyBombGloveEffectCollisionAlgolithm();
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
    virtual bool IsCollision(std::shared_ptr<rachet::CollisionComponent >object, std::shared_ptr<rachet::CollisionComponent >target, rachet::CollisionInfo& out) override;
};
}
#endif // !RACHET_ENEMY_BOMB_GLOVE_EFFECT_COLLISION_ALGOLITHM_H