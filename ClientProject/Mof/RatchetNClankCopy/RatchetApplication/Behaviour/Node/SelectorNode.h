#ifndef RATCHET_BEHAVIOUR_SELECTOR_NODE_H
#define RATCHET_BEHAVIOUR_SELECTOR_NODE_H


#include "CompositeNode.h"

#include "../Executor/SelectorNodeExecutor.h"


namespace ratchet::behaviour {
class SelectorNode : public ratchet::behaviour::CompositeNode {
    using super = ratchet::behaviour::CompositeNode;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SelectorNode() :
        super("Selector") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SelectorNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<super>(ptr);
        return std::make_shared<ratchet::behaviour::SelectorNodeExecutor>(temp);
    }
};
}
#endif // !RATCHET_BEHAVIOUR_SELECTOR_NODE_H