#ifndef BEHAVIOUR_NOT_RECOGNIZING_TARGET_NODE_H
#define BEHAVIOUR_NOT_RECOGNIZING_TARGET_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/NotRecognizingTargetNodeExecutor.h"


namespace behaviour {
class NotRecognizingTargetNode : public behaviour::DecoratorNodeBase {
    using super = behaviour::DecoratorNodeBase;
    using Executor = behaviour::NotRecognizingTargetNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    NotRecognizingTargetNode() :
        super("NotRecognizingTargetNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotRecognizingTargetNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<behaviour::SimplexNode>(ptr);
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

        auto target = args.enemy_com.lock()->GetTarget();
        return target.expired();
    }
};
}
#endif // !BEHAVIOUR_NOT_RECOGNIZING_TARGET_NODE_H