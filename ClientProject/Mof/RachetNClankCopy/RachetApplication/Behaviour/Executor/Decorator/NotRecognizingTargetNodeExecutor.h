#ifndef BEHAVIOUR_NOT_RECOGNIZING_TARGET_NODE_EXECUTOR_H
#define BEHAVIOUR_NOT_RECOGNIZING_TARGET_NODE_EXECUTOR_H


#include "../DecoratorNodeExecutor.h"

#include "../../../Component/Enemy/EnemyComponent.h"


namespace behaviour {
class NotRecognizingTargetNodeExecutor : public behaviour::DecoratorNodeExecutor {
    using super = behaviour::DecoratorNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<rachet::Actor> actor;
        //! �G�l�~�[
        std::weak_ptr<rachet::EnemyComponent> ENEMY_com;
    };
private:
    //! ���s����
    behaviour::NotRecognizingTargetNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    NotRecognizingTargetNodeExecutor(const behaviour::SimplexNodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotRecognizingTargetNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
        if (auto actor = super::_actor.lock()) {
            _node_args.ENEMY_com = actor->GetComponent<rachet::EnemyComponent>();
        } // if
    }
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        return super::DecoratorNodeExecute(_node_args);
    }
};
}
#endif // !BEHAVIOUR_NOT_RECOGNIZING_TARGET_NODE_EXECUTOR_H