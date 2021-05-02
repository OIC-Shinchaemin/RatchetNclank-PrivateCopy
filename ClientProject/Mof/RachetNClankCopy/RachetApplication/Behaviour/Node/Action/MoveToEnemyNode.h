#ifndef BEHAVIOUR_MOVE_TO_ENEMY_NODE_H
#define BEHAVIOUR_MOVE_TO_ENEMY_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/MoveToEnemyNodeExecutor.h"


namespace behaviour {
class MoveToEnemyNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MoveToEnemyNode() :
        super("MoveToEnemyNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MoveToEnemyNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::MoveToEnemyNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::MoveToEnemyNodeExecutor::NodeArgs>(node_args);
        auto actor = args.actor.lock();

        auto target = args.enemy_com.lock()->GetTarget();
        _ASSERT_EXPR(!target.expired(), L"保持しているポインタが無効です");
        Mof::CSphere range_sphere;
        if (auto com = args.ranged_attack_com.lock(); com) {
            range_sphere = com->GetCanAttackRangeSphere();
        } // if
        else if (auto com = args.melee_attack_com.lock(); com) {
            range_sphere = com->GetCanAttackRangeSphere();
        } // else if

        auto pos = target.lock()->GetPosition();
        if (range_sphere.CollisionPoint(pos)) {
            return true;
        } // if
        

        if (args.state_com.lock()->CanTransition(state::EnemyActionStateType::kEnemyActionMoveState)) {
            args.state_com.lock()->ChangeState(state::EnemyActionStateType::kEnemyActionMoveState);
        //args.state_com.lock()->ChangeState("EnemyActionMoveState");
        } // if

        
        return false;
    };
};
}
#endif // !BEHAVIOUR_MOVE_TO_ENEMY_NODE_H