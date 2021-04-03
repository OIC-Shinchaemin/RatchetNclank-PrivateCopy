#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"

#include <unordered_map>
#include <string>

#include "../SightRecognition.h"
#include "../Attack.h"
#include "../Factory/BehaviourExecutorFactory.h"


namespace my {
enum class AIState {
    Patrol,
    Combat
};
enum class EnemyState {
    Move,
    Attack,
};
class Enemy : public my::Character {
    using super = my::Character;
    using EnemyPtr = std::shared_ptr<my::Enemy>;
private:
    //! �����ʒu
    Mof::CVector3 _init_position;
    //! �W�I
    std::weak_ptr<my::Character>_target;
    //! ���o
    my::SightRecognition _sight;
    //! ���o
    my::Attack _attack;
    //! ���
    my::AIState _state;
    //! ���
    my::EnemyState _enemy_state;
    //! �r�w�C�r�A���s
    behaviour::NodeExecutorPtr< EnemyPtr > _patrol_behaviour_executor;
    //! �r�w�C�r�A���s
    behaviour::NodeExecutorPtr< EnemyPtr > _combat_behaviour_executor;
    //! �t�@�N�g���[
    my::BehaviourExecutorFactory _behaviour_executor_factory;
public:
    bool ChangeToPatrolState(void);
    bool ChangeToCombatState(void);
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDistanceFromInitPosition(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTarget(void);
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool TargetInAttackRange(void);
    /// <summary>
    /// ���n��
    /// </summary>
    /// <param name=""></param>
    bool OverLooking(void);
    /// <summary>
    /// �����ʒu�ɖ߂�
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
    /// <summary>
    /// �ǂ�������
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ChaseTarget(void);
    /// <summary>
    /// �U��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Attack(void);
    void ChaseTo(Mof::CVector3 target, float speed, float angular_speed);
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
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetAttackSphere(void) const;
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

    bool ChangeToMoveState(void);
    bool ChangeToAttackState(void);
};
}
#endif // !MY_ENEMY_H