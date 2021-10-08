#ifndef RATCHET_BEHAVIOUR_SEQUENCER_NODE_H
#define RATCHET_BEHAVIOUR_SEQUENCER_NODE_H


#include "CompositeNode.h"

#include "../Executor/SequencerNodeExecutor.h"


namespace ratchet::behaviour {
class SequencerNode : public behaviour::CompositeNode {
    using super = ratchet::behaviour::CompositeNode;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SequencerNode() :
        super("Sequencer") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SequencerNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const override {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<super>(ptr);
        return std::make_shared<ratchet::behaviour::SequencerNodeExecutor>(temp);
    }
};
}
#endif // !RATCHET_BEHAVIOUR_SEQUENCER_NODE_H