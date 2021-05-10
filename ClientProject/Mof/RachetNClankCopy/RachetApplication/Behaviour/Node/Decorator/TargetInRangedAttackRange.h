#ifndef BEHAVIOUR_TARGET_IN_RANGED_ATTACK_NODE_H
#define BEHAVIOUR_TARGET_IN_RANGED_ATTACK_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/TargetInRangedAttackRangeNodeExecutor.h"


namespace behaviour {
class TargetInRangedAttackRangeNode : public behaviour::DecoratorNodeBase {
    using super = behaviour::DecoratorNodeBase;
    using Executor = behaviour::TargetInRangedAttackRangeNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TargetInRangedAttackRangeNode() :
        super("TargetInRangedAttackRangeNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TargetInRangedAttackRangeNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<behaviour::SimplexNode>(ptr);
        return std::make_shared<Executor>(temp);
        //auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        //return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);
        
        auto target = args.enemy_com.lock()->GetTarget();
        if (target.expired()) {
            return false;
        } // if
       
        auto pos = target.lock()->GetPosition();
        auto range_sphere = args.ranged_attack_com.lock()->GetCanAttackRangeSphere();
        if (range_sphere.CollisionPoint(pos)) {
            return true;
        } // if
        return false;
    }
};
}
#endif // !BEHAVIOUR_TARGET_IN_RANGED_ATTACK_NODE_H