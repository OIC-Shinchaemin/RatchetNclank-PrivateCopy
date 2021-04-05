<<<<<<< HEAD
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
=======
#ifndef BEHAVIOUR_COMPOSITENODE_H
#define BEHAVIOUR_COMPOSITENODE_H


#include "Node.h"


namespace behaviour {
template<typename Actor>
class CompositeNode : public behaviour::Node<Actor> {
    using super = behaviour::Node<Actor>;
protected:
    //! �q�m�[�h
    NodeList<Actor> _children;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="name"></param>
    CompositeNode(const std::string& name) :
        super(name),
        _children() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CompositeNode() = default;
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const NodeList<Actor>& GetChildren(void) const { return _children; }
    /// <summary>
    /// �Q�b�^�[
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    NodeList<Actor>& GetChildren(void) { return _children; }
    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="node"></param>
    void AddChild(const NodePtr<Actor>& node) { _children.push_back(node); }
};
template<typename Actor> using CompositeNodePtr = std::shared_ptr<CompositeNode<Actor>>;
}
#endif // !BEHAVIOUR_COMPOSITENODE_H
>>>>>>> origin/Ex55_WeaponAction
