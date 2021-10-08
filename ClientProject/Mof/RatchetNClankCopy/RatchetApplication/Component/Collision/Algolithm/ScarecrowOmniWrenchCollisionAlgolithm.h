#ifndef RATCHET_SCARECROW_OMNI_WRENCH_COLLISION_ALGOLITHM_H
#define RATCHET_SCARECROW_OMNI_WRENCH_COLLISION_ALGOLITHM_H


#include "../CollisionAlgolithm.h"


namespace ratchet {
class ScarecrowOmniWrenchCollisionAlgolithm : public ratchet::CollisionAlgolithm {
    using super = ratchet::CollisionAlgolithm;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ScarecrowOmniWrenchCollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ScarecrowOmniWrenchCollisionAlgolithm();
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
    virtual bool IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent >object, std::shared_ptr<ratchet::component::collision::CollisionComponent >target, component::collision::CollisionInfo& out) override;
};
}
#endif // !RATCHET_SCARECROW_OMNI_WRENCH_COLLISION_ALGOLITHM_H