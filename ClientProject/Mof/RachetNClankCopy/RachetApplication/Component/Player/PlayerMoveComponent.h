#ifndef MY_PLAYER_MOVE_COMPONENT_H
#define MY_PLAYER_MOVE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace my {
class PlayerMoveComponent : public my::ActionComponent {
    using super = my::ActionComponent;
private:
    //! �ړ����x
    float _move_speed;
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! ���x
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<class PlayerStateComponent> _state_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    //! �J����
    std::weak_ptr<class CameraComponent> _camera_com;
    //! ���
    std::weak_ptr<class PlayerComponent> _type_com;
    /// <summary>
    /// �ύX
    /// </summary>
    /// <param name="name"></param>
    void ChageState(const std::string& name);
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
    virtual void InputMoveAngularVelocity(float angle, float speed);
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
    /// ����
    /// </summary>
    /// <param name="move_speed"></param>
    /// <param name="angular_speed"></param>
    /// <param name="ideal_angle"></param>
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
#endif // !MY_PLAYER_MOVE_COMPONENT_H