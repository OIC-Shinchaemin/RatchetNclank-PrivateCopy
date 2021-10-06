#ifndef RATCHET_COMPONENT_ENEMY_ENEMY_RANGED_ATTACK_COMPONENT_H
#define RATCHET_COMPONENT_ENEMY_ENEMY_RANGED_ATTACK_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>

#include "Base/Core/Timer.h"

#include "../VelocityComponent.h"
#include "../MotionComponent.h"
#include "../MotionStateComponent.h"


namespace ratchet::component::enemy {
class EnemyRangedAttackComponent : public ratchet::component::ActionComponent {
    using super = ratchet::component::ActionComponent;
private:
    //! �e�̑傫��
    float _shot_bullet_scale;
    //! �U���͈�
    float _range;
    //! �T�C�Y
    float _volume;
    //! ���ˑ���
    float _shot_speed;
    //! �Ԋu
    base::core::Timer _interval;
    //! ���x
    std::weak_ptr<ratchet::component::VelocityComponent> _velocity_com;
    //! ���[�V����
    std::weak_ptr<ratchet::component::MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<ratchet::component::MotionStateComponent> _motion_state_com;
    //! �^
    std::weak_ptr<class EnemyComponent> _enemy_com;
    //! ���
    std::weak_ptr<class EnemyStateComponent> _state_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyRangedAttackComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyRangedAttackComponent(const EnemyRangedAttackComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyRangedAttackComponent();
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
};
}
#endif // !RATCHET_COMPONENT_ENEMY_ENEMY_RANGED_ATTACK_COMPONENT_H