#ifndef BEHAVIOUR_LOOK_AROUND_NODE_EXECUTOR_H
#define BEHAVIOUR_LOOK_AROUND_NODE_EXECUTOR_H


#include "../ActionNodeExecutor.h"

#include <memory>

#include "../../../Component/AIStateComponent.h"
#include "../../../Component/Enemy/EnemyComponent.h"
#include "../../../Component/Enemy/EnemyStateComponent.h"


namespace behaviour {
class LookAroundNodeExecutor : public behaviour::ActionNodeExecutor {
    using super = behaviour::ActionNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::Actor> actor;
        //! AI
        std::weak_ptr<ratchet::AIStateComponent> ai_com;
        //! �G�l�~�[
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
        //! �G�l�~�[���
        std::weak_ptr<ratchet::EnemyStateComponent> state_com;
    };
private:
    //! ���s����
    behaviour::LookAroundNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    LookAroundNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~LookAroundNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ai_com = actor->GetComponent<ratchet::AIStateComponent>();
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
            _node_args.state_com = actor->GetComponent<ratchet::EnemyStateComponent>();
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
#endif // !BEHAVIOUR_LOOK_AROUND_NODE_EXECUTOR_H