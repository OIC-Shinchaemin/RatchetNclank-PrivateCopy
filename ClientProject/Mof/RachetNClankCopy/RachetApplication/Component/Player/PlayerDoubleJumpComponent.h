#ifndef MY_PLAYER_DOUBLE_JUMP_COMPONENT_H
#define MY_PLAYER_DOUBLE_JUMP_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerDoubleJumpComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! �ő�
    //float _jump_speed_max;
    //! ���x
    float _jump_speed;
    //! ����
    float _jump_decrase;
    //! ���x
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! ���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;

    virtual void InputJumpVelocity(float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerDoubleJumpComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerDoubleJumpComponent(const PlayerDoubleJumpComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerDoubleJumpComponent();
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
    /// �Z�b�^�[
    /// </summary>
    /// <param name="speed"></param>
    void SetJumpSpeed(float speed);
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
#endif // !MY_PLAYER_DOUBLE_JUMP_COMPONENT_H