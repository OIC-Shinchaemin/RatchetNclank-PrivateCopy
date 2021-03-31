#pragma once

#include		"../Executor/NodeExecutor.h"

namespace Behaviour {
	/**
	 * @brief		�����̎q�������m�[�h
	 */
template < typename T >
class CompositeNode : public Node< T > {
protected:
	/** �q�m�[�h */
	NodeList< T >			_children;
public:
	CompositeNode(const std::string& name)
		: Node< T >(name)
		, _children() {
	}
	virtual ~CompositeNode() = default;

	void AddChild(const NodePtr< T >& node) { _children.push_back(node); }
	NodeList< T >& GetChildren() { return _children; }
	const NodeList< T >& GetChildren() const { return _children; }
};
template < typename T > using CompositeNodePtr = std::shared_ptr<CompositeNode< T >>;
}