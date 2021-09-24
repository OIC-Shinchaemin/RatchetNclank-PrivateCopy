#ifndef RATCHET_BEHAVIOUR_CONDITIONAL_NODE_H
#define RATCHET_BEHAVIOUR_CONDITIONAL_NODE_H

#include "Node.h"

#include "../Executor/ConditionalNodeExecutor.h"


namespace ratchet::behaviour {
class ConditionalNodeBase : public ratchet::behaviour::Node {
    using super = ratchet::behaviour::Node;
public:
    enum class Operator {
        Equal, // ==
        NotEqual, // !=
        Less, // <
        LessEqual, // <=
        Greater, // >
        GreaterEqual, // >=
    };
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ConditionalNodeBase() :
        super("Conditional") {
    }
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    ConditionalNodeBase(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ConditionalNodeBase() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const override {
        auto ptr = std::const_pointer_cast<super>(super::shared_from_this());
        return std::make_shared<ratchet::behaviour::ConditionalNodeExecutor>(ptr);
    }
};
}
#endif // !RATCHET_BEHAVIOUR_CONDITIONAL_NODE_H