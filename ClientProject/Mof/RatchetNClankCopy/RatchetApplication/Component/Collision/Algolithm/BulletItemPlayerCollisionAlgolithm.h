#ifndef RATCHET_BulletItem_PLAYER_COLLISION_ALGOLITHM_H
#define RATCHET_BulletItem_PLAYER_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace ratchet {
class BulletItemPlayerCollisionAlgolithm : public ratchet::CollisionAlgolithm {
    using super = ratchet::CollisionAlgolithm;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BulletItemPlayerCollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BulletItemPlayerCollisionAlgolithm();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetLayerType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetTargetType(void) const override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent >object, std::shared_ptr<ratchet::component::collision::CollisionComponent >target, component::collision::CollisionInfo& out) override;
};
}
#endif // !RATCHET_BulletItem_PLAYER_COLLISION_ALGOLITHM_H