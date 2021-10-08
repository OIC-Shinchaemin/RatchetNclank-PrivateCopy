#ifndef RATCHET_BEHAVIOUR_IF_CLOSE_FROM_HOME_NODE_H
#define RATCHET_BEHAVIOUR_IF_CLOSE_FROM_HOME_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/IfCloseFromHomeNodeExecutor.h"


namespace ratchet::behaviour {
class IfCloseFromHomeNode : public ratchet::behaviour::DecoratorNodeBase {
    using super = ratchet::behaviour::DecoratorNodeBase;
    using Executor = ratchet::behaviour::IfCloseFromHomeNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    IfCloseFromHomeNode() :
        super("IfCloseFromHomeNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~IfCloseFromHomeNode() = default;
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

        float distance = Mof::CVector3Utilities::Distance(args.actor.lock()->GetInitialPosition(), args.actor.lock()->GetPosition());
        return !(distance > args.type_com.lock()->GetHomeDistance());
    }
};
}
#endif // !RATCHET_BEHAVIOUR_IF_CLOSE_FROM_HOME_NODE_H