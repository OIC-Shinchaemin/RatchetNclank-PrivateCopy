#ifndef RATCHET_BEHAVIOUR_SIMPLEX_NODE_EXECUTOR_H
#define RATCHET_BEHAVIOUR_SIMPLEX_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/SimplexNode.h"


namespace ratchet { namespace behaviour {
class SimplexNodeExecutor : public ratchet::behaviour::NodeExecutor {
    using super = ratchet::behaviour::NodeExecutor;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    SimplexNodeExecutor(const ratchet::behaviour::SimplexNodePtr& node) :
        super(node) {
        auto& ptr = node->GetChild();
        auto add = ptr->CreateExecutor();
        add->SetParent(super::weak_from_this());
        super::_children.push_back(add);
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~SimplexNodeExecutor() = default;
    /// <summary>
    /// ���s��Ԃ�S�ă��Z�b�g
    /// ��Ԃ�Inactive�ɐݒ�
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        super::Reset();
        for (auto& ptr : super::_children) {
            ptr->Reset();
        } // for
    }
};
}
}
#endif // !RATCHET_BEHAVIOUR_SIMPLEX_NODE_EXECUTOR_H