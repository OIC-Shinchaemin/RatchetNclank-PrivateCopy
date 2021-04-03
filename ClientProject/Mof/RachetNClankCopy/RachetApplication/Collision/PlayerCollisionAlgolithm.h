#ifndef MY_PLAYER_COLLISION_ALGOLITHM_H
#define MY_PLAYER_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace my {
class PlayerEnemyCollisionAlgolithm : public my::CollisionAlgolithm {
    using super = my::CollisionAlgolithm;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    PlayerEnemyCollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerEnemyCollisionAlgolithm();
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
    /// �Փ�
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    virtual void Collision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, const my::CollisionInfo& info) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, my::CollisionInfo& out) override;
};
}
#endif // !MY_PLAYER_COLLISION_ALGOLITHM_H