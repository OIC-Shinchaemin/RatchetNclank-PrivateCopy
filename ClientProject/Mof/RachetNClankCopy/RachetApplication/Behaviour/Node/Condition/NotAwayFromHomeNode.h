#ifndef BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H
#define BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H


#include "../ConditionalNode.h"
#include "../../../Actor.h"


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
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        return Mof::CVector3Utilities::Distance(actor->GetInitialPosition(), actor->GetPosition()) < 5.0f;
    }
};
}
#endif // !BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_H