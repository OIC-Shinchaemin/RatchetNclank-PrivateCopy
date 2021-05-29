#ifndef BEHAVIOUR_MELEE_ATTACK_NODE_EXECUTOR_H
#define BEHAVIOUR_MELEE_ATTACK_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/MotionComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"
#include "../../../Component/Enemy/EnemyMeleeAttackComponent.h"


namespace behaviour {
class MeleeAttackNodeExecutor : public behaviour::ActionNodeExecutor {
    using super = behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<my::Actor> actor;
        //! AI
        std::weak_ptr<my::AIStateComponent> ai_com;
        //! AI
        std::weak_ptr<my::MotionComponent> motion_com;
        //! �G�l�~�[
        std::weak_ptr<my::EnemyComponent> enemy_com;
        //! �G�l�~�[���
        std::weak_ptr<my::EnemyStateComponent> state_com;
        //! �G�l�~�[���
        std::weak_ptr<my::EnemyMeleeAttackComponent> attack_com;
    };
private:
    //! ���s����
    behaviour::MeleeAttackNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    MeleeAttackNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~MeleeAttackNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ai_com = actor->GetComponent<my::AIStateComponent>();
            _node_args.motion_com = actor->GetComponent<my::MotionComponent>();
            _node_args.enemy_com = actor->GetComponent<my::EnemyComponent>();
            _node_args.state_com = actor->GetComponent<my::EnemyStateComponent>();
            _node_args.attack_com = actor->GetComponent<my::EnemyMeleeAttackComponent>();
        } // if
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::ActionNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_MELEE_ATTACK_NODE_EXECUTOR_H