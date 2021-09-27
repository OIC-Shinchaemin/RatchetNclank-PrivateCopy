#ifndef RATCHET_PLAYER_BARRACK_COLLISION_ALGOLITHM_H
#define RATCHET_PLAYER_BARRACK_COLLISION_ALGOLITHM_H


#include "../CollisionAlgolithm.h"


namespace ratchet {
class PlayerBarrackCollisionAlgolithm : public ratchet::CollisionAlgolithm {
    using super = ratchet::CollisionAlgolithm;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerBarrackCollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerBarrackCollisionAlgolithm();
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
#endif // !RATCHET_PLAYER_BARRACK_COLLISION_ALGOLITHM_H