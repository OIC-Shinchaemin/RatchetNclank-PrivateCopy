#ifndef BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H
#define BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H


#include "NodeExecutor.h"

#include "../Node/CompositeNode.h"


namespace behaviour {
template<typename Actor>
class CompositeNodeExecutor : public NodeExecutor<Actor> {
    using super = NodeExecutor<Actor>;
protected:
    //! ���s��
    NodeExecutorPtr<Actor> _current;
public:
    /// <summary>
    /// �R���X�g���N�^
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
    /// �f�X�g���N�^
    /// </summary>
    virtual ~CompositeNodeExecutor() = default;
    /// <summary>
    /// ���s���K�v�ȃ|�C���^���L���b�V��
    /// </summary>
    /// <param actor=""></param>
    virtual void Prepare(std::any actor) override {
        for (auto& ptr : super::_children) {
            ptr->Prepare(actor);
        } // for
    }
    /// <summary>
    /// ���s��Ԃ�S�ă��Z�b�g
    /// ��Ԃ�Inactive�ɐݒ�
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override{
        super::Reset();
        _current.reset();
        for (auto& ptr : super::_children) {
            ptr->Reset();
        } // for
    }
};
}
#endif // !BEHAVIOUR_COMPOSITE_NODE_EXECUTOR_H