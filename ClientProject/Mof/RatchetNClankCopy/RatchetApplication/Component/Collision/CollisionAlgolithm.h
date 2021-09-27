#ifndef RATCHET_COLLISION_ALGOLITHM_H
#define RATCHET_COLLISION_ALGOLITHM_H


#include <memory>

#include "CollisionComponent.h"


namespace ratchet {
class CollisionAlgolithm {
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CollisionAlgolithm();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CollisionAlgolithm();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetType(void) {
        return typeid(*this).name();
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetLayerType(void) const = 0;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetTargetType(void) const = 0;
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name="object"></param>
    /// <param name="target"></param>
    /// <returns></returns>
    virtual bool IsCollision(std::shared_ptr<ratchet::component::collision::CollisionComponent >object, std::shared_ptr<ratchet::component::collision::CollisionComponent >target, component::collision::CollisionInfo& out) = 0;
};
}
#endif // !RATCHET_COLLISION_ALGOLITHM_H