#ifndef BEHAVIOUR_AWAY_FROM_HOME_NODE_H
#define BEHAVIOUR_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"

#include "../../Executor/Condition/AwayFromHomeNodeExecutor.h"


namespace behaviour {
class AwayFromHomeNode : public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
    using Executor = behaviour::AwayFromHomeNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    AwayFromHomeNode() :
        super("AwayFromHomeNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~AwayFromHomeNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::AwayFromHomeNodeExecutor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);
        auto actor = args.actor.lock();

        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) > 2.0f;
    }
};
}
#endif // !BEHAVIOUR_AWAY_FROM_HOME_NODE_H