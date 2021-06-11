#ifndef RACHET_ENEMY_MOVE_COMPONENT_H
#define RACHET_ENEMY_MOVE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace rachet {
class EnemyMoveComponent : public rachet::ActionComponent {
    using super = rachet::ActionComponent;
private:
    //! �ړ����x
    float _move_speed;
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! �ڕW
    Mof::CVector3 _target;
    //! ���x
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! ���
    std::weak_ptr<class EnemyStateComponent> _action_state_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;    
    //! �^
    std::weak_ptr<class EnemyComponent> _ENEMY_com;
    virtual void InputMoveVelocity(float speed);
    virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyMoveComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyMoveComponent(const EnemyMoveComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyMoveComponent();
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
    /// <param name="radian"></param>
    void SetTargetPosition(Mof::CVector3 position);
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
    virtual std::string_view GetStateType(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetTargetPosition(void) const;
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
    virtual std::shared_ptr<rachet::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
};
}
#endif // !RACHET_ENEMY_MOVE_COMPONENT_H