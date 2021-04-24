#ifndef BEHAVIOUR_RANGED_ATTACK_NODE_H
#define BEHAVIOUR_RANGED_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../../Actor.h"
#include "../../../Actor/Character/Enemy.h"
#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace behaviour {
class RangedAttackNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    RangedAttackNode() :
        super("RangedAttackNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~RangedAttackNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);
        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();
        if (target.expired()) {
            return false;
        } // if
        
        auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
        ai_state_com->ChangeState("AICombatState");

        auto state_com = actor->GetComponent<my::EnemyStateComponent>();
        state_com->ChangeState("EnemyActionRangedAttackState");
        return false;
    }
};
}
#endif // !BEHAVIOUR_RANGED_ATTACK_NODE_H