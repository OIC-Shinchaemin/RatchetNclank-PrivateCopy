#ifndef BEHAVIOUR_MELLE_ATTACK_NODE_H
#define BEHAVIOUR_MELLE_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/MeleeAttackNodeExecutor.h"


namespace behaviour {
class MeleeAttackNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MeleeAttackNode() :
        super("MeleeAttackNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MeleeAttackNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::MeleeAttackNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::MeleeAttackNodeExecutor::NodeArgs>(node_args);

        auto target = args.enemy_com.lock()->GetTarget();
        if (target.expired()) {
            return false;
        } // if

        auto pos = target.lock()->GetPosition();
        auto attack_com = args.attack_com.lock();
        if (attack_com->GetCanAttackRangeSphere().CollisionPoint(pos)) {
            args.ai_com.lock()->ChangeState("AICombatState");
            args.state_com.lock()->ChangeState("EnemyActionMeleeAttackState");
            return false;
        } // if

        return true;

    }
};
}
#endif // !BEHAVIOUR_MELLE_ATTACK_NODE_H