#ifndef BEHAVIOUR_MOVE_TO_ENEMY_NODE_H
#define BEHAVIOUR_MOVE_TO_ENEMY_NODE_H


#include "../ActionNode.h"

#include "../Component/Enemy/EnemyComponent.h"
#include "../Component/Enemy/EnemyStateComponent.h"
#include "../Component/Enemy/EnemyMoveComponent.h"
#include "../Component/Enemy/EnemyMeleeAttackComponent.h"
#include "../../../Actor/Character/Enemy.h"


namespace behaviour {
class MoveToEnemyNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MoveToEnemyNode() :
        super("MoveToEnemyNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MoveToEnemyNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();

        _ASSERT_EXPR(!target.expired(), L"�ێ����Ă���|�C���^�������ł�");
        auto attack_com = actor->GetComponent<my::EnemyMeleeAttackComponent>();
        auto pos = target.lock()->GetPosition();
        if (attack_com->GetCanAttackRangeSphere().CollisionPoint(pos)) {
            return true;
        } // if

        auto state_com = actor->GetComponent<my::EnemyStateComponent>();
        state_com->ChangeState("EnemyActionMoveState");
        return false;
    };
};
}
#endif // !BEHAVIOUR_MOVE_TO_ENEMY_NODE_H