#ifndef BEHAVIOUR_SIMPLEX_NODE_H
#define BEHAVIOUR_SIMPLEX_NODE_H


#include "ConditionalNode.h"


namespace behaviour {
class SimplexNode : public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
protected:
    //! �q�m�[�h
    behaviour::NodePtr _child;
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
    void SetChild(const behaviour::NodePtr& action) { _child = action; }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodePtr& GetChild(void) { return _child; }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const behaviour::NodePtr& GetChild(void) const { return _child; }
};
using SimplexNodePtr = std::shared_ptr<SimplexNode>;
}
#endif // !BEHAVIOUR_SIMPLEX_NODE_H