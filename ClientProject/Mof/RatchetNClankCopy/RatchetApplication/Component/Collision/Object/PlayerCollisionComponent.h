#ifndef RATCHET_COMPONENT_COLLISION_PLAYER_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_PLAYER_COLLISION_COMPONENT_H


#include "../CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>

#include "../../VelocityComponent.h"


namespace ratchet::component::player { class PlayerComponent; class PlayerStateComponent; }
namespace ratchet::component::collision {
class PlayerCollisionComponent : public ratchet::component::collision::CollisionComponent {
    using super = ratchet::component::collision::CollisionComponent;
private:
    //! �v���C���[
    std::weak_ptr<ratchet::component::player::PlayerComponent> _player_com;
    //! ���x
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! �v���C���[
    std::weak_ptr<ratchet::component::player::PlayerStateComponent> _state_com;
    //! Elevator�ɏ���Ă���
    bool _on_elevator;
    //! ����ray��Stage�̏Փˎ��J�ڂ�����
    std::vector<std::string> _next_status;
    //! �X�e�[�W�Ƃ̐ڐG�ʒu
    Mof::CVector3 _collision_point_stage_down_ray;
public:
    //! �Q�b�^�[
    base::accessor::Getter<decltype(_collision_point_stage_down_ray)> collision_point_stage_down_ray = _collision_point_stage_down_ray;
private:
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name=""></param>
    void ChangeState(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetFrontRay(void);
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="ptr"></param>
    virtual void CollisionStageFrontRay(Mof::LPMeshContainer mesh, const StageObject& obj);
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="ptr"></param>
    virtual void CollisionStageDownRay(Mof::LPMeshContainer mesh, const StageObject& obj);
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageElevator(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info);
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageBridge(Mof::LPMeshContainer mesh, GimmickPtr& gimmick, Mof::CRay3D ray, Mof::COLLISIONOUTGEOMETRY& info);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerCollisionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerCollisionComponent(const PlayerCollisionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerCollisionComponent();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CSphere> GetSphere(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CBoxAABB> GetBox(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetRay(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::CRay3D> GetNextRay(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<::ratchet::component::collision::SightObject> GetSightObject(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsOnElevator(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="ptr"></param>
    virtual void CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) override;
    /// <summary>
    /// �Փ�
    /// </summary>
    /// <param name="mesh"></param>
    /// <param name="gimmick"></param>
    virtual void CollisionStageGimmick(Mof::LPMeshContainer mesh, GimmickPtr& gimmick) override;
};
}
#endif // !RATCHET_COMPONENT_COLLISION_PLAYER_COLLISION_COMPONENT_H