<<<<<<< HEAD
#pragma once

#include "CompositeNodeExecutor.h"

namespace Behaviour {
/** �m�[�h���s�p�N���X */
template < typename T >
class SelectorNodeExecutor : public CompositeNodeExecutor< T > {
public:
	SelectorNodeExecutor(const CompositeNodePtr< T >& node)
		: CompositeNodeExecutor< T >(node) {
	}
	virtual ~SelectorNodeExecutor() = default;

	/**
	 * @brief		�m�[�h�̎��s����
	 * @param[in]	actor		���s�A�N�^�[
	 * @return		Succeeded	���s�̐���
	 *				Failed		���s�̎��s
	 */
	Result Exec(T& actor) override {
		//���s�ς�
		if (_state == State::Completed) {
			return Result::Sucess;
		}
		else if (_state == State::Incompleted) {
			return Result::Failure;
		}
		//���s�J�n
		_state = State::Running;
		for (auto& ptr : _children) {
			Result re = ptr->Exec(actor);
			if (re == Result::Sucess) {
				_state = State::Completed;
				return Result::Sucess;
			}
			else if (re == Result::None) {
				return Result::None;
			}
		}
		_state = State::Incompleted;
		return Result::Failure;
	}
};
}
=======
#ifndef BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H
#define BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H


#include "CompositeNodeExecutor.h"


namespace behaviour {
template <typename Actor>
class SelectorNodeExecutor : public behaviour::CompositeNodeExecutor<Actor> {
    using super = behaviour::CompositeNodeExecutor<Actor>;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    SelectorNodeExecutor(const CompositeNodePtr<Actor>& node) :
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
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        if (super::_current) {
            auto re = super::_current->Execute(actor);
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
            auto re = ptr->Execute(actor);
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
#endif // !BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H
>>>>>>> origin/Ex55_WeaponAction
