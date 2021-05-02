#ifndef BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H
#define BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"

#include "../../Executor/Condition/NotAwayFromHomeNodeExecutor.h"


namespace behaviour {
class NotAwayFromHomeNode: public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    NotAwayFromHomeNode() :
        super("NotAwayFromHomeNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~NotAwayFromHomeNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::NotAwayFromHomeNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::NotAwayFromHomeNodeExecutor::NodeArgs>(node_args);
        auto actor = args.actor.lock();

        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) < 9.5f;
    }
};
}
#endif // !BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H