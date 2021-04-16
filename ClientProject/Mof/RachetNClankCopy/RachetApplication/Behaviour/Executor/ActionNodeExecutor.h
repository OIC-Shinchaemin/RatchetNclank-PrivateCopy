#ifndef BEHAVIOUR_ACTION_NODE_EXECUTOR_H
#define BEHAVIOUR_ACTION_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "My/Core/Trait.h"


namespace behaviour {
template<typename Actor>
class ActionNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
private:
    //! アクター
    std::weak_ptr<typename ty::remove_shared<Actor>::type> _actor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    ActionNodeExecutor(const NodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ActionNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        _actor = std::any_cast<Actor>(actor);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual INodeExecutor<Actor>::Result Execute(void) override {
        //実行済み
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else if
        //実行開始
        super::_state = super::State::Running;
        auto temp = _actor.lock();
        //if (std::dynamic_pointer_cast<behaviour::ActionNodeBase>(super::_node)->Execute(temp)) {
        if (super::_node->Execute(temp)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        return super::Result::None;
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_EXECUTOR_H