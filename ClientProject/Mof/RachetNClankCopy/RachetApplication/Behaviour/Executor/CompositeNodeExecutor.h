#ifndef BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
#define BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/CompositeNode.h"


namespace behaviour {
template<typename Actor>
class CompositeNodeExecutor : public NodeExecutor<Actor> {
    using super = NodeExecutor<Actor>;
protected:
    //! 実行中
    NodeExecutorPtr<Actor> _current;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    CompositeNodeExecutor(const CompositeNodePtr<Actor>& node) :
        super(node) {
        for (auto& ptr : node->GetChildren()) {
            auto add = ptr->CreateExecutor();
            add->SetParent(super::weak_from_this());
            super::_children.push_back(add);
        }
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CompositeNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        for (auto& ptr : super::_children) {
            ptr->Prepare(actor);
        } // for
    }
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override{
        super::Reset();
        _current.reset();
        for (auto& ptr : super::_children) {
            ptr->Reset();
        } // for
    }
};
}
#endif // !BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H