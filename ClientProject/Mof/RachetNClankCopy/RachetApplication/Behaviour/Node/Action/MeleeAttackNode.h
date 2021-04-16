#ifndef BEHAVIOUR_MELLE_ATTACK_NODE_H
#define BEHAVIOUR_MELLE_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"


namespace behaviour {
template<typename Actor>
class MeleeAttackNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MeleeAttackNode() :
        super("MeleeAttackNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MeleeAttackNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<Actor>(ptr);

        if (actor->GetTarget().expired()) {
            return false;
        } // if

        auto attack_com = actor->GetComponent<my::EnemyAttackComponent>();
        auto pos = actor->GetTarget().lock()->GetPosition();
        if (attack_com->GetCanAttackRangeSphere().CollisionPoint(pos)) {
            auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
            ai_state_com->ChangeState("AICombatState");

            auto state_com = actor->GetComponent<my::EnemyStateComponent>();
            state_com->ChangeState("EnemyActionAttackState");
            return false;
        } // if

        return true;

    }
};
}
#endif // !BEHAVIOUR_MELLE_ATTACK_NODE_H