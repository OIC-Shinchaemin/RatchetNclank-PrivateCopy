#ifndef BEHAVIOUR_TARGET_OUT_OF_MELEE_ATTACK_RANGE_NODE_H
#define BEHAVIOUR_TARGET_OUT_OF_MELEE_ATTACK_RANGE_NODE_H


#include "../ConditionalNode.h"

#include "../../../Component/Enemy/EnemyAttackComponent.h"


namespace behaviour {
template<typename Actor>
class TargetOutOfMeleeAttackRangeNode : public behaviour::ConditionalNodeBase<Actor> {
    using super = behaviour::ConditionalNodeBase<Actor>;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TargetOutOfMeleeAttackRangeNode() :
        super("TargetOutOfMeleeAttackRangeNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~TargetOutOfMeleeAttackRangeNode() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<Actor>(ptr);
        
        _ASSERT_EXPR(!actor->GetTarget().expired(), L"保持しているポインタが無効です");

        auto attack_com = actor->GetComponent<my::EnemyAttackComponent>();
        auto pos = actor->GetTarget().lock()->GetPosition();
        return !attack_com->GetCanAttackRangeSphere().CollisionPoint(pos);
    }
};
}
#endif // !BEHAVIOUR_TARGET_OUT_OF_MELEE_ATTACK_RANGE_NODE_H