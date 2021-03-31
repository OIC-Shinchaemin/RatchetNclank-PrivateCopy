#ifndef BEHAVIOUR_NODE_EXECUTOR_H
#define BEHAVIOUR_NODE_EXECUTOR_H


#include "INodeExecutor.h"

#include "../Node/Node.h"


namespace behaviour {
template<typename Actor>
class NodeExecutor : public INodeExecutor<Actor> {
    using super = INodeExecutor<Actor>;
protected:
    //! ���
    super::State _state;
    //! �Ή��m�[�h
    NodePtr<Actor> _node;
    //! �e�m�[�h
    NodeExecutorWeakPtr<Actor> _parent;
    //! �q�m�[�h
    NodeExecutorList<Actor> _children;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="node"></param>
    NodeExecutor(const NodePtr<Actor>& node) :
        super(),
        _state(super::State::Inactive),
        _node(node),
        _parent(),
        _children() {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~NodeExecutor() = default;
    /// <summary>
    /// �Z�b�^�[
    /// </summary>
    /// <param name="ptr"></param>
    void SetParent(NodeExecutorWeakPtr<Actor> ptr) override {
        _parent = ptr;
    }
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual behaviour::INodeExecutor<Actor>::Result Execute(Actor& actor) override { return behaviour::INodeExecutor<Actor>::Result::Failure; }
    /// <summary>
    /// ���s��Ԃ�S�ă��Z�b�g
    /// ��Ԃ�Inactive�ɐݒ�
    /// </summary>
    /// <param name=""></param>
    virtual void Reset(void) override {
        _state = super::State::Inactive;
    }
};
}
#endif // !BEHAVIOUR_NODE_EXECUTOR_H