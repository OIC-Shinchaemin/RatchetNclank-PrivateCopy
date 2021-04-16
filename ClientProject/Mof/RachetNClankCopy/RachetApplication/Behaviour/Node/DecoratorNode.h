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
    /// コンストラクタ
    /// </summary>
    DecoratorNodeBase() :
        super("Decorator") {
    }
    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~DecoratorNodeBase() = default;
    /// <summary>
    /// 作成
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
    //! 判定子
    behaviour::ConditionalNodeBase::Operator _operator;
    //! 比較用パラメーター
    ParameterNodePtr<Actor, Value> _param1;
    //! 比較用パラメーター
    ParameterNodePtr<Actor, Value> _param2;
public:
    /// <summary>
    /// コンストラクタ
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
    /// デストラクタ
    /// </summary>
    virtual ~DecoratorNode() = default;
    /// <summary>
    /// ノードの実行処理
    /// </summary>
    /// <param name="actor">実行アクター</param>
    /// <returns>Succeeded:実行の成功</returns>
    /// <returns>Failed:実行の失敗</returns>
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