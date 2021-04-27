#ifndef BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H
#define BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"

#include "../../Executor/Condition/NotAwayFromHomeNodeExecutor.h"


namespace behaviour {
class NotAwayFromHomeNode: public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    NotAwayFromHomeNode() :
        super("NotAwayFromHomeNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotAwayFromHomeNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::NotAwayFromHomeNodeExecutor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::NotAwayFromHomeNodeExecutor::NodeArgs>(node_args);
        auto actor = args.actor.lock();

        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) < 9.5f;
    }
};
}
#endif // !BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H