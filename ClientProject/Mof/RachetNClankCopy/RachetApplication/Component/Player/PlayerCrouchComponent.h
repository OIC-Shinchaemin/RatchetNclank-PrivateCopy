#ifndef MY_PLAYER_CROUCH_COMPONENT_H
#define MY_PLAYER_CROUCH_COMPONENT_H


#include "PlayerActionComponent.h"

#include <memory>


namespace my {
class PlayerCrouchComponent : public my::PlayerActionComponent {
    using super = my::PlayerActionComponent;
private:
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! �J����
    std::weak_ptr<class CameraComponent> _camera_com;
public:
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="speed"></param>
    //virtual void InputMoveVelocity(float speed);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name="angle"></param>
    /// <param name="speed"></param>
    //virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    PlayerCrouchComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    PlayerCrouchComponent(const PlayerCrouchComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~PlayerCrouchComponent();
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
    //bool Move(float move_speed, float angular_speed, float ideal_angle);
    /// <summary>
    /// �l��
    /// </summary>
    /// <param name="stick">�o��</param>
    /// <param name="move_angle">�o��</param>
    /// <returns></returns>
    //bool AquireInputData(Mof::CVector2& stick, float& move_angle);
};
}
#endif // !MY_PLAYER_CROUCH_COMPONENT_H