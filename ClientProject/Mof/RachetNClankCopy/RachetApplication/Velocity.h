#ifndef MY_VELOCITY_H
#define MY_VELOCITY_H


#include <Mof.h>


namespace my {
class Velocity {
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
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Velocity();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~Velocity();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="value"></param>
    void SetVelocity(Mof::CVector3 value);
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
    /// �ǉ�
    /// </summary>
    void AddVelocityForce(Mof::CVector3 accele);
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="accele"></param>
    void AddAngularVelocityForce(Mof::CVector3 accele);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time">����</param>
    /// <returns></returns>
    bool Update(float delta_time);
};
}
#endif // !MY_VELOCITY_H