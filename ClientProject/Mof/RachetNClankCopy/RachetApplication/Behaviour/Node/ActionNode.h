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