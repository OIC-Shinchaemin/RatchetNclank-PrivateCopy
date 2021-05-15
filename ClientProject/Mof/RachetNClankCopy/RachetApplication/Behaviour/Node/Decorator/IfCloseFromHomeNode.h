#ifndef BEHAVIOUR_IF_CLOSE_FROM_HOME_NODE_H
#define BEHAVIOUR_IF_CLOSE_FROM_HOME_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/IfCloseFromHomeNodeExecutor.h"


namespace behaviour {
class IfCloseFromHomeNode : public behaviour::DecoratorNodeBase {
    using super = behaviour::DecoratorNodeBase;
    using Executor = behaviour::IfCloseFromHomeNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    IfCloseFromHomeNode() :
        super("IfCloseFromHomeNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~IfCloseFromHomeNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<behaviour::SimplexNode>(ptr);
        return std::make_shared<Executor>(temp);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<Executor::NodeArgs>(node_args);

        float distance = Mof::CVector3Utilities::Distance(args.actor.lock()->GetInitialPosition(), args.actor.lock()->GetPosition());
        return !(distance > args.type_com.lock()->GetHomeDistance());
    }
};
}
#endif // !BEHAVIOUR_IF_CLOSE_FROM_HOME_NODE_H