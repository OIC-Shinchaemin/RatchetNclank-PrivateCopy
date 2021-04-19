#ifndef MY_COLLISION_ALGOLITHM_H
#define MY_COLLISION_ALGOLITHM_H


#include <memory>

#include "../Object/CollisionComponent.h"


namespace my {
class CollisionAlgolithm {
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CollisionAlgolithm();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CollisionAlgolithm();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetLayerType(void) const = 0;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetTargetType(void) const = 0;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<my::CollisionComponent >object, std::shared_ptr<my::CollisionComponent >target, my::CollisionInfo& out) = 0;
};
}
#endif // !MY_COLLISION_ALGOLITHM_H