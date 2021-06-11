#ifndef RATCHET_BLASTER_BULLET_COLLISION_COMPONENT_H
#define RATCHET_BLASTER_BULLET_COLLISION_COMPONENT_H


#include "CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace ratchet {
class BlasterBulletCollisionComponent: public ratchet::CollisionComponent {
    using super = ratchet::CollisionComponent;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BlasterBulletCollisionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BlasterBulletCollisionComponent(const BlasterBulletCollisionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BlasterBulletCollisionComponent();
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    virtual std::optional<ratchet::SightObject> GetSightObject(void) override;
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// 複製
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="ptr"></param>
    virtual void CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) override;
};
}
#endif // !RATCHET_BLASTER_BULLET_COLLISION_COMPONENT_H