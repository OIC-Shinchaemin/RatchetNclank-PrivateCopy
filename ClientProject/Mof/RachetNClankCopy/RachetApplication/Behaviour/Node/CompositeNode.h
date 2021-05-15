#ifndef BEHAVIOUR_COMPOSITENODE_H
#define BEHAVIOUR_COMPOSITENODE_H


#include "Node.h"


namespace behaviour {
class CompositeNode : public behaviour::Node {
    using super = behaviour::Node;
protected:
    //! 子ノード
    behaviour::NodeList _children;
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
    const behaviour::NodeList& GetChildren(void) const { 
        return this->_children;
    }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodeList& GetChildren(void) { 
        return this->_children; 
    }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="node"></param>
    void AddChild(const behaviour::NodePtr& node) { 
        _children.push_back(node); 
    }
};
using CompositeNodePtr = std::shared_ptr<behaviour::CompositeNode>;
}
#endif // !BEHAVIOUR_COMPOSITENODE_H