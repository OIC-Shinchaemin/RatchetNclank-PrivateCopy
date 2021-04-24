#ifndef BEHAVIOUR_MELLE_ATTACK_NODE_H
#define BEHAVIOUR_MELLE_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../../Actor.h"
#include "../../../Actor/Character/Enemy.h"
#include "../../../Component/AIStateComponent.h"
#include "../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"


namespace behaviour {
class MeleeAttackNode : public behaviour::ActionNodeBase {
    using super = behaviour::ActionNodeBase;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    MeleeAttackNode() :
        super("MeleeAttackNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MeleeAttackNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);
        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();

        if (target.expired()) {
            return false;
        } // if

        auto attack_com = actor->GetComponent<my::EnemyMeleeAttackComponent>();
        auto pos = target.lock()->GetPosition();
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