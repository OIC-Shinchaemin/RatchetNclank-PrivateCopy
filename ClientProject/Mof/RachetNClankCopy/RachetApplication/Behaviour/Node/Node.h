#pragma once

#include		"../Executor/INodeExecutor.h"

namespace Behaviour {

	//�m�[�h�|�C���^�u�������̂��߂̑O����`
template < typename T > class Node;
template < typename T > using NodePtr = std::shared_ptr<Node< T >>;
template < typename T > using NodeList = std::list<NodePtr< T >>;

template < typename T >
class Node : public std::enable_shared_from_this<Node<T>> {
protected:
	/** �m�[�h�� */
	std::string _name;
public:
	Node(const std::string& name)
		: _name(name) {
	}
	virtual ~Node() = default;

	/**
	 * @brief		�m�[�h�̎��s����
	 * @param[in]	actor		���s�A�N�^�[
	 * @return		true		���s�̐���
	 *				false		���s�̎��s
	 */
	virtual bool Exec(T& actor) { return false; }

	virtual NodeExecutorPtr< T > CreateExecutor() const = 0;
	const std::string& GetName() const noexcept { return _name; }
};
}