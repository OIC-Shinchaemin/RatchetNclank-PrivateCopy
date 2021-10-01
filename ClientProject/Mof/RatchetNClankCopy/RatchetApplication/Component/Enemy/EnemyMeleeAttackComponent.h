#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_MELEE_ATTACK_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_MELEE_ATTACK_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


namespace ratchet::component::collision { class EnemyMeleeAttackCollisionComponent; }
namespace ratchet::component::enemy {
class EnemyMeleeAttackComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
private:
    //! �U���͈�
    float _range;
    //! �T�C�Y
    float _volume;
    //! �U���J�n�܂ł̗P�\
    base::core::Timer _wait;
    //! ���[�V����
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
    //! ���[�V����
    std::weak_ptr<ratchet::component::collision::EnemyMeleeAttackCollisionComponent> _collision_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyMeleeAttackComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyMeleeAttackComponent(const EnemyMeleeAttackComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyMeleeAttackComponent();
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
    virtual std::string_view GetStateType(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetRange(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetVolume(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetCanAttackRangeSphere(void) const;
    /// <summary>
    /// ������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Initialize(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    virtual bool Update(float delta_time) override;
    /// <summary>
    /// ���
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Release(void) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_ATTACK_COMPONENT_H