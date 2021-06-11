#ifndef BEHAVIOUR_CHANGE_COMBAT_NODE_H
#define BEHAVIOUR_CHANGE_COMBAT_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/ChangeCombatNodeExecutor.h"


namespace behaviour {
class ChangeCombatNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
    using Executor = behaviour::ChangeCombatNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ChangeCombatNode() :
        super("ChangeCombatNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ChangeCombatNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
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
        args.ai_com.lock()->ChangeState("AICombatState");
        return true;
    }
};
}
#endif // !BEHAVIOUR_CHANGE_COMBAT_NODE_H