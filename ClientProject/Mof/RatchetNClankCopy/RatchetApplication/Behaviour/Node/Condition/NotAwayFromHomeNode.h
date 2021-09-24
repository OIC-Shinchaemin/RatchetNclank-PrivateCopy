#ifndef RATCHET_BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H
#define RATCHET_BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"

#include "../../Executor/Condition/NotAwayFromHomeNodeExecutor.h"


namespace ratchet::behaviour {
class NotAwayFromHomeNode : public ratchet::behaviour::ConditionalNodeBase {
    using super = ratchet::behaviour::ConditionalNodeBase;
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
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<ratchet::behaviour::Node>(super::shared_from_this());
        return std::make_shared<ratchet::behaviour::NotAwayFromHomeNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<ratchet::behaviour::NotAwayFromHomeNodeExecutor::NodeArgs>(node_args);
        auto actor = args.actor.lock();

        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) < 2.0f;
    }
};
}
#endif // !RATCHET_BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H