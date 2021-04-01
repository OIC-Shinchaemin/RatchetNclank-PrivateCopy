#ifndef BEHAVIOUR_DECORATOR_NODE_H
#define BEHAVIOUR_DECORATOR_NODE_H


#include "SimplexNode.h"

#include "../Executor/DecoratorNodeExecutor.h"


namespace behaviour {
template<typename Actor>
class DecoratorNodeBase : public behaviour::SimplexNode<Actor> {
    using super = behaviour::SimplexNode<Actor>;
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
    virtual NodeExecutorPtr<Actor> CreateExecutor(void) const override {
        auto ptr = std::const_pointer_cast<behaviour::Node<Actor>>(super::shared_from_this());
        auto temp = std::dynamic_pointer_cast<behaviour::DecoratorNodeBase<Actor>>(ptr);
        return std::make_shared<DecoratorNodeExecutor<Actor>>(temp);
    }
};
template <typename Actor, typename Value>
class DecoratorNode : public behaviour::DecoratorNodeBase<Actor> {
    using super = behaviour::DecoratorNodeBase<Actor>;
protected:
    //! 判定子
    behaviour::ConditionalNodeBase<Actor>::Operator _operator;
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
    DecoratorNode(behaviour::ConditionalNodeBase<Actor>::Operator op, ParameterNodePtr<Actor, Value> p1, ParameterNodePtr<Actor, Value> p2) :
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
    virtual bool Execute(Actor& actor) override {
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