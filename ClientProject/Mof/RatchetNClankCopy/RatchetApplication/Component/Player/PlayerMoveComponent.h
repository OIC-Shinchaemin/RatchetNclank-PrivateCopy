#ifndef RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_MOVE_COMPONENT_H
#define RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_MOVE_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>

#include "../CameraComponent.h"

namespace ratchet::component::player { class PlayerComponent; }
namespace ratchet::component::player::action {
class PlayerMoveComponent : 
    public ::ratchet::component::player::action::PlayerActionComponent {
    using super = ::ratchet::component::player::action::PlayerActionComponent;
    struct InputInfo {
        Mof::CVector2 in;
        float move_angle = 0.0f;
        bool move_flag = false;
        bool jump_flag = false;
        bool attack_flag = false;

        void Reset(void) {
            in.x = 0.0f;
            in.y = 0.0f;
            move_angle = 0.0f;
            move_flag = false;
            jump_flag = false;
            attack_flag = false;
        }
    };
private:
    //! �ړ����x
    float _move_speed;
    //! �ő�l
    float _move_speed_max;
    //! ������
    float _move_speed_increase;
    //! ��]���x
    float _angular_speed;
    //! �ő�l
    float _angular_speed_max;
    //! ������
    float _angular_speed_increase;
    //! ���W�A��
    float _ideal_angle;
    
    //! �ړ����x
    //float _velocity_force_xz_max;
    //! ���͏��
    ratchet::component::player::action::PlayerMoveComponent::InputInfo _input_info;
    //! ���
    std::weak_ptr<ratchet::component::player::PlayerComponent> _type_com;
    //! �J����
    std::weak_ptr<::ratchet::component::CameraComponent> _camera_com;
    //! ��]���Ȃ�
    bool _angular_freeze;
public:
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="speed"></param>
    virtual void InputMoveVelocity(float speed);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="angle"></param>
    /// <param name="speed"></param>
    virtual void InputMoveAngularVelocity(float ideal_angle, float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerMoveComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerMoveComponent(const PlayerMoveComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerMoveComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="speed"></param>
    void SetMoveSpeed(float speed);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="speed"></param>
    void SetAngularSpeed(float speed);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="radian"></param>
    void SetIdealAngle(float radian);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="flag"></param>
    void SetAngularFreezeFlag(bool flag);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDefaultMoveSpeed(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetMoveSpeed(void) const;
    /// <summary>
    /// ����
    /// </summary>
    bool IsAngularFreeze(void) const;
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
    /// ����
    /// </summary>
    /// <param name="move_speed"></param>
    /// <param name="angular_speed"></param>
    /// <param name="ideal_angle">���W�A��</param>
    /// <returns>���s</returns>
    bool Move(float move_speed, float angular_speed, float ideal_angle);
    /// <summary>
    /// �l��
    /// </summary>
    /// <param name="stick">�o��</param>
    /// <param name="move_angle">�o��</param>
    /// <returns></returns>
    bool AquireInputData(Mof::CVector2& stick, float& move_angle);
};
}
#endif // !RATCHET_COMPONENT_PLAYER_ACTION_PLAYER_MOVE_COMPONENT_H