#ifndef BEHAVIOUR_SEQUENCER_NODE_H
#define BEHAVIOUR_SEQUENCER_NODE_H


#include "CompositeNode.h"

#include "../Executor/SequencerNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class SequencerNode : public behaviour ::CompositeNode<Actor> {
    using super = behaviour::CompositeNode<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SequencerNode(): 
        super("Sequencer") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SequencerNode() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual NodeExecutorPtr<Actor> CreateExecutor(void) const override {
       auto ptr = std::const_pointer_cast<Node<Actor>>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<super>(ptr);
        return std::make_shared<behaviour ::SequencerNodeExecutor<Actor>>(temp);
    }
};
}
#endif // !BEHAVIOUR_SEQUENCER_NODE_H