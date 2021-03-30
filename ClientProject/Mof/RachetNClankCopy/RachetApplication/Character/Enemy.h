#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"

#include "../SightRecognition.h"


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
enum class AIState {
    Patrol,
    Combat
};
class Enemy : public my::Character {
    using super = my::Character;
private:
    //! �W�I
    std::weak_ptr<my::Character>_target;
    //std::vector< std::weak_ptr<my::Character>>_recognized;
    //! ���o
    my::SightRecognition _sight;
    //! ���
    my::AIState _state;
    //! ���x
    my::Velocity _velocity;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="rotate"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdateRotate(float delta_time, Mof::CVector3 rotate, Mof::CVector3 velocity);
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <param name="position"></param>
    /// <param name="velocity"></param>
    /// <returns></returns>
    Mof::CVector3 UpdatePosition(float delta_time, Mof::CVector3 position, Mof::CVector3 velocity);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Enemy();
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// ������
    /// </summary>
    /// <param name="transform"></param>
    /// <returns></returns>
    virtual bool Initialize(const def::Transform& transform) override;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// �X�V
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// �`��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ���F�\����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// �f�o�b�O
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_ENEMY_H