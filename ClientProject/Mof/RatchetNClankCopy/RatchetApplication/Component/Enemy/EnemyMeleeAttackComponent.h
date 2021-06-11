#ifndef RATCHET_ENEMY_MELEE_ATTACK_COMPONENT_H
#define RATCHET_ENEMY_MELEE_ATTACK_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"


namespace ratchet {
class EnemyMeleeAttackComponent : public ratchet::ActionComponent {
    using super = ratchet::ActionComponent;
private:
private:
    //! �U���͈�
    float _range;
    //! �T�C�Y
    float _volume;
    //! �U���J�n�܂ł̗P�\
    base::core::Timer _wait;
    //! ���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! ���[�V����
    std::weak_ptr<class EnemyMeleeAttackCollisionComponent> _collision_com;
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
    virtual std::shared_ptr<ratchet::Component> Clone(void) override;
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
#endif // !RATCHET_ENEMY_ATTACK_COMPONENT_H