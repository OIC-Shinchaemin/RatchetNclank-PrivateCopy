#ifndef RATCHET_BEHAVIOUR_SIMPLEX_NODE_H
#define RATCHET_BEHAVIOUR_SIMPLEX_NODE_H


#include "ConditionalNode.h"


namespace ratchet {
namespace behaviour {
class SimplexNode : public ratchet::behaviour::ConditionalNodeBase {
    using super = ratchet::behaviour::ConditionalNodeBase;
protected:
    //! �q�m�[�h
    ratchet::behaviour::NodePtr _child;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    SimplexNode(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SimplexNode() = default;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="node"></param>
    void SetChild(const ratchet::behaviour::NodePtr& action) {
        this->_child = action;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::behaviour::NodePtr& GetChild(void) {
        return this->_child;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const ratchet::behaviour::NodePtr& GetChild(void) const { return _child; }
};
using SimplexNodePtr = std::shared_ptr<SimplexNode>;
}
}
#endif // !RATCHET_BEHAVIOUR_SIMPLEX_NODE_H