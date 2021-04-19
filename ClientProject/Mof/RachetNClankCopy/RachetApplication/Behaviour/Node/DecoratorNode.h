#ifndef BEHAVIOUR_DECORATOR_NODE_H
#define BEHAVIOUR_DECORATOR_NODE_H


#include "SimplexNode.h"
#include "ParameterNode.h"

#include "../Executor/DecoratorNodeExecutor.h"


namespace behaviour {
class DecoratorNodeBase : public behaviour::SimplexNode {
    using super = behaviour::SimplexNode;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DecoratorNodeBase() :
        super("Decorator") {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~DecoratorNodeBase() = default;
    /// <summary>
    /// �쐬
    /// </summary>
    /// <param name=""></param>
    /// <returns></returns>
    virtual NodeExecutorPtr CreateExecutor(void) const override {
        auto ptr = std::const_pointer_cast<behaviour::Node>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<behaviour::DecoratorNodeBase>(ptr);
        return std::make_shared<behaviour::DecoratorNodeExecutor>(temp);
    }
};
template <typename Actor, typename Value>
class DecoratorNode : public behaviour::DecoratorNodeBase {
    using super = behaviour::DecoratorNodeBase;
protected:
    //! ����q
    behaviour::ConditionalNodeBase::Operator _operator;
    //! ��r�p�p�����[�^�[
    ParameterNodePtr<Actor, Value> _param1;
    //! ��r�p�p�����[�^�[
    ParameterNodePtr<Actor, Value> _param2;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="op"></param>
    /// <param name="p1"></param>
    /// <param name="p2"></param>
    DecoratorNode(behaviour::ConditionalNodeBase::Operator op, ParameterNodePtr<Actor, Value> p1, ParameterNodePtr<Actor, Value> p2) :
        super(),
        _operator(op),
        _param1(p1),
        _param2(p2) {
    }
    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~DecoratorNode() = default;
    /// <summary>
    /// �m�[�h�̎��s����
    /// </summary>
    /// <param name="actor">���s�A�N�^�[</param>
    /// <returns>Succeeded:���s�̐���</returns>
    /// <returns>Failed:���s�̎��s</returns>
    virtual bool Execute(std::any ptr) override {
        auto actor = std::any_cast<Actor>(ptr);

        switch (_operator) {
            case super::Operator::Equal: // ==
                return _param1->GetValue(actor) == _param2->GetValue(actor);
            case super::Operator::NotEqual: // !=
                return _param1->GetValue(actor) != _param2->GetValue(actor);
            case super::Operator::Less: // <
                return _param1->GetValue(actor) < _param2->GetValue(actor);
            case super::Operator::LessEqual: // <=
                return _param1->GetValue(actor) <= _param2->GetValue(actor);
            case super::Operator::Greater: // >
                return _param1->GetValue(actor) > _param2->GetValue(actor);
            case super::Operator::GreaterEqual: // >=
                return _param1->GetValue(actor) >= _param2->GetValue(actor);
        } // switch
        return false;
    }
};
}
#endif // !BEHAVIOUR_DECORATOR_NODE_H