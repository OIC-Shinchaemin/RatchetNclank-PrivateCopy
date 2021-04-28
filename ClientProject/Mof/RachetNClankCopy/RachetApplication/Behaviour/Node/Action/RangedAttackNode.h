#ifndef BEHAVIOUR_RANGED_ATTACK_NODE_H
#define BEHAVIOUR_RANGED_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/RangedAttackNodeExecutor.h"


namespace behaviour {
class RangedAttackNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    RangedAttackNode() :
        super("RangedAttackNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~RangedAttackNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::RangedAttackNodeExecutor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::RangedAttackNodeExecutor::NodeArgs>(node_args);
        args.ai_com.lock()->ChangeState("AICombatState");
        args.state_com.lock()->ChangeState("EnemyActionRangedAttackState");
        return false;
    }
};
}
#endif // !BEHAVIOUR_RANGED_ATTACK_NODE_H