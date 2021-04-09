#ifndef MY_ENEMY_H
#define MY_ENEMY_H


#include "Character.h"
#include "My/Core/Observer.h"

#include <unordered_map>
#include <string>

#include "My/Core/StateMachine.h"
#include "../Timer.h"
#include "../Idle.h"
#include "../Move.h"
#include "../SightRecognition.h"
#include "../Attack.h"


namespace my {
class Enemy : public my::Character {
    using super = my::Character;
    using EnemyPtr = std::shared_ptr<my::Enemy>;
public:
    enum class MotionType {
        IdleWait,
        MoveRun,
        AttackOne,
        CountMax,
    };
private:
    //! 初期位置
    Mof::CVector3 _init_position;
    //! 標的
    std::weak_ptr<my::Actor>_target;
    //! タイマー
    my::Timer _thinking_time;


    //! 待機
    std::shared_ptr<my::Idle> _idle;
    //! 攻撃
    std::shared_ptr<my::Move> _move;
    //! 視覚
    std::shared_ptr<my::SightRecognition> _sight;
    //! 攻撃
    std::shared_ptr<my::Attack>_attack;



    //! 状態
    my::StateMachine _motion_state_machine;
    //! 状態
    my::StateMachine _ai_state_machine;

    template<class State>
    void RegisterMotionState(my::StateMachine& out) {
        auto shared_this = std::dynamic_pointer_cast<my::Enemy>(shared_from_this());

        auto ptr = std::make_shared<State>();
        ptr->SetLPMeshMotionController(_motion);
        ptr->SetMotionNames(_motion_names);
        ptr->SetEnemy(shared_this);
        ptr->SetVelocity(&_velocity);
        ptr->SetAttack(_attack);
        out.RegisterState(ptr);
    }
    template<class State>
    void RegisterAIState(my::StateMachine& out) {
        auto shared_this = std::dynamic_pointer_cast<my::Enemy>(shared_from_this());
        auto ptr = std::make_shared<State>();
        ptr->SetEnemy(shared_this);
        ptr->GenerateBehaviourExecutor();
        out.RegisterState(ptr);
    }
public:
    void ChaseTo(Mof::CVector3 target, float speed, float angular_speed);
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDistanceFromInitPosition(void);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool HasTarget(void);
    /// <summary>
    /// 判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool TargetInAttackRange(void);
    /// <summary>
    /// 初期位置に戻る
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
    /// <summary>
    /// 見渡す
    /// </summary>
    /// <param name=""></param>
    bool OverLooking(void);
    /// <summary>
    /// 追いかける
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ChaseTarget(void);
    /// <summary>
    /// 攻撃
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Attack(void);
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name="ray"></param>
    /// <param name="length"></param>
    /// <param name="color"></param>
    void RenderRay(const Mof::CRay3D& ray, float length, int color);
    void RenderRay(Mof::Vector3 start, float degree_y);
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Enemy();
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~Enemy();
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="ptr"></param>
    void SetTarget(const std::shared_ptr<my::Character>& ptr);
    /// <summary>
    /// 生成
    /// </summary>
    /// <param name=""></param>
    void GenerateCollisionObject(void);
    /// <summary>
    /// 初期化
    /// </summary>
    /// <param name="param"></param>
    /// <returns></returns>
    virtual bool Initialize(my::Actor::Param* param) override;
    /// <summary>
    /// 入力
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Input(void) override;
    /// <summary>
    /// 更新
    /// </summary>
    /// <param name="delta_time"></param>
    /// <returns></returns>
    virtual bool Update(float delta_time);
    bool ChangeToPatrolState(void);
    bool ChangeToCombatState(void);
    /// <summary>
    /// 変更
    /// </summary>
    /// <param name="next"></param>
    /// <returns></returns>
    bool ChangeMotionState(const char* next_state);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;
};
}
#endif // !MY_ENEMY_H