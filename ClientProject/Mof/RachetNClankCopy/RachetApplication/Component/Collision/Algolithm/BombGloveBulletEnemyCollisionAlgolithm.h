#ifndef MY_BOMB_GLOVE_BULLET_ENEMY_COLLISION_ALGOLITHM_H
#define MY_BOMB_GLOVE_BULLET_ENEMY_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace my {
class BombGloveBulletEnemyCollisionAlgolithm : public my::CollisionAlgolithm {
    using super = my::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    BombGloveBulletEnemyCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGloveBulletEnemyCollisionAlgolithm();
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
    virtual bool IsCollision(std::shared_ptr<my::CollisionComponent >object, std::shared_ptr<my::CollisionComponent >target, my::CollisionInfo& out) override;
};
}
#endif // !MY_BOMB_GLOVE_BULLET_ENEMY_COLLISION_ALGOLITHM_H