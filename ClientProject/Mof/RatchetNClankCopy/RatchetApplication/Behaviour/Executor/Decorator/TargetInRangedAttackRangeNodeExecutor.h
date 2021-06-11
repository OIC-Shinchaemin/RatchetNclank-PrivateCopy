#ifndef RATCHET_BEHAVIOUR_TARGET_IN_RANGED_ATTACK_RANGE_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_TARGET_IN_RANGED_ATTACK_RANGE_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace ratchet { namespace behaviour {
class TargetInRangedAttackRangeNodeExecutor : public ratchet::behaviour::DecoratorNodeExecutor {
    using super = ratchet::behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::Actor> actor;
        //! エネミー
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
        //! 攻撃
        std::weak_ptr<ratchet::EnemyRangedAttackComponent> ranged_attack_com;
    };
private:
    //! 実行引数
    ratchet::behaviour::TargetInRangedAttackRangeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    TargetInRangedAttackRangeNodeExecutor(const ratchet::behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TargetInRangedAttackRangeNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
            _node_args.ranged_attack_com = actor->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::EnemyRangedAttackComponent>();
        } // if
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::DecoratorNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_TARGET_IN_RANGED_ATTACK_RANGE_NODE_EXECUTOR_H