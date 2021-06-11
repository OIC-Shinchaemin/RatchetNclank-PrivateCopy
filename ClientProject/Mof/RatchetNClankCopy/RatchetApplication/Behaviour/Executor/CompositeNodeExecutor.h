#ifndef BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
#define BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/CompositeNode.h"


namespace behaviour {
class CompositeNodeExecutor : public behaviour::NodeExecutor {
    using super = behaviour::NodeExecutor;
protected:
    //! 実行中
    behaviour::NodeExecutorPtr _current;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    CompositeNodeExecutor(const behaviour::CompositeNodePtr& node) :
        super(node) {
        for (auto& ptr : node->GetChildren()) {
            auto add = ptr->CreateExecutor();
            add->SetParent(super::weak_from_this());
            super::_children.push_back(add);
        } // for
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
    virtual void Reset(void) override {
        super::Reset();
        //_current.reset();
        for (auto& ptr : super::_children) {
            ptr->Reset();
        } // for
    }
};
}
#endif // !BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H