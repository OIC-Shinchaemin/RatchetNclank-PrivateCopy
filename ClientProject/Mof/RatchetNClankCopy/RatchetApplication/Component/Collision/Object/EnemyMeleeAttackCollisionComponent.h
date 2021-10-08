#ifndef RATCHET_COMPONENT_COLLISION_ENEMY_MELEE_ATTACK_COLLISION_COMPONENT_H
#define RATCHET_COMPONENT_COLLISION_ENEMY_MELEE_ATTACK_COLLISION_COMPONENT_H


#include "../CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace ratchet::component::enemy { class EnemyMeleeAttackComponent; }
namespace ratchet::component::collision {
class EnemyMeleeAttackCollisionComponent : public ratchet::component::collision::CollisionComponent {
    using super = ratchet::component::collision::CollisionComponent;
private:
    //! �U��
    std::weak_ptr<ratchet::component::enemy::EnemyMeleeAttackComponent> _attack_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyMeleeAttackCollisionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyMeleeAttackCollisionComponent(const EnemyMeleeAttackCollisionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyMeleeAttackCollisionComponent();
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
};
}
#endif // !RATCHET_COMPONENT_COLLISION_ENEMY_MELEE_ATTACK_COLLISION_COMPONENT_H