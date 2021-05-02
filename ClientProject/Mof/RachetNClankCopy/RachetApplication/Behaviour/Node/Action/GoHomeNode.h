#ifndef BEHAVIOUR_GO_HOME_NODE_H
#define BEHAVIOUR_GO_HOME_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/GoHomeNodeExecutor.h"
#include "../../../State/EnemyAction/EnemyActionStateDefine.h"


namespace behaviour {
class GoHomeNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GoHomeNode() :
        super("GoHomeNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GoHomeNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::GoHomeNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::GoHomeNodeExecutor::NodeArgs>(node_args);
        if (args.state_com.lock()->CanTransition(state::EnemyActionStateType::kEnemyActionGoHomeState)) {
            args.state_com.lock()->ChangeState(state::EnemyActionStateType::kEnemyActionGoHomeState);
        } // if
        else {
            return false;
        } // else


        float distance = Mof::CVector3Utilities::Distance(
            args.actor.lock()->GetInitialPosition(), args.actor.lock()->GetPosition());
        if (distance > 2.5f) {
            return false;
        } // if
        return true;
    }
};
}
#endif // !BEHAVIOUR_GO_HOME_NODE_H