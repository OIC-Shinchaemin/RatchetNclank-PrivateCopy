<<<<<<< HEAD
#pragma once

#include "NodeExecutor.h"

namespace Behaviour {

    /** ƒm[ƒhÀs—pƒNƒ‰ƒX */
template < typename T >
class ActionNodeExecutor : public NodeExecutor< T > {
public:
    ActionNodeExecutor(const NodePtr< T >& node)
        : NodeExecutor< T >(node) {
    }
    virtual ~ActionNodeExecutor() = default;

    /**
     * @brief		ƒm[ƒh‚ÌÀsˆ—
     * @param[in]	actor		ÀsƒAƒNƒ^[
     * @return		Succeeded	Às‚Ì¬Œ÷
     *				Failed		Às‚Ì¸”s
     */
    virtual Result Exec(T& actor) {
        //ÀsÏ‚İ
        if (_state == State::Completed) {
            return Result::Sucess;
        }
        else if (_state == State::Incompleted) {
            return Result::Failure;
        }
        //ÀsŠJn
        _state = State::Running;
        if (_node->Exec(actor)) {
            _state = State::Completed;
            return Result::Sucess;
        }
        return Result::None;
    }
};
}
=======
#ifndef BEHAVIOUR_ACTION_NODE_EXECUTOR_H
#define BEHAVIOUR_ACTION_NODE_EXECUTOR_H


#include "NodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ActionNodeExecutor : public behaviour::NodeExecutor<Actor> {
    using super = behaviour::NodeExecutor<Actor>;
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    /// <param name="node"></param>
    ActionNodeExecutor(const NodePtr<Actor>& node) :
        super(node) {
    }
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~ActionNodeExecutor() = default;
    /// <summary>
    /// ãƒãƒ¼ãƒ‰ã®å®Ÿè¡Œ
    /// </summary>
    /// <param name="actor">å®Ÿè¡Œã‚¢ã‚¯ã‚¿ãƒ¼</param>
    /// <returns>true:å®Ÿè¡Œã®æˆåŠŸ</returns>
    /// <returns>false:å®Ÿè¡Œã®å¤±æ•—</returns>
    virtual INodeExecutor<Actor>::Result Execute(Actor& actor) override {
        //å®Ÿè¡Œæ¸ˆã¿
        if (super::_state == super::State::Completed) {
            return super::Result::Sucess;
        } // if
        else if (super::_state == super::State::Incompleted) {
            return super::Result::Failure;
        } // else if
        //å®Ÿè¡Œé–‹å§‹
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
>>>>>>> origin/Ex55_WeaponAction
