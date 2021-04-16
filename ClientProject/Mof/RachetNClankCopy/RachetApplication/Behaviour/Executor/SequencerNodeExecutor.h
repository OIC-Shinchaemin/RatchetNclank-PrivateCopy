#ifndef BEHAVIOUR_SEQUENCER_NODE_EXECUTOR_H
#define BEHAVIOUR_SEQUENCER_NODE_EXECUTOR_H


#include "CompositeNodeExecutor.h"


namespace behaviour {
class SequencerNodeExecutor : public behaviour::CompositeNodeExecutor {
    using super = behaviour::CompositeNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    SequencerNodeExecutor(const behaviour::CompositeNodePtr& node) :
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SequencerNodeExecutor() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual behaviour::INodeExecutor::Result Execute(void) override {
        if (super::_current) {
            auto re = super::_current->Execute();
            if (re != super::Result::None) {
                super::_current = nullptr;
            } // if
            return super::Result::None;
        } // if


        // ���s�ς�
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else if
        // ���s�J�n
        super::_state = super::State::Running;
        for (auto& ptr : super::_children) {
            auto re = ptr->Execute();
            if (re == super::Result::Failure) {
                super::_state = super::State::Incompleted;
                return super::Result::Failure;
            } // if
            else if (re == super::Result::None) {
                return super::Result::None;
            } // else if
        } // for
        super::_state = super::State::Completed;
        return super::Result::Sucess;
    }
};
}
#endif // !BEHAVIOUR_SEQUENCER_NODE_EXECUTOR_H