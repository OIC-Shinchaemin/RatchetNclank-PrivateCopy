<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"../Executor/ActionNodeExecutor.h"

namespace Behaviour {

	/**
	 * @brief		ˆ—Àsƒm[ƒh
	 *				Œp³‚µ‚Äˆ—‚ğì¬‚·‚é
	 */
template < typename T >
class ActionNodeBase : public Node< T > {
protected:
public:
	ActionNodeBase()
		: Node< T >("Action") {
	}
	virtual ~ActionNodeBase() = default;

	virtual NodeExecutorPtr< T > CreateExecutor() const {
		NodePtr< T > ptr = std::const_pointer_cast<Node< T >>(shared_from_this());
		return std::make_shared<ActionNodeExecutor< T >>(ptr);
	}
};

/**
 * @brief		ƒAƒNƒ^[‚ÌŠÖ”Às—pƒm[ƒh
 */
template < typename T >
class FunctionNode : public ActionNodeBase< T > {
protected:
	/** Àsˆ— */
	using OnExecFunction = std::function< bool(T&) >;
	/** Àsˆ— */
	OnExecFunction			OnExec;
public:
	FunctionNode(OnExecFunction exec)
		: ActionNodeBase< T >()
		, OnExec(exec) {
	}
	virtual ~FunctionNode() = default;

	/**
	 * @brief		ƒm[ƒh‚ÌÀsˆ—
	 * @param[in]	actor		ÀsƒAƒNƒ^[
	 * @return		true		Às‚Ì¬Œ÷
	 *				false		Às‚Ì¸”s
	 */
	virtual bool Exec(T& actor) {
		return OnExec(actor);
	}
};
}
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_ACTION_NODE_H
#define BEHAVIOUR_ACTION_NODE_H


#include "Node.h"

#include "../Executor/ActionNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ActionNodeBase : public behaviour::Node<Actor> {
    using super = behaviour::Node<Actor>;
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    ActionNodeBase() :
        super("Action") {
    }
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~ActionNodeBase() = default;
    /// <summary>
    /// ä½œæˆ
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual behaviour::NodeExecutorPtr<Actor> CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<super>(super::shared_from_this());
        return std::make_shared<ActionNodeExecutor<Actor>>(ptr);
    }
};
template<typename Actor>
class FunctionNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
protected:
    //! å®Ÿè¡Œå‡¦ç†
    using OnExecFunction = std::function< bool(Actor&) >;
    //! å®Ÿè¡Œå‡¦ç†
    OnExecFunction OnExec;
public:
    /// <summary>
    /// ã‚³ãƒ³ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    /// <param name="exec"></param>
    FunctionNode(OnExecFunction exec) :
        super(), 
        OnExec(exec) {
    }
    /// <summary>
    /// ãƒ‡ã‚¹ãƒˆãƒ©ã‚¯ã‚¿
    /// </summary>
    virtual ~FunctionNode() = default;
    /// <summary>
    /// ãƒãƒ¼ãƒ‰ã®å®Ÿè¡Œ
    /// </summary>
    /// <param name="actor">å®Ÿè¡Œã‚¢ã‚¯ã‚¿ãƒ¼</param>
    /// <returns>true:å®Ÿè¡Œã®æˆåŠŸ</returns>
    /// <returns>false:å®Ÿè¡Œã®å¤±æ•—</returns>
    virtual bool Execute(Actor& actor) override{
        return OnExec(actor);
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_BASE_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
