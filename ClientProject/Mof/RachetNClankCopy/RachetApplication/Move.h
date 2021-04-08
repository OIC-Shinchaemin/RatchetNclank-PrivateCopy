#ifndef MY_MOVE_H
#define MY_MOVE_H


#include "Action.h"

#include "Velocity.h"


namespace my {
class Move : public my::Action {
    using super = my::Action;
private:
    //! �ړ����x
    float _move_speed;
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! ���x
    my::Velocity*_velocity;

    virtual void InputMoveVelocity(float speed);
    virtual void InputMoveVelocity(Mof::CVector2 stick, float speed);
    virtual void InputMoveAngularVelocity(Mof::CVector2 stick, float speed);
    virtual void InputMoveAngularVelocity(float angle, float speed);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool InactiveCondition(void) const override;
    /// <summary>
    /// ���s
    /// </summary>
    /// <param name="delta_time"></param>
    virtual void Execute(float delta_time) override;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Move();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Move();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetVelocity(my::Velocity* ptr);
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
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
};
}
#endif // !MY_MOVE_H