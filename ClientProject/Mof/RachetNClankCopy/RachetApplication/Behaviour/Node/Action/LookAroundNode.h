#ifndef BEHAVIOUR_LOOK_AROUND_NODE_H
#define BEHAVIOUR_LOOK_AROUND_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"


namespace behaviour {
class LookAroundNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    LookAroundNode() :
        super("LookAroundNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~LookAroundNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);
        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();

        if (!target.expired()) {
            auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
            ai_state_com->ChangeState("AICombatState");
            return true;
        } // if

        auto state_com = actor->GetComponent<my::EnemyStateComponent>();
        state_com->ChangeState("EnemyActionIdleState");
        return false;
    }
};
}
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_H