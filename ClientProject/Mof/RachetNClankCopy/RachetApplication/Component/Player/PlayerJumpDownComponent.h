#ifndef MY_PLAYER_JUMP_DOWN_COMPONENT_H
#define MY_PLAYER_JUMP_DOWN_COMPONENT_H


#include "../UpdateComponent.h"

#include <memory>


namespace my {
class PlayerJumpDownComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:
    //! �ő�
    float _jump_speed_max;
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

    virtual void InputJumpVelocity(float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpDownComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpDownComponent(const PlayerJumpDownComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerJumpDownComponent();
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
#endif // !MY_PLAYER_JUMP_DOWN_COMPONENT_H