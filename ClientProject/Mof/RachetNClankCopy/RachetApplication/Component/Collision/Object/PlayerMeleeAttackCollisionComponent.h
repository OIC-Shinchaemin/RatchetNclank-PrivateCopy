#ifndef MY_PLAYER_MELEE_ATTACK_COLLISION_COMPONENT_H
#define MY_PLAYER_MELEE_ATTACK_COLLISION_COMPONENT_H


#include "CollisionComponent.h"

#include <optional>
#include <memory>

#include <Mof.h>


namespace my {
class PlayerMeleeAttackCollisionComponent : public my::CollisionComponent {
    using super = my::CollisionComponent;
private:
    //! �傫��
    float _volume;
    //! �A�N�^�[����̋���
    float _front_offset;
    //! �v���C���[
    std::weak_ptr<class PlayerComponent> _player_com;
    //! �U��
    std::weak_ptr<class PlayerMeleeAttackOneComponent> _attack_one_com;
    //! �U��
    std::weak_ptr<class PlayerMeleeAttackTwoComponent> _attack_two_com;
    //! �U��
    std::weak_ptr<class PlayerMeleeAttackThreeComponent> _attack_three_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerMeleeAttackCollisionComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerMeleeAttackCollisionComponent(const PlayerMeleeAttackCollisionComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerMeleeAttackCollisionComponent();
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
    virtual std::optional<my::SightObject> GetSightObject(void) override;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;    
};
}
#endif // !MY_PLAYER_MELEE_ATTACK_COLLISION_COMPONENT_H