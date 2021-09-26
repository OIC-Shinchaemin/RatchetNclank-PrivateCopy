#ifndef RATCHET_BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_NODE_H
#define RATCHET_BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/IfTargetOutMeleeAttackRangeNodeExecutor.h"


namespace ratchet::behaviour {
class IfTargetOutMeleeAttackRangeNode : public ratchet::behaviour::DecoratorNodeBase {
    using super = ratchet::behaviour::DecoratorNodeBase;
    using Executor = ratchet::behaviour::IfTargetOutMeleeAttackRangeNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    IfTargetOutMeleeAttackRangeNode() :
        super("IfTargetOutMeleeAttackRangeNode ") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~IfTargetOutMeleeAttackRangeNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<ratchet::behaviour::SimplexNode>(ptr);
        return std::make_shared<Executor>(temp);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
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
#endif // !RATCHET_BEHAVIOUR_IF_TARGET_OUT_MELEE_ATTACK_NODE_H