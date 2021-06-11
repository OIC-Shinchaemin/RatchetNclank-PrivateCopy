#ifndef RATCHET_ENEMY_IDLE_COMPONENT_H
#define RATCHET_ENEMY_IDLE_COMPONENT_H


#include "../ActionComponent.h"

#include <memory>


namespace ratchet {
class EnemyIdleComponent : public ratchet::ActionComponent {
    using super = ratchet::ActionComponent;
private:
    //! ��]���x
    float _angular_speed;
    //! ���W�A��
    float _ideal_angle;
    //! ���x
    std::weak_ptr<class VelocityComponent> _velocity_com;
    //! ���[�V����
    std::weak_ptr<class MotionStateComponent> _motion_state_com;
    
    virtual void InputMoveAngularVelocity(float angle, float speed);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    EnemyIdleComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    EnemyIdleComponent(const EnemyIdleComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~EnemyIdleComponent();
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
    float GetIdealAngle(void) const;
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
    virtual std::shared_ptr<ratchet::component::Component> Clone(void) override;
    /// <summary>
    /// �J�n
    /// </summary>
    /// <param name=""></param>
    /// <returns>����</returns>
    virtual bool Start(void) override;
};
}
#endif // !RATCHET_ENEMY_IDLE_COMPONENT_H