<<<<<<< HEAD
<<<<<<< HEAD
#pragma once

#include		"NodeExecutor.h"
#include		"../Node/CompositeNode.h"

namespace Behaviour {

	/**
	 * @brief		¡ÌqðÂm[hÌÀspNX
	 */
template < typename T >
class CompositeNodeExecutor : public NodeExecutor< T > {
public:
	CompositeNodeExecutor(const CompositeNodePtr< T >& node)
		: NodeExecutor< T >(node) {
		for (auto& ptr : node->GetChildren()) {
			auto add = ptr->CreateExecutor();
			add->SetParent(weak_from_this());
			_children.push_back(add);
		}
	}
	virtual ~CompositeNodeExecutor() = default;

	/**
	 * @brief		m[hÌÀsóÔðSÄZbgµÄ
	 *				óÔðInactiveÉÝè·é
	 */
	virtual void Reset() {
		NodeExecutor::Reset();
		for (auto& ptr : _children) {
			ptr->Reset();
		}
	}
};

}
=======
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
#ifndef BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
#define BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/CompositeNode.h"


namespace behaviour {
template<typename Actor>
class CompositeNodeExecutor : public NodeExecutor<Actor> {
    using super = NodeExecutor<Actor>;
protected:
    //! Às
    NodeExecutorPtr<Actor> _current;
public:
    /// <summary>
    /// ã³ã³ã¹ãã©ã¯ã¿
    /// </summary>
    /// <param name="node"></param>
    CompositeNodeExecutor(const CompositeNodePtr<Actor>& node) :
        super(node) {
        for (auto& ptr : node->GetChildren()) {
            auto add = ptr->CreateExecutor();
            add->SetParent(super::weak_from_this());
            super::_children.push_back(add);
        }
    }
    /// <summary>
    /// ãã¹ãã©ã¯ã¿
    /// </summary>
    virtual ~CompositeNodeExecutor() = default;
    /// <summary>
    /// å®è¡ç¶æãå¨ã¦ãªã»ãã
    /// ç¶æãInactiveã«è¨­å®
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override{
        super::Reset();
        _current.reset();
        for (auto& ptr : super::_children) {
            ptr->Reset();
        }
    }
};
}
#endif // !BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
<<<<<<< HEAD
>>>>>>> origin/Ex55_WeaponAction
=======
>>>>>>> 0872728f9b1d5b6a69437db90362aaa9c002b485
