#ifndef BEHAVIOUR_ACTION_NODE_H
#define BEHAVIOUR_ACTION_NODE_H


#include "Node.h"

#include "../Executor/ActionNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class ActionNodeBase : public behaviour::Node<Actor> {
    using super = behaviour::Node<Actor>;
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
    virtual behaviour::NodeExecutorPtr<Actor> CreateExecutor(void) const {
        auto ptr = std::const_pointer_cast<super>(super::shared_from_this());
        return std::make_shared<ActionNodeExecutor<Actor>>(ptr);
    }
};
template<typename Actor>
class FunctionNode : public behaviour::ActionNodeBase<Actor> {
    using super = behaviour::ActionNodeBase<Actor>;
protected:
    //! ���s����
    using OnExecFunction = std::function< bool(Actor&) >;
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
    virtual bool Execute(std::any ptr) override{
        auto actor = std::any_cast<Actor>(ptr);
        return OnExec(actor);
    }
};
}
#endif // !BEHAVIOUR_ACTION_NODE_BASE_H