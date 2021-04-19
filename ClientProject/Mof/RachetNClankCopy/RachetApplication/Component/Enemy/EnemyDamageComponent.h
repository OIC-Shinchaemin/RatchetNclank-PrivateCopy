#ifndef MY_ENEMY_DAMAGE_COMPONENT_H
#define MY_ENEMY_DAMAGE_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>

#include "My/Core/Timer.h"


namespace my {
class EnemyDamageComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    ////! ��e�p�x
    //Mof::CVector3 _damage_angle;
    ////! ���x
    //std::weak_ptr<class VelocityComponent> _velocity_com;
    ////! ���[�V����
    //std::weak_ptr<class MotionComponent> _motion_com;
    ////! ���[�V����
    //std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! Hp
    std::weak_ptr<class HpComponent> _hp_com;
    ////! �ҋ@
    //std::weak_ptr<class PlayerIdleComponent> _idle_com;
    ////! �ҋ@
    //std::weak_ptr<class PlayerInvincibleComponent> _invincible_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyDamageComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyDamageComponent(const EnemyDamageComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyDamageComponent();
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual std::string GetType(void) const override;
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
    virtual std::shared_ptr<my::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
};
}
#endif // !MY_ENEMY_DAMAGE_COMPONENT_H