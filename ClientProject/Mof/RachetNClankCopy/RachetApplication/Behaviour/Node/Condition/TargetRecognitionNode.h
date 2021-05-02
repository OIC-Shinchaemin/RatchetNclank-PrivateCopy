#ifndef BEHAVIOUR_TARGET_RECOGNITION_NODE_H
#define BEHAVIOUR_TARGET_RECOGNITION_NODE_H


#include "../ConditionalNode.h"

#include "../../Executor/Condition/TargetRecognitionNodeExecutor.h"


namespace behaviour {
class TargetRecognitionNode : public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TargetRecognitionNode() :
        super("TargetRecognition") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TargetRecognitionNode() = default;
    /// <summary>
    /// 作成
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::TargetRecognitionNodeExecutor>(ptr);
    }
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="node_args">実行引数</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::TargetRecognitionNodeExecutor::NodeArgs>(node_args);
        auto target = args.enemy_com.lock()->GetTarget();
        return !target.expired();
    }
};
}
#endif // !BEHAVIOUR_TARGET_RECOGNITION_NODE_H