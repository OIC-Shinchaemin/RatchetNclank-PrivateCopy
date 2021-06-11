#ifndef BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H
#define BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../../Actor.h"


namespace behaviour {
class ConditionalNodeExecutor : public behaviour::NodeExecutor {
    using super = behaviour::NodeExecutor;
protected:
    //! アクター
    std::weak_ptr<rachet::Actor> _actor;
    /// <summary>
    /// ノード実行
    /// </summary>
    /// <param name="args"></param>
    /// <returns></returns>
    behaviour::INodeExecutor::Result ConditionalNodeExecute(std::any args) {
        // 実行開始
        super::_state = super::State::Running;
        if (super::_node->Execute(args)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    ConditionalNodeExecutor(const behaviour::NodePtr& node) :
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ConditionalNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        _actor = std::any_cast<std::shared_ptr<rachet::Actor>>(actor);
    }
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        auto temp = _actor.lock();
        return this->ConditionalNodeExecute(temp);
    }
};
}
#endif // !BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H