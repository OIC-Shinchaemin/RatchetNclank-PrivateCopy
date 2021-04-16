#ifndef BEHAVIOUR_SELECTOR_NODE_H
#define BEHAVIOUR_SELECTOR_NODE_H


#include "CompositeNode.h"

#include "../Executor/SelectorNodeExecutor.h"


namespace behaviour {
class SelectorNode : public behaviour::CompositeNode {
	using super = behaviour::CompositeNode;
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
	virtual behaviour::NodeExecutorPtr CreateExecutor(void) const {
		auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
		auto temp = std::dynamic_pointer_cast<super>(ptr);
		return std::make_shared<behaviour::SelectorNodeExecutor>(temp);
	}
};
}
#endif // !BEHAVIOUR_SELECTOR_NODE_H