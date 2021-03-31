#ifndef BEHAVIOUR_SIMPLEX_NODE_H
#define BEHAVIOUR_SIMPLEX_NODE_H


#include "ConditionalNode.h"


namespace behaviour {
template < typename Actor>
class SimplexNode : public behaviour::ConditionalNodeBase<Actor> {
    using super = behaviour::ConditionalNodeBase<Actor>;
protected:
    //! �q�m�[�h
    NodePtr<Actor> _child;
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
    void SetChild(const NodePtr<Actor>& action) { _child = action; }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    NodePtr<Actor>& GetChild(void) { return _child; }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const NodePtr<Actor>& GetChild(void) const { return _child; }
};
template<typename Actor> using SimplexNodePtr = std::shared_ptr<SimplexNode<Actor>>;
}
#endif // !BEHAVIOUR_SIMPLEX_NODE_H