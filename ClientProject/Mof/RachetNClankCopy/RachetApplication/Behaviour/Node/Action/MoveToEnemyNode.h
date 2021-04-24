#ifndef BEHAVIOUR_MOVE_TO_ENEMY_NODE_H
#define BEHAVIOUR_MOVE_TO_ENEMY_NODE_H


#include "../ActionNode.h"

#include "../Component/Enemy/EnemyComponent.h"
#include "../Component/Enemy/EnemyStateComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyMeleeAttackComponent.h"
#include "../Component/Enemy/EnemyRangedAttackComponent.h"
#include "../../../Actor/Character/Enemy.h"


namespace behaviour {
class MoveToEnemyNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    MoveToEnemyNode() :
        super("MoveToEnemyNode") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~MoveToEnemyNode() = default;
    /// <summary>
    /// ノードの実行
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>true:実行の成功</returns>
    /// <returns>false:実行の失敗</returns>
    virtual bool Execute(std::any ptr) override {
        
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();

        _ASSERT_EXPR(!target.expired(), L"保持しているポインタが無効です");

        Mof::CSphere range_sphere;
        if (auto com = actor->GetComponent<my::EnemyRangedAttackComponent>(); com) {
            range_sphere = com->GetCanAttackRangeSphere();
        } // if
        else if (auto com = actor->GetComponent<my::EnemyMeleeAttackComponent>(); com) {
            range_sphere = com->GetCanAttackRangeSphere();
        } // else if

        auto pos = target.lock()->GetPosition();
        if (range_sphere.CollisionPoint(pos)) {
            return true;
        } // if

        auto state_com = actor->GetComponent<my::EnemyStateComponent>();
        state_com->ChangeState("EnemyActionMoveState");
        return false;
    };
};
}
#endif // !BEHAVIOUR_MOVE_TO_ENEMY_NODE_H