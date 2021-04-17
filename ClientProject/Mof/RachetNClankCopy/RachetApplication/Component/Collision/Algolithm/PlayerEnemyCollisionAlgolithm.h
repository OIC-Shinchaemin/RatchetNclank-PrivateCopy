#ifndef MY_PLAYER_ENEMY_COLLISION_ALGOLITHM_H
#define MY_PLAYER_ENEMY_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace my {
class PlayerEnemyCollisionAlgolithm : public my::CollisionAlgolithm {
    using super = my::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerEnemyCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerEnemyCollisionAlgolithm();
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
    virtual bool IsCollision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, my::CollisionInfo& out) override;
};
}
#endif // !MY_PLAYER_ENEMY_COLLISION_ALGOLITHM_H