#ifndef RATCHET_BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_NODE_H
#define RATCHET_BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/IfTargetOutMeleeAttackRangeNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class IfTargetOutMeleeAttackRangeNode : public ratchet::behaviour::DecoratorNodeBase {
    using super = ratchet::behaviour::DecoratorNodeBase;
    using Executor = ratchet::behaviour::IfTargetOutMeleeAttackRangeNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    IfTargetOutMeleeAttackRangeNode() :
        super("IfTargetOutMeleeAttackRangeNode ") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~IfTargetOutMeleeAttackRangeNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<ratchet::behaviour::SimplexNode>(ptr);
        return std::make_shared<Executor>(temp);
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
        if (target.expired()) {
            return false;
        } // if

        auto pos = target.lock()->GetPosition();
        auto range_sphere = args.melee_attack_com.lock()->GetCanAttackRangeSphere();
        return !range_sphere.CollisionPoint(pos);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_NODE_H