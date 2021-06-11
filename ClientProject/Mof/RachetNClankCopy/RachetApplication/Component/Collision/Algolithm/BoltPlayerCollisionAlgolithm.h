#ifndef RACHET_BOLT_PLAYER_COLLISION_ALGOLITHM_H
#define RACHET_BOLT_PLAYER_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace rachet {
class BoltPlayerCollisionAlgolithm : public rachet::CollisionAlgolithm {
    using super = rachet::CollisionAlgolithm;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    BoltPlayerCollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~BoltPlayerCollisionAlgolithm();
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
    virtual bool IsCollision(std::shared_ptr<rachet::CollisionComponent >object, std::shared_ptr<rachet::CollisionComponent >target, rachet::CollisionInfo& out) override;
};
}
#endif // !RACHET_BOLT_PLAYER_COLLISION_ALGOLITHM_H