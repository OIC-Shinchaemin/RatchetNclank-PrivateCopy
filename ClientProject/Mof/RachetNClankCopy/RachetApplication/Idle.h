#ifndef MY_IDLE_H
#define MY_IDLE_H


#include "Action.h"

#include "Velocity.h"


namespace my {
class Idle : public my::Action {
    using super = my::Action;
private:
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! ���x
    my::Velocity* _velocity;

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
    Idle();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Idle();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetVelocity(my::Velocity* ptr);
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
#endif // !MY_IDLE_H