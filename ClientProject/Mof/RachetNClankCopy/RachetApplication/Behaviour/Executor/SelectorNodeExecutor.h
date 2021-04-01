#ifndef BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H
#define BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H


#include "CompositeNodeExecutor.h"


namespace behaviour {
template <typename Actor>
class SelectorNodeExecutor : public behaviour::CompositeNodeExecutor<Actor> {
    using super = behaviour::CompositeNodeExecutor<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    SelectorNodeExecutor(const CompositeNodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SelectorNodeExecutor() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        // 実行済み
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else if
        // 実行開始
        super::_state = super::State::Running;
        for (auto& ptr : super::_children) {
            auto re = ptr->Execute(actor);
            if (re == super::Result::Sucess) {
                super::_state = super::State::Completed;
                return super::Result::Sucess;
            } // if
            else if (re == super::Result::None) {
                return super::Result::None;
            } // else if
        } // for
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
};
}
#endif // !BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H
