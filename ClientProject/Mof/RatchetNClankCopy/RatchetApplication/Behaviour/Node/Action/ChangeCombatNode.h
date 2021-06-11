#ifndef RATCHET_BEHAVIOUR_CHANGE_COMBAT_NODE_H
#define RATCHET_BEHAVIOUR_CHANGE_COMBAT_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/ChangeCombatNodeExecutor.h"


namespace ratchet {  namespace behaviour {
class ChangeCombatNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
    using Executor = ratchet::behaviour::ChangeCombatNodeExecutor;
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
        args.ai_com.lock()->ChangeState("AICombatState");
        return true;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_CHANGE_COMBAT_NODE_H