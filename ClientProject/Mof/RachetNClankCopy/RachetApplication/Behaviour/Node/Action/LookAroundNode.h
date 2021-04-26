#ifndef BEHAVIOUR_LOOK_AROUND_NODE_H
#define BEHAVIOUR_LOOK_AROUND_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/LookAroundNodeExecutor.h"


namespace behaviour {
class LookAroundNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
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
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::LookAroundNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::LookAroundNodeExecutor::NodeArgs>(node_args);
        
        auto target = args.enemy_com.lock()->GetTarget();
        if (!target.expired()) {
            args.ai_com.lock()->ChangeState("AICombatState");
            return true;
        } // if
        args.state_com.lock()->ChangeState("EnemyActionIdleState");
        return false;
    }
};
}
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_H