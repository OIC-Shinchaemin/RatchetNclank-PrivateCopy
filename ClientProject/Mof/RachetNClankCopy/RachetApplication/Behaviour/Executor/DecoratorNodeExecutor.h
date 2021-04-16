#ifndef BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H
#define BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H


#include "SimplexNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class DecoratorNodeExecutor : public behaviour::SimplexNodeExecutor<Actor> {
    using super = behaviour::SimplexNodeExecutor<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    DecoratorNodeExecutor(const SimplexNodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~DecoratorNodeExecutor() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual INodeExecutor<Actor>::Result Execute(void) override {
        // 実行開始
        super::_state = super::State::Running;
        auto temp = Actor();
        if (super::_node->Execute(temp)) {
            for (auto& ptr : super::_children) {
                auto re = ptr->Execute();
                if (re == super::Result::Sucess) {
                    super::_state = super::State::Completed;
                    return super::Result::Sucess;
                } // if
                else if (re == super::Result::None) {
                    return super::Result::None;
                } // else if
                else {
                    super::_state = super::State::Incompleted;
                    return super::Result::Failure;
                } // else
            } // for
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
};
}
#endif // !BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H