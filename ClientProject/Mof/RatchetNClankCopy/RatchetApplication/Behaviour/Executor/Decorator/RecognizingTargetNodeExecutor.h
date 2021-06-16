#ifndef RATCHET_BEHAVIOUR_RECOGNIZING_TARGET_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_RECOGNIZING_TARGET_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace ratchet { namespace behaviour {
class RecognizingTargetNodeExecutor : public ratchet::behaviour::DecoratorNodeExecutor {
    using super = ratchet::behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! �G�l�~�[
        std::weak_ptr<ratchet::component::enemy::EnemyComponent> ENEMY_com;
    };
private:
    //! ���s����
    ratchet::behaviour::RecognizingTargetNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    RecognizingTargetNodeExecutor(const ratchet::behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~RecognizingTargetNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::component::enemy::EnemyComponent>();
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
#endif // !RATCHET_BEHAVIOUR_RECOGNIZING_TARGET_NODE_EXECUTOR_H