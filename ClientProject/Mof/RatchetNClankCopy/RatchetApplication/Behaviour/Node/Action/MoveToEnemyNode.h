#ifndef RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_H
#define RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/MoveToEnemyNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class MoveToEnemyNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
    using Executor = ratchet::behaviour::MoveToEnemyNodeExecutor;
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
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);
        auto target = args.ENEMY_com.lock()->GetTarget();

        if (args.state_com.lock()->CanTransition(ratchet::state::EnemyActionStateType::kEnemyActionMoveState)) {
            args.move_com.lock()->SetTargetPosition(target.lock()->GetPosition());
            args.state_com.lock()->ChangeState(ratchet::state::EnemyActionStateType::kEnemyActionMoveState);
        } // if

        Mof::CSphere range_sphere;
        if (auto com = args.melee_attack_com.lock(); com) {
            range_sphere = com->GetCanAttackRangeSphere();
            
            auto pos = target.lock()->GetPosition();
            if (range_sphere.CollisionPoint(pos)) {
                return true;
            } // if
        } // if
        return false;
    };
};
}
}
#endif // !RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_H