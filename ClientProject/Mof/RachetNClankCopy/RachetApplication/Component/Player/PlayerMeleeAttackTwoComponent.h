#ifndef MY_PLAYER_MELEE_ATTACK_TWO_COMPONENT_H
#define MY_PLAYER_MELEE_ATTACK_TWO_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerMeleeAttackTwoComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! �\��
    bool _next_reserve;
    //! ���x
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! ���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! ����
    std::weak_ptr<class PlayerWeaponComponent> _weapon_com;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChageState(const std::string& name);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerMeleeAttackTwoComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerMeleeAttackTwoComponent(const PlayerMeleeAttackTwoComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerMeleeAttackTwoComponent();
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
    virtual std::string_view GetStateType(void) const override;
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
    /// <summary>
    /// �I��
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool End(void) override;
};
}
#endif // !MY_PLAYER_MELEE_ATTACK_TWO_COMPONENT_H