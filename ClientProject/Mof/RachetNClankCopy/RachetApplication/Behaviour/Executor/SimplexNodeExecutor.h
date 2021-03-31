#ifndef BEHAVIOUR_SIMPLEX_NODE_EXECUTOR_H
#define BEHAVIOUR_SIMPLEX_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/SimplexNode.h"


namespace behaviour {
template<typename Actor>
class SimplexNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    SimplexNodeExecutor(const SimplexNodePtr<Actor>& node) :
        super(node) {
        auto& ptr = node->GetChild();
        auto add = ptr->CreateExecutor();
        add->SetParent(super::weak_from_this());
        super::_children.push_back(add);
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SimplexNodeExecutor() = default;
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        super::Reset();
        for (auto& ptr : super::_children) {
            ptr->Reset();
        } // for
    }
};
}
#endif // !BEHAVIOUR_SIMPLEX_NODE_EXECUTOR_H