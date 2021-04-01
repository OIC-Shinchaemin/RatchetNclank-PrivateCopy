#ifndef BEHAVIOUR_ACTION_NODE_EXECUTOR_H
#define BEHAVIOUR_ACTION_NODE_EXECUTOR_H


#include "NodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ActionNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    ActionNodeExecutor(const NodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionNodeExecutor() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        //���s�ς�
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else uif
        //���s�J�n
        super::_state = super::State::Running;
        if (super::_node->Execute(actor)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        }
        return super::Result::None;
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_EXECUTOR_H