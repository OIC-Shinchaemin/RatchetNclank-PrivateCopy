#ifndef BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_RANGE_NODE_EXECUTOR_H
#define BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_RANGE_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"


namespace behaviour {
class IfTargetOutMeleeAttackRangeNodeExecutor : public behaviour::DecoratorNodeExecutor {
    using super = behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::Actor> actor;
        //! エネミー
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
        //! エネミー
        std::weak_ptr<ratchet::EnemyMeleeAttackComponent> melee_attack_com;
    };
private:
    //! 実行引数
    behaviour::IfTargetOutMeleeAttackRangeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    IfTargetOutMeleeAttackRangeNodeExecutor(const behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~IfTargetOutMeleeAttackRangeNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
            _node_args.melee_attack_com = actor->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::EnemyMeleeAttackComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::DecoratorNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_RANGE_NODE_EXECUTOR_H