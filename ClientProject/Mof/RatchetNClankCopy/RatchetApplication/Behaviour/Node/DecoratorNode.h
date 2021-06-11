#ifndef BEHAVIOUR_DECORATOR_NODE_H
#define BEHAVIOUR_DECORATOR_NODE_H


#include "SimplexNode.h"

#include "../Executor/DecoratorNodeExecutor.h"


namespace behaviour {
class DecoratorNodeBase : public behaviour::SimplexNode {
    using super = behaviour::SimplexNode;
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
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<behaviour::DecoratorNodeBase>(ptr);
        return std::make_shared<behaviour::DecoratorNodeExecutor>(temp);
    }
};
}
#endif // !BEHAVIOUR_DECORATOR_NODE_H