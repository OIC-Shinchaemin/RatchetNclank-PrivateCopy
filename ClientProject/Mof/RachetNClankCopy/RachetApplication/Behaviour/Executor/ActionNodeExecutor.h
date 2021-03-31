#pragma once

#include "NodeExecutor.h"

namespace Behaviour {

    /** �m�[�h���s�p�N���X */
template < typename T >
class ActionNodeExecutor : public NodeExecutor< T > {
public:
    ActionNodeExecutor(const NodePtr< T >& node)
        : NodeExecutor< T >(node) {
    }
    virtual ~ActionNodeExecutor() = default;

    /**
     * @brief		�m�[�h�̎��s����
     * @param[in]	actor		���s�A�N�^�[
     * @return		Succeeded	���s�̐���
     *				Failed		���s�̎��s
     */
    virtual Result Exec(T& actor) {
        //���s�ς�
        if (_state == State::Completed) {
            return Result::Sucess;
        }
        else if (_state == State::Incompleted) {
            return Result::Failure;
        }
        //���s�J�n
        _state = State::Running;
        if (_node->Exec(actor)) {
            _state = State::Completed;
            return Result::Sucess;
        }
        return Result::None;
    }
};
}