#ifndef RATCHET_BEHAVIOUR_COMPOSITENODE_H
#define RATCHET_BEHAVIOUR_COMPOSITENODE_H


#include "Node.h"


namespace ratchet {  namespace behaviour {
class CompositeNode : public ratchet::behaviour::Node {
    using super = ratchet::behaviour::Node;
protected:
    //! �q�m�[�h
    ratchet::behaviour::NodeList _children;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    CompositeNode(const std::string& name) :
        super(name),
        _children() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CompositeNode() = default;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const ratchet::behaviour::NodeList& GetChildren(void) const { 
        return this->_children;
    }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::behaviour::NodeList& GetChildren(void) { 
        return this->_children; 
    }
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="node"></param>
    void AddChild(const ratchet::behaviour::NodePtr& node) { 
        _children.push_back(node); 
    }
};
using CompositeNodePtr = std::shared_ptr<ratchet::behaviour::CompositeNode>;
}
}
#endif // !RATCHET_BEHAVIOUR_COMPOSITENODE_H