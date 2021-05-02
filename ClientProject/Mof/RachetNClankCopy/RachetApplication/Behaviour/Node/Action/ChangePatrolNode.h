#ifndef BEHAVIOUR_CHANGE_PATROL_NODE_H
#define BEHAVIOUR_CHANGE_PATROL_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/ChangePatrolNodeExecutor.h"


namespace behaviour {
class ChangePatrolNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ChangePatrolNode() :
        super("ChangePatrolNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ChangePatrolNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::ChangePatrolNodeExecutor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::ChangePatrolNodeExecutor::NodeArgs>(node_args);
        // can transition state
        // if()
        args.ai_com.lock()->ChangeState("AIPatrolState");
        return true;
    }
};
}
#endif // !BEHAVIOUR_CHANGE_PATROL_NODE_H