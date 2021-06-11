#ifndef RATCHET_BEHAVIOUR_CHANGE_PATROL_NODE_H
#define RATCHET_BEHAVIOUR_CHANGE_PATROL_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/ChangePatrolNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class ChangePatrolNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
    using Executor = ratchet::behaviour::ChangePatrolNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ChangePatrolNode() :
        super("ChangePatrolNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ChangePatrolNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<Executor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);
        args.ai_com.lock()->ChangeState("AIPatrolState");
        return true;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_CHANGE_PATROL_NODE_H