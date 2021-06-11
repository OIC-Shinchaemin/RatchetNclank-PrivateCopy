#ifndef BEHAVIOUR_CHANGE_COMBAT_NODE_H
#define BEHAVIOUR_CHANGE_COMBAT_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/ChangeCombatNodeExecutor.h"


namespace behaviour {
class ChangeCombatNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
    using Executor = behaviour::ChangeCombatNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ChangeCombatNode() :
        super("ChangeCombatNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ChangeCombatNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);
        args.ai_com.lock()->ChangeState("AICombatState");
        return true;
    }
};
}
#endif // !BEHAVIOUR_CHANGE_COMBAT_NODE_H