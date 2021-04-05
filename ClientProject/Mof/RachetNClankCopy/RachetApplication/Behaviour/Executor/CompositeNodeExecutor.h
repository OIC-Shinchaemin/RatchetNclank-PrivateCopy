<<<<<<< HEAD
#pragma once

#include		"NodeExecutor.h"
#include		"../Node/CompositeNode.h"

namespace Behaviour {

	/**
	 * @brief		複数の子供を持つノードの実行用クラス
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
	 * @brief		ノードの実行状態を全てリセットして
	 *				状態をInactiveに設定する
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
#ifndef BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
#define BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/CompositeNode.h"


namespace behaviour {
template<typename Actor>
class CompositeNodeExecutor : public NodeExecutor<Actor> {
    using super = NodeExecutor<Actor>;
protected:
    //! 実行中
    NodeExecutorPtr<Actor> _current;
public:
    /// <summary>
    /// コンストラクタ
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
    /// デストラクタ
    /// </summary>
    virtual ~CompositeNodeExecutor() = default;
    /// <summary>
    /// 実行状態を全てリセット
    /// 状態をInactiveに設定
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
>>>>>>> origin/Ex55_WeaponAction
