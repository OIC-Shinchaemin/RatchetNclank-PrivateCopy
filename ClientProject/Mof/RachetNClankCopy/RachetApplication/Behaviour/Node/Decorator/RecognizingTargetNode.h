#ifndef BEHAVIOUR_RECOGNIZING_TARGET_NODE_H
#define BEHAVIOUR_RECOGNIZING_TARGET_NODE_H


#include "../DecoratorNode.h"

#include "../../Executor/Decorator/RecognizingTargetNodeExecutor.h"


namespace behaviour {
class RecognizingTargetNode : public behaviour::DecoratorNodeBase {
    using super = behaviour::DecoratorNodeBase;
    using Executor = behaviour::RecognizingTargetNodeExecutor;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RecognizingTargetNode() :
        super("RecognizingTargetNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~RecognizingTargetNode() = default;
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

        auto target = args.enemy_com.lock()->GetTarget();
        if (!target.expired()) {
            return true;
        } // if
        return false;
    }
};
}
#endif // !BEHAVIOUR_RECOGNIZING_TARGET_NODE_H