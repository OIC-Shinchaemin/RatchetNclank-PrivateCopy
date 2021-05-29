#ifndef BEHAVIOUR_MELLE_ATTACK_NODE_H
#define BEHAVIOUR_MELLE_ATTACK_NODE_H


#include "../ActionNode.h"

#include "../../Executor/Action/MeleeAttackNodeExecutor.h"


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
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        return std::make_shared<behaviour::MeleeAttackNodeExecutor>(ptr);
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="node_args">���s����</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any node_args) override {
        auto args = std::any_cast<behaviour::MeleeAttackNodeExecutor::NodeArgs>(node_args);

        auto target = args.enemy_com.lock()->GetTarget();
        if (target.expired()) {
            return false;
        } // if

        auto pos = target.lock()->GetPosition();
        auto range_sphere = args.attack_com.lock()->GetCanAttackRangeSphere();
        if (!range_sphere.CollisionPoint(pos)) {
            //args.ai_com.lock()->ChangeState("AIPatrolState");
            return false;
        } // if



        if (args.state_com.lock()->CanTransition(state::EnemyActionStateType::kEnemyActionMeleeAttackState)) {
            args.state_com.lock()->ChangeState(state::EnemyActionStateType::kEnemyActionMeleeAttackState);
            return false;
        } // if




        if (args.state_com.lock()->IsEqual(state::EnemyActionStateType::kEnemyActionMeleeAttackState) && 
            args.motion_com.lock()->IsEndMotion()) {
            args.ai_com.lock()->ChangeState("AICombatState");
            return false;
        } // if

        return false;
    }
};
}
#endif // !BEHAVIOUR_MELLE_ATTACK_NODE_H