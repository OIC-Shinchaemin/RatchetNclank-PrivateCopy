#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_UP_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_UP_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace ratchet ::component ::player::action {
class PlayerJumpUpComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    using This = ratchet::component::player::action::PlayerJumpUpComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;

        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
        }
    };
private:
    //! ��
    float _jump_speed;
    //! ����
    float _jump_decrase;
    //! ����
    float _move_speed;
    //! ����
    float _angular_speed;
    //!  ���~
    float _gravity_down;
    //! �����I��������
    std::optional<float> _force_move_radian_angle;
    //! ���͏��
    This::InputInfo _input_info;
    //! �ړ�
    std::weak_ptr<class PlayerMoveComponent> _move_com;
    /// <summary>
    /// �W�����v���x����
    /// </summary>
    /// <param name="speed"></param>
    virtual void InputJumpVelocity(float speed);
public:
    //! �A�N�Z�b�T
    base::accessor::Accessor<decltype(_force_move_radian_angle)> force_move_radian_angle = _force_move_radian_angle;
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerJumpUpComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerJumpUpComponent(const PlayerJumpUpComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerJumpUpComponent();
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
    /// <param name="scalar"></param>
    void SetMoveSpeed(float scalar);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="scalar"></param>
    void SetAngularSpeed(float scalar);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="speed"></param>
    void SetJumpSpeed(float scalar);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="speed"></param>
    void SetGravityDown(float scalar);
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
    virtual bool Input(void) override;
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
    /// <returns></returns>
    virtual bool End(void) override;
};
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_UP_COMPONENT_H