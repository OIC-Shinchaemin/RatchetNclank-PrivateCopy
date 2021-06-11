#ifndef RACHET_PLAYER_WATER_FLOW_COLLISION_ALGOLITHM_H
#define RACHET_PLAYER_WATER_FLOW_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace rachet {
class PlayerWaterFlowCollisionAlgolithm : public rachet::CollisionAlgolithm {
    using super = rachet::CollisionAlgolithm;
public:    
    /// <summary>
    /// コンストラクタ
    /// </summary>
    PlayerWaterFlowCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerWaterFlowCollisionAlgolithm();
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
#endif // !RACHET_PLAYER_WATER_FLOW_COLLISION_ALGOLITHM_H