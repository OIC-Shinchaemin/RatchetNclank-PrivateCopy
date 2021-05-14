#ifndef BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H
#define BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyMoveComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace behaviour {
class MoveToEnemyNodeExecutor : public behaviour::ActionNodeExecutor {
    using super = behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<my::Actor> actor;
        //! エネミー
        std::weak_ptr<my::EnemyComponent> enemy_com;
        //! エネミー
        std::weak_ptr<my::EnemyMoveComponent> move_com;
        //! エネミー状態
        std::weak_ptr<my::EnemyStateComponent> state_com;
        //! 近接攻撃
        std::weak_ptr<my::EnemyMeleeAttackComponent> melee_attack_com;
        //! 遠距離攻撃
        std::weak_ptr<my::EnemyRangedAttackComponent> ranged_attack_com;
    };
private:
    //! 実行引数
    behaviour::MoveToEnemyNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    MoveToEnemyNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MoveToEnemyNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.enemy_com = actor->GetComponent<my::EnemyComponent>();
            _node_args.state_com = actor->GetComponent<my::EnemyStateComponent>();
            _node_args.move_com = actor->GetComponent<my::EnemyMoveComponent>();
            _node_args.melee_attack_com= actor->GetComponent<my::EnemyMeleeAttackComponent>();
            _node_args.ranged_attack_com = actor->GetComponent<my::EnemyRangedAttackComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::ActionNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H