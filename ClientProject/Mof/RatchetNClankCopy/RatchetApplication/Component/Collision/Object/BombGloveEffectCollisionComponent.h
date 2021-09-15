#ifndef RATCHET_COMPONENT_COLLISION_BOMB_GLOVE_EFFECT_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_BOMB_GLOVE_EFFECT_COLLISION_COMPONENT_H


#include "../CollisionComponent.h"

#include <optional>
#include <memory>


namespace ratchet::component::collision {
class BombGloveEffectCollisionComponent : public ratchet::component::collision::CollisionComponent {
    using super = ratchet::component::collision::CollisionComponent;
private:
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    BombGloveEffectCollisionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    BombGloveEffectCollisionComponent(const BombGloveEffectCollisionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~BombGloveEffectCollisionComponent();
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
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="ptr"></param>
    //virtual void CollisionStage(Mof::LPMeshContainer mesh, const Mof::CMatrix44& world) override;
};
}
#endif // !RATCHET_COMPONENT_COLLISION_BOMB_GLOVE_EFFECT_COLLISION_COMPONENT_H