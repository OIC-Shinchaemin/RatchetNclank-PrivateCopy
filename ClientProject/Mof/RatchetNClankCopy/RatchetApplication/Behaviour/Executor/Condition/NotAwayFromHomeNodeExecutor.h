#ifndef RATCHET_BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_EXECUTOR_H


#include "../ConditionalNodeExecutor.h"


namespace ratchet {
namespace behaviour {
class NotAwayFromHomeNodeExecutor : public ratchet::behaviour::ConditionalNodeExecutor {
    using super = ratchet::behaviour::ConditionalNodeExecutor;
public:
    struct NodeArgs {
        //! �A�N�^�[
        std::weak_ptr<ratchet::actor::Actor> actor;
    };
private:
    //! ���s����
    ratchet::behaviour::NotAwayFromHomeNodeExecutor::NodeArgs _node_args;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    NotAwayFromHomeNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node),
        _node_args() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NotAwayFromHomeNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        super::Prepare(actor);
        _node_args.actor = super::_actor;
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
#endif // !RATCHET_BEHAVIOUR_NOT_AWAY_FROM_HOME_NODE_EXECUTOR_H