<<<<<<< HEAD
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
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_COMPOSITENODE_H
#define BEHAVIOUR_COMPOSITENODE_H


#include "Node.h"


namespace behaviour {
template<typename Actor>
class CompositeNode : public behaviour::Node<Actor> {
    using super = behaviour::Node<Actor>;
protected:
    //! 子ノード
    NodeList<Actor> _children;
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    CompositeNode(const std::string& name) :
        super(name),
        _children() {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~CompositeNode() = default;
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    const NodeList<Actor>& GetChildren(void) const { return _children; }
    /// <summary>
    /// ゲッター
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    NodeList<Actor>& GetChildren(void) { return _children; }
    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="node"></param>
    void AddChild(const NodePtr<Actor>& node) { _children.push_back(node); }
};
template<typename Actor> using CompositeNodePtr = std::shared_ptr<CompositeNode<Actor>>;
}
#endif // !BEHAVIOUR_COMPOSITENODE_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
