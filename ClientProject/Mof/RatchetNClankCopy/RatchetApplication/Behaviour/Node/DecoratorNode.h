#ifndef RATCHET_BEHAVIOUR_DECORATOR_NODE_H
#define RATCHET_BEHAVIOUR_DECORATOR_NODE_H


#include "SimplexNode.h"

#include "../Executor/DecoratorNodeExecutor.h"


namespace ratchet::behaviour {
class DecoratorNodeBase : public ratchet::behaviour::SimplexNode {
    using super = ratchet::behaviour::SimplexNode;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DecoratorNodeBase() :
        super("Decorator") {
    }
    DecoratorNodeBase(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~DecoratorNodeBase() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual NodeExecutorPtr CreateExecutor(void) const override {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<ratchet::behaviour::DecoratorNodeBase>(ptr);
        return std::make_shared<ratchet::behaviour::DecoratorNodeExecutor>(temp);
    }
};
}
#endif // !RATCHET_BEHAVIOUR_DECORATOR_NODE_H