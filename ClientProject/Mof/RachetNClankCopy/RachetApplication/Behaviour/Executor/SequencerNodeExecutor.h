#ifndef BEHAVIOUR_SEQUENCER_NODE_EXECUTOR_H
#define BEHAVIOUR_SEQUENCER_NODE_EXECUTOR_H


#include "CompositeNodeExecutor.h"


namespace behaviour {
class SequencerNodeExecutor : public behaviour::CompositeNodeExecutor {
    using super = behaviour::CompositeNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    SequencerNodeExecutor(const behaviour::CompositeNodePtr& node) :
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~SequencerNodeExecutor() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        if (super::_current) {
            auto re = super::_current->Execute();
            if (re != super::Result::None) {
                super::_current = nullptr;
            } // if
            return super::Result::None;
        } // if


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
            auto re = ptr->Execute();
            if (re == super::Result::Failure) {
                super::_state = super::State::Incompleted;
                return super::Result::Failure;
            } // if
            else if (re == super::Result::None) {
                return super::Result::None;
            } // else if
        } // for
        super::_state = super::State::Completed;
        return super::Result::Sucess;
    }
};
}
#endif // !BEHAVIOUR_SEQUENCER_NODE_EXECUTOR_H