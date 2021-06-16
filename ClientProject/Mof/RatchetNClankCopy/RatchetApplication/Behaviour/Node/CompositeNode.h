#ifndef RATCHET_BEHAVIOUR_COMPOSITENODE_H
#define RATCHET_BEHAVIOUR_COMPOSITENODE_H


#include "Node.h"


namespace ratchet {  namespace behaviour {
class CompositeNode : public ratchet::behaviour::Node {
    using super = ratchet::behaviour::Node;
protected:
    //! 子ノード
    ratchet::behaviour::NodeList _children;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    CompositeNode(const std::string& name) :
        super(name),
        _children() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CompositeNode() = default;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const ratchet::behaviour::NodeList& GetChildren(void) const { 
        return this->_children;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    ratchet::behaviour::NodeList& GetChildren(void) { 
        return this->_children; 
    }
    /// <summary>
    /// 追加
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