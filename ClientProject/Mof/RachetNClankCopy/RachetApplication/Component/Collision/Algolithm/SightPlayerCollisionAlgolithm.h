#ifndef RATCHET_SIGHT_PLAYER_COLLISION_ALGOLITHM_H
#define RATCHET_SIGHT_PLAYER_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace ratchet {
class SightPlayerCollisionAlgolithm: public ratchet::CollisionAlgolithm {
    using super = ratchet::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SightPlayerCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SightPlayerCollisionAlgolithm();
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
#endif // !RATCHET_SIGHT_PLAYER_COLLISION_ALGOLITHM_H