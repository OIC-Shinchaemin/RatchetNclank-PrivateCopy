#ifndef BEHAVIOUR_TARGET_RECOGNITION_NODE_H
#define BEHAVIOUR_TARGET_RECOGNITION_NODE_H


#include "../ConditionalNode.h"


namespace behaviour {
template<typename Actor>
class TargetRecognitionNode : public behaviour::ConditionalNodeBase<Actor> {
    using super = behaviour::ConditionalNodeBase<Actor>;
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
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<Actor>(ptr);
        return !actor->GetTarget().expired();
    }
};
}
#endif // !BEHAVIOUR_TARGET_RECOGNITION_NODE_H