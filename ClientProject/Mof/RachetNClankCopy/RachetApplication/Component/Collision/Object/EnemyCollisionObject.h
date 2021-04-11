#ifndef MY_ENEMY_COLLISION_OBJECT_H
#define MY_ENEMY_COLLISION_OBJECT_H


#include "CollisionObject.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace my {
class EnemyCollisionObject : public my::CollisionObject {
    using super = my::CollisionObject;
private:
    //! 所有者
    std::weak_ptr<class Enemy> _owner;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    EnemyCollisionObject();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~EnemyCollisionObject();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="owner"></param>
    virtual void SetOwner(std::any owner) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::any GetOwner(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual const char* GetType(void) const override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CSphere> GetSphere(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) override;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<my::SightObject> GetSightObject(void) override;
};
}
#endif // !MY_ENEMY_COLLISION_OBJECT_H