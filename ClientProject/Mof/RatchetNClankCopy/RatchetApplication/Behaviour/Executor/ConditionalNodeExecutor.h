#ifndef RATCHET_BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../../Actor/Actor.h"


namespace ratchet { namespace behaviour {
class ConditionalNodeExecutor : public ratchet::behaviour::NodeExecutor {
    using super = ratchet::behaviour::NodeExecutor;
protected:
    //! �A�N�^�[
    std::weak_ptr<ratchet::actor::Actor> _actor;
    /// <summary>
    /// �m�[�h���s
    /// </summary>
    /// <param name="args"></param>
    /// <returns></returns>
    ratchet::behaviour::INodeExecutor::Result ConditionalNodeExecute(std::any args) {
        // ���s�J�n
        super::_state = super::State::Running;
        if (super::_node->Execute(args)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    ConditionalNodeExecutor(const ratchet::behaviour::NodePtr& node) :
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ConditionalNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        _actor = std::any_cast<std::shared_ptr<ratchet::actor::Actor>>(actor);
    }
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        auto temp = _actor.lock();
        return this->ConditionalNodeExecute(temp);
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H