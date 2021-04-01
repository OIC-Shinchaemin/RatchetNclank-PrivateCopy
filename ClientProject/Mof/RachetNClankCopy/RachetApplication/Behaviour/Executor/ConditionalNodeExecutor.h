#ifndef BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H
#define BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H


#include "NodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ConditionalNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    ConditionalNodeExecutor(const NodePtr<Actor>& node) : 
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ConditionalNodeExecutor() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        // ���s�J�n
        super::_state = super::State::Running;
        if (super::_node->Execute(actor)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
};
}
#endif // !BEHAVIOUR_CONDITIONAL_NODE_EXECUTOR_H