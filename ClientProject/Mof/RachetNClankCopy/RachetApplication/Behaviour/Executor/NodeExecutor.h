<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"INodeExecutor.h"
#include		"../Node/Node.h"

namespace Behaviour {
	/** ƒm[ƒhÀs—pƒNƒ‰ƒX */
template < typename T >
class NodeExecutor : public INodeExecutor< T > {
protected:
	/** ó‘Ô */
	State						_state;
	/** ‘Î‰ƒm[ƒh */
	NodePtr< T >				_node;
	/** eƒm[ƒh */
	NodeExecutorWeakPtr< T >	_parent;
	/** qƒm[ƒh */
	NodeExecutorList< T >		_children;
public:
	NodeExecutor(const NodePtr< T >& node)
		: _state(State::Inactive)
		, _node(node)
		, _parent()
		, _children() {
	}
	virtual ~NodeExecutor() = default;

	/**
	 * @brief		ƒm[ƒh‚ÌÀsˆ—
	 * @param[in]	actor		ÀsƒAƒNƒ^[
	 * @return		Succeeded	Às‚Ì¬Œ÷
	 *				Failed		Às‚Ì¸”s
	 */
	virtual Result Exec(T& actor) { return Result::Failure; }

	/**
	 * @brief		ƒm[ƒh‚ÌÀsó‘Ô‚ğ‘S‚ÄƒŠƒZƒbƒg‚µ‚Ä
	 *				ó‘Ô‚ğInactive‚Éİ’è‚·‚é
	 */
	virtual void Reset() {
		_state = State::Inactive;
	}

	/**
	 * @brief		e‚Ìİ’è
	 * @param[in]	ptr			eƒAƒNƒ^[
	 */
	void SetParent(NodeExecutorWeakPtr< T >& ptr) override {
		_parent = ptr;
	}
};
}
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_NODE_EXECUTOR_H
#define BEHAVIOUR_NODE_EXECUTOR_H


#include "INodeExecutor.h"

#include "../Node/Node.h"

#include <Mof.h>


namespace behaviour {
template<typename Actor>
class NodeExecutor : public INodeExecutor<Actor> {
    using super = INodeExecutor<Actor>;
protected:
    //! çŠ¶æ…‹
    super::State _state;
    //! å¯¾å¿œãƒãƒ¼ãƒ‰
    NodePtr<Actor> _node;
    //! è¦ª
    NodeExecutorWeakPtr<Actor> _parent;
    //! å­ä¾›
    NodeExecutorList<Actor> _children;
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    /// <param name="node"></param>
    NodeExecutor(const NodePtr<Actor>& node) :
        super(),
        _state(super::State::Inactive),
        _node(node),
        _parent(),
        _children() {
    }
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~NodeExecutor() = default;
    /// <summary>
    /// ã‚»ãƒƒã‚¿ãƒ¼
    /// </summary>
    /// <param name="ptr"></param>
    void SetParent(NodeExecutorWeakPtr<Actor> ptr) override {
        _parent = ptr;
    }
    /// <summary>
    /// ãƒãƒ¼ãƒ‰ã®å®Ÿè¡Œå‡¦ç†
    /// </summary>
    /// <param name="actor">å®Ÿè¡Œã‚¢ã‚¯ã‚¿ãƒ¼</param>
    /// <returns>Succeeded:å®Ÿè¡Œã®æˆåŠŸ</returns>
    /// <returns>Failed:å®Ÿè¡Œã®å¤±æ•—</returns>
    virtual behaviour::INodeExecutor<Actor>::Result Execute(Actor& actor) override { return behaviour::INodeExecutor<Actor>::Result::Failure; }
    /// <summary>
    /// å®Ÿè¡ŒçŠ¶æ…‹ã‚’å…¨ã¦ãƒªã‚»ãƒƒãƒˆ
    /// çŠ¶æ…‹ã‚’Inactiveã«è¨­å®š
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        _state = super::State::Inactive;
    }
    /// <summary>
    /// ƒfƒoƒbƒO
    /// </summary>
    /// <typeparam name="Actor"></typeparam>
    virtual void DebugRender(Mof::CVector2 position) override {
        MofU32 color;
        if (_state == super::State::Inactive) {
            color = MOF_COLOR_WHITE;
        } // else if
        if (_state == super::State::Running) {
            color = MOF_COLOR_RED;
        } // if
        if (_state == super::State::Completed) {
            color = MOF_COLOR_GREEN;
        } // else if
        if (_state == super::State::Incompleted) {
            color = MOF_COLOR_BLUE;
        } // else if


        ::CGraphicsUtilities::RenderString(position.x, position.y, color, _node->GetName().c_str());
        auto pos = position;
        pos.x += 100.0f;
        for (auto ptr : _children) {
            ptr->DebugRender(pos);
            pos.y += 20.0f;
        } // for
    }
    virtual void DebugRender(void) override {
        this->DebugRender(Mof::CVector2(100.0f, 100.0f));
    }
};
}
#endif // !BEHAVIOUR_NODE_EXECUTOR_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
