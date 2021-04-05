#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"

#include <unordered_map>
#include <string>

#include "../SightRecognition.h"
<<<<<<< HEAD
#include "../Behaviour/Executor/INodeExecutor.h"
=======
#include "../Attack.h"
#include "../Factory/BehaviourExecutorFactory.h"
>>>>>>> origin/Ex55_WeaponAction


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
    //! ๅๆไฝ็ฝฎ
    Mof::CVector3 _init_position;
<<<<<<< HEAD
    //! WI
    std::weak_ptr<my::Actor>_target;
    //! o
    std::shared_ptr<my::SightRecognition>  _sight;
    //! o
    std::shared_ptr<my::Attack>_attack;
    //! ๓ิ
    my::AIState _state;
<<<<<<< HEAD

    Behaviour::NodeExecutorPtr< std::shared_ptr< my::Enemy >> _behaviour_executor;

=======
    //! ๓ิ
    my::EnemyState _enemy_state;
    //! rwCrAภs
=======
    //! ๆจ็
    std::weak_ptr<my::Character>_target;
    //! ่ฆ่ฆ
    my::SightRecognition _sight;
    //! ็ถๆ
    my::AIState _state;
    //! ใใใคใใขๅฎ่ก
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    behaviour::NodeExecutorPtr< EnemyPtr > _patrol_behaviour_executor;
    //! ใใใคใใขๅฎ่ก
    behaviour::NodeExecutorPtr< EnemyPtr > _combat_behaviour_executor;
<<<<<<< HEAD
    //! t@Ng[
    my::BehaviourExecutorFactory _behaviour_executor_factory;
public:
    bool ChangeToPatrolState(void);
    bool ChangeToCombatState(void);
    /// <summary>
    /// Qb^[
=======
    
    /// <summary>
    /// ไฝๆ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr< EnemyPtr >  CreatePatrolBehaviour(void);
    /// <summary>
    /// ไฝๆ
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDistanceFromInitPosition(void);
    /// <summary>
<<<<<<< HEAD
    /// ป่
=======
    /// ใฒใใฟใผ
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTarget(void);
    /// <summary>
    /// ๅคๅฎ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool TargetInAttackRange(void);
    /// <summary>
    /// ่ฆๆธกใ
    /// </summary>
    /// <param name=""></param>
    bool OverLooking(void);
    /// <summary>
<<<<<<< HEAD
    /// ๚สuษ฿้
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
    /// <summary>
    /// วขฉฏ้
=======
    /// ่ฟฝใใใใ
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ChaseTarget(void);
    /// <summary>
<<<<<<< HEAD
    /// U
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Attack(void);
    void ChaseTo(Mof::CVector3 target, float speed, float angular_speed);
>>>>>>> origin/Ex55_WeaponAction
=======
    /// ๅๆไฝ็ฝฎใซๆปใ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// <summary>
    /// ๆ็ป
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// ใณใณในใใฉใฏใฟ
    /// </summary>
    Enemy();
    /// <summary>
    /// ใในใใฉใฏใฟ
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// ใปใใฟใผ
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
<<<<<<< HEAD
    /// Qb^[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetAttackSphere(void) const;
    /// <summary>
    /// ถฌ
    /// </summary>
    /// <param name=""></param>
    void GenerateCollisionObject(void);
    /// <summary>
    /// ๚ป
=======
    /// ๅๆๅ
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// ๅฅๅ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// ๆดๆฐ
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// ๆ็ป
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// ่ฆ่ชๅฏ่ฝๅคๅฎ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// ใใใใฐ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;

    bool ChangeToMoveState(void);
    bool ChangeToAttackState(void);
};
}
#endif // !MY_ENEMY_H