#ifndef RATCHET_COMPONENT_COLLISION_OMNI_WRENCH_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_OMNI_WRENCH_COLLISION_COMPONENT_H


#include "CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace ratchet {
namespace component {
namespace collision {
class OmniWrenchCollisionComponent : public ratchet::component::collision::CollisionComponent {
    using super = ratchet::component::collision::CollisionComponent;
private:
    //! オフセット
    float _offset;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    OmniWrenchCollisionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    OmniWrenchCollisionComponent(const OmniWrenchCollisionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~OmniWrenchCollisionComponent();
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
    virtual std::optional<::ratchet::component::collision::SightObject> GetSightObject(void) override;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
};
}
}
}
#endif // !RATCHET_COMPONENT_COLLISION_OMNI_WRENCH_COLLISION_COMPONENT_H