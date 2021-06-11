#ifndef RATCHET_BEHAVIOUR_TARGET_RECOGNITION_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_TARGET_RECOGNITION_NODE_EXECUTOR_H


#include "../ConditionalNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace ratchet {
namespace behaviour {
class TargetRecognitionNodeExecutor : public ratchet::behaviour::ConditionalNodeExecutor {
    using super = ratchet::behaviour::ConditionalNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::actor::Actor> actor;
        //! �G�l�~�[
        std::weak_ptr<ratchet::EnemyComponent> ENEMY_com;
    };
private:
    //! ���s����
    ratchet::behaviour::TargetRecognitionNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    TargetRecognitionNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~TargetRecognitionNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<ratchet::EnemyComponent>();
        } // if
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        return super::ConditionalNodeExecute(_node_args);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_TARGET_RECOGNITION_NODE_EXECUTOR_H