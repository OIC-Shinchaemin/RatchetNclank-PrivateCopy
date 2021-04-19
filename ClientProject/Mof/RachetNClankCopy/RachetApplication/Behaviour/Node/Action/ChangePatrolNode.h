#ifndef BEHAVIOUR_CHANGE_PATROL_NODE_H
#define BEHAVIOUR_CHANGE_PATROL_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"


namespace behaviour {
class ChangePatrolNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ChangePatrolNode() :
        super("ChangePatrolNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~ChangePatrolNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        // can transition state
        if (1) {
        } // if
        auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
        ai_state_com->ChangeState("AIPatrolState");
        return true;
    }
};
}
#endif // !BEHAVIOUR_CHANGE_PATROL_NODE_H