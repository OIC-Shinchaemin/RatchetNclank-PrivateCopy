#ifndef RATCHET_BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_H
#define RATCHET_BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_H


#include "../ConditionalNode.h"

#include "../../Executor/Condition/NotTargetRecognitionNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class NotTargetRecognitionNode : public ratchet::behaviour::ConditionalNodeBase {
    using super = ratchet::behaviour::ConditionalNodeBase;
    using Executor = ratchet::behaviour::NotTargetRecognitionNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    NotTargetRecognitionNode() :
        super("NotTargetRecognition") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotTargetRecognitionNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<ratchet::behaviour::TargetRecognitionNodeExecutor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<ratchet::behaviour::TargetRecognitionNodeExecutor::NodeArgs>(node_args);
        auto target = args.ENEMY_com.lock()->GetTarget();
        return target.expired();
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_H