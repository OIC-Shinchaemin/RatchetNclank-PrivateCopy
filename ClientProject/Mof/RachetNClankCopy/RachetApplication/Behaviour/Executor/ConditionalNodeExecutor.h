#ifndef BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H
#define BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "My/Core/Trait.h"

#include "../../Actor.h"


namespace behaviour {
class ConditionalNodeExecutor : public behaviour::NodeExecutor {
    using super = behaviour::NodeExecutor;
private:
    //! アクター
    std::weak_ptr<my::Actor> _actor;
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
        _actor = std::any_cast<std::shared_ptr<my::Actor>>(actor);
    }
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        // 実行開始
        super::_state = super::State::Running;
        auto temp = _actor.lock();
        //if (std::dynamic_pointer_cast<behaviour::ConditionalNodeBase>(super::_node)->Execute(temp)) {
        if (super::_node->Execute(temp)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
};
}
#endif // !BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H