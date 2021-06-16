#ifndef RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyMoveComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace ratchet {
namespace behaviour {
class MoveToEnemyNodeExecutor : public ratchet::behaviour::ActionNodeExecutor {
    using super = ratchet::behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! エネミー
        std::weak_ptr<ratchet::component::enemy::EnemyComponent> ENEMY_com;
        //! エネミー
        std::weak_ptr<ratchet::component::enemy::EnemyMoveComponent> move_com;
        //! エネミー状態
        std::weak_ptr<ratchet::component::enemy::EnemyStateComponent> state_com;
        //! 近接攻撃
        std::weak_ptr<ratchet::component::enemy::EnemyMeleeAttackComponent> melee_attack_com;
        //! 遠距離攻撃
        std::weak_ptr<ratchet::component::enemy::EnemyRangedAttackComponent> ranged_attack_com;
    };
private:
    //! 実行引数
    ratchet::behaviour::MoveToEnemyNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    MoveToEnemyNodeExecutor(const ratchet::behaviour::NodePtr& node) :
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
            _node_args.ENEMY_com = actor->GetComponent<ratchet::component::enemy::EnemyComponent>();
            _node_args.state_com = actor->GetComponent<ratchet::component::enemy::EnemyStateComponent>();
            _node_args.move_com = actor->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::enemy::EnemyMoveComponent>();
            _node_args.melee_attack_com = actor->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::enemy::EnemyMeleeAttackComponent>();
            _node_args.ranged_attack_com = actor->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::enemy::EnemyRangedAttackComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::ActionNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H