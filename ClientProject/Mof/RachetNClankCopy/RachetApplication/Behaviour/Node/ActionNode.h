<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"../Executor/ActionNodeExecutor.h"

namespace Behaviour {

	/**
	 * @brief		ภsm[h
	 *				pณตฤ๐์ฌท้
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
 * @brief		AN^[ฬึภspm[h
 */
template < typename T >
class FunctionNode : public ActionNodeBase< T > {
protected:
	/** ภs */
	using OnExecFunction = std::function< bool(T&) >;
	/** ภs */
	OnExecFunction			OnExec;
public:
	FunctionNode(OnExecFunction exec)
		: ActionNodeBase< T >()
		, OnExec(exec) {
	}
	virtual ~FunctionNode() = default;

	/**
	 * @brief		m[hฬภs
	 * @param[in]	actor		ภsAN^[
	 * @return		true		ภsฬฌ๗
	 *				false		ภsฬธs
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
    /// ใณใณในใใฉใฏใฟ
    /// </summary>
    ActionNodeBase() :
        super("Action") {
    }
    /// <summary>
    /// ใในใใฉใฏใฟ
    /// </summary>
    virtual ~ActionNodeBase() = default;
    /// <summary>
    /// ไฝๆ
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
    //! ๅฎ่กๅฆ็
    using OnExecFunction = std::function< bool(Actor&) >;
    //! ๅฎ่กๅฆ็
    OnExecFunction OnExec;
public:
    /// <summary>
    /// ใณใณในใใฉใฏใฟ
    /// </summary>
    /// <param name="exec"></param>
    FunctionNode(OnExecFunction exec) :
        super(), 
        OnExec(exec) {
    }
    /// <summary>
    /// ใในใใฉใฏใฟ
    /// </summary>
    virtual ~FunctionNode() = default;
    /// <summary>
    /// ใใผใใฎๅฎ่ก
    /// </summary>
    /// <param name="actor">ๅฎ่กใขใฏใฟใผ</param>
    /// <returns>true:ๅฎ่กใฎๆๅ</returns>
    /// <returns>false:ๅฎ่กใฎๅคฑๆ</returns>
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
