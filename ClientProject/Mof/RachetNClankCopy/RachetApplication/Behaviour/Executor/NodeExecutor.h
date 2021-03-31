#pragma once

#include		"INodeExecutor.h"
#include		"../Node/Node.h"

namespace Behaviour {
	/** �m�[�h���s�p�N���X */
template < typename T >
class NodeExecutor : public INodeExecutor< T > {
protected:
	/** ��� */
	State						_state;
	/** �Ή��m�[�h */
	NodePtr< T >				_node;
	/** �e�m�[�h */
	NodeExecutorWeakPtr< T >	_parent;
	/** �q�m�[�h */
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
	 * @brief		�m�[�h�̎��s����
	 * @param[in]	actor		���s�A�N�^�[
	 * @return		Succeeded	���s�̐���
	 *				Failed		���s�̎��s
	 */
	virtual Result Exec(T& actor) { return Result::Failure; }

	/**
	 * @brief		�m�[�h�̎��s��Ԃ�S�ă��Z�b�g����
	 *				��Ԃ�Inactive�ɐݒ肷��
	 */
	virtual void Reset() {
		_state = State::Inactive;
	}

	/**
	 * @brief		�e�̐ݒ�
	 * @param[in]	ptr			�e�A�N�^�[
	 */
	void SetParent(NodeExecutorWeakPtr< T >& ptr) override {
		_parent = ptr;
	}
};
}