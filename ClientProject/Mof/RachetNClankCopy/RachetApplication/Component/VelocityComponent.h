#ifndef MY_VELOCITY_COMPONENT_H
#define MY_VELOCITY_COMPONENT_H


#include "UpdateComponent.h"

#include <memory>


namespace my {
class VelocityComponent : public my::UpdateComponent {
    using super = my::UpdateComponent;
private:    
    //! ���x
    Mof::CVector3 _velocity;
    //! �p���x
    Mof::CVector3 _angular_velocity;
    //! �t�^���x
    Mof::CVector3 _velocity_force;
    //! �t�^���x
    Mof::CVector3 _angular_velocity_force;
    //! ����Y
    float _gravity;
    //! �����W��XZ
    float _drag;
    //! �����W��
    float _angular_drag;
    //! �e������
    bool _use_gravity;
    //! �x�~
    bool _sleep;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="priority"></param>
    VelocityComponent(int priority);
    /// <summary>
    /// �R�s�[�R���X�g���N�^
    /// </summary>
    /// <param name="obj"></param>
    VelocityComponent(const VelocityComponent& obj);
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~VelocityComponent();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetVelocity(Mof::CVector3 value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetGravity(float value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetDrag(float value);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="use"></param>
    void SetUseGravity(bool use);
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="b"></param>
    void SetSleep(bool b);
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
    Mof::CVector3 GetVelocity(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetAngularVelocity(void) const;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CVector3 GetVelocityForce(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool IsSleep(void) const;
    /// <summary>
    /// �ǉ�
    /// </summary>
    void AddVelocityForce(Mof::CVector3 accele);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="accele"></param>
    void AddAngularVelocityForce(Mof::CVector3 accele);
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
};
}
#endif // !MY_VELOCITY_COMPONENT_H