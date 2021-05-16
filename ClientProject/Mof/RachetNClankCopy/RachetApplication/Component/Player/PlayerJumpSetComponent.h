#ifndef MY_PLAYER_JUMP_SET_COMPONENT_H
#define MY_PLAYER_JUMP_SET_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerJumpSetComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! �W�����v
    float _jump_speed;
    //! �W�����v
    float _jump_speed_first;
    //! �W�����v
    float _jump_speed_increase;
    //! ���[�V����
    std::weak_ptr<class MotionComponent> _motion_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    //! �ړ�
    std::weak_ptr<class PlayerJumpUpComponent> _jump_com;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpSetComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpSetComponent(const PlayerJumpSetComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerJumpSetComponent();
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
#endif // !MY_PLAYER_JUMP_SET_COMPONENT_H