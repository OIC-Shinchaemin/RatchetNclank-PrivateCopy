#ifndef BEHAVIOUR_TARGET_IN_MELEE_ATTACK_RANGE_NODE_EXECUTOR_H
#define BEHAVIOUR_TARGET_IN_MELEE_ATTACK_RANGE_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"


namespace behaviour {
class TargetInMeleeAttackRangeNodeExecutor : public behaviour::DecoratorNodeExecutor {
    using super = behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<rachet::Actor> actor;
        //! エネミー
        std::weak_ptr<rachet::EnemyComponent> ENEMY_com;
        //! エネミー
        std::weak_ptr<rachet::EnemyMeleeAttackComponent> melee_attack_com;
    };
private:
    //! 実行引数
    behaviour::TargetInMeleeAttackRangeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    TargetInMeleeAttackRangeNodeExecutor(const behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TargetInMeleeAttackRangeNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<rachet::EnemyComponent>();
            _node_args.melee_attack_com = actor->GetComponent<rachet::ActionComponent>()->GetComponent<rachet::EnemyMeleeAttackComponent>();
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
#endif // !BEHAVIOUR_TARGET_RECOGNITION_NODE_EXECUTOR_H