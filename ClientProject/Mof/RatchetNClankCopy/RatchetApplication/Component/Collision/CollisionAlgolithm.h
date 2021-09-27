#ifndef RATCHET_COLLISION_ALGOLITHM_H
#define RATCHET_COLLISION_ALGOLITHM_H


#include <memory>

#include "CollisionComponent.h"


namespace ratchet {
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
    virtual const char* GetType(void) {
        return typeid(*this).name();
    }
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
    virtual bool IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent >object, std::shared_ptr<ratchet::component::collision::CollisionComponent >target, component::collision::CollisionInfo& out) = 0;
};
}
#endif // !RATCHET_COLLISION_ALGOLITHM_H