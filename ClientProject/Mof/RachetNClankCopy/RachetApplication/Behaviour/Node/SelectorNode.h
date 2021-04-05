<<<<<<< HEAD
#pragma once

#include		"CompositeNode.h"
#include		"../Executor/SelectorNodeExecutor.h"

namespace Behaviour {

	/**
	 * @brief		�Z���N�^�[���s�p�m�[�h
	 *				���ԂɃm�[�h�����s���ǂꂩ��ł�Sucess���Ԃ��Ă������_�ŏI������
	 */
template < typename T >
class SelectorNode : public CompositeNode< T > {
protected:
public:
	SelectorNode()
		: CompositeNode< T >("Selector") {
	}
	virtual ~SelectorNode() = default;

	virtual NodeExecutorPtr<T> CreateExecutor() const {
		NodePtr< T > ptr = std::const_pointer_cast<Node< T >>(shared_from_this());
		auto temp = std::dynamic_pointer_cast<CompositeNode< T >>(ptr);
		return std::make_shared<SelectorNodeExecutor< T >>(temp);
	}
};
}
=======
#ifndef BEHAVIOUR_SELECTOR_NODE_H
#define BEHAVIOUR_SELECTOR_NODE_H


#include "CompositeNode.h"

#include "../Executor/SelectorNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class SelectorNode : public behaviour::CompositeNode<Actor> {
	using super = behaviour::CompositeNode<Actor>;
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	SelectorNode() : 
		super("Selector") {
	}
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	virtual ~SelectorNode() = default;
	/// <summary>
	/// �쐬
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual NodeExecutorPtr<Actor> CreateExecutor(void) const {
		auto ptr = std::const_pointer_cast<behaviour::Node<Actor>>(super::shared_from_this());
		auto temp = std::dynamic_pointer_cast<super>(ptr);
		return std::make_shared<behaviour::SelectorNodeExecutor<Actor>>(temp);
	}
};
}
#endif // !BEHAVIOUR_SELECTOR_NODE_H
>>>>>>> origin/Ex55_WeaponAction
