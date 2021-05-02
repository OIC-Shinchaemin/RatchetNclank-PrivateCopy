#ifndef BEHAVIOUR_SIMPLEX_NODE_H
#define BEHAVIOUR_SIMPLEX_NODE_H


#include "ConditionalNode.h"


namespace behaviour {
class SimplexNode : public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
protected:
    //! 子ノード
    behaviour::NodePtr _child;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    SimplexNode(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SimplexNode() = default;
    /// <summary>
    /// セッター
    /// </summary>
    /// <param name="node"></param>
    void SetChild(const behaviour::NodePtr& action) { _child = action; }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    behaviour::NodePtr& GetChild(void) { return _child; }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const behaviour::NodePtr& GetChild(void) const { return _child; }
};
using SimplexNodePtr = std::shared_ptr<SimplexNode>;
}
#endif // !BEHAVIOUR_SIMPLEX_NODE_H