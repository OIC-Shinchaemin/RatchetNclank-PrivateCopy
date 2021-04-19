#ifndef MY_ENEMY_BOMB_GLOVE_BULLET_COLLISION_ALGOLITHM_H
#define MY_ENEMY_BOMB_GLOVE_BULLET_COLLISION_ALGOLITHM_H


#include "CollisionAlgolithm.h"


namespace my {
class EnemyBombGloveBulletCollisionAlgolithm: public my::CollisionAlgolithm {
    using super = my::CollisionAlgolithm;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    EnemyBombGloveBulletCollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyBombGloveBulletCollisionAlgolithm();
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
    virtual bool IsCollision(std::shared_ptr<my::CollisionComponent >object, std::shared_ptr<my::CollisionComponent >target, my::CollisionInfo& out) override;
};
}
#endif // !MY_ENEMY_BOMB_GLOVE_BULLET_COLLISION_ALGOLITHM_H