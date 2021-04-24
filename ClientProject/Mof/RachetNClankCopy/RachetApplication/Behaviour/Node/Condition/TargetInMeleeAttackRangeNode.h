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
    /// �R���X�g���N�^
    /// </summary>
    TargetInMeleeAttackRangeNode() :
        super("TargetInMeleeAttackRangeNode") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TargetInMeleeAttackRangeNode() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {        
        auto actor = std::any_cast<std::shared_ptr<my::Actor>>(ptr);

        auto target = actor->GetComponent<my::EnemyComponent>()->GetTarget();


        _ASSERT_EXPR(!target.expired(), L"�ێ����Ă���|�C���^�������ł�");

        auto attack_com = actor->GetComponent<my::EnemyMeleeAttackComponent>();
        auto pos = target.lock()->GetPosition();
        return attack_com->GetCanAttackRangeSphere().CollisionPoint(pos);
    }
};
}
#endif // !BEHAVIOUR_TARGET_IN_MELEE_ATTACK_RANGE_NODE_H