#ifndef RATCHET_BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/CompositeNode.h"


namespace ratchet { namespace behaviour {
class CompositeNodeExecutor : public ratchet::behaviour::NodeExecutor {
    using super = ratchet::behaviour::NodeExecutor;
protected:
    //! 実行中
    ratchet::behaviour::NodeExecutorPtr _current;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    CompositeNodeExecutor(const ratchet::behaviour::CompositeNodePtr& node) :
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
}
#endif // !RATCHET_BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H