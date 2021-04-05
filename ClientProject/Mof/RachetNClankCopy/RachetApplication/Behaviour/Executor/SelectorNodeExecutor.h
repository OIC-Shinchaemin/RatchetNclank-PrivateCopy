<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include "CompositeNodeExecutor.h"

namespace Behaviour {
/** ƒm[ƒhÀs—pƒNƒ‰ƒX */
template < typename T >
class SelectorNodeExecutor : public CompositeNodeExecutor< T > {
public:
	SelectorNodeExecutor(const CompositeNodePtr< T >& node)
		: CompositeNodeExecutor< T >(node) {
	}
	virtual ~SelectorNodeExecutor() = default;

	/**
	 * @brief		ƒm[ƒh‚ÌÀsˆ—
	 * @param[in]	actor		ÀsƒAƒNƒ^[
	 * @return		Succeeded	Às‚Ì¬Œ÷
	 *				Failed		Às‚Ì¸”s
	 */
	Result Exec(T& actor) override {
		//ÀsÏ‚İ
		if (_state == State::Completed) {
			return Result::Sucess;
		}
		else if (_state == State::Incompleted) {
			return Result::Failure;
		}
		//ÀsŠJn
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
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H
#define BEHAVIOUR_SELECTOR_NODE_EXECUTOR_H


#include "CompositeNodeExecutor.h"


namespace behaviour {
template <typename Actor>
class SelectorNodeExecutor : public behaviour::CompositeNodeExecutor<Actor> {
    using super = behaviour::CompositeNodeExecutor<Actor>;
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    /// <param name="node"></param>
    SelectorNodeExecutor(const CompositeNodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~SelectorNodeExecutor() = default;
    /// <summary>
    /// ãƒãƒ¼ãƒ‰ã®å®Ÿè¡Œå‡¦ç†
    /// </summary>
    /// <param name="actor">å®Ÿè¡Œã‚¢ã‚¯ã‚¿ãƒ¼</param>
    /// <returns>Succeeded:å®Ÿè¡Œã®æˆåŠŸ</returns>
    /// <returns>Failed:å®Ÿè¡Œã®å¤±æ•—</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
<<<<<<< HEAD
        if (super::_current) {
            auto re = super::_current->Execute(actor);
            if (re != super::Result::None) {
                super::_current = nullptr;
            } // if
            return super::Result::None;
        } // if

        // ÀsÏ‚İ
=======
        // å®Ÿè¡Œæ¸ˆã¿
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else if
        // å®Ÿè¡Œé–‹å§‹
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
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
