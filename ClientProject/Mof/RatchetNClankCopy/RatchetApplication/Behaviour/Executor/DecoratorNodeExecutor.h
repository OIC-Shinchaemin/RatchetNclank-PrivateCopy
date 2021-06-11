#ifndef RATCHET_BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H


#include "SimplexNodeExecutor.h"

#include "../../Actor.h"


namespace ratchet { namespace behaviour {
class DecoratorNodeExecutor : public ratchet::behaviour::SimplexNodeExecutor {
    using super = ratchet::behaviour::SimplexNodeExecutor;
protected:
    //! �A�N�^�[
    std::weak_ptr<ratchet::Actor> _actor;
    /// <summary>
    /// �m�[�h���s
    /// </summary>
    /// <param name="args"></param>
    /// <returns></returns>
    ratchet::behaviour::INodeExecutor::Result DecoratorNodeExecute(std::any args) {
        // ���s�J�n
        super::_state = super::State::Running;
        if (super::_node->Execute(args)) {
            for (auto& ptr : super::_children) {
                auto re = ptr->Execute();
                if (re == super::Result::Sucess) {
                    super::_state = super::State::Completed;
                    return super::Result::Sucess;
                } // if
                else if (re == super::Result::None) {
                    return super::Result::None;
                } // else if
                else {
                    super::_state = super::State::Incompleted;
                    return super::Result::Failure;
                } // else
            } // for
        } // if
        super::_state = super::State::Incompleted;
        return super::Result::Failure;
    }
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    DecoratorNodeExecutor(const ratchet::behaviour::SimplexNodePtr& node) :
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~DecoratorNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        _actor = std::any_cast<std::shared_ptr<ratchet::Actor>>(actor);
        for (auto& ptr : super::_children) {
            ptr->Prepare(actor);
        } // for
    }
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual ratchet::behaviour::INodeExecutor::Result Execute(void) override {
        auto temp = _actor.lock();
        return this->DecoratorNodeExecute(temp);
        // ���s�J�n
        //super::_state = super::State::Running;
        //auto temp = _actor.lock();
        //if (super::_node->Execute(temp)) {
        //    for (auto& ptr : super::_children) {
        //        auto re = ptr->Execute();
        //        if (re == super::Result::Sucess) {
        //            super::_state = super::State::Completed;
        //            return super::Result::Sucess;
        //        } // if
        //        else if (re == super::Result::None) {
        //            return super::Result::None;
        //        } // else if
        //        else {
        //            super::_state = super::State::Incompleted;
        //            return super::Result::Failure;
        //        } // else
        //    } // for
        //} // if
        //super::_state = super::State::Incompleted;
        //return super::Result::Failure;
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H