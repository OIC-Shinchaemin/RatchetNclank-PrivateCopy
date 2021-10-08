#ifndef RATCHET_BEHAVIOUR_ACTION_NODE_H
#define RATCHET_BEHAVIOUR_ACTION_NODE_H


#include "Node.h"

#include "../Executor/ActionNodeExecutor.h"


namespace ratchet::behaviour {
class ActionNodeBase : public ratchet::behaviour::Node {
    using super = ratchet::behaviour::Node;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ActionNodeBase(const std::string& name) :
        super(name) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~ActionNodeBase() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual ratchet::behaviour::NodeExecutorPtr CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<super>(super::shared_from_this());
        return std::make_shared<ActionNodeExecutor>(ptr);
    }
};
template<typename Actor>
class FunctionNode : public ratchet::behaviour::ActionNodeBase {
    using super = ratchet::behaviour::ActionNodeBase;
protected:
    //! ���s����
    using OnExecFunction = std::function<bool(Actor&)>;
    //! ���s����
    OnExecFunction OnExec;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="exec"></param>
    FunctionNode(OnExecFunction exec) :
        super("FunctionNode"),
        OnExec(exec) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~FunctionNode() = default;
    /// <summary>
    /// �m�[�h�̎��s
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>true:���s�̐���</returns>
    /// <returns>false:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<Actor>(ptr);
        return OnExec(actor);
    }
};
}
#endif // !RATCHET_BEHAVIOUR_ACTION_NODE_BASE_H