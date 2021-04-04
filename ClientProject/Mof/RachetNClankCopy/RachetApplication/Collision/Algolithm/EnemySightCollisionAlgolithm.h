#ifndef MY_ENEMY_SIGHT_COLLISION_ALGOLITHM_H
#define MY_ENEMY_SIGHT_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace my {
class EnemySightPlayerCollisionAlgolithm: public my::CollisionAlgolithm {
    using super = my::CollisionAlgolithm;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemySightPlayerCollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemySightPlayerCollisionAlgolithm();
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
    //virtual void Collision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, const my::CollisionInfo& info) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<my::CollisionObject >object, std::shared_ptr<my::CollisionObject >target, my::CollisionInfo& out) override;
};
}
#endif // !MY_ENEMY_SIGHT_COLLISION_ALGOLITHM_H