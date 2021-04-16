#ifndef BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H
#define BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H


#include "SimplexNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class DecoratorNodeExecutor : public behaviour::SimplexNodeExecutor<Actor> {
    using super = behaviour::SimplexNodeExecutor<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    DecoratorNodeExecutor(const SimplexNodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~DecoratorNodeExecutor() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual INodeExecutor<Actor>::Result Execute(void) override {
        // ���s�J�n
        super::_state = super::State::Running;
        auto temp = Actor();
        if (super::_node->Execute(temp)) {
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
};
}
#endif // !BEHAVIOUR_DECORATOR_NODE_EXECUTOR_H