#ifndef BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_EXECUTOR_H
#define BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_EXECUTOR_H


#include "../ConditionalNodeExecutor.h"


namespace behaviour {
class NotAwayFromHomeNodeExecutor : public behaviour::ConditionalNodeExecutor {
    using super = behaviour::ConditionalNodeExecutor;
public:
    struct NodeArgs {
        //! アクター
        std::weak_ptr<ratchet::Actor> actor;
    };
private:
    //! 実行引数
    behaviour::NotAwayFromHomeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="node"></param>
    NotAwayFromHomeNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NotAwayFromHomeNodeExecutor() = default;
    /// <summary>
    /// 実行時必要なポインタをキャッシュ
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::ConditionalNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_EXECUTOR_H