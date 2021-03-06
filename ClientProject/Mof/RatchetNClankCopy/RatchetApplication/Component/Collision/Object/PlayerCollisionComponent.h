#ifndef RATCHET_COMPONENT_COLLISION_PLAYER_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_PLAYER_COLLISION_COMPONENT_H


#include "CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>

#include "../../VelocityComponent.h"


namespace ratchet {
namespace component {
namespace player { class PlayerComponent; class PlayerStateComponent; }
namespace collision {
class PlayerCollisionComponent : public ratchet::component::collision::CollisionComponent {
    using super = ratchet::component::collision::CollisionComponent;
private:
    //! プレイヤー
    std::weak_ptr<ratchet::component::player::PlayerComponent> _player_com;
    //! 速度
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! プレイヤー
    std::weak_ptr<ratchet::component::player::PlayerStateComponent> _state_com;
    //! Elevatorに乗っている
    bool _on_elevator;
    //! 落下rayとStageの衝突時遷移する状態
    std::vector<std::string> _next_status;
private:
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name=""></param>
    void ChangeState(void);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetFrontRay(void);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="ptr"></param>
    virtual void CollisionStageFrontRay(Mof::LPMeshContainer mesh, const StageObject& obj);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="ptr"></param>
    virtual void CollisionStageDownRay(Mof::LPMeshContainer mesh, const StageObject& obj);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageElevator(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info);
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageBridge(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="priority"></param>
    PlayerCollisionComponent(int priority);
    /// <summary>
    /// コピーコンストラクタ
    /// </summary>
    /// <param name="obj"></param>
    PlayerCollisionComponent(const PlayerCollisionComponent& obj);
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~PlayerCollisionComponent();
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
    virtual std::optional<Mof::CRay3D> GetNextRay(void) override;
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
    virtual void CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) override;
    /// <summary>
    /// 衝突
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) override;
};
}
}
}
#endif // !RATCHET_COMPONENT_COLLISION_PLAYER_COLLISION_COMPONENT_H