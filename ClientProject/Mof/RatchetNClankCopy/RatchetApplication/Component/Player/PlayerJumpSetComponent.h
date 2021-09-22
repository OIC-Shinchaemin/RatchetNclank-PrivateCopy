#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_SET_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_SET_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace ratchet {
namespace component {
namespace player {
namespace action {
class PlayerJumpSetComponent : public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    using This = ratchet::component::player::action::PlayerJumpSetComponent;
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
    //! �W�����v
    float _jump_speed;
    //! �W�����v
    float _jump_speed_first;
    //! �W�����v
    float _jump_speed_increase;
    //! �ړ�
    //float _default_move_speed;
    //! �ړ�
    //float _default_angular_speed;
    //! �ړ�
    float _move_speed;
    //! �ړ�
    float _angular_speed;
    //! ���͏��
    This::InputInfo _input_info;
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
}
}
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_JUMP_SET_COMPONENT_H