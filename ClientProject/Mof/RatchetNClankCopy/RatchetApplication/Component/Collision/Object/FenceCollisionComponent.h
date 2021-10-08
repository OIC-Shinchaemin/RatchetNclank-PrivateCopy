#ifndef RATCHET_COMPONENT_COLLISION_FENCE_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_FENCE_COLLISION_COMPONENT_H


#include "../CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>

#include "../../MeshComponent.h"


namespace ratchet::component::collision {
class FenceCollisionComponent : public ratchet::component::collision::CollisionComponent {
    using super = ratchet::component::collision::CollisionComponent;
private:
    //! ���
    //std::weak_ptr<ratchet::component::ship::FenceStateComponent> _state_com;
    //! ����
    float _height;
    //! ���b�V��
    std::weak_ptr<ratchet::component::MeshComponent> _mesh;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    FenceCollisionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    FenceCollisionComponent(const FenceCollisionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~FenceCollisionComponent();
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
    virtual std::optional<Mof::LPMeshContainer> GetMesh(void) override;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::optional<::ratchet::component::collision::SightObject> GetSightObject(void) override;
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
    /// <param name="mesh"></param>
    /// <param name="obj"></param>
    virtual void CollisionStage(Mof::LPMeshContainer mesh, const StageObject& obj) override;
};
}
#endif // !RATCHET_COMPONENT_COLLISION_FENCE_COLLISION_COMPONENT_H