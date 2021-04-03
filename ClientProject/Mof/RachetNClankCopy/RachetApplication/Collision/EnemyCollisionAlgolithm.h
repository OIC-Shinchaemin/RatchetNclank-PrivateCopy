#ifndef MY_ENEMY_COLLISION_ALGOLITHM_H
#define MY_ENEMY_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace my {
class EnemyPlayerCollisionAlgolithm: public my::CollisionAlgolithm {
    using super = my::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyPlayerCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyPlayerCollisionAlgolithm();
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
    /// 衝突
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    virtual void Collision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, const my::CollisionInfo& info) override;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, my::CollisionInfo& out) override;
};
}
#endif // !MY_ENEMY_COLLISION_ALGOLITHM_H