#ifndef BEHAVIOUR_ACTION_NODE_EXECUTOR_H
#define BEHAVIOUR_ACTION_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "My/Core/Trait.h"


namespace behaviour {
template<typename Actor>
class ActionNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
private:
    //! �A�N�^�[
    std::weak_ptr<typename ty::remove_shared<Actor>::type> _actor;
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
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(Actor actor) override {
        _actor = actor;
    }
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
        } // else if
        //���s�J�n
        super::_state = super::State::Running;
        if (super::_node->Execute(actor)) {
            super::_state = super::State::Completed;
            return super::Result::Sucess;
        } // if
        return super::Result::None;
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_EXECUTOR_H