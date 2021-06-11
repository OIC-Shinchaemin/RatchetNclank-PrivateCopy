#ifndef RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyMoveComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace ratchet {
namespace behaviour {
class MoveToEnemyNodeExecutor : public ratchet::behaviour::ActionNodeExecutor {
    using super = ratchet::behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! �G�l�~�[
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
        //! �G�l�~�[
        std::weak_ptr<ratchet::EnemyMoveComponent> move_com;
        //! �G�l�~�[���
        std::weak_ptr<ratchet::EnemyStateComponent> state_com;
        //! �ߐڍU��
        std::weak_ptr<ratchet::EnemyMeleeAttackComponent> melee_attack_com;
        //! �������U��
        std::weak_ptr<ratchet::EnemyRangedAttackComponent> ranged_attack_com;
    };
private:
    //! ���s����
    ratchet::behaviour::MoveToEnemyNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    MoveToEnemyNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MoveToEnemyNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
            _node_args.state_com = actor->GetComponent<ratchet::EnemyStateComponent>();
            _node_args.move_com = actor->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::EnemyMoveComponent>();
            _node_args.melee_attack_com = actor->GetComponent<ratchet::ActionComponent>()->GetComponent<ratchet::EnemyMeleeAttackComponent>();
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
        return super::ActionNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_MOVE_TO_ENEMY_NODE_EXECUTOR_H