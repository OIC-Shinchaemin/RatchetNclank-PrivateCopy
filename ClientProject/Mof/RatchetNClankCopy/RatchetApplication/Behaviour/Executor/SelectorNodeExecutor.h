#ifndef RATCHET_BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H


#include "CompositeNodeExecutor.h"


namespace ratchet {
namespace behaviour {
class SelectorNodeExecutor : public ratchet::behaviour::CompositeNodeExecutor {
    using super = ratchet::behaviour::CompositeNodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    SelectorNodeExecutor(const ratchet::behaviour::CompositeNodePtr& node) :
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SelectorNodeExecutor() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
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
            if (re == super::Result::Sucess) {
                super::_state = super::State::Completed;
                return super::Result::Sucess;
            } // if
            else if (re == super::Result::None) {
                return super::Result::None;
            } // else if
        } // for
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H