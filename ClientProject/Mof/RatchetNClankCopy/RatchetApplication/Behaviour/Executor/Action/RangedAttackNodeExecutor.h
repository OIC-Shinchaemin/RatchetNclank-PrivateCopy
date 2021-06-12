#ifndef RATCHET_BEHAVIOUR_RANGED_ATTACK_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_RANGED_ATTACK_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/MotionComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyRangedAttackComponent.h"


namespace ratchet {
namespace behaviour {
class RangedAttackNodeExecutor : public ratchet::behaviour::ActionNodeExecutor {
    using super = ratchet::behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! AI
        std::weak_ptr<ratchet::component::AIStateComponent> ai_com;
        //! ���[�V����
        std::weak_ptr<ratchet::component::MotionComponent> motion_com;
        //! �G�l�~�[
        std::weak_ptr<ratchet::component::enemy::EnemyComponent> ENEMY_com;
        //! �G�l�~�[���
        std::weak_ptr<ratchet::component::enemy::EnemyStateComponent> state_com;
        //! �U��
        std::weak_ptr<ratchet::component::enemy::EnemyRangedAttackComponent> attack_com;
    };
private:
    //! ���s����
    ratchet::behaviour::RangedAttackNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    RangedAttackNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~RangedAttackNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ai_com = actor->GetComponent<ratchet::component::AIStateComponent>();
            _node_args.ENEMY_com = actor->GetComponent<ratchet::component::enemy::EnemyComponent>();
            _node_args.motion_com = actor->GetComponent<ratchet::component::MotionComponent>();
            _node_args.state_com = actor->GetComponent<ratchet::component::enemy::EnemyStateComponent>();
            _node_args.attack_com = actor->GetComponent<ratchet::component::ActionComponent>()->GetComponent<ratchet::component::enemy::EnemyRangedAttackComponent>();
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
#endif // !RATCHET_BEHAVIOUR_RANGED_ATTACK_NODE_EXECUTOR_H