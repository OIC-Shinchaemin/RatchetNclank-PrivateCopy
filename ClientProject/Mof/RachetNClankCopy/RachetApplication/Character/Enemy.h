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
    //! 初期位置
    Mof::CVector3 _init_position;
<<<<<<< HEAD
    //! �W�I
    std::weak_ptr<my::Actor>_target;
    //! ���o
    std::shared_ptr<my::SightRecognition>  _sight;
    //! ���o
    std::shared_ptr<my::Attack>_attack;
    //! ���
    my::AIState _state;
<<<<<<< HEAD

    Behaviour::NodeExecutorPtr< std::shared_ptr< my::Enemy >> _behaviour_executor;

=======
    //! ���
    my::EnemyState _enemy_state;
    //! �r�w�C�r�A���s
=======
    //! 標的
    std::weak_ptr<my::Character>_target;
    //! 視覚
    my::SightRecognition _sight;
    //! 状態
    my::AIState _state;
    //! ビヘイビア実行
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    behaviour::NodeExecutorPtr< EnemyPtr > _patrol_behaviour_executor;
    //! ビヘイビア実行
    behaviour::NodeExecutorPtr< EnemyPtr > _combat_behaviour_executor;
<<<<<<< HEAD
    //! �t�@�N�g���[
    my::BehaviourExecutorFactory _behaviour_executor_factory;
public:
    bool ChangeToPatrolState(void);
    bool ChangeToCombatState(void);
    /// <summary>
    /// �Q�b�^�[
=======
    
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodeExecutorPtr< EnemyPtr >  CreatePatrolBehaviour(void);
    /// <summary>
    /// 作成
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    float GetDistanceFromInitPosition(void);
    /// <summary>
<<<<<<< HEAD
    /// ����
=======
    /// ゲッター
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
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
    /// 見渡す
    /// </summary>
    /// <param name=""></param>
    bool OverLooking(void);
    /// <summary>
<<<<<<< HEAD
    /// �����ʒu�ɖ߂�
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
    /// <summary>
    /// �ǂ�������
=======
    /// 追いかける
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ChaseTarget(void);
    /// <summary>
<<<<<<< HEAD
    /// �U��
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool Attack(void);
    void ChaseTo(Mof::CVector3 target, float speed, float angular_speed);
>>>>>>> origin/Ex55_WeaponAction
=======
    /// 初期位置に戻る
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool GoHome(void);
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
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
<<<<<<< HEAD
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    Mof::CSphere GetAttackSphere(void) const;
    /// <summary>
    /// ����
    /// </summary>
    /// <param name=""></param>
    void GenerateCollisionObject(void);
    /// <summary>
    /// ������
=======
    /// 初期化
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
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
    /// <summary>
    /// 描画
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual bool Render(void) override;
    /// <summary>
    /// 視認可能判定
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    bool ContainInRecognitionRange(Mof::CVector3 pos);
    /// <summary>
    /// デバッグ
    /// </summary>
    /// <param name=""></param>
    virtual void RenderDebug(void) override;

    bool ChangeToMoveState(void);
    bool ChangeToAttackState(void);
};
}
#endif // !MY_ENEMY_H