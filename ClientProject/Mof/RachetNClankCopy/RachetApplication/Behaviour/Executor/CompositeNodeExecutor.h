#pragma once

#include		"NodeExecutor.h"
#include		"../Node/CompositeNode.h"

namespace Behaviour {

	/**
	 * @brief		�����̎q�������m�[�h�̎��s�p�N���X
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
	 * @brief		�m�[�h�̎��s��Ԃ�S�ă��Z�b�g����
	 *				��Ԃ�Inactive�ɐݒ肷��
	 */
	virtual void Reset() {
		NodeExecutor::Reset();
		for (auto& ptr : _children) {
			ptr->Reset();
		}
	}
};

}