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
    //! åˆæœŸä½ç½®
    Mof::CVector3 _init_position;
<<<<<<< HEAD
    //! •W“I
    std::weak_ptr<my::Actor>_target;
    //! ‹Šo
    std::shared_ptr<my::SightRecognition>  _sight;
    //! ‹Šo
    std::shared_ptr<my::Attack>_attack;
    //! ó‘Ô
    my::AIState _state;
<<<<<<< HEAD

    Behaviour::NodeExecutorPtr< std::shared_ptr< my::Enemy >> _behaviour_executor;

=======
    //! ó‘Ô
    my::EnemyState _enemy_state;
    //! ƒrƒwƒCƒrƒAÀs
=======
    //! æ¨™çš„
    std::weak_ptr<my::Character>_target;
    //! è¦–è¦š
    my::SightRecognition _sight;
    //! çŠ¶æ…‹
    my::AIState _state;
    //! ãƒ“ãƒ˜ã‚¤ãƒ“ã‚¢å®Ÿè¡Œ
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    behaviour::NodeExecutorPtr< EnemyPtr > _patrol_behaviour_executor;
    //! ãƒ“ãƒ˜ã‚¤ãƒ“ã‚¢å®Ÿè¡Œ
    behaviour::NodeExecutorPtr< EnemyPtr > _combat_behaviour_executor;
<<<<<<< HEAD
    //! ƒtƒ@ƒNƒgƒŠ[
    my::BehaviourExecutorFactory _behaviour_executor_factory;
public:
    bool ChangeToPatrolState(void);
    bool ChangeToCombatState(void);
    /// <summary>
    /// ƒQƒbƒ^[
=======
    
    /// <summary>
    /// ä½œæˆ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr< EnemyPtr >  CreatePatrolBehaviour(void);
    /// <summary>
    /// ä½œæˆ
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDistanceFromInitPosition(void);
    /// <summary>
<<<<<<< HEAD
    /// ”»’è
=======
    /// ã‚²ãƒƒã‚¿ãƒ¼
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTarget(void);
    /// <summary>
    /// åˆ¤å®š
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool TargetInAttackRange(void);
    /// <summary>
    /// è¦‹æ¸¡ã™
    /// </summary>
    /// <param name=""></param>
    bool OverLooking(void);
    /// <summary>
<<<<<<< HEAD
    /// ‰ŠúˆÊ’u‚É–ß‚é
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
    /// <summary>
    /// ’Ç‚¢‚©‚¯‚é
=======
    /// è¿½ã„ã‹ã‘ã‚‹
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ChaseTarget(void);
    /// <summary>
<<<<<<< HEAD
    /// UŒ‚
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Attack(void);
    void ChaseTo(Mof::CVector3 target, float speed, float angular_speed);
>>>>>>> origin/Ex55_WeaponAction
=======
    /// åˆæœŸä½ç½®ã«æˆ»ã‚‹
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// <summary>
    /// æç”»
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    Enemy();
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// ã‚»ãƒƒã‚¿ãƒ¼
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
<<<<<<< HEAD
    /// ƒQƒbƒ^[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetAttackSphere(void) const;
    /// <summary>
    /// ¶¬
    /// </summary>
    /// <param name=""></param>
    void GenerateCollisionObject(void);
    /// <summary>
    /// ‰Šú‰»
=======
    /// åˆæœŸåŒ–
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// å…¥åŠ›
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// æ›´æ–°
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    /// <summary>
    /// æç”»
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// è¦–èªå¯èƒ½åˆ¤å®š
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// ãƒ‡ãƒãƒƒã‚°
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;

    bool ChangeToMoveState(void);
    bool ChangeToAttackState(void);
};
}
#endif // !MY_ENEMY_H