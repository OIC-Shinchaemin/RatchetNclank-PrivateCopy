#ifndef BEHAVIOUR_MELLE_ATTACK_NODE_H
#define BEHAVIOUR_MELLE_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyIdleComponent.h"
#include "../../../Component/Enemy/EnemyMoveComponent.h"
#include "../../../Component/Enemy/EnemyAttackComponent.h"


namespace behaviour {
template<typename Actor>
class MeleeAttackNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
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
    virtual bool Execute(Actor& actor) override {
        auto attack_com = actor->GetComponent<my::EnemyAttackComponent>();
        if (actor->GetTarget().expired()) {
            return false;
        } // if

        _ASSERT_EXPR(!actor->GetTarget().expired(), L"�ێ����Ă���|�C���^�������ł�");

        auto pos = actor->GetTarget().lock()->GetPosition();




        if (attack_com->GetCanAttackRangeSphere().CollisionPoint(pos)) {

            auto move_com = actor->GetComponent<my::EnemyMoveComponent>();

            move_com->SetMoveSpeed(0.0f);
            move_com->SetAngularSpeed(0.0f);

            attack_com->Start();

            auto state_com = actor->GetComponent<my::EnemyStateComponent>();
            state_com->ChangeState("EnemyActionAttackState");

            auto ai_state_com = actor->GetComponent<my::AIStateComponent>();
            ai_state_com->ChangeState("AICombatState");
            return false;
        } // if

        return true;

    }
};
}
#endif // !BEHAVIOUR_MELLE_ATTACK_NODE_H