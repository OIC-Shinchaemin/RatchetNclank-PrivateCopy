#ifndef BEHAVIOUR_TARGET_IN_MELEE_ATTACK_RANGE_NODE_H
#define BEHAVIOUR_TARGET_IN_MELEE_ATTACK_RANGE_NODE_H


#include "../ConditionalNode.h"

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"


namespace behaviour {
class TargetInMeleeAttackRangeNode : public behaviour::ConditionalNodeBase {
    using super = behaviour::ConditionalNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TargetInMeleeAttackRangeNode() :
        super("TargetInMeleeAttackRangeNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TargetInMeleeAttackRangeNode() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {        
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();


        _ASSERT_EXPR(!target.expired(), L"保持しているポインタが無効です");

        auto attack_com = actor->GetComponent<my::EnemyMeleeAttackComponent>();
        auto pos = target.lock()->GetPosition();
        return attack_com->GetCanAttackRangeSphere().CollisionPoint(pos);
    }
};
}
#endif // !BEHAVIOUR_TARGET_IN_MELEE_ATTACK_RANGE_NODE_H