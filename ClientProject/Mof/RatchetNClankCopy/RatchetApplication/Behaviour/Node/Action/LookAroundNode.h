#ifndef RATCHET_BEHAVIOUR_LOOK_AROUND_NODE_H
#define RATCHET_BEHAVIOUR_LOOK_AROUND_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/LookAroundNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class LookAroundNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
    using Executor = ratchet::behaviour::LookAroundNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LookAroundNode() :
        super("LookAroundNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~LookAroundNode() = default;
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
        
        if (args.state_com.lock()->CanTransition(ratchet::state::EnemyActionStateType::kEnemyActionIdleState)) {
            args.state_com.lock()->ChangeState(ratchet::state::EnemyActionStateType::kEnemyActionIdleState);
        } // if
        return true;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_LOOK_AROUND_NODE_H