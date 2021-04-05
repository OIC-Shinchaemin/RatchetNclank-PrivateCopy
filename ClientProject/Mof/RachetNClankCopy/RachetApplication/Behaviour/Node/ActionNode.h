<<<<<<< HEAD
#pragma once

#include		"../Executor/ActionNodeExecutor.h"

namespace Behaviour {

	/**
	 * @brief		�������s�m�[�h
	 *				�p�����ď������쐬����
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
 * @brief		�A�N�^�[�̊֐����s�p�m�[�h
 */
template < typename T >
class FunctionNode : public ActionNodeBase< T > {
protected:
	/** ���s���� */
	using OnExecFunction = std::function< bool(T&) >;
	/** ���s���� */
	OnExecFunction			OnExec;
public:
	FunctionNode(OnExecFunction exec)
		: ActionNodeBase< T >()
		, OnExec(exec) {
	}
	virtual ~FunctionNode() = default;

	/**
	 * @brief		�m�[�h�̎��s����
	 * @param[in]	actor		���s�A�N�^�[
	 * @return		true		���s�̐���
	 *				false		���s�̎��s
	 */
	virtual bool Exec(T& actor) {
		return OnExec(actor);
	}
};
}
=======
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
    /// �R���X�g���N�^
    /// </summary>
    ActionNodeBase() :
        super("Action") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionNodeBase() = default;
    /// <summary>
    /// �쐬
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
    //! ���s����
    using OnExecFunction = std::function< bool(Actor&) >;
    //! ���s����
    OnExecFunction OnExec;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="exec"></param>
    FunctionNode(OnExecFunction exec) :
        super(), 
        OnExec(exec) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~FunctionNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(Actor& actor) override{
        return OnExec(actor);
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_BASE_H
>>>>>>> origin/Ex55_WeaponAction
