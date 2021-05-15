#ifndef BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H
#define BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H


#include "../ConditionalNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace behaviour {
class NotTargetRecognitionNodeExecutor : public behaviour::ConditionalNodeExecutor {
    using super = behaviour::ConditionalNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<my::Actor> actor;
        //! �G�l�~�[
        std::weak_ptr<my::EnemyComponent> enemy_com;
    };
private:
    //! ���s����
    behaviour::NotTargetRecognitionNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    NotTargetRecognitionNodeExecutor(const behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotTargetRecognitionNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.enemy_com = actor->GetComponent<my::EnemyComponent>();
        } // if
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::ConditionalNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_NOT_TARGET_RECOGNITION_NODE_EXECUTOR_H