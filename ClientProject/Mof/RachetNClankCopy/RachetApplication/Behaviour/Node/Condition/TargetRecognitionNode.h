#ifndef BEHAVIOUR_TARGET_RECOGNITION_NODE_H
#define BEHAVIOUR_TARGET_RECOGNITION_NODE_H


#include "../ConditionalNode.h"

#include "../../../Actor.h"
#include "../../../Component/Enemy/EnemyComponent.h"


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
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor =  std::dynamic_pointer_cast<my::Enemy>(std::any_cast<std::shared_ptr<my::Actor>>(ptr));
        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();
        return !target.expired();
    }
};
}
#endif // !BEHAVIOUR_TARGET_RECOGNITION_NODE_H