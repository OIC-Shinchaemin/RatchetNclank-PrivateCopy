#ifndef BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H
#define BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H


#include "NodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ConditionalNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    ConditionalNodeExecutor(const NodePtr<Actor>& node) : 
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ConditionalNodeExecutor() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        // 実行開始
        super::_state = super::State::Running;
        if (super::_node->Execute(actor)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
};
}
#endif // !BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H