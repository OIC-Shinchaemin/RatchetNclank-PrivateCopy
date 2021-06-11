#ifndef RATCHET_BEHAVIOUR_TARGET_IN_RANGED_ATTACK_RANGE_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_TARGET_IN_RANGED_ATTACK_RANGE_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace ratchet { namespace behaviour {
class TargetInRangedAttackRangeNodeExecutor : public ratchet::behaviour::DecoratorNodeExecutor {
    using super = ratchet::behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::Actor> actor;
        //! �G�l�~�[
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
        //! �U��
        std::weak_ptr<ratchet::EnemyRangedAttackComponent> ranged_attack_com;
    };
private:
    //! ���s����
    ratchet::behaviour::TargetInRangedAttackRangeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    TargetInRangedAttackRangeNodeExecutor(const ratchet::behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TargetInRangedAttackRangeNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
            _node_args.ranged_attack_com = actor->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::EnemyRangedAttackComponent>();
        } // if
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::DecoratorNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_TARGET_IN_RANGED_ATTACK_RANGE_NODE_EXECUTOR_H